/*******************************************************************************
  Camera Frame Sink - DRM/KMS Overlay Plane

  Company:
    Microchip Technology Inc.

  File Name:
    cam_sink_drm.c

  Summary:
    Pushes captured frames straight to a DRM/KMS overlay plane.

  Description:
    This is the preferred sink on the target. The LCD controller's overlay plane
    is programmed with DRM_FORMAT_YUYV and the camera's YUYV frames are copied
    into the plane's framebuffer as-is, so the display hardware performs the
    YUV-to-RGB conversion and any scaling. No per-pixel CPU work happens on the
    frame path at all, which is the whole reason for preferring this route over
    drawing through Legato.

    Legato keeps rendering the cluster UI to its own plane; the two composite in
    hardware. The sink deliberately does not touch the plane Legato is using.

    Plane acquisition:

    1. Prefer an overlay plane that the DRM backend has not claimed and that
       advertises YUYV. Such a plane is created here and is ours alone.
    2. Otherwise, prefer an unclaimed overlay plane advertising RGB565 and
       convert in software.
    3. Otherwise, take over the highest-indexed overlay plane that Legato is not
       actively rendering to, reallocating its framebuffer to our format.

    Not every LCD controller exposes YUV on every layer -- on the Microchip LCDC
    it is typically the high-end overlay only -- hence the RGB565 fallback,
    which costs a software conversion but keeps the preview working.

  Remarks:
    Compiled to a stub returning CAM_ERR_UNSUPPORTED unless USE_DRM_KMS is
    defined, so host/SDL2 builds link without libdrm.
 *******************************************************************************/

#include <stdio.h>
#include <string.h>

#include "cam_sink.h"
#include "cam_convert.h"

#ifdef USE_DRM_KMS

#include <drm_fourcc.h>

#include "linux/display/drm/drm_backend.h"
#include "linux/display/drm/drm_device.h"
#include "linux/display/drm/plane.h"

/* Two buffers so a frame is never written into the framebuffer the controller
   is currently scanning out. */
#define CAM_DRM_BUFFER_COUNT 2

/*******************************************************************************
 * Backend State
 * File-scope because one camera preview per process is the documented limit.
 ******************************************************************************/
typedef struct
{
    struct plane_data* plane;
    bool               planeIsOurs;     // Created here, so free it on close
    uint32_t           format;          // DRM FourCC in use
    uint32_t           width;           // Plane framebuffer geometry
    uint32_t           height;
    uint32_t           backBuf;         // Buffer index to render into next
    bool               visible;         // Plane has been committed to the CRTC

    /* Kept so close() can hand the slot back. The graphics backend walks
       gd->planes[] every frame end, so leaving a freed pointer parked there
       would be a use-after-free. */
    struct GfxDevice*  gfxDevice;
    unsigned int       planeIndex;
    bool               registered;      // gd->planes[planeIndex] is our plane
} camDrmSink;

static camDrmSink drmSink;

/*******************************************************************************
 * camDrmOverlayOrdinal
 * kms_device_find_plane_by_type() indexes planes by their ordinal *within a
 * type*, not by their position in device->planes[]. Converts the latter to the
 * former so a plane found by scanning can be created by type and index.
 ******************************************************************************/
static bool camDrmOverlayOrdinal(const struct kms_device* device,
                                 unsigned int planeIndex,
                                 unsigned int* ordinal)
{
    unsigned int i;
    unsigned int count = 0;

    for (i = 0; i < device->num_planes; i++)
    {
        if (device->planes[i]->type == DRM_PLANE_TYPE_OVERLAY)
        {
            if (i == planeIndex)
            {
                *ordinal = count;
                return true;
            }

            count++;
        }
    }

    return false;
}

/*******************************************************************************
 * camDrmFindUnclaimedOverlay
 * Looks for an overlay plane the DRM backend has not built a plane_data for and
 * which advertises the requested format. Returns its index in device->planes[].
 ******************************************************************************/
static bool camDrmFindUnclaimedOverlay(struct GfxDevice* gd,
                                       uint32_t format,
                                       unsigned int* planeIndex)
{
    struct kms_device* device = gd->device;
    unsigned int i;

    /* Walk downwards: the highest planes are the least likely to be the base
       layer Legato composites the UI into. */
    for (i = device->num_planes; i > 0; i--)
    {
        unsigned int idx = i - 1u;

        if (device->planes[idx]->type != DRM_PLANE_TYPE_OVERLAY)
        {
            continue;
        }

        if (gd->planes[idx] != NULL)
        {
            continue;   /* Already owned by the graphics backend. */
        }

        if (!kms_plane_supports_format(device->planes[idx], format))
        {
            continue;
        }

        *planeIndex = idx;
        return true;
    }

    return false;
}

/*******************************************************************************
 * camDrmFindReclaimableOverlay
 * Last resort: an overlay plane already owned by the graphics backend that
 * Legato is not actively rendering into, whose framebuffer we can reallocate.
 ******************************************************************************/
static bool camDrmFindReclaimableOverlay(struct GfxDevice* gd,
                                         uint32_t format,
                                         unsigned int* planeIndex)
{
    struct kms_device* device = gd->device;
    unsigned int i;

    for (i = device->num_planes; i > 0; i--)
    {
        unsigned int idx = i - 1u;

        if (device->planes[idx]->type != DRM_PLANE_TYPE_OVERLAY)
        {
            continue;
        }

        if (gd->planes[idx] == NULL)
        {
            continue;
        }

        if (idx == gd->active_layer_id)
        {
            continue;   /* Legato is drawing here. Leave it alone. */
        }

        if (!kms_plane_supports_format(device->planes[idx], format))
        {
            continue;
        }

        *planeIndex = idx;
        return true;
    }

    return false;
}

/*******************************************************************************
 * camDrmConfigurePlane
 * Positions and scales the plane for the requested destination rectangle. This
 * only records the properties; plane_apply() commits them, and that is what
 * makes the plane visible, so the commit is deliberately left to the caller.
 ******************************************************************************/
static void camDrmConfigurePlane(struct plane_data* plane,
                                 const camSinkConfig* cfg)
{
    uint32_t destW = (cfg->destWidth  != 0) ? cfg->destWidth  : cfg->srcWidth;
    uint32_t destH = (cfg->destHeight != 0) ? cfg->destHeight : cfg->srcHeight;

    plane_set_pos(plane, cfg->destX, cfg->destY);

    /* The controller scales the plane, so a destination larger or smaller than
       the camera frame costs nothing on the CPU. */
    plane_set_scale_independent(plane,
                               (double)destW / (double)cfg->srcWidth,
                               (double)destH / (double)cfg->srcHeight);

    if (cfg->alpha <= 255u)
    {
        (void)plane_set_alpha(plane, cfg->alpha);
    }
}

/*******************************************************************************
 * camDrmBlankBuffers
 * Fills every framebuffer with opaque black in the plane's own format.
 *
 * A freshly allocated framebuffer is zero-filled, and all-zero YUYV is not
 * black: Y=0 with U=V=0 is chroma at full negative swing, which the controller
 * decodes to bright green. Black in YUYV is Y=0 with U=V=128, so the buffers
 * have to be written rather than just left as allocated.
 ******************************************************************************/
static void camDrmBlankBuffers(camDrmSink* state)
{
    struct plane_data* plane = state->plane;
    uint32_t fb;

    for (fb = 0; fb < plane->buffer_count; fb++)
    {
        uint8_t* base = (uint8_t*)plane->bufs[fb];
        uint32_t pitch;
        uint32_t row;

        if (base == NULL)
        {
            continue;
        }

        pitch = plane->fbs[fb]->pitch;

        if (state->format == DRM_FORMAT_RGB565)
        {
            memset(base, 0, (size_t)pitch * state->height);
            continue;
        }

        for (row = 0; row < state->height; row++)
        {
            uint32_t* out = (uint32_t*)(base + ((size_t)row * pitch));
            uint32_t words;
            uint32_t pattern;
            uint32_t i;

            if (state->format == DRM_FORMAT_YUYV)
            {
                /* Y0 U Y1 V = 00 80 00 80 covers two pixels per word. */
                words   = state->width / 2u;
                pattern = 0x80008000u;
            }
            else
            {
                words   = state->width;     /* ARGB8888, one pixel per word. */
                pattern = 0xFF000000u;
            }

            for (i = 0; i < words; i++)
            {
                out[i] = pattern;
            }
        }
    }
}

/*******************************************************************************
 * camDrmPresent
 * Copies one captured frame into the plane's back buffer and flips.
 ******************************************************************************/
static camResult camDrmPresent(camSink* sink, const camFrame* frame)
{
    camDrmSink* state;
    struct plane_data* plane;
    camConvertSource src;
    camConvertDest dst;
    uint32_t target;

    if ((sink == NULL) || (frame == NULL) || (sink->impl == NULL))
    {
        return CAM_ERR_PARAM;
    }

    state = (camDrmSink*)sink->impl;
    plane = state->plane;

    if (plane == NULL)
    {
        return CAM_ERR_STATE;
    }

    target = state->backBuf;

    if (plane->bufs[target] == NULL)
    {
        return CAM_ERR_STATE;
    }

    src.data   = frame->data;
    src.width  = frame->width;
    src.height = frame->height;
    src.stride = frame->stride;

    dst.data   = (uint8_t*)plane->bufs[target];
    dst.width  = state->width;
    dst.height = state->height;
    dst.stride = plane->fbs[target]->pitch;

    if (state->format == DRM_FORMAT_YUYV)
    {
        /* Native path: no colour conversion, the controller does it. */
        Cam_Convert_YUYVCopy(&src, &dst);
    }
    else if (state->format == DRM_FORMAT_RGB565)
    {
        Cam_Convert_YUYVToRGB565(&src, &dst);
    }
    else
    {
        Cam_Convert_YUYVToARGB8888(&src, &dst);
    }

    if (plane_flip(plane, target) < 0)
    {
        return CAM_ERR_IO;
    }

    if (!state->visible)
    {
        /* First frame. plane_flip() has just made the plane visible with real
           video in it; plane_apply() re-commits the same buffer to pick up the
           alpha and rotation properties that only it applies. */
        (void)plane_apply(plane);
        state->visible = true;
    }

    state->backBuf = (target + 1u) % plane->buffer_count;
    sink->framesPresented++;

    return CAM_OK;
}

/*******************************************************************************
 * camDrmClose
 ******************************************************************************/
static void camDrmClose(camSink* sink)
{
    camDrmSink* state = &drmSink;

    if (sink == NULL)
    {
        return;
    }

    /* Operates on the module state directly rather than sink->impl, so it can
       also serve as the cleanup path for a partially completed open. */
    if (state->plane != NULL)
    {
        plane_hide(state->plane);

        /* Drop our claim before freeing, so the graphics backend never sees a
           dangling plane_data pointer in its array. */
        if (state->registered && (state->gfxDevice != NULL))
        {
            state->gfxDevice->planes[state->planeIndex] = NULL;
            state->registered = false;
        }

        if (state->planeIsOurs)
        {
            plane_free(state->plane);
        }
        else
        {
            /* Borrowed from the graphics backend: unmap but leave it allocated
               so the backend's own bookkeeping stays valid. */
            plane_fb_unmap(state->plane);
        }

        state->plane = NULL;
    }

    memset(state, 0, sizeof(*state));

    sink->impl = NULL;
    sink->fn   = NULL;
    sink->open = false;
}

static const camSinkVTable camDrmVTable =
{
    "drm",
    camDrmPresent,
    camDrmClose
};

camResult Cam_Sink_DRM_Open(camSink* sink, const camSinkConfig* cfg)
{
    /* Formats to try, best first: YUYV needs no conversion, RGB565 is half the
       memory traffic of ARGB8888. */
    static const uint32_t formats[] =
    {
        DRM_FORMAT_YUYV,
        DRM_FORMAT_RGB565,
        DRM_FORMAT_ARGB8888
    };

    struct GfxDevice* gd;
    unsigned int planeIndex = 0;
    unsigned int ordinal = 0;
    uint32_t chosenFormat = 0;
    bool unclaimed = false;
    bool found = false;
    unsigned int f;

    if ((sink == NULL) || (cfg == NULL))
    {
        return CAM_ERR_PARAM;
    }

    gd = GFX_GetDevice();
    if ((gd == NULL) || (gd->device == NULL))
    {
        return CAM_ERR_UNSUPPORTED;    /* DRM backend not in use. */
    }

    memset(&drmSink, 0, sizeof(drmSink));
    drmSink.gfxDevice = gd;

    /* Prefer a plane we can have to ourselves, and within that prefer the
       format that costs the least CPU. */
    for (f = 0; (f < (sizeof(formats) / sizeof(formats[0]))) && !found; f++)
    {
        if (camDrmFindUnclaimedOverlay(gd, formats[f], &planeIndex))
        {
            chosenFormat = formats[f];
            unclaimed = true;
            found = true;
        }
    }

    for (f = 0; (f < (sizeof(formats) / sizeof(formats[0]))) && !found; f++)
    {
        if (camDrmFindReclaimableOverlay(gd, formats[f], &planeIndex))
        {
            chosenFormat = formats[f];
            unclaimed = false;
            found = true;
        }
    }

    if (!found)
    {
        printf("camera: no overlay plane can carry the preview\n");
        return CAM_ERR_UNSUPPORTED;
    }

    if (unclaimed)
    {
        if (!camDrmOverlayOrdinal(gd->device, planeIndex, &ordinal))
        {
            return CAM_ERR_UNSUPPORTED;
        }

        drmSink.plane = plane_create_buffered(gd->device,
                                              DRM_PLANE_TYPE_OVERLAY,
                                              (int)ordinal,
                                              (int)cfg->srcWidth,
                                              (int)cfg->srcHeight,
                                              chosenFormat,
                                              CAM_DRM_BUFFER_COUNT);
        if (drmSink.plane == NULL)
        {
            printf("camera: plane_create_buffered failed for %s\n",
                   kms_format_str(chosenFormat));
            return CAM_ERR_UNSUPPORTED;
        }

        drmSink.planeIsOurs = true;
        drmSink.planeIndex  = planeIndex;

        /* Record ownership so the graphics backend does not later hand this
           same plane out to a Legato layer. Cleared again in close(). */
        gd->planes[planeIndex] = drmSink.plane;
        drmSink.registered = true;
    }
    else
    {
        drmSink.plane       = gd->planes[planeIndex];
        drmSink.planeIsOurs = false;
        drmSink.planeIndex  = planeIndex;

        if (plane_fb_reallocate(drmSink.plane,
                                (int)cfg->srcWidth,
                                (int)cfg->srcHeight,
                                chosenFormat) < 0)
        {
            printf("camera: plane_fb_reallocate failed for %s\n",
                   kms_format_str(chosenFormat));
            drmSink.plane = NULL;
            return CAM_ERR_UNSUPPORTED;
        }

        printf("camera: reusing graphics overlay plane %u for preview\n", planeIndex);
    }

    if (plane_fb_map(drmSink.plane) < 0)
    {
        printf("camera: plane_fb_map failed\n");
        camDrmClose(sink);   /* Works off module state, so the plane is released. */
        return CAM_ERR_BUFFERS;
    }

    drmSink.format  = chosenFormat;
    drmSink.width   = plane_width(drmSink.plane);
    drmSink.height  = plane_height(drmSink.plane);
    drmSink.backBuf = 0;

    sink->fn         = &camDrmVTable;
    sink->impl       = &drmSink;
    sink->nativeYUYV = (chosenFormat == DRM_FORMAT_YUYV);

    /* Nothing has been captured yet, so make sure the buffers hold black rather
       than the green that an untouched YUYV allocation displays as. */
    camDrmBlankBuffers(&drmSink);

    camDrmConfigurePlane(drmSink.plane, cfg);

    if (!drmSink.planeIsOurs)
    {
        /* A borrowed plane is already enabled, and plane_fb_reallocate() has
           just freed the framebuffer it was scanning out, so it has to be
           re-committed now. It shows black until the first frame lands. */
        (void)plane_apply(drmSink.plane);
        drmSink.visible = true;
    }

    /* A plane created here is not committed yet: leaving it disabled until the
       first frame is what keeps a blank preview rectangle off the display. */

    printf("camera: overlay plane %u, format %s, %ux%u, %u buffers\n",
           planeIndex, kms_format_str(chosenFormat),
           drmSink.width, drmSink.height, drmSink.plane->buffer_count);

    return CAM_OK;
}

#else /* !USE_DRM_KMS */

camResult Cam_Sink_DRM_Open(camSink* sink, const camSinkConfig* cfg)
{
    (void)sink;
    (void)cfg;

    /* Built without DRM/KMS support (for example a host SDL2 build). */
    return CAM_ERR_UNSUPPORTED;
}

#endif /* USE_DRM_KMS */

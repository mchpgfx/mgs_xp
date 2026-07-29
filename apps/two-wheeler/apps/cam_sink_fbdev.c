/*******************************************************************************
  Camera Frame Sink - Linux Framebuffer

  Company:
    Microchip Technology Inc.

  File Name:
    cam_sink_fbdev.c

  Summary:
    Writes captured frames into a Linux framebuffer device.

  Description:
    Fallback sink for targets with no DRM/KMS overlay plane. Unlike DRM, fbdev
    offers neither hardware colour conversion nor hardware scaling, so frames
    are converted from YUYV to the framebuffer's own pixel format in software
    (see cam_convert.c) and written into the destination rectangle.

    The destination rectangle is clipped to the framebuffer, and the conversion
    scales the frame to whatever rectangle survives clipping.

    Only 16- and 32-bit framebuffers are handled; those are the two the display
    stack in this tree is configured for.

  Remarks:
    fbdev has no concept of layers, so this composites by writing directly into
    the visible framebuffer. Where the UI also draws, whichever writes last
    wins, and the preview may be overdrawn on the next full UI redraw. This is
    inherent to fbdev, and is exactly why the DRM overlay sink is preferred.
 *******************************************************************************/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <linux/fb.h>

#include "cam_sink.h"
#include "cam_convert.h"

#define CAM_FBDEV_DEFAULT_DEVICE "/dev/fb0"

/*******************************************************************************
 * Backend State
 ******************************************************************************/
typedef struct
{
    int      fd;
    uint8_t* base;           // mmap'd framebuffer
    size_t   mapLength;

    uint32_t stride;         // Bytes per row
    uint32_t bytesPerPixel;

    /* Destination rectangle after clipping to the framebuffer. */
    uint32_t destX;
    uint32_t destY;
    uint32_t destWidth;
    uint32_t destHeight;
} camFbSink;

static camFbSink fbSink;

/*******************************************************************************
 * camFbPresent
 * Converts one frame into the clipped destination rectangle.
 ******************************************************************************/
static camResult camFbPresent(camSink* sink, const camFrame* frame)
{
    camFbSink* state;
    camConvertSource src;
    camConvertDest dst;

    if ((sink == NULL) || (frame == NULL) || (sink->impl == NULL))
    {
        return CAM_ERR_PARAM;
    }

    state = (camFbSink*)sink->impl;

    if (state->base == NULL)
    {
        return CAM_ERR_STATE;
    }

    src.data   = frame->data;
    src.width  = frame->width;
    src.height = frame->height;
    src.stride = frame->stride;

    /* Point the destination at the top-left of the rectangle and let the
       converter walk it using the framebuffer's row stride. */
    dst.data   = state->base
                 + ((size_t)state->destY * state->stride)
                 + ((size_t)state->destX * state->bytesPerPixel);
    dst.width  = state->destWidth;
    dst.height = state->destHeight;
    dst.stride = state->stride;

    if (state->bytesPerPixel == 2u)
    {
        Cam_Convert_YUYVToRGB565(&src, &dst);
    }
    else
    {
        Cam_Convert_YUYVToARGB8888(&src, &dst);
    }

    sink->framesPresented++;

    return CAM_OK;
}

/*******************************************************************************
 * camFbClose
 ******************************************************************************/
static void camFbClose(camSink* sink)
{
    camFbSink* state;

    if ((sink == NULL) || (sink->impl == NULL))
    {
        return;
    }

    state = (camFbSink*)sink->impl;

    if (state->base != NULL)
    {
        munmap(state->base, state->mapLength);
        state->base = NULL;
    }

    if (state->fd >= 0)
    {
        close(state->fd);
        state->fd = -1;
    }

    memset(state, 0, sizeof(*state));
    state->fd = -1;

    sink->impl = NULL;
    sink->fn   = NULL;
    sink->open = false;
}

static const camSinkVTable camFbVTable =
{
    "fbdev",
    camFbPresent,
    camFbClose
};

camResult Cam_Sink_FBDev_Open(camSink* sink, const camSinkConfig* cfg)
{
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    const char* devPath = CAM_FBDEV_DEFAULT_DEVICE;
    uint32_t destW;
    uint32_t destH;
    int32_t x;
    int32_t y;

    if ((sink == NULL) || (cfg == NULL))
    {
        return CAM_ERR_PARAM;
    }

    memset(&fbSink, 0, sizeof(fbSink));
    fbSink.fd = -1;

    fbSink.fd = open(devPath, O_RDWR);
    if (fbSink.fd < 0)
    {
        return CAM_ERR_UNSUPPORTED;     /* No framebuffer on this system. */
    }

    if (ioctl(fbSink.fd, FBIOGET_VSCREENINFO, &vinfo) < 0)
    {
        printf("camera: FBIOGET_VSCREENINFO failed: %s\n", strerror(errno));
        close(fbSink.fd);
        fbSink.fd = -1;
        return CAM_ERR_UNSUPPORTED;
    }

    if (ioctl(fbSink.fd, FBIOGET_FSCREENINFO, &finfo) < 0)
    {
        printf("camera: FBIOGET_FSCREENINFO failed: %s\n", strerror(errno));
        close(fbSink.fd);
        fbSink.fd = -1;
        return CAM_ERR_UNSUPPORTED;
    }

    if ((vinfo.bits_per_pixel != 16u) && (vinfo.bits_per_pixel != 32u))
    {
        printf("camera: unsupported framebuffer depth %u bpp\n", vinfo.bits_per_pixel);
        close(fbSink.fd);
        fbSink.fd = -1;
        return CAM_ERR_UNSUPPORTED;
    }

    fbSink.bytesPerPixel = vinfo.bits_per_pixel / 8u;
    fbSink.stride        = finfo.line_length;
    fbSink.mapLength     = finfo.smem_len;

    /* Clip the requested rectangle to the visible framebuffer. */
    destW = (cfg->destWidth  != 0) ? cfg->destWidth  : cfg->srcWidth;
    destH = (cfg->destHeight != 0) ? cfg->destHeight : cfg->srcHeight;

    x = (cfg->destX > 0) ? cfg->destX : 0;
    y = (cfg->destY > 0) ? cfg->destY : 0;

    if ((uint32_t)x >= vinfo.xres) { x = 0; }
    if ((uint32_t)y >= vinfo.yres) { y = 0; }

    if ((destW + (uint32_t)x) > vinfo.xres)
    {
        destW = vinfo.xres - (uint32_t)x;
    }

    if ((destH + (uint32_t)y) > vinfo.yres)
    {
        destH = vinfo.yres - (uint32_t)y;
    }

    if ((destW == 0) || (destH == 0))
    {
        close(fbSink.fd);
        fbSink.fd = -1;
        return CAM_ERR_PARAM;
    }

    fbSink.destX      = (uint32_t)x;
    fbSink.destY      = (uint32_t)y;
    fbSink.destWidth  = destW;
    fbSink.destHeight = destH;

    fbSink.base = (uint8_t*)mmap(NULL, fbSink.mapLength,
                                 PROT_READ | PROT_WRITE, MAP_SHARED,
                                 fbSink.fd, 0);
    if (fbSink.base == MAP_FAILED)
    {
        printf("camera: framebuffer mmap failed: %s\n", strerror(errno));
        fbSink.base = NULL;
        close(fbSink.fd);
        fbSink.fd = -1;
        return CAM_ERR_BUFFERS;
    }

    sink->fn         = &camFbVTable;
    sink->impl       = &fbSink;
    sink->nativeYUYV = false;   /* fbdev always needs a software conversion. */

    printf("camera: fbdev %s %ux%u %ubpp stride=%u, preview rect %ux%u at (%u,%u)\n",
           devPath, vinfo.xres, vinfo.yres, vinfo.bits_per_pixel,
           fbSink.stride, fbSink.destWidth, fbSink.destHeight,
           fbSink.destX, fbSink.destY);

    return CAM_OK;
}

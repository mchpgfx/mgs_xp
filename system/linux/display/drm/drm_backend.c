/*******************************************************************************
* Copyright (C) 2025 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#ifdef USE_DRM_KMS

#include <drm_fourcc.h>
#include <xf86drm.h>
#include <xf86drmMode.h>

#include "drm_backend.h"
#include "gfx/legato/common/legato_color.h"
#include "gfx/legato/common/legato_pixelbuffer.h"
#include "gfx/legato/generated/le_gen_init.h"


static struct GfxDevice *GfxDev = NULL;

static void GFX_DriverInterface_Update(void)
{
    return;
}

static gfxColorMode drm2mgs_format(uint32_t format)
{
    switch (format) {
        case DRM_FORMAT_RGB565:
            return GFX_COLOR_MODE_RGB_565;
        case DRM_FORMAT_XRGB8888:
        case DRM_FORMAT_ARGB8888:
            return GFX_COLOR_MODE_ARGB_8888;
        case DRM_FORMAT_RGBX8888:
        case DRM_FORMAT_RGBA8888:
        default:
            return GFX_COLOR_MODE_RGBA_8888;
    }
}

static uint32_t mgs2drm_format(gfxColorMode mode)
{
    switch (mode) {
        case GFX_COLOR_MODE_RGB_565:
            return DRM_FORMAT_RGB565;
        case GFX_COLOR_MODE_RGB_888:
            return DRM_FORMAT_RGB888;
        case GFX_COLOR_MODE_ARGB_8888:
            return DRM_FORMAT_ARGB8888;
        case GFX_COLOR_MODE_RGBA_8888:
        default:
            return DRM_FORMAT_RGBA8888;
    }
}

static gfxDriverIOCTLResponse GFX_DriverInterface_IOCTL(gfxDriverIOCTLRequest request,
                                                        void *arg)
{
    gfxIOCTLArg_Value *val;
    gfxIOCTLArg_DisplaySize *disp;
    gfxIOCTLArg_DisplayBuffer *dispbuf;
    gfxIOCTLArg_LayerRect *rect;
    gfxIOCTLArg_LayerValue *layerval;
    struct plane_data *plane = NULL;
    uint32_t i = 0;

    if (!GfxDev) {
        printf("GfxDev not yet initialized");
        return GFX_IOCTL_ERROR_UNKNOWN;
    }

    switch (request) {
        case GFX_IOCTL_GET_BUFFER_COUNT: {
            val = (gfxIOCTLArg_Value *)arg;
            val->value.v_uint = GfxDev->max_buffers;
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_GET_DISPLAY_SIZE: {
            disp = (gfxIOCTLArg_DisplaySize *)arg;
            disp->width = GfxDev->width;
            disp->height = GfxDev->height;
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_FRAME_START: {
            val = (gfxIOCTLArg_Value *)arg;
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_GET_LAYER_RECT: {
            rect = (gfxIOCTLArg_LayerRect *)arg;

            //rect->layer.id = arg->id;
            plane = GfxDev->planes[rect->layer.id];
            if (!plane) {
                //printf("GFX_IOCTL_GET_LAYER_RECT: Get plane id %d failed\n", rect->layer.id);
                //return GFX_IOCTL_ERROR_UNKNOWN;

            	GfxDev->planes[rect->layer.id] = plane_create_buffered(GfxDev->device, DRM_PLANE_TYPE_OVERLAY,
                                              (rect->layer.id ? (rect->layer.id - 1) : 0),
                                              GfxDev->width,
                                              GfxDev->height,
                                              DRM_FORMAT_RGB565,
                                              GfxDev->max_buffers);
            	if (!GfxDev->planes[rect->layer.id]) {
            	    printf("error: failed to create overlay plane index = %d\n", i);
                	return GFX_IOCTL_ERROR_UNKNOWN;
           		}

            	plane_set_pos(GfxDev->planes[rect->layer.id], 0, 0);
            	plane_apply(GfxDev->planes[rect->layer.id]);
					
            	rect->x = plane_x(GfxDev->planes[rect->layer.id]);
            	rect->y = plane_y(GfxDev->planes[rect->layer.id]);
            	rect->width = plane_width(GfxDev->planes[rect->layer.id]);
            	rect->height = plane_height(GfxDev->planes[rect->layer.id]);

            	return GFX_IOCTL_OK;
            }

            rect->x = plane_x(plane);
            rect->y = plane_y(plane);
            rect->width = plane_width(plane);
            rect->height = plane_height(plane);

            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_LAYER_SWAP: {
            /* this command is for swapping the buffers incase double or triple buffering for the active layer */
            plane = GfxDev->planes[GfxDev->active_layer_id];
            if (!plane) {
                printf("GFX_IOCTL_LAYER_SWAP: Get plane id %d failed\n", GfxDev->active_layer_id);
                return GFX_IOCTL_ERROR_UNKNOWN;
            }

            if (plane->buffer_count > 1) {

                plane->buffer_index++;

                if (plane->buffer_index >= plane->buffer_count) {
                    plane->buffer_index = 0;
                }

                plane->plane_flip = true;
            }

            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_SET_ACTIVE_LAYER: {
            val = (gfxIOCTLArg_Value *)arg;
            if (val && val->value.v_uint >= GfxDev->device->num_planes) {
                printf("GFX_IOCTL_SET_ACTIVE_LAYER: Invalid plane id = %d\n", val->value.v_uint);
                return GFX_IOCTL_ERROR_UNKNOWN;
            }

            GfxDev->active_layer_id = val->value.v_uint;

            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_FRAME_END: {
            /* Here you do plane flip on all layers */
            for (i = 0; i < GfxDev->device->num_planes; i++) {
                plane = GfxDev->planes[i];
                if (plane && plane->plane_flip) {
                    plane_flip_async(plane, plane->buffer_index);
                    plane->plane_flip = false;
                }
            }
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_GET_FRAMEBUFFER: {
            plane = GfxDev->planes[GfxDev->active_layer_id];
            if (plane && (plane_fb_map(plane) >= 0)) {
                val = (gfxIOCTLArg_Value *)arg;
                val->value.v_pbuffer = (void *)plane->bufs[plane->buffer_index];
                return GFX_IOCTL_OK;
            }
            printf("error: kms_framebuffer_map() failed \n");
            return GFX_IOCTL_ERROR_UNKNOWN;
        }
        case GFX_IOCTL_CREATE_FRAMEBUFFER: {
            dispbuf = (gfxIOCTLArg_DisplayBuffer *)arg;
            if (!dispbuf) {
                printf("error: invaild DisplayBuffer parameters \n");
                return GFX_IOCTL_ERROR_UNKNOWN;
            }

            void *ptr;
            if (GfxDev->fbs_count == 0) {
                GfxDev->fbs = calloc(1, sizeof(struct kms_framebuffer *));
                if (!GfxDev->fbs) {
                    printf("error: failed to allocate memory GfxDev->fb\n");
                    return GFX_IOCTL_ERROR_UNKNOWN;
                }
            } else {
                GfxDev->fbs = realloc(GfxDev->fbs, (GfxDev->fbs_count + 1) * sizeof (struct kms_framebuffer *));
                if (!GfxDev->fbs) {
                    printf("error: failed to re allocate memory GfxDev->fb\n");
                    return GFX_IOCTL_ERROR_UNKNOWN;
                }
            }

            GfxDev->fbs[GfxDev->fbs_count] = kms_framebuffer_create(GfxDev->device, dispbuf->width, dispbuf->height, mgs2drm_format(dispbuf->mode));
            if (!GfxDev->fbs[GfxDev->fbs_count]) {
                printf("error: failed to create fb\n");
                return GFX_IOCTL_ERROR_UNKNOWN;
            }

            if (kms_framebuffer_map(GfxDev->fbs[GfxDev->fbs_count], &ptr) < 0) {
                printf("error: kms_framebuffer_map() failed:\n");
                return GFX_IOCTL_ERROR_UNKNOWN;
            }
            GfxDev->fbs_count++;
            dispbuf->bufptr = ptr;

            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_SET_LAYER_LOCK: {
            break;
        }
        case GFX_IOCTL_GET_LAYER_ENABLED: {
            break;
        }
        case GFX_IOCTL_SET_LAYER_ENABLED: {
            layerval = (gfxIOCTLArg_LayerValue *)arg;
            if (layerval && layerval->layer.id >= GfxDev->device->num_planes) {
                printf("GFX_IOCTL_SET_LAYER_ENABLED: Invalid plane id = %d\n", layerval->layer.id);
                return GFX_IOCTL_ERROR_UNKNOWN;
            }

            plane = GfxDev->planes[layerval->layer.id];
            plane_apply_fb_parms(plane, GfxDev->fbs[layerval->layer.id]);
            //plane_set_pos(plane, layerpos->x, layerpos->y);
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_SET_LAYER_UNLOCK: {
            break;
        }
        case GFX_IOCTL_SET_LAYER_POSITION: {
            gfxIOCTLArg_LayerPosition *layerpos = (gfxIOCTLArg_LayerPosition *)arg;
            if (layerpos && layerpos->layer.id >= GfxDev->device->num_planes) {
                printf("GFX_IOCTL_SET_LAYER_POSITION: Invalid plane id = %d\n", layerpos->layer.id);
                return GFX_IOCTL_ERROR_UNKNOWN;
            }

            GfxDev->active_layer_id = layerpos->layer.id;
            plane = GfxDev->planes[layerpos->layer.id];
            plane_set_pos(plane, layerpos->x, layerpos->y);
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_SET_LAYER_SIZE: {
            layerval = (gfxIOCTLArg_LayerValue *)arg;
            if (layerval && layerval->layer.id >= GfxDev->device->num_planes) {
                printf("GFX_IOCTL_SET_LAYER_SIZE: Invalid plane id = %d\n", layerval->layer.id);
                return GFX_IOCTL_ERROR_UNKNOWN;
            }

            GfxDev->active_layer_id = layerval->layer.id;
            //To Changing the layer size need to delete and recreate new plane with width and height.
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_SET_LAYER_WINDOW_SIZE: {
            gfxIOCTLArg_LayerSize *layersval = (gfxIOCTLArg_LayerSize *)arg;
            if (layersval && layersval->layer.id >= GfxDev->device->num_planes) {
                printf("GFX_IOCTL_SET_LAYER_WINDOW_SIZE: Invalid plane id = %d\n", layersval->layer.id);
                return GFX_IOCTL_ERROR_UNKNOWN;
            }

            GfxDev->active_layer_id = layersval->layer.id;
            plane = GfxDev->planes[layersval->layer.id];
            plane_set_pan_size(plane, layersval->width, layersval->height);
            //To Changing the layer size need to delete and recreate new plane with width and height.
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_SET_LAYER_ALPHA: {
            layerval = (gfxIOCTLArg_LayerValue *)arg;
            if (layerval && layerval->layer.id >= GfxDev->device->num_planes) {
                printf("GFX_IOCTL_SET_LAYER_ALPHA: Invalid plane id = %d\n", layerval->layer.id);
                return GFX_IOCTL_ERROR_UNKNOWN;
            }

            GfxDev->active_layer_id = layerval->layer.id;
            plane = GfxDev->planes[layerval->layer.id];
            plane_apply_alpha(plane, layerval->value.v_uint);
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_SET_LAYER_BASE_ADDRESS: {
            layerval = (gfxIOCTLArg_LayerValue *)arg;
            if (layerval && layerval->layer.id >= GfxDev->device->num_planes) {
                printf("GFX_IOCTL_SET_LAYER_BASE_ADDRESS: Invalid plane id = %d\n", layerval->layer.id);
                return GFX_IOCTL_ERROR_UNKNOWN;
            }

            GfxDev->active_layer_id = layerval->layer.id;
            for (i = 0; i < GfxDev->fbs_count; i++) {
                if ((uint32_t *)GfxDev->fbs[i]->ptr == (uint32_t *)layerval->value.v_pointer) {
                    plane = GfxDev->planes[layerval->layer.id];
                    kms_plane_set(plane->plane, GfxDev->fbs[i], plane->x, plane->y, 1.0, 1.0);
                    return GFX_IOCTL_OK;
                }
            }
            return GFX_IOCTL_ERROR_UNKNOWN;
        }
        case GFX_IOCTL_SET_LAYER_COLOR_MODE: {
            // To Changing the color mode here needs to receate frame buffer.
            break;
        }
        default: {
            return GFX_IOCTL_UNSUPPORTED;
        }
    }
    return GFX_IOCTL_UNSUPPORTED;
}

static int plane_reallocate(struct plane_data *plane, uint32_t format)
{
    int err;

    if (plane->type == DRM_PLANE_TYPE_PRIMARY) {
        plane_free(plane);

        plane = plane_create(GfxDev->device, DRM_PLANE_TYPE_PRIMARY, 0,
                             GfxDev->device->screens[0]->width,
                             GfxDev->device->screens[0]->height,
                             format);
        if (!plane) {
            printf("error: failed to create primary plane\n");
            return -1;
        }

        plane_set_pos(plane, 0, 0);
        plane_apply(plane);

        GfxDev->planes[GfxDev->active_layer_id] = plane;
        GfxDev->format = format;
    } else {
        err = plane_fb_reallocate(plane, (int)plane_width(plane), (int)plane_height(plane), format);
        if (err < 0) {
            printf("%s: plane_fb_reallocate failed with format : %s\n", __FUNCTION__, kms_format_str(format));
            return -1;
        }
    }

    return 0;
}

static gfxResult GFX_DriverInterface_BlitBuffer(int32_t x, int32_t y, gfxPixelBuffer *buf)
{
    int err;
    int32_t r;
    uint32_t offset = 0;
    struct plane_data *plane;
    uint32_t format = mgs2drm_format(buf->mode);
    uint32_t bpp = kms_format_bpp(format) / 8;

    if (!GfxDev) {
        printf("GfxDev not yet initialized");
        return GFX_FAILURE;
    }

    plane = GfxDev->planes[GfxDev->active_layer_id];
    if (plane) {
        err = plane_fb_map(plane);
        if (err < 0) {
            printf("error: kms_framebuffer_map() failed: %s\n", strerror(-err));
            return GFX_FAILURE;
        }
        if (plane_format(plane) != format) {

            err = plane_reallocate(plane, format);
            if (err < 0) {
                printf("error: plane_reallocate failed: %s\n", strerror(-err));
                return GFX_FAILURE;
            }

            err = plane_fb_map(plane);
            if (err < 0) {
                printf("error: kms_framebuffer_map() failed: %s\n", strerror(-err));
                return GFX_FAILURE;
            }
        }
        for (r = 0; r < buf->size.height; r++) {
            offset = ((r + y) * plane->fbs[plane->buffer_index]->pitch) + (x * bpp);
            memcpy((void *)(plane->bufs[plane->buffer_index] + offset), gfxPixelBufferOffsetGet(buf, 0, r), buf->size.width * bpp);
        }

        plane_fb_unmap(plane);
        return GFX_SUCCESS;
    }

    printf("%s: Invaid plane\n", __FUNCTION__);
    return GFX_FAILURE;
}

static struct GfxDevice *drm_device_initialize(int32_t dev_num)
{
    int32_t fd, err;
    uint32_t i;
    char dev_path[255];
    struct kms_device *device;
    struct plane_data **planes;
    struct GfxDevice *gd;

    gd = (struct GfxDevice *) malloc(sizeof(struct GfxDevice));
    if (gd == NULL) {
        printf("memory allocation of GfxDevice failed \n");
        return NULL;
    }

    memset(gd, 0, sizeof(struct GfxDevice));

    gd->max_buffers = 1;

    snprintf(dev_path, sizeof(dev_path), "/dev/dri/card%d", dev_num);

    fd = open(dev_path, O_RDWR);
    if (fd < 0) {
        fprintf(stderr, "open() failed: %m\n");
        return NULL;
    }

    err = drmSetClientCap(fd, DRM_CLIENT_CAP_UNIVERSAL_PLANES, 1);
    if (err < 0) {
        fprintf(stderr, "drmSetClientCap() failed: %d\n", err);
        goto err;
    }

    device = kms_device_open(fd);
    if (!device) {
        goto err;
    }

    device->fd = fd;
	
	/* uncomment if you need to debug messages of drm/kms device */
    //kms_device_dump(device);

    planes = calloc(device->num_planes, sizeof(struct plane_data *));
    if (!planes) {
        printf("memory allocation of planes failed \n");
        goto err1;
    }

    for (i = 0; i < device->num_planes - 1; i++) {
        if (device->planes[i]->type == DRM_PLANE_TYPE_PRIMARY) {
            planes[i] = plane_create_buffered(device, DRM_PLANE_TYPE_PRIMARY, 0,
                                              device->screens[0]->width,
                                              device->screens[0]->height,
                                              DRM_FORMAT_RGB565,
                                              gd->max_buffers);
            if (!planes[i]) {
                printf("error: failed to create primary plane\n");
                goto err2;
            }

            plane_set_pos(planes[i], 0, 0);
            plane_apply(planes[i]);
            gd->active_layer_id = i;

        }else if (device->planes[i]->type == DRM_PLANE_TYPE_OVERLAY) {
            planes[i] = plane_create_buffered(device, DRM_PLANE_TYPE_OVERLAY,
                                              (i ? (i - 1) : 0),
                                              device->screens[0]->width,
                                              device->screens[0]->height,
                                              DRM_FORMAT_RGBA8888,
                                              gd->max_buffers);
            if (!planes[i]) {
                printf("error: failed to create overlay plane index = %d\n", i);
                goto err2;
            }

            plane_set_pos(planes[i], 0, 0);
            plane_apply(planes[i]);
        }
    }

    gd->planes = planes;
    gd->device = device;
    gd->width = device->screens[0]->width;
    gd->height = device->screens[0]->height;
    gd->format = DRM_FORMAT_RGB565;
    return gd;

err2:
    for (i = 0; i < device->num_planes; i++) {
        if (planes[i]) {
            plane_free(planes[i]);
        }
    }

    if (planes) {
        free(planes);
    }
err1:
    kms_device_close(device);
err:
    close(fd);
    return NULL;
}

void GFX_Update(void)
{
    if (!GfxDev) {
        //printf("GfxDev not yet initialized");
        return;
    }

    GFX_DriverInterface_Update();
}

struct GfxDevice *GFX_Initialize(void)
{
    int32_t dev_num = 0;

    //ToDO dev_num should be send from upper layer.
    GfxDev = drm_device_initialize(dev_num);
    if (!GfxDev) {
        printf("drm_device_initialize failed \n");
        free(GfxDev);
        return NULL;
    }

    GfxDev->gfxDriverInterface.update =  GFX_DriverInterface_Update;
    GfxDev->gfxDriverInterface.blitBuffer = GFX_DriverInterface_BlitBuffer;
    GfxDev->gfxDriverInterface.ioctl = GFX_DriverInterface_IOCTL;

    return GfxDev;
}

void GFX_DeInitalize(void)
{
    uint32_t i = 0;

    if (GfxDev != NULL) {
        for (i = 0; i < GfxDev->device->num_planes; i++) {
            if ( GfxDev->planes[i]) {
                plane_free(GfxDev->planes[i]);
            }
        }

        kms_device_close(GfxDev->device);
        drmClose(GfxDev->device->fd);
        free(GfxDev->planes);
    }
}
#endif


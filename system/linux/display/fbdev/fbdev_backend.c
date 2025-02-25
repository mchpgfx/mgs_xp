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
#include <unistd.h>
#include <fcntl.h>
#include <libinput.h>
#include <libudev.h>
#include <sys/mman.h>
#include <sys/ioctl.h> 
#include "fbdev_backend.h"
#include "gfx/legato/common/legato_color.h"
#include "gfx/legato/common/legato_pixelbuffer.h"
#include "gfx/legato/generated/le_gen_init.h"

#define UFX_IOCTL_REPORT_DAMAGE (0xAA)

struct dloarea {
    int x, y;
    int w, h;
};

static struct FBDevDevice FbDev;

static void FBDev_DriverInterface_Update(void)
{
	return;
}

static gfxDriverIOCTLResponse FBDev_DriverInterface_IOCTL(gfxDriverIOCTLRequest request,
                                                        void *arg)
{
    gfxIOCTLArg_Value *val;
    gfxIOCTLArg_DisplaySize *disp;
    //gfxIOCTLArg_DisplayBuffer *dispbuf;
    gfxIOCTLArg_LayerRect *rect;
    //gfxIOCTLArg_LayerValue *layerval;

    if (FbDev.fbptr == NULL) {
        printf("FbDev not yet initialized");
        return GFX_IOCTL_ERROR_UNKNOWN;
    }

    switch (request) {
        case GFX_IOCTL_GET_BUFFER_COUNT: {
            val = (gfxIOCTLArg_Value *)arg;
            val->value.v_uint = FbDev.max_buffers;
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_GET_DISPLAY_SIZE: {
            disp = (gfxIOCTLArg_DisplaySize *)arg;
            disp->width = FbDev.width;
            disp->height = FbDev.height;
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_FRAME_START: {
            val = (gfxIOCTLArg_Value *)arg;
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_GET_LAYER_RECT: {
            rect = (gfxIOCTLArg_LayerRect *)arg;
			rect->x = 0; //plane_x(plane);
            rect->y = 0; //plane_y(plane);
            rect->width = FbDev.width;
            rect->height = FbDev.height; 
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_LAYER_SWAP: {
            /* this command is for swapping the buffers incase double or triple buffering for the active layer */
			if (FbDev.max_buffers > 1) {
				memcpy((void *)(FbDev.fbptr), FbDev.fbs[FbDev.current_index], FbDev.screensize);
				if (FbDev.current_index == 0)
					FbDev.current_index = 1;
				else
					FbDev.current_index = 0;
			}
            	return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_SET_ACTIVE_LAYER: {
            val = (gfxIOCTLArg_Value *)arg;
            if (val && (val->value.v_uint < 0 && val->value.v_uint > 0) ) {
                printf("GFX_IOCTL_SET_ACTIVE_LAYER: Invalid = %d\n", val->value.v_uint);
                return GFX_IOCTL_ERROR_UNKNOWN;
            }
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_FRAME_END: {
            /* Here you do plane flip on all layers */
			if (FbDev.max_buffers > 1) {
				struct dloarea area;
				area.x = 0;
				area.y = 0;
				area.w = FbDev.width;
				area.y = FbDev.height;

				if (ioctl (FbDev.fbfd, UFX_IOCTL_REPORT_DAMAGE, &area)) {
					printf("UFX_IOCTL_REPORT_DAMAGE error \n");
					return GFX_IOCTL_ERROR_UNKNOWN;
    			}
			}
            return GFX_IOCTL_OK; 
        }
        case GFX_IOCTL_GET_FRAMEBUFFER: {
            printf("GFX_IOCTL_GET_FRAMEBUFFER: Todo\n");
                return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_CREATE_FRAMEBUFFER: {
            printf("GFX_IOCTL_CREATE_FRAMEBUFFER: Todo\n");
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_SET_LAYER_LOCK: {
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_GET_LAYER_ENABLED: {
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_SET_LAYER_ENABLED: {
            printf("GFX_IOCTL_SET_LAYER_ENABLED: Todo\n");
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_SET_LAYER_UNLOCK: {
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_SET_LAYER_POSITION: {
            printf("GFX_IOCTL_SET_LAYER_POSITION: Todo\n");
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_SET_LAYER_SIZE: {
            printf("GFX_IOCTL_SET_LAYER_SIZE: Todo\n");
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_SET_LAYER_WINDOW_SIZE: {
            printf("GFX_IOCTL_SET_LAYER_WINDOW_SIZE: Todo\n");
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_SET_LAYER_ALPHA: {
            printf("GFX_IOCTL_SET_LAYER_WINDOW_SIZE: Todo\n");
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_SET_LAYER_BASE_ADDRESS: {
            printf("GFX_IOCTL_SET_LAYER_BASE_ADDRESS: Todo\n");
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_SET_LAYER_COLOR_MODE: {
            // To Changing the color mode here needs to receate frame buffer.
            printf("GFX_IOCTL_SET_LAYER_COLOR_MODE: Todo\n");
            return GFX_IOCTL_OK;
        }
        default: {
            printf("GFX_IOCTL_UNSUPPORTED: Todo %d\n",request);
            return GFX_IOCTL_UNSUPPORTED;
        }
    }
    return GFX_IOCTL_UNSUPPORTED;
}

static gfxResult FBDev_DriverInterface_BlitBuffer(int32_t x, int32_t y, gfxPixelBuffer *buf)
{
    int32_t r;
    uint32_t offset = 0;
    uint32_t bpp = FbDev.vinfo.bits_per_pixel / 8;
	uint32_t pitch = FbDev.width * bpp;

    if (FbDev.fbptr == NULL) {
        printf("FbDev not yet initialized");
        return GFX_FAILURE;
    }

	if (FbDev.max_buffers > 1) {
		for (r = 0; r < buf->size.height; r++) {
			offset = ((r + y) * pitch) + (x * bpp);
			memcpy((void *)(FbDev.fbs[FbDev.current_index] + offset), gfxPixelBufferOffsetGet(buf, 0, r), buf->size.width * bpp);
		}
	}
	else {
		for (r = 0; r < buf->size.height; r++) {
			offset = ((r + y) * pitch) + (x * bpp);
			memcpy((void *)(((uint8_t*)FbDev.fbptr) + offset), gfxPixelBufferOffsetGet(buf, 0, r), buf->size.width * bpp);
    	} 
	}
    return GFX_SUCCESS;
}

struct FBDevDevice *FBDev_Initialize(void)
{
	const char *devname = "/dev/fb0";

    // open the frame buffer file for reading & writing
    FbDev.fbfd = open(devname, O_RDWR);
    if (FbDev.fbfd < 0) {
        printf("can't open framebuffer device: %s\n", devname);
		return NULL;
    }

	printf("The framebuffer device was opened successfully\n");

    if (ioctl (FbDev.fbfd, FBIOGET_FSCREENINFO, &(FbDev.finfo))) {
        close (FbDev.fbfd);
        printf("Error reading Fbdev fixed information\n");
		return NULL;
    }

    if (ioctl (FbDev.fbfd, FBIOGET_VSCREENINFO, &(FbDev.vinfo))) {
        close (FbDev.fbfd);
        printf("Error reading FBDev variable information\n");
		return NULL;
    }

    // print info about the buffer
    printf("%s: %dx%d, %dbpp\n", __FUNCTION__, FbDev.vinfo.xres, FbDev.vinfo.yres, FbDev.vinfo.bits_per_pixel);
    // calculates size
    FbDev.screensize = FbDev.vinfo.xres * FbDev.vinfo.yres * FbDev.vinfo.bits_per_pixel / 8;
	FbDev.width = FbDev.vinfo.xres;
	FbDev.height = FbDev.vinfo.yres;

    // map the device to memory 
    FbDev.fbptr = mmap(0, FbDev.screensize, PROT_READ | PROT_WRITE, MAP_SHARED, FbDev.fbfd, 0);
    if (FbDev.fbptr == NULL) {
        close (FbDev.fbfd);
        printf("Error: failed to map framebuffer device to memory\n");
    }

	FbDev.max_buffers = 1;
	if (FbDev.max_buffers > 1)
	{
		FbDev.current_index = 0;
		FbDev.fbs = (uint8_t **)calloc(FbDev.max_buffers, sizeof(uint8_t *));
		if (!FbDev.fbs) {
    	    FBDev_DeInitalize();
			printf("error: failed to allocate memory FbDev.fb\n");
			return NULL;
		}
	
		for (uint32_t i = 0; i < FbDev.max_buffers; i++){
			FbDev.fbs[i] = (uint8_t *)calloc(FbDev.screensize, sizeof(uint8_t));
		}
	}

    printf("The framebuffer device was successfully mapped to memory\n");

    FbDev.gfxDriverInterface.update =  FBDev_DriverInterface_Update;
    FbDev.gfxDriverInterface.blitBuffer = FBDev_DriverInterface_BlitBuffer;
    FbDev.gfxDriverInterface.ioctl = FBDev_DriverInterface_IOCTL;

    return &FbDev;
}

void FBDev_DeInitalize(void)
{
	if (FbDev.max_buffers > 1) {
    	for (uint32_t i = 0; i < FbDev.max_buffers; i++) {
        	free(FbDev.fbs[i]);
    	}
    	free(FbDev.fbs);
	}

	if(FbDev.fbptr != NULL)
    	munmap (FbDev.fbptr, FbDev.screensize);

	if(FbDev.fbfd >= 0) {
    	close (FbDev.fbfd);
		FbDev.fbfd = -1;
	}
}


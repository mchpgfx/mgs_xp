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

#ifndef GFX_BACKEND_H
#define GFX_BACKEND_H

#include <stdint.h>

#include "drm_device.h"
#include "plane.h"
#include "gfx/driver/gfx_driver.h"

//#define DRIVER_DISPLAY_WIDTH 1280
//#define DRIVER_DISPLAY_HEIGHT 800

struct GfxDevice {
    uint32_t *v_bufptr;
    uint32_t width, height;
    uint32_t format;
    struct plane_data **planes;
    struct kms_screen *screen;
    struct kms_device *device;
	struct kms_framebuffer **fbs;
	uint32_t fbs_count;
    uint32_t active_layer_id;
    uint32_t max_buffers;
    gfxDisplayDriver gfxDriverInterface;
};


struct GfxDevice *GFX_Initialize(void);

void GFX_Update(void);

//int32_t GFX_Initialize_touch(void);

void GFX_DeInitalize(void);

#endif // GFX_BACKEND_H

/*******************************************************************************
* Copyright (C) 2023 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _GFX_SDL2_H
#define _GFX_SDL2_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "gfx/driver/gfx_driver.h"
//#include "system/input/sys_input.h"
//#include "system/time/sys_time.h"

// You may exclude hardware specific code using any of these macros.
#define MGS_SIM true
#define GFX_SDL2_ONLY true
#define GFX_SIMULATOR_ENABLED true

// Display and Controller Subsystem
bool GFX_SDL2_Initialize(void);
void GFX_SDL2_Update(void);
gfxResult GFX_SDL2_BlitBuffer(int32_t x, int32_t y, gfxPixelBuffer *buf);
gfxDriverIOCTLResponse GFX_SDL2_IOCTL(gfxDriverIOCTLRequest req,
                                     void *arg);
#if 0
// Timer Subsystem
void GFX_SDL2_TimerStart(void);
void GFX_SDL2_TimerStop(void);
void GFX_SDL2_TimerStubCompareSet(uint32_t dummy);
void GFX_SDL2_TimerRegisterCallback(SYS_TIME_PLIB_CALLBACK callback, uintptr_t context);
uint32_t GFX_SDL2_TimerGetFreqHz(void);
uint32_t GFX_SDL2_TimerCounterGet(void);
#endif

static const gfxDisplayDriver gfxDriverInterface =
{
    .update = GFX_SDL2_Update,
    .blitBuffer = GFX_SDL2_BlitBuffer,
    .ioctl = GFX_SDL2_IOCTL
};

#endif

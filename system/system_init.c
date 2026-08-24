
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

#include <stdio.h>
#include <string.h>

#include "gfx/legato/generated/le_gen_init.h"
#include "gfx/legato/legato.h"

#ifdef _WIN32
    /* Windows platform */
    #include <windows.h>
    #include "windows/timer/timer.h"
    #ifdef USE_SDL2
    #include "windows/display/sdl2/gfx_sdl2.h"
    #endif
#else
    /* Linux platform */
    #include <time.h>   /* Needed for struct timespec */
    #include "linux/timer/timer.h"

    #ifdef USE_DRM_KMS
    #include "linux/display/drm/drm_backend.h"
    #endif

    #include "linux/display/fbdev/fbdev_backend.h"

    #ifdef USE_SDL2
    #include "linux/display/sdl2/gfx_sdl2.h"
    #endif

    #include "linux/input/libinput_backend.h"
#endif

#ifdef USE_CANVAS
#include "gfx/canvas/gfx_canvas_api.h"
extern gfxDisplayDriver gfxCanvasDriverInterface;
#endif

#include "system_init.h"

uint32_t dt = 0;

#ifdef _WIN32
static LARGE_INTEGER perfFreq;
static LARGE_INTEGER lastTime;
#else
static struct timespec lastTime;
#endif

static uint32_t getTickMs(void)
{
#ifdef _WIN32
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    return (uint32_t)((now.QuadPart * 1000) / perfFreq.QuadPart);
#else
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return (uint32_t)(now.tv_sec * 1000 + now.tv_nsec / 1000000);
#endif
}

int mssleep(long miliseconds)
{
#ifdef _WIN32
    Sleep((DWORD)miliseconds);
    return 0;
#else
    struct timespec rem;
    struct timespec req= {
        (int)(miliseconds / 1000),     /* secs (Must be Non-Negative) */
        (miliseconds % 1000) * 1000000 /* nano (Must be in range of 0 to 999999999) */
    };

    return nanosleep(&req , &rem);
#endif
}

void SYS_Initialize(
#ifdef __GNUC__
    __attribute__((unused))
#endif
    void* data)
{
#ifdef _WIN32
    /* Windows: SDL2 only */
    timer_init();
    QueryPerformanceFrequency(&perfFreq);
    QueryPerformanceCounter(&lastTime);

    #ifdef USE_SDL2
    if(GFX_SDL2_Initialize())
    {
        printf("initialize SDL2 Backend Success\n");
        return;
    }
    #endif

    printf("initializing Display Backend Failed\n");
    exit(1);

#else
    /* Linux: try DRM, then fbdev, then SDL2 */
    timer_init();
    clock_gettime(CLOCK_MONOTONIC, &lastTime);

    #ifdef USE_DRM_KMS
    struct GfxDevice* gd = NULL;
    gd = GFX_Initialize();
    if(gd != NULL)
    {
        printf("initialize DRM/KM Backend Success\n");

        LibInput_Initialize(gd->width, gd->height);

        #ifdef USE_CANVAS
        GFX_CANVAS_Initialize(&gd->gfxDriverInterface);

        if (leInitialize(&gfxCanvasDriverInterface, NULL) == LE_FAILURE) {
            GFX_DeInitalize();
            return;
        }
        #else
        if (leInitialize(&gd->gfxDriverInterface, NULL) == LE_FAILURE) {
            GFX_DeInitalize();
            return;
        }
        #endif
        legato_initializeScreenState();
        return;
    }
    #endif

    struct FBDevDevice* fbdev = NULL;
    fbdev = (struct FBDevDevice*) FBDev_Initialize();
    if(fbdev != NULL)
    {
        printf("initialize FBDev Backend Success\n");

        LibInput_Initialize(fbdev->width, fbdev->height);

        #ifdef USE_CANVAS
        GFX_CANVAS_Initialize(&fbdev->gfxDriverInterface);

        if (leInitialize(&gfxCanvasDriverInterface, NULL) == LE_FAILURE) {
            FBDev_DeInitalize();
            return;
        }
        #else
        if (leInitialize(&fbdev->gfxDriverInterface, NULL) == LE_FAILURE) {
            FBDev_DeInitalize();
            return;
        }
        #endif
        legato_initializeScreenState();
        return;
    }

    #ifdef USE_SDL2
    if(GFX_SDL2_Initialize())
    {
        printf("initialize SDL2 Backend Success\n");
        return;
    }
    #endif

    printf("initializing Display Backend Failed\n");
    exit(1);
#endif
}

void SYS_Tasks(void)
{
    static uint32_t lastTick = 0;
    uint32_t currentTick = getTickMs();
    dt = currentTick - lastTick;
    lastTick = currentTick;

#ifdef _WIN32
    /* Windows: SDL2 handles display and input */
    #ifdef USE_SDL2
    GFX_SDL2_Update();
    #endif
#else
    /* Linux */
    #ifdef USE_DRM_KMS
    GFX_Update();
    #endif

    #ifdef USE_CANVAS
    GFX_CANVAS_Task();
    #endif

    #ifdef USE_SDL2
    GFX_SDL2_Update();
    #else
    LibInput_Update();
    #endif
#endif

    leUpdate(dt);
    legato_updateScreenState();
}


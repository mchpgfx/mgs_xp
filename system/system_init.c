
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
#include <time.h>   /* Needed for struct timespec */

#include "gfx/legato/generated/le_gen_init.h"
#include "gfx/legato/legato.h"

#include "linux/timer/timer.h"

#ifdef USE_DRM_KMS
#include "linux/display/drm/drm_backend.h"
#endif

#include "linux/display/fbdev/fbdev_backend.h"

#ifdef USE_SDL2
#include "linux/display/sdl2/gfx_sdl2.h"
#endif

#ifdef USE_CANVAS
#include "gfx/canvas/gfx_canvas_api.h"
extern gfxDisplayDriver gfxCanvasDriverInterface;
#endif

#include "linux/input/libinput_backend.h"

#include "system_init.h"

int mssleep(long miliseconds)
{
   struct timespec rem;
   struct timespec req= {
       (int)(miliseconds / 1000),     /* secs (Must be Non-Negative) */ 
       (miliseconds % 1000) * 1000000 /* nano (Must be in range of 0 to 999999999) */ 
   };

   return nanosleep(&req , &rem);
}

void SYS_Initialize(__attribute__((unused)) void* data)
{
	timer_init();

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
    	    //ToDo Add drm device deinitialize
			GFX_DeInitalize();
    	    return;
    	}

#else
    	// initialize hardware layer
    	if (leInitialize(&gd->gfxDriverInterface, NULL) == LE_FAILURE) {
    	    //ToDo Add drm device deinitialize
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
    	    //ToDo Add drm device deinitialize
			FBDev_DeInitalize();
    	    return;
    	}

#else
    	// initialize hardware layer
    	if (leInitialize(&fbdev->gfxDriverInterface, NULL) == LE_FAILURE) {
    	    //ToDo Add drm device deinitialize
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
}

void SYS_Tasks(void)
{
#ifdef USE_DRM_KMS
	GFX_Update();
#endif

#ifdef USE_CANVAS
	GFX_CANVAS_Task();	
#endif

#if USE_SDL2
	GFX_SDL2_Update();
#else
	LibInput_Update();
#endif

	leUpdate(0);
	legato_updateScreenState();
}


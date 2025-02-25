/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_scrn_wq.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/
#include "gfx/legato/generated/le_gen_init.h"
#include "app_common.h"
#include "app_sys_timer.h"

#define CLOCK_TICK_TIMER_PERIOD_MS 50
#define ANIM_PERIOD_MS 500
#define MGS_LOGO_HIDEX -320
#define MGS_LOGO_SHOWX 46
#define MCHP_LOGO_HIDEX 316
#define MCHP_LOGO_SHOWX 52
#define EASE_COEFF 2
#define SPLASH_DELAY_MS 300
#define SPLASH_DURATION_MS 1000
#define ANIM_PERIOD_TICKS (ANIM_PERIOD_MS/CLOCK_TICK_TIMER_PERIOD_MS)

typedef enum
{
    APP_SPLASH_INIT,
    APP_SPLASH_WAIT_FOR_GUI,
    APP_SPLASH_ANIM_MGS,
    APP_SPLASH_ANIM_PAUSE,
    APP_SPLASH_ANIM_MCHP,
    APP_SPLASH_DONE,
    APP_SPLASH_EXIT,
} APP_SPLASH_STATES;

static APP_SPLASH_STATES appSplashState;
static volatile unsigned int tickCount = 0;
static volatile unsigned int animTickCount = 0;
uint32_t animTickCountLast = 0;
static SYS_TIME_HANDLE timer = SYS_TIME_HANDLE_INVALID;

static void APP_UI_Timer_Callback ( uintptr_t context)
{
    tickCount++;

    if (tickCount % ANIM_PERIOD_TICKS)
        animTickCount++;
}

void Screen_Splash_OnShow(void)
{
    if (get_direct_boot() == true)
    {
        appSplashState = APP_SPLASH_EXIT;
    }
    else
    {
        appSplashState = APP_SPLASH_INIT;

        APP_LE_SETX(Screen_Splash_MicrochipLogo, MCHP_LOGO_HIDEX);
        APP_LE_SETX(Screen_Splash_MGSLogo, MGS_LOGO_HIDEX);

        timer = SYS_TIME_CallbackRegisterMS(APP_UI_Timer_Callback,
                                            1,
                                            CLOCK_TICK_TIMER_PERIOD_MS,
                                            SYS_TIME_PERIODIC);
        SYS_TIME_TimerStart(timer);
    }
}

void Screen_Splash_OnHide(void){}

void Screen_Splash_OnUpdate(void)
{
    switch(appSplashState)
    {
        case APP_SPLASH_INIT:
        {
            appSplashState = APP_SPLASH_WAIT_FOR_GUI;
            SYS_TIME_DelayMS(SPLASH_DELAY_MS, &timer);
            
            break;
        }
        case APP_SPLASH_WAIT_FOR_GUI:
        {
            if (leIsDrawing() == LE_FALSE && SYS_TIME_DelayIsComplete(timer))
            {
                appSplashState = APP_SPLASH_ANIM_MGS;
            }
            
            break;
        }
        case APP_SPLASH_ANIM_MGS:
        {
            if (animTickCount != animTickCountLast)
            {
                int32_t xmgs = APP_LE_GETX(Screen_Splash_MGSLogo);
                int32_t xmchp = APP_LE_GETX(Screen_Splash_MicrochipLogo);

                int32_t deltax1 = (MGS_LOGO_SHOWX - xmgs) / EASE_COEFF;
                int32_t deltax2 = (MCHP_LOGO_SHOWX - xmchp) / EASE_COEFF;
                                
                if (deltax1 != 0)
                {
                    APP_LE_SETX(Screen_Splash_MGSLogo, xmgs + deltax1);
                }
                else
                {
                    APP_LE_SETX(Screen_Splash_MGSLogo, MGS_LOGO_SHOWX);
                }
                
                if (deltax2 != 0)
                {
                    APP_LE_SETX(Screen_Splash_MicrochipLogo, xmchp + deltax2);
                }
                else
                {
                    APP_LE_SETX(Screen_Splash_MicrochipLogo, MCHP_LOGO_SHOWX);
                }
                
                if (deltax1 == 0 && deltax2 == 0)
                {
                    appSplashState = APP_SPLASH_DONE;
                    SYS_TIME_DelayMS(SPLASH_DURATION_MS, &timer);
                }
                
                animTickCountLast = animTickCount;
            }
            
            break;
        }
        case APP_SPLASH_DONE:
        {
            if (SYS_TIME_DelayIsComplete(timer) == true)
            {         
                SYS_TIME_TimerStop(timer); 
                SYS_TIME_TimerDestroy(timer); 
            
                appSplashState = APP_SPLASH_EXIT;
            }
            
            break;
        }
        case APP_SPLASH_EXIT:
        {
            legato_showScreen(screenID_Screen_Main);
            
            break;
        }
        default:
        {
            break;
        }
    }    
}
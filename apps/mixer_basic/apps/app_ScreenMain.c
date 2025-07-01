/*******************************************************************************
  Application Source

  File Name:
    app_ScreenMain.c

  Summary:
    Application screen and widget callback code

  Description:
    Application screen and widget callback code
 *******************************************************************************/

//DOM-IGNORE-BEGIN
/*****************************************************************************
 Copyright (C) 2024 Microchip Technology Inc. and its subsidiaries.

Microchip Technology Inc. and its subsidiaries.

Subject to your compliance with these terms, you may use Microchip software 
and any derivatives exclusively with Microchip products. It is your 
responsibility to comply with third party license terms applicable to your 
use of third party software (including open source software) that may 
accompany Microchip software.

THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR 
PURPOSE.

IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE 
FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN 
ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, 
THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*****************************************************************************/
//DOM-IGNORE-END

#include <stdbool.h>

#include "gfx/legato/generated/screen/le_gen_screen_Main.h"

#include "app_ScreenMain.h"
#include "app_macros.h"
#include "app_audioIntf.h"

#define APP_SCRN_SET_EVENT(event)   if (event < APP_SCRN_EVT_MAX) \ 
                                    { appScreenEvents.eventFlag |= (1 << event); }

#define APP_SCRN_SET_EVENT_ID(event, id) \
                                    if (event < APP_SCRN_EVT_MAX) \ 
                                    { \
                                        appScreenEvents.eventFlag |= (1 << event); \
                                        appScreenEvents.eventParm[event].idx = id; \
                                    }

#define APP_SCRN_SET_EVENT_ID_VALUE(event, id, val) \
                                    if (event < APP_SCRN_EVT_MAX) \ 
                                    { \
                                        appScreenEvents.eventFlag |= (1 << event); \
                                        appScreenEvents.eventParm[event].idx = id; \
                                        appScreenEvents.eventParm[event].value = val; \
                                    }

#define APP_SCRN_CLEAR_EVENT(event) if (event < APP_SCRN_EVT_MAX) \ 
                                    { appScreenEvents.eventFlag &= ~(1 << event); }

#define MAIN_VOLKNOB_MAX_Y 420
#define MAIN_VOLKNOB_MIN_Y 150

#define INPUT_VOLKNOB_MAX_Y 360
#define INPUT_VOLKNOB_MIN_Y 141

typedef struct 
{
    bool enabled;
    unsigned int volume;
    bool cue;
    bool mute;
    bool solo;
} INPUT_IDX_STATE_t;

typedef struct
{
    bool enabled;
} OUTPUT_IDX_STATE_t;

typedef struct
{
    bool running;
    bool mute;
    unsigned int volume;
} MAIN_STATE_t;

typedef struct
{
    leButtonWidget ** enableButton;
    leButtonWidget ** cueButton;
    leButtonWidget ** muteButton;
    leButtonWidget ** soloButton;
    leImageWidget ** colorBar;
    leButtonWidget ** volumeKnob;
} INPUT_IDX_WIDGETS_t;

APP_SCRN_STATE_t App_ScreenIdleEventHandler(APP_SCRN_EVENT_TYPE_t event, APP_SCRN_EVENT_PARM_t parm);
APP_SCRN_STATE_t App_ScreenRunEventHandler(APP_SCRN_EVENT_TYPE_t event, APP_SCRN_EVENT_PARM_t parm);

static INPUT_IDX_WIDGETS_t appInputWidgets[APP_AUDIO_IDX_MAX] = 
{
    [0] = {

        .enableButton = &Main_btnInputCh1,
        .cueButton = &Main_btnCue,
        .muteButton = &Main_btnM,
        .soloButton = &Main_btnS,
        .colorBar = &Main_pnlColorBar,
        .volumeKnob = &Main_btnGainKnob,
    },

    [1] = {

        .enableButton = &Main_btnInputCh2,
        .cueButton = &Main_btnCue_2,
        .muteButton = &Main_btnM_2,
        .soloButton = &Main_btnS_2,
        .colorBar = &Main_pnlColorBar_2,
        .volumeKnob = &Main_btnGainKnob_2,
    },

    [2] = {

        .enableButton = &Main_btnInputCh3,
        .cueButton = &Main_btnCue_3,
        .muteButton = &Main_btnM_3,
        .soloButton = &Main_btnS_3,
        .colorBar = &Main_pnlColorBar_3,
        .volumeKnob = &Main_btnGainKnob_3,
    },

    [3] = {

        .enableButton = &Main_btnInputCh4,
        .cueButton = &Main_btnCue_4,
        .muteButton = &Main_btnM_4,
        .soloButton = &Main_btnS_4,
        .colorBar = &Main_pnlColorBar_4,
        .volumeKnob = &Main_btnGainKnob_4,
    },
};

static leButtonWidget **  appOutputWidgets[APP_AUDIO_IDX_MAX] = 
{
    &Main_btnOutputCh1,
    &Main_btnOutputCh2,
    &Main_btnOutputCh3,
    &Main_btnOutputCh4,
};

static APP_SCRN_STATE_t appScreenState;
static APP_SCRN_EVENTS_t appScreenEvents;

static INPUT_IDX_STATE_t appInputStates[APP_AUDIO_IDX_MAX];
static OUTPUT_IDX_STATE_t appOutputStates[APP_AUDIO_IDX_MAX];
static MAIN_STATE_t appMainState;

/* Touch event filters for pressure knob touch input */
/* Touch event filters to support manual pressure knob setting via touch */
static leBool Knob_filterEvent(leWidget* target, leWidgetEvent* evt, void* data)
{
    leBool retval = LE_FALSE;    
    lePoint pnt;
    
    pnt.x = ((leWidgetEvent_TouchDown *) evt)->x;
    pnt.y = ((leWidgetEvent_TouchDown *) evt)->y;      
    
    switch(evt->id)
    {
        case LE_EVENT_TOUCH_MOVE:         
        case LE_EVENT_TOUCH_DOWN:
        {
            uint32_t height = target->fn->getHeight(target);
            
            evt->accepted = LE_TRUE;
            evt->owner = target;
            
            if (target == (leWidget*) Main_btnMainGain)
            {
                unsigned int volume;

                pnt.y = pnt.y < MAIN_VOLKNOB_MIN_Y ? MAIN_VOLKNOB_MIN_Y : pnt.y;
                pnt.y = pnt.y > MAIN_VOLKNOB_MAX_Y ? MAIN_VOLKNOB_MAX_Y : pnt.y;

                volume = ((MAIN_VOLKNOB_MAX_Y - pnt.y) * 100) / (MAIN_VOLKNOB_MAX_Y - MAIN_VOLKNOB_MIN_Y);

                APP_LE_SETY(target, pnt.y - (height / 2));

                APP_SCRN_SET_EVENT_ID_VALUE(APP_SCRN_EVT_MAIN_VOLUME, 0, volume);
            }
            else
            {
                unsigned int volume;

                leUtils_PointScreenToLocalSpace(target->parent, &pnt);
                
                pnt.y = pnt.y < INPUT_VOLKNOB_MIN_Y ? INPUT_VOLKNOB_MIN_Y : pnt.y;
                pnt.y = pnt.y > INPUT_VOLKNOB_MAX_Y ? INPUT_VOLKNOB_MAX_Y : pnt.y;

                volume = ((MAIN_VOLKNOB_MAX_Y - pnt.y) * 100) / (MAIN_VOLKNOB_MAX_Y - MAIN_VOLKNOB_MIN_Y);
                
                APP_LE_SETY(target, pnt.y - (height / 2));

                if (target == (leWidget *) Main_btnGainKnob)
                {
                    APP_SCRN_SET_EVENT_ID_VALUE(APP_SCRN_EVT_INPUT_VOLUME, 0, volume);
                }
                else if (target == (leWidget *) Main_btnGainKnob_2)
                {
                    APP_SCRN_SET_EVENT_ID_VALUE(APP_SCRN_EVT_INPUT_VOLUME, 1, volume);
                }
                if (target == (leWidget *) Main_btnGainKnob_3)
                {
                    APP_SCRN_SET_EVENT_ID_VALUE(APP_SCRN_EVT_INPUT_VOLUME, 2, volume);
                }
                if (target == (leWidget *) Main_btnGainKnob_4)
                {
                    APP_SCRN_SET_EVENT_ID_VALUE(APP_SCRN_EVT_INPUT_VOLUME, 3, volume);
                }
            }
            
            retval = LE_TRUE;
            
            break;
        }   
        case LE_EVENT_TOUCH_UP:            
        {
            evt->accepted = LE_TRUE;
                    
            retval = LE_TRUE;

            break;        
        }
        default:
            break;
    }
    
   return retval;
}

static leWidgetEventFilter KnobArea_eventFilter =
{
    Knob_filterEvent,
    NULL
};

void Main_OnShow(void)
{

    /* Make sure # of events are within limit */
    static_assert(APP_SCRN_EVT_MAX <= APP_SCRN_EVT_LIMIT);

    appScreenState = APP_SCRN_INIT;

    APP_LE_SETEVENTFILTER(Main_btnGainKnob, KnobArea_eventFilter);
    APP_LE_SETEVENTFILTER(Main_btnGainKnob_2, KnobArea_eventFilter);
    APP_LE_SETEVENTFILTER(Main_btnGainKnob_3, KnobArea_eventFilter);
    APP_LE_SETEVENTFILTER(Main_btnGainKnob_4, KnobArea_eventFilter);
    
    APP_LE_SETEVENTFILTER(Main_btnMainGain, KnobArea_eventFilter);

    App_Reset_State();
    App_Screen_Update();
    App_Screen_SetMainVolKnob(VOLUME_DEFAULT_PCT);
}

void Main_OnHide(void)
{
    
}

void Main_OnUpdate(void)
{
    switch(appScreenState)
    {
        case APP_SCRN_INIT:
        {
            appScreenState = APP_SCRN_IDLE;
            break;
        }
        case APP_SCRN_IDLE:
        {
            //Handle events 
            unsigned int i;

            if (appScreenEvents.eventFlag != 0)
            {
                for (i = 0; i < APP_SCRN_EVT_MAX; i++)
                {
                    if (appScreenEvents.eventFlag & (1 << i))
                    {
                        appScreenState  = App_ScreenIdleEventHandler(i, appScreenEvents.eventParm[i]);

                        APP_SCRN_CLEAR_EVENT(i);
                    }
                }

                App_Screen_Update();

                appScreenEvents.eventFlag = 0;
            }

            break;
        }
        case APP_SCRN_RUN:
        {
            //Handle events 
            unsigned int i;

            if (appScreenEvents.eventFlag != 0)
            {
                for (i = 0; i < APP_SCRN_EVT_MAX; i++)
                {
                    if (appScreenEvents.eventFlag & (1 << i))
                    {
                        appScreenState = App_ScreenRunEventHandler(i, appScreenEvents.eventParm[i]);

                        APP_SCRN_CLEAR_EVENT(i);
                    }
                }

                App_Screen_Update();

                appScreenEvents.eventFlag = 0;
            }

            break;
        }
        case APP_SCRN_STOP:
        {
            appScreenState = APP_SCRN_IDLE;
            break;
        }
        default:
            break;
    }

}

void event_Main_btnInputCh1_OnReleased(leButtonWidget* btn)
{
    APP_SCRN_SET_EVENT_ID(APP_SCRN_EVT_INPUT_ENABLE, APP_AUDIO_IDX1);
}

void event_Main_btnInputCh2_OnReleased(leButtonWidget* btn)
{
    APP_SCRN_SET_EVENT_ID(APP_SCRN_EVT_INPUT_ENABLE, APP_AUDIO_IDX2);
}

void event_Main_btnInputCh3_OnReleased(leButtonWidget* btn)
{
    APP_SCRN_SET_EVENT_ID(APP_SCRN_EVT_INPUT_ENABLE, APP_AUDIO_IDX3);
}

void event_Main_btnInputCh4_OnReleased(leButtonWidget* btn)
{
    APP_SCRN_SET_EVENT_ID(APP_SCRN_EVT_INPUT_ENABLE, APP_AUDIO_IDX4);
}

void event_Main_btnRun_OnReleased(leButtonWidget* btn)
{
    APP_SCRN_SET_EVENT(APP_SCRN_EVT_RUN);
}

void event_Main_btnOutputCh1_OnReleased(leButtonWidget* btn)
{
    APP_SCRN_SET_EVENT_ID(APP_SCRN_EVT_OUTPUT_ENABLE, APP_AUDIO_IDX1);
}

void event_Main_btnOutputCh2_OnReleased(leButtonWidget* btn)
{
    APP_SCRN_SET_EVENT_ID(APP_SCRN_EVT_OUTPUT_ENABLE, APP_AUDIO_IDX2);
}

void event_Main_btnOutputCh3_OnReleased(leButtonWidget* btn)
{
    APP_SCRN_SET_EVENT_ID(APP_SCRN_EVT_OUTPUT_ENABLE, APP_AUDIO_IDX3);
}

void event_Main_btnOutputCh4_OnReleased(leButtonWidget* btn)
{
    APP_SCRN_SET_EVENT_ID(APP_SCRN_EVT_OUTPUT_ENABLE, APP_AUDIO_IDX4);
}

void event_Main_btnCue_4_OnReleased(leButtonWidget* btn)
{
    APP_SCRN_SET_EVENT_ID(APP_SCRN_EVT_INPUT_CUE, APP_AUDIO_IDX4);
}

void event_Main_btnM_4_OnReleased(leButtonWidget* btn)
{
    APP_SCRN_SET_EVENT_ID(APP_SCRN_EVT_INPUT_MUTE, APP_AUDIO_IDX4);
}

void event_Main_btnS_4_OnReleased(leButtonWidget* btn)
{
    APP_SCRN_SET_EVENT_ID(APP_SCRN_EVT_INPUT_SOLO, APP_AUDIO_IDX4);
}

void event_Main_btnCue_3_OnReleased(leButtonWidget* btn)
{
    APP_SCRN_SET_EVENT_ID(APP_SCRN_EVT_INPUT_CUE, APP_AUDIO_IDX3);
}

void event_Main_btnM_3_OnReleased(leButtonWidget* btn)
{
    APP_SCRN_SET_EVENT_ID(APP_SCRN_EVT_INPUT_MUTE, APP_AUDIO_IDX3);
}

void event_Main_btnS_3_OnReleased(leButtonWidget* btn)
{
    APP_SCRN_SET_EVENT_ID(APP_SCRN_EVT_INPUT_SOLO, APP_AUDIO_IDX3);
}

void event_Main_btnCue_2_OnReleased(leButtonWidget* btn)
{
    APP_SCRN_SET_EVENT_ID(APP_SCRN_EVT_INPUT_CUE, APP_AUDIO_IDX2);
}

void event_Main_btnM_2_OnReleased(leButtonWidget* btn)
{
    APP_SCRN_SET_EVENT_ID(APP_SCRN_EVT_INPUT_MUTE, APP_AUDIO_IDX2);
}

void event_Main_btnS_2_OnReleased(leButtonWidget* btn)
{
    APP_SCRN_SET_EVENT_ID(APP_SCRN_EVT_INPUT_SOLO, APP_AUDIO_IDX2);
}

void event_Main_btnCue_OnReleased(leButtonWidget* btn)
{
    APP_SCRN_SET_EVENT_ID(APP_SCRN_EVT_INPUT_CUE, APP_AUDIO_IDX1);
}

void event_Main_btnM_OnReleased(leButtonWidget* btn)
{
    APP_SCRN_SET_EVENT_ID(APP_SCRN_EVT_INPUT_MUTE, APP_AUDIO_IDX1);
}

void event_Main_btnS_OnReleased(leButtonWidget* btn)
{
    APP_SCRN_SET_EVENT_ID(APP_SCRN_EVT_INPUT_SOLO, APP_AUDIO_IDX1);
}

void event_Main_btnMainMute_OnReleased(leButtonWidget* btn)
{
    APP_SCRN_SET_EVENT(APP_SCRN_EVT_MAIN_MUTE);
}

void event_Main_btnReset_OnReleased(leButtonWidget* btn)
{
    APP_SCRN_SET_EVENT(APP_SCRN_EVT_RESET);
}

APP_SCRN_STATE_t App_ScreenRunEventHandler(APP_SCRN_EVENT_TYPE_t event, APP_SCRN_EVENT_PARM_t parm)
{
    APP_SCRN_STATE_t nextState = APP_SCRN_RUN;

    switch(event)
    {
        case APP_SCRN_EVT_INPUT_VOLUME:
        {
            if (App_AudioIntf_InputSetVol((APP_AUDIO_IDX_t) parm.idx, parm.value) == APP_AUDIO_INTF_SUCCESS)
            {
                appInputStates[parm.idx].volume = parm.value;
            }            
            
            break;
        }
        case APP_SCRN_EVT_INPUT_MUTE:
        {
            if (App_AudioIntf_InputMute((APP_AUDIO_IDX_t) parm.idx, !appInputStates[parm.idx].mute) == APP_AUDIO_INTF_SUCCESS)
            {
                appInputStates[parm.idx].mute = !appInputStates[parm.idx].mute;
            }

            break;
        }
        case APP_SCRN_EVT_INPUT_SOLO:
        {
            if (App_AudioIntf_InputSolo((APP_AUDIO_IDX_t) parm.idx, !appInputStates[parm.idx].solo) == APP_AUDIO_INTF_SUCCESS)
            {
                appInputStates[parm.idx].solo = !appInputStates[parm.idx].solo;
            }

            break;
        }
        case APP_SCRN_EVT_INPUT_CUE:
        {
            if (App_AudioIntf_InputCue((APP_AUDIO_IDX_t) parm.idx, !appInputStates[parm.idx].cue) == APP_AUDIO_INTF_SUCCESS)
            {
                appInputStates[parm.idx].cue = !appInputStates[parm.idx].cue;
            }            
            break;
        }
        case APP_SCRN_EVT_MAIN_VOLUME:
        {
            if (App_AudioIntf_MainSetVol(parm.value) == APP_AUDIO_INTF_SUCCESS)
            {
                appMainState.volume = parm.value;
            }  
            break;
        }
        case APP_SCRN_EVT_MAIN_MUTE:
        {
            if (App_AudioIntf_MainMute(!appMainState.mute) == APP_AUDIO_INTF_SUCCESS)
            {
                appMainState.mute = !appMainState.mute;
            }              
            break;
        }
        case APP_SCRN_EVT_RUN:
        {
            if (App_AudioIntf_MixerStop() == APP_AUDIO_INTF_SUCCESS)
            {
                appMainState.running = false;
                nextState = APP_SCRN_STOP;
            }
            break;
        }
        default:
            break;
    }

    return nextState;
}

APP_SCRN_STATE_t App_ScreenIdleEventHandler(APP_SCRN_EVENT_TYPE_t event, APP_SCRN_EVENT_PARM_t parm)
{
    APP_SCRN_STATE_t nextState = APP_SCRN_IDLE;

    switch(event)
    {
        case APP_SCRN_EVT_INPUT_ENABLE:
        {
            if (App_AudioIntf_InputEnable((APP_AUDIO_IDX_t) parm.idx, !appInputStates[parm.idx].enabled) == APP_AUDIO_INTF_SUCCESS)
            {
                appInputStates[parm.idx].enabled = !appInputStates[parm.idx].enabled;
            }
            break;
        }
        case APP_SCRN_EVT_INPUT_VOLUME:
        {
            if (App_AudioIntf_InputSetVol((APP_AUDIO_IDX_t) parm.idx, parm.value) == APP_AUDIO_INTF_SUCCESS)
            {
                appInputStates[parm.idx].volume = parm.value;
            }            
            
            break;
        }
        case APP_SCRN_EVT_INPUT_MUTE:
        {
            if (App_AudioIntf_InputMute((APP_AUDIO_IDX_t) parm.idx, !appInputStates[parm.idx].mute) == APP_AUDIO_INTF_SUCCESS)
            {
                appInputStates[parm.idx].mute = !appInputStates[parm.idx].mute;
            }

            break;
        }
        case APP_SCRN_EVT_INPUT_SOLO:
        {
            if (App_AudioIntf_InputSolo((APP_AUDIO_IDX_t) parm.idx, !appInputStates[parm.idx].solo) == APP_AUDIO_INTF_SUCCESS)
            {
                appInputStates[parm.idx].solo = !appInputStates[parm.idx].solo;
            }

            break;
        }
        case APP_SCRN_EVT_INPUT_CUE:
        {
            if (App_AudioIntf_InputCue((APP_AUDIO_IDX_t) parm.idx, !appInputStates[parm.idx].cue) == APP_AUDIO_INTF_SUCCESS)
            {
                appInputStates[parm.idx].cue = !appInputStates[parm.idx].cue;
            }            
            break;
        }
        case APP_SCRN_EVT_OUTPUT_ENABLE:
        {
            if (App_AudioIntf_OutputEnable((APP_AUDIO_IDX_t) parm.idx, !appOutputStates[parm.idx].enabled) == APP_AUDIO_INTF_SUCCESS)
            {
                appOutputStates[parm.idx].enabled = !appOutputStates[parm.idx].enabled;
            }            
    
            break;
        }
        case APP_SCRN_EVT_MAIN_VOLUME:
        {
            if (App_AudioIntf_MainSetVol(parm.value) == APP_AUDIO_INTF_SUCCESS)
            {
                appMainState.volume = parm.value;
            }  
            break;
        }
        case APP_SCRN_EVT_MAIN_MUTE:
        {
            if (App_AudioIntf_MainMute(!appMainState.mute) == APP_AUDIO_INTF_SUCCESS)
            {
                appMainState.mute = !appMainState.mute;
            }              
            break;
        }
        case APP_SCRN_EVT_RUN:
        {
            if (App_AudioIntf_MixerRun() == APP_AUDIO_INTF_SUCCESS)
            {
                appMainState.running = true;
                nextState = APP_SCRN_RUN;
            }
            break;
        }
        case APP_SCRN_EVT_RESET:
        {
            App_AudioIntf_Reset();
            App_Reset_State();
            break;
        }
        default:
            break;
    }

    return nextState;
}

void App_Screen_SetMainVolKnob(unsigned int volume)
{
    lePoint pos;
    
    if (volume <= 100)
    {
        uint32_t height = Main_btnMainGain->fn->getHeight(Main_btnMainGain);

        pos.y = MAIN_VOLKNOB_MAX_Y - ((volume * (MAIN_VOLKNOB_MAX_Y - MAIN_VOLKNOB_MIN_Y)) / 100);

        pos.y -= height / 2;

        Main_btnMainGain->fn->setY(Main_btnMainGain, pos.y);
    }
}

void App_Screen_SetInputVolKnob(APP_AUDIO_IDX_t idx, unsigned int volume)
{
    lePoint pos;
    
    if (idx < APP_AUDIO_IDX_MAX && volume <= 100)
    {
        uint32_t height = (*(appInputWidgets[idx].volumeKnob))->fn->getHeight(*(appInputWidgets[idx].volumeKnob));

        pos.y = INPUT_VOLKNOB_MAX_Y - ((volume * (INPUT_VOLKNOB_MAX_Y - INPUT_VOLKNOB_MIN_Y)) / 100);

        pos.y -= height / 2;

        (*(appInputWidgets[idx].volumeKnob))->fn->setY((*(appInputWidgets[idx].volumeKnob)), pos.y);
    }
}

void App_Screen_Update(void)
{
    unsigned int i;
    leImage * image;
    leScheme * scheme;
    leWidget * widget;       

    for (i = 0; i < APP_AUDIO_IDX_MAX; i++)
    {
        /* Update enable button and color bar */
        if (appInputStates[i].enabled == true)
        {
            (*(appInputWidgets[i].enableButton))->fn->setReleasedImage((*(appInputWidgets[i].enableButton)), (leImage *) &Button1Down);    
            
            scheme = (appInputStates[i].mute == true) ? &RedScheme : &GreenScheme;
            
            widget = *(appInputWidgets[i].colorBar);
            widget->fn->setScheme(widget, scheme);

        }
        else
        {
            (*(appInputWidgets[i].enableButton))->fn->setReleasedImage((*(appInputWidgets[i].enableButton)), (leImage *) &Button1Up);
            
            scheme = (appInputStates[i].mute == true) ? &RedScheme : &GrayScheme;

            widget = *(appInputWidgets[i].colorBar);
            widget->fn->setScheme(widget, scheme);

            // (*(appInputWidgets[i].colorBar))->fn->setScheme((*(appInputWidgets[i].colorBar)), scheme);
        }

        /* Update Input mute button */
        image = (appInputStates[i].mute == true) ? &Small2ButtonDown : &Small2ButtonUp;
        (*(appInputWidgets[i].muteButton))->fn->setReleasedImage((*(appInputWidgets[i].muteButton)), image);    

        /* Update Input cue buttons */
        image = (appInputStates[i].cue == true) ? &SmallButtonDown : &SmallButtonUp;
        (*(appInputWidgets[i].cueButton))->fn->setReleasedImage((*(appInputWidgets[i].cueButton)), image);

        /* Update Input solo buttons */
        image = (appInputStates[i].solo == true) ? &Small2ButtonDown : &Small2ButtonUp;
        (*(appInputWidgets[i].soloButton))->fn->setReleasedImage((*(appInputWidgets[i].soloButton)), image);     

        /* Update volume knob */
        // App_Screen_SetInputVolKnob(i, appInputStates[i].volume);

        /* Update Output buttons */
        image = (appOutputStates[i].enabled == true) ? &Button3Down : &Button3Up;
        (*(appOutputWidgets[i]))->fn->setReleasedImage((*(appOutputWidgets[i])), image);
    }

    /* Update Main Control */
    /* Update Main volume */
    // App_Screen_SetMainVolKnob(appMainState.volume);
    
    /* Update enable button and color bar */
    if (appMainState.running== true)
    {
        Main_btnRun->fn->setReleasedImage(Main_btnRun, (leImage *) &Button2Down);    
        Main_btnRun->fn->setString(Main_btnRun, (leString*)&string_StringStop);

        Main_btnRun->fn->setScheme(Main_btnRun, (leScheme*) &RedScheme);
        
        scheme = (appMainState.mute == true) ? &RedScheme : &GreenScheme;
        Main_pnlColorBarMain->fn->setScheme(Main_pnlColorBarMain, scheme);
    }
    else
    {
        Main_btnRun->fn->setReleasedImage(Main_btnRun, (leImage *) &Button2Up);    
        Main_btnRun->fn->setString(Main_btnRun, (leString*)&string_StringRun);
        Main_btnRun->fn->setScheme(Main_btnRun, (leScheme*) &WhiteTextScheme);
        
        scheme = (appMainState.mute == true) ? &RedScheme : &GrayScheme;
        Main_pnlColorBarMain->fn->setScheme(Main_pnlColorBarMain, scheme);
    }

    /* Update Input mute button */
    image = (appMainState.mute  == true) ? &SmallButtonDown : &SmallButtonUp;
    Main_btnMainMute->fn->setReleasedImage(Main_btnMainMute, image);        

}

void App_Reset_State(void)
{
    unsigned int i;

    for (i = 0; i < APP_AUDIO_IDX_MAX; i++)
    {
        appInputStates[i].volume = VOLUME_DEFAULT_PCT;
        appInputStates[i].cue = false;
        appInputStates[i].enabled = false;
        appInputStates[i].mute = false;
        appInputStates[i].solo = false;

        appOutputStates[i].enabled = false;
    }

    appMainState.running = false;
    appMainState.volume = VOLUME_DEFAULT_PCT;
    appMainState.mute = false;
}


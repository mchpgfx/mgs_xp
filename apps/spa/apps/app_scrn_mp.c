/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_scrn_mp.c

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

static bool curLightTheme = true;
static void update_theme();

static leBool VolumePanel_filterEvent(leWidget* target, leWidgetEvent* evt, void* data);
static leWidgetEventFilter VolumePanel_eventFilter =
{
    VolumePanel_filterEvent,
    NULL
};

void Screen_Music_Player_OnShow(void)
{
    curLightTheme = true;
    update_theme();
    
    Screen_Music_Player_ButtonWidget_Back->fn->setCornerRadius(Screen_Music_Player_ButtonWidget_Back, DEFAULT_BTN_CORNER_RADIUS);
    Screen_Music_Player_ButtonWidget_SearchBT->fn->setCornerRadius(Screen_Music_Player_ButtonWidget_SearchBT, DEFAULT_BTN_CORNER_RADIUS);
    Screen_Music_Player_ButtonWidget_BT1->fn->setCornerRadius(Screen_Music_Player_ButtonWidget_BT1, DEFAULT_BTN_CORNER_RADIUS);
    Screen_Music_Player_ButtonWidget_BT2->fn->setCornerRadius(Screen_Music_Player_ButtonWidget_BT2, DEFAULT_BTN_CORNER_RADIUS);
    Screen_Music_Player_ButtonWidget_BT3->fn->setCornerRadius(Screen_Music_Player_ButtonWidget_BT3, DEFAULT_BTN_CORNER_RADIUS);
    
    Screen_Music_Player_PanelWidget_VolLight->fn->setCornerRadius(Screen_Music_Player_PanelWidget_VolLight, 2);
    Screen_Music_Player_PanelWidget_VolDark->fn->setCornerRadius(Screen_Music_Player_PanelWidget_VolDark, 2);
    
    if (get_music_playing())
    {
        Screen_Music_Player_ButtonWidget_PlayPause->fn->setPressed(Screen_Music_Player_ButtonWidget_PlayPause, LE_TRUE);
    }
    
    Screen_Music_Player_PanelWidget_Vol->fn->installEventFilter(Screen_Music_Player_PanelWidget_Vol, VolumePanel_eventFilter);
    
    int32_t volBarPos = get_music_volume_coord_musics();
    if (volBarPos < 5)
    {
        APP_LE_SETVISIBLE(Screen_Music_Player_PanelWidget_VolDark, LE_FALSE);
    }
    else
    {
        Screen_Music_Player_PanelWidget_VolDark->fn->setWidth(Screen_Music_Player_PanelWidget_VolDark, volBarPos);
    }
}

void Screen_Music_Player_OnHide(void)
{
    Screen_Music_Player_PanelWidget_Vol->fn->removeEventFilter(Screen_Music_Player_PanelWidget_Vol, VolumePanel_eventFilter);
}

void Screen_Music_Player_OnUpdate(void)
{
}

void event_Screen_Music_Player_ButtonWidget_Back_OnReleased(leButtonWidget* btn)
{
    legato_showScreen(screenID_Screen_Main);
}

void event_Screen_Music_Player_ButtonWidget_SearchBT_OnPressed(leButtonWidget* btn)
{
    Screen_Music_Player_ButtonWidget_SearchBT->fn->setBorderType(Screen_Music_Player_ButtonWidget_SearchBT, LE_WIDGET_BORDER_LINE);
}
void event_Screen_Music_Player_ButtonWidget_SearchBT_OnReleased(leButtonWidget* btn)
{
    Screen_Music_Player_ButtonWidget_SearchBT->fn->setBorderType(Screen_Music_Player_ButtonWidget_SearchBT, LE_WIDGET_BORDER_NONE);
}

static leBool VolumePanel_filterEvent(leWidget* target, leWidgetEvent* evt, void* data)
{    
    leBool retval = LE_FALSE;
    int32_t x;
    
    switch(evt->id)
    {
        case LE_EVENT_TOUCH_DOWN:
        {
            // Need to take into account parent widget position and volume bar offset
            x = ((leWidgetEvent_TouchDown *) evt)->x - VOL_MUSIC_PANEL_X_OFFSET - VOL_MUSIC_PANEL_OFFSET;
            // need to compare the X coordinate with the panel X coordinate and the volume bar maximum width
            if (x >= Screen_Music_Player_PanelWidget_Vol->fn->getX(Screen_Music_Player_PanelWidget_Vol) &&
                x <= Screen_Music_Player_PanelWidget_Vol->fn->getX(Screen_Music_Player_PanelWidget_Vol) + Screen_Music_Player_PanelWidget_VolLight->fn->getWidth(Screen_Music_Player_PanelWidget_VolLight))
            {
                x = x - Screen_Music_Player_PanelWidget_Vol->fn->getX(Screen_Music_Player_PanelWidget_Vol);

                //Below bug does not reproduce on a simple project           
                if(x < 5)  //Workaround to fix issue with width 4 or smaller that will end up in error handler
                {
                    APP_LE_SETVISIBLE(Screen_Music_Player_PanelWidget_VolDark, LE_FALSE);
                }
                else
                {
                    if (APP_LE_GETVISIBLE(Screen_Music_Player_PanelWidget_VolDark) == LE_FALSE)
                    {
                        APP_LE_SETVISIBLE(Screen_Music_Player_PanelWidget_VolDark, LE_TRUE);
                    }
                    Screen_Music_Player_PanelWidget_VolDark->fn->setWidth(Screen_Music_Player_PanelWidget_VolDark, x);
                }
                set_music_volume_from_musics(x);    
            }
            
            evt->accepted = LE_TRUE;
            evt->owner = target;
            
            retval = LE_TRUE;
            
            break;
        }   
        case LE_EVENT_TOUCH_MOVE:            
        {
            x = ((leWidgetEvent_TouchMove *) evt)->x - VOL_MUSIC_PANEL_X_OFFSET - VOL_MUSIC_PANEL_OFFSET; 
            if (x >= Screen_Music_Player_PanelWidget_Vol->fn->getX(Screen_Music_Player_PanelWidget_Vol) &&
                x <= Screen_Music_Player_PanelWidget_Vol->fn->getX(Screen_Music_Player_PanelWidget_Vol) + Screen_Music_Player_PanelWidget_VolLight->fn->getWidth(Screen_Music_Player_PanelWidget_VolLight))
            {
                x = x - Screen_Music_Player_PanelWidget_Vol->fn->getX(Screen_Music_Player_PanelWidget_Vol);

                //Below bug does not reproduce on a simple project
                if(x < 5)  //Workaround to fix issue with width 4 or smaller that will end up in error handler
                {
                    APP_LE_SETVISIBLE(Screen_Music_Player_PanelWidget_VolDark, LE_FALSE);
                }
                else
                {
                    if (APP_LE_GETVISIBLE(Screen_Music_Player_PanelWidget_VolDark) == LE_FALSE)
                    {
                        APP_LE_SETVISIBLE(Screen_Music_Player_PanelWidget_VolDark, LE_TRUE);
                    }
                    Screen_Music_Player_PanelWidget_VolDark->fn->setWidth(Screen_Music_Player_PanelWidget_VolDark, x);
                }
                set_music_volume_from_musics(x);
            }
            
            evt->accepted = LE_TRUE;
            
            retval = LE_TRUE;
           
            break;
        }
        default:
            break;
    }
    
   return retval;
}

void event_Screen_Music_Player_ButtonWidget_Prev_OnReleased(leButtonWidget* btn){}
void event_Screen_Music_Player_ButtonWidget_Next_OnReleased(leButtonWidget* btn){}
void event_Screen_Music_Player_ButtonWidget_PlayPause_OnPressed(leButtonWidget* btn)
{
    Screen_Music_Player_ImageWidget_2_0->fn->setVisible(Screen_Music_Player_ImageWidget_2_0, LE_FALSE);
    set_music_playing(true);
}
void event_Screen_Music_Player_ButtonWidget_PlayPause_OnReleased(leButtonWidget* btn)
{
    Screen_Music_Player_ImageWidget_2_0->fn->setVisible(Screen_Music_Player_ImageWidget_2_0, LE_TRUE);
    set_music_playing(false);
}

static void update_theme()
{
    if (get_light_theme() != curLightTheme)
    {
        curLightTheme = get_light_theme();
        if (curLightTheme)
        {
            //set to light theme
            Screen_Music_Player_Panel_0->fn->setScheme(Screen_Music_Player_Panel_0, &EditPanel);
            Screen_Music_Player_ImageWidget_0->fn->setImage(Screen_Music_Player_ImageWidget_0, (leImage*)&vertical_line);
            Screen_Music_Player_ImageWidget_selBT->fn->setImage(Screen_Music_Player_ImageWidget_selBT, (leImage*)&lee_iphone);
            Screen_Music_Player_ImageWidget_2_0->fn->setImage(Screen_Music_Player_ImageWidget_2_0, (leImage*)&check_small);
            Screen_Music_Player_ButtonWidget_SearchBT->fn->setPressedImage(Screen_Music_Player_ButtonWidget_SearchBT, (leImage*)&wifi_scan);
            Screen_Music_Player_ButtonWidget_SearchBT->fn->setReleasedImage(Screen_Music_Player_ButtonWidget_SearchBT, (leImage*)&wifi_scan);

            Screen_Music_Player_ButtonWidget_BT1->fn->setPressedImage(Screen_Music_Player_ButtonWidget_BT1, (leImage*)&phone_iphone);
            Screen_Music_Player_ButtonWidget_BT1->fn->setReleasedImage(Screen_Music_Player_ButtonWidget_BT1, (leImage*)&phone_iphone);
            Screen_Music_Player_ButtonWidget_BT2->fn->setPressedImage(Screen_Music_Player_ButtonWidget_BT2, (leImage*)&phone_iphone);
            Screen_Music_Player_ButtonWidget_BT2->fn->setReleasedImage(Screen_Music_Player_ButtonWidget_BT2, (leImage*)&phone_iphone);
            Screen_Music_Player_ButtonWidget_BT3->fn->setPressedImage(Screen_Music_Player_ButtonWidget_BT3, (leImage*)&phone_iphone);
            Screen_Music_Player_ButtonWidget_BT3->fn->setReleasedImage(Screen_Music_Player_ButtonWidget_BT3, (leImage*)&phone_iphone);

            Screen_Music_Player_ImageWidget_Volume->fn->setImage(Screen_Music_Player_ImageWidget_Volume, (leImage*)&volume_16x16);
            Screen_Music_Player_ButtonWidget_Prev->fn->setPressedImage(Screen_Music_Player_ButtonWidget_Prev, (leImage*)&skip_previous_48x48);
            Screen_Music_Player_ButtonWidget_Prev->fn->setReleasedImage(Screen_Music_Player_ButtonWidget_Prev, (leImage*)&skip_previous_48x48);
            Screen_Music_Player_ButtonWidget_PlayPause->fn->setPressedImage(Screen_Music_Player_ButtonWidget_PlayPause, (leImage*)&play_circle_48x48);
            Screen_Music_Player_ButtonWidget_PlayPause->fn->setReleasedImage(Screen_Music_Player_ButtonWidget_PlayPause, (leImage*)&pause_circle_48x48);
            Screen_Music_Player_ButtonWidget_Next->fn->setPressedImage(Screen_Music_Player_ButtonWidget_Next, (leImage*)&skip_next_48x48);
            Screen_Music_Player_ButtonWidget_Next->fn->setReleasedImage(Screen_Music_Player_ButtonWidget_Next, (leImage*)&skip_next_48x48);

            Screen_Music_Player_ButtonWidget_Back->fn->setPressedImage(Screen_Music_Player_ButtonWidget_Back, (leImage*)&reply);
            Screen_Music_Player_ButtonWidget_Back->fn->setReleasedImage(Screen_Music_Player_ButtonWidget_Back, (leImage*)&reply);

            Screen_Music_Player_LabelWidget_0->fn->setScheme(Screen_Music_Player_LabelWidget_0, &Scheme_Light);
            Screen_Music_Player_LabelWidget_2->fn->setScheme(Screen_Music_Player_LabelWidget_2, &Scheme_Light);
            Screen_Music_Player_LabelWidget_3->fn->setScheme(Screen_Music_Player_LabelWidget_3, &Scheme_Light);
            Screen_Music_Player_ButtonWidget_SearchBT->fn->setScheme(Screen_Music_Player_ButtonWidget_SearchBT, &Scheme_Light);
            Screen_Music_Player_ButtonWidget_BT1->fn->setScheme(Screen_Music_Player_ButtonWidget_BT1, &Scheme_Light);
            Screen_Music_Player_ButtonWidget_BT2->fn->setScheme(Screen_Music_Player_ButtonWidget_BT2, &Scheme_Light);
            Screen_Music_Player_ButtonWidget_BT3->fn->setScheme(Screen_Music_Player_ButtonWidget_BT3, &Scheme_Light);
            Screen_Music_Player_LabelWidget_ST->fn->setScheme(Screen_Music_Player_LabelWidget_ST, &Scheme_Light);
            Screen_Music_Player_LabelWidget_AN->fn->setScheme(Screen_Music_Player_LabelWidget_AN, &Scheme_Light);
            Screen_Music_Player_ButtonWidget_Back->fn->setScheme(Screen_Music_Player_ButtonWidget_Back, &Scheme_Light);
            Screen_Music_Player_PanelWidget_VolLight->fn->setScheme(Screen_Music_Player_PanelWidget_VolLight, &SliderLightScheme);
            Screen_Music_Player_PanelWidget_VolDark->fn->setScheme(Screen_Music_Player_PanelWidget_VolDark, &SliderDarkScheme);
        }
        else
        {
            //set to dark theme
            Screen_Music_Player_Panel_0->fn->setScheme(Screen_Music_Player_Panel_0, &EditPanel_Dark);
            Screen_Music_Player_ImageWidget_0->fn->setImage(Screen_Music_Player_ImageWidget_0, (leImage*)&vertical_line_dark);
            Screen_Music_Player_ImageWidget_selBT->fn->setImage(Screen_Music_Player_ImageWidget_selBT, (leImage*)&lee_iphone_dark);
            Screen_Music_Player_ImageWidget_2_0->fn->setImage(Screen_Music_Player_ImageWidget_2_0, (leImage*)&check_small_dark);
            Screen_Music_Player_ButtonWidget_SearchBT->fn->setPressedImage(Screen_Music_Player_ButtonWidget_SearchBT, (leImage*)&wifi_scan_dark);
            Screen_Music_Player_ButtonWidget_SearchBT->fn->setReleasedImage(Screen_Music_Player_ButtonWidget_SearchBT, (leImage*)&wifi_scan_dark);

            Screen_Music_Player_ButtonWidget_BT1->fn->setPressedImage(Screen_Music_Player_ButtonWidget_BT1, (leImage*)&phone_iphone_dark);
            Screen_Music_Player_ButtonWidget_BT1->fn->setReleasedImage(Screen_Music_Player_ButtonWidget_BT1, (leImage*)&phone_iphone_dark);
            Screen_Music_Player_ButtonWidget_BT2->fn->setPressedImage(Screen_Music_Player_ButtonWidget_BT2, (leImage*)&phone_iphone_dark);
            Screen_Music_Player_ButtonWidget_BT2->fn->setReleasedImage(Screen_Music_Player_ButtonWidget_BT2, (leImage*)&phone_iphone_dark);
            Screen_Music_Player_ButtonWidget_BT3->fn->setPressedImage(Screen_Music_Player_ButtonWidget_BT3, (leImage*)&phone_iphone_dark);
            Screen_Music_Player_ButtonWidget_BT3->fn->setReleasedImage(Screen_Music_Player_ButtonWidget_BT3, (leImage*)&phone_iphone_dark);

            Screen_Music_Player_ImageWidget_Volume->fn->setImage(Screen_Music_Player_ImageWidget_Volume, (leImage*)&volume_16x16_dark);
            Screen_Music_Player_ButtonWidget_Prev->fn->setPressedImage(Screen_Music_Player_ButtonWidget_Prev, (leImage*)&skip_previous_48x48_dark);
            Screen_Music_Player_ButtonWidget_Prev->fn->setReleasedImage(Screen_Music_Player_ButtonWidget_Prev, (leImage*)&skip_previous_48x48_dark);
            Screen_Music_Player_ButtonWidget_PlayPause->fn->setPressedImage(Screen_Music_Player_ButtonWidget_PlayPause, (leImage*)&play_circle_48x48_dark);
            Screen_Music_Player_ButtonWidget_PlayPause->fn->setReleasedImage(Screen_Music_Player_ButtonWidget_PlayPause, (leImage*)&pause_circle_48x48_dark);
            Screen_Music_Player_ButtonWidget_Next->fn->setPressedImage(Screen_Music_Player_ButtonWidget_Next, (leImage*)&skip_next_48x48_dark);
            Screen_Music_Player_ButtonWidget_Next->fn->setReleasedImage(Screen_Music_Player_ButtonWidget_Next, (leImage*)&skip_next_48x48_dark);

            Screen_Music_Player_ButtonWidget_Back->fn->setPressedImage(Screen_Music_Player_ButtonWidget_Back, (leImage*)&reply_dark);
            Screen_Music_Player_ButtonWidget_Back->fn->setReleasedImage(Screen_Music_Player_ButtonWidget_Back, (leImage*)&reply_dark);

            Screen_Music_Player_LabelWidget_0->fn->setScheme(Screen_Music_Player_LabelWidget_0, &Scheme_Dark);
            Screen_Music_Player_LabelWidget_2->fn->setScheme(Screen_Music_Player_LabelWidget_2, &Scheme_Dark);
            Screen_Music_Player_LabelWidget_3->fn->setScheme(Screen_Music_Player_LabelWidget_3, &Scheme_Dark);
            Screen_Music_Player_ButtonWidget_SearchBT->fn->setScheme(Screen_Music_Player_ButtonWidget_SearchBT, &Scheme_Dark);
            Screen_Music_Player_ButtonWidget_BT1->fn->setScheme(Screen_Music_Player_ButtonWidget_BT1, &Scheme_Dark);
            Screen_Music_Player_ButtonWidget_BT2->fn->setScheme(Screen_Music_Player_ButtonWidget_BT2, &Scheme_Dark);
            Screen_Music_Player_ButtonWidget_BT3->fn->setScheme(Screen_Music_Player_ButtonWidget_BT3, &Scheme_Dark);
            Screen_Music_Player_LabelWidget_ST->fn->setScheme(Screen_Music_Player_LabelWidget_ST, &Scheme_Dark);
            Screen_Music_Player_LabelWidget_AN->fn->setScheme(Screen_Music_Player_LabelWidget_AN, &Scheme_Dark);
            Screen_Music_Player_ButtonWidget_Back->fn->setScheme(Screen_Music_Player_ButtonWidget_Back, &Scheme_Dark);
            Screen_Music_Player_PanelWidget_VolLight->fn->setScheme(Screen_Music_Player_PanelWidget_VolLight, &SliderLightScheme_Dark);
            Screen_Music_Player_PanelWidget_VolDark->fn->setScheme(Screen_Music_Player_PanelWidget_VolDark, &SliderDarkScheme_Dark);
        }        
    }
}
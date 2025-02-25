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

static char cStrBuff[MAX_CSTR_STR_SIZE];
static leDynamicString *appAutoOnStr;
static leDynamicString *appAutoOffStr;
static bool lastACCState;

static bool curLightTheme = true;
static void update_theme();

void Screen_Water_Q_OnShow(void)
{
    bool autoClean = get_auto_clean_setting();
    lastACCState = autoClean;
    curLightTheme = true;
    
    update_theme();
    
    Screen_Water_Q_ButtonWidget_Back->fn->setCornerRadius(Screen_Water_Q_ButtonWidget_Back, DEFAULT_BTN_CORNER_RADIUS);
    Screen_Water_Q_ButtonWidget_StartCC->fn->setCornerRadius(Screen_Water_Q_ButtonWidget_StartCC, DEFAULT_BTN_CORNER_RADIUS);
    Screen_Water_Q_ButtonWidget_ACCOff->fn->setCornerRadius(Screen_Water_Q_ButtonWidget_ACCOff, DEFAULT_BTN_CORNER_RADIUS);
    Screen_Water_Q_ButtonWidget_ACCOn->fn->setCornerRadius(Screen_Water_Q_ButtonWidget_ACCOn, DEFAULT_BTN_CORNER_RADIUS);
    Screen_Water_Q_ButtonWidget_RstFilterClean->fn->setCornerRadius(Screen_Water_Q_ButtonWidget_RstFilterClean, DEFAULT_BTN_CORNER_RADIUS);
    Screen_Water_Q_ButtonWidget_RstWatChg->fn->setCornerRadius(Screen_Water_Q_ButtonWidget_RstWatChg, DEFAULT_BTN_CORNER_RADIUS);
    
    /* Allocate and initialize Dynamic String */
    appAutoOnStr = leDynamicString_New();
    appAutoOffStr = leDynamicString_New();
    if (autoClean == true)
    {
        appAutoOnStr->fn->setFont(appAutoOnStr, (leFont*) &InterBold12);
        appAutoOffStr->fn->setFont(appAutoOffStr, (leFont*) &InterRegular12);
        Screen_Water_Q_ButtonWidget_ACCOn->fn->setBorderType(Screen_Water_Q_ButtonWidget_ACCOn, LE_WIDGET_BORDER_LINE);
        Screen_Water_Q_ButtonWidget_ACCOff->fn->setBorderType(Screen_Water_Q_ButtonWidget_ACCOff, LE_WIDGET_BORDER_NONE);
    }
    else
    {
        appAutoOnStr->fn->setFont(appAutoOnStr, (leFont*) &InterRegular12); 
        appAutoOffStr->fn->setFont(appAutoOffStr, (leFont*) &InterBold12);
        Screen_Water_Q_ButtonWidget_ACCOn->fn->setBorderType(Screen_Water_Q_ButtonWidget_ACCOn, LE_WIDGET_BORDER_NONE);
        Screen_Water_Q_ButtonWidget_ACCOff->fn->setBorderType(Screen_Water_Q_ButtonWidget_ACCOff, LE_WIDGET_BORDER_LINE);
    }
    sprintf(cStrBuff, "On");
    appAutoOnStr->fn->setFromCStr(appAutoOnStr, cStrBuff);
    Screen_Water_Q_ButtonWidget_ACCOn->fn->setString(Screen_Water_Q_ButtonWidget_ACCOn, (leString *) appAutoOnStr);
    sprintf(cStrBuff, "Off");
    appAutoOffStr->fn->setFromCStr(appAutoOffStr, cStrBuff);
    Screen_Water_Q_ButtonWidget_ACCOff->fn->setString(Screen_Water_Q_ButtonWidget_ACCOff, (leString *) appAutoOffStr);

    Screen_Water_Q_ButtonWidget_ACCOn->fn->invalidate(Screen_Water_Q_ButtonWidget_ACCOn);
    Screen_Water_Q_ButtonWidget_ACCOff->fn->invalidate(Screen_Water_Q_ButtonWidget_ACCOff);
}

void Screen_Water_Q_OnHide(void)
{
    leString_Delete((leString *) appAutoOnStr);
    leString_Delete((leString *) appAutoOffStr);
}

void Screen_Water_Q_OnUpdate(void)
{
    bool autoClean = get_auto_clean_setting();
    
    if (autoClean != lastACCState)
    {
        lastACCState = autoClean;
        if (autoClean == true)
        {
            appAutoOnStr->fn->setFont(appAutoOnStr, (leFont*) &InterBold12);
            appAutoOffStr->fn->setFont(appAutoOffStr, (leFont*) &InterRegular12);
            Screen_Water_Q_ButtonWidget_ACCOn->fn->setBorderType(Screen_Water_Q_ButtonWidget_ACCOn, LE_WIDGET_BORDER_LINE);
            Screen_Water_Q_ButtonWidget_ACCOff->fn->setBorderType(Screen_Water_Q_ButtonWidget_ACCOff, LE_WIDGET_BORDER_NONE);
        }
        else
        {
            appAutoOnStr->fn->setFont(appAutoOnStr, (leFont*) &InterRegular12); 
            appAutoOffStr->fn->setFont(appAutoOffStr, (leFont*) &InterBold12);
            Screen_Water_Q_ButtonWidget_ACCOn->fn->setBorderType(Screen_Water_Q_ButtonWidget_ACCOn, LE_WIDGET_BORDER_NONE);
            Screen_Water_Q_ButtonWidget_ACCOff->fn->setBorderType(Screen_Water_Q_ButtonWidget_ACCOff, LE_WIDGET_BORDER_LINE);
        }
        Screen_Water_Q_ButtonWidget_ACCOn->fn->invalidate(Screen_Water_Q_ButtonWidget_ACCOn);
        Screen_Water_Q_ButtonWidget_ACCOff->fn->invalidate(Screen_Water_Q_ButtonWidget_ACCOff);
    }
}

void event_Screen_Water_Q_ButtonWidget_Back_OnReleased(leButtonWidget* btn)
{
    legato_showScreen(screenID_Screen_Main);
}

void event_Screen_Water_Q_ButtonWidget_ACCOff_OnReleased(leButtonWidget* btn)
{
    set_auto_clean_setting(false);
}
void event_Screen_Water_Q_ButtonWidget_ACCOn_OnReleased(leButtonWidget* btn)
{
    set_auto_clean_setting(true);
}

void event_Screen_Water_Q_ButtonWidget_StartCC_OnReleased(leButtonWidget* btn){}
void event_Screen_Water_Q_ButtonWidget_RstFilterClean_OnReleased(leButtonWidget* btn){}
void event_Screen_Water_Q_ButtonWidget_RstWatChg_OnReleased(leButtonWidget* btn){}

static void update_theme()
{
    if (get_light_theme() != curLightTheme)
    {
        curLightTheme = get_light_theme();
        if (curLightTheme)
        {
            Screen_Water_Q_Panel_0->fn->setScheme(Screen_Water_Q_Panel_0, &EditPanel);
            Screen_Water_Q_ButtonWidget_Back->fn->setScheme(Screen_Water_Q_ButtonWidget_Back, &Scheme_Light);
            Screen_Water_Q_ButtonWidget_Back->fn->setPressedImage(Screen_Water_Q_ButtonWidget_Back, (leImage*)&reply);
            Screen_Water_Q_ButtonWidget_Back->fn->setReleasedImage(Screen_Water_Q_ButtonWidget_Back, (leImage*)&reply);
            Screen_Water_Q_LabelWidget_0->fn->setScheme(Screen_Water_Q_LabelWidget_0, &Scheme_Light);
            Screen_Water_Q_ImageWidget_0->fn->setImage(Screen_Water_Q_ImageWidget_0, (leImage*)&vertical_line);
            Screen_Water_Q_LabelWidget_1->fn->setScheme(Screen_Water_Q_LabelWidget_1, &Scheme_Light);
            Screen_Water_Q_ButtonWidget_StartCC->fn->setScheme(Screen_Water_Q_ButtonWidget_StartCC, &Scheme_Light);
            Screen_Water_Q_LabelWidget_2->fn->setScheme(Screen_Water_Q_LabelWidget_2, &Scheme_Light);
            Screen_Water_Q_ButtonWidget_ACCOff->fn->setScheme(Screen_Water_Q_ButtonWidget_ACCOff, &Scheme_Light);
            Screen_Water_Q_ButtonWidget_ACCOn->fn->setScheme(Screen_Water_Q_ButtonWidget_ACCOn, &Scheme_Light);
            Screen_Water_Q_LabelWidget_3->fn->setScheme(Screen_Water_Q_LabelWidget_3, &Scheme_Light);
            Screen_Water_Q_LabelWidget_4->fn->setScheme(Screen_Water_Q_LabelWidget_4, &Scheme_Light);
            Screen_Water_Q_LabelWidget_5->fn->setScheme(Screen_Water_Q_LabelWidget_5, &Scheme_Light);
            Screen_Water_Q_LabelWidget_6->fn->setScheme(Screen_Water_Q_LabelWidget_6, &Scheme_Light);
            Screen_Water_Q_LabelWidget_7->fn->setScheme(Screen_Water_Q_LabelWidget_7, &Scheme_Light);
            Screen_Water_Q_LabelWidget_8->fn->setScheme(Screen_Water_Q_LabelWidget_8, &Scheme_Light);
            Screen_Water_Q_LabelWidget_9->fn->setScheme(Screen_Water_Q_LabelWidget_9, &Scheme_Light);
            Screen_Water_Q_LabelWidget_3_0->fn->setScheme(Screen_Water_Q_LabelWidget_3_0, &Scheme_Light);
            Screen_Water_Q_LabelWidget_FC->fn->setScheme(Screen_Water_Q_LabelWidget_FC, &Scheme_Light);
            Screen_Water_Q_LabelWidget_FC_Date->fn->setScheme(Screen_Water_Q_LabelWidget_FC_Date, &Scheme_Light);
            Screen_Water_Q_LabelWidget_WatCh->fn->setScheme(Screen_Water_Q_LabelWidget_WatCh, &Scheme_Light);
            Screen_Water_Q_LabelWidget_WatCh_Date->fn->setScheme(Screen_Water_Q_LabelWidget_WatCh_Date, &Scheme_Light);
            Screen_Water_Q_ButtonWidget_RstFilterClean->fn->setScheme(Screen_Water_Q_ButtonWidget_RstFilterClean, &Scheme_Light);
            Screen_Water_Q_ButtonWidget_RstWatChg->fn->setScheme(Screen_Water_Q_ButtonWidget_RstWatChg, &Scheme_Light);
        }
        else
        {
            Screen_Water_Q_Panel_0->fn->setScheme(Screen_Water_Q_Panel_0, &EditPanel_Dark);
            Screen_Water_Q_ButtonWidget_Back->fn->setScheme(Screen_Water_Q_ButtonWidget_Back, &Scheme_Dark);
            Screen_Water_Q_ButtonWidget_Back->fn->setPressedImage(Screen_Water_Q_ButtonWidget_Back, (leImage*)&reply_dark);
            Screen_Water_Q_ButtonWidget_Back->fn->setReleasedImage(Screen_Water_Q_ButtonWidget_Back, (leImage*)&reply_dark);
            Screen_Water_Q_LabelWidget_0->fn->setScheme(Screen_Water_Q_LabelWidget_0, &Scheme_Dark);
            Screen_Water_Q_ImageWidget_0->fn->setImage(Screen_Water_Q_ImageWidget_0, (leImage*)&vertical_line_dark);
            Screen_Water_Q_LabelWidget_1->fn->setScheme(Screen_Water_Q_LabelWidget_1, &Scheme_Dark);
            Screen_Water_Q_ButtonWidget_StartCC->fn->setScheme(Screen_Water_Q_ButtonWidget_StartCC, &Scheme_Dark);
            Screen_Water_Q_LabelWidget_2->fn->setScheme(Screen_Water_Q_LabelWidget_2, &Scheme_Dark);
            Screen_Water_Q_ButtonWidget_ACCOff->fn->setScheme(Screen_Water_Q_ButtonWidget_ACCOff, &Scheme_Dark);
            Screen_Water_Q_ButtonWidget_ACCOn->fn->setScheme(Screen_Water_Q_ButtonWidget_ACCOn, &Scheme_Dark);
            Screen_Water_Q_LabelWidget_3->fn->setScheme(Screen_Water_Q_LabelWidget_3, &Scheme_Dark);
            Screen_Water_Q_LabelWidget_4->fn->setScheme(Screen_Water_Q_LabelWidget_4, &Scheme_Dark);
            Screen_Water_Q_LabelWidget_5->fn->setScheme(Screen_Water_Q_LabelWidget_5, &Scheme_Dark);
            Screen_Water_Q_LabelWidget_6->fn->setScheme(Screen_Water_Q_LabelWidget_6, &Scheme_Dark);
            Screen_Water_Q_LabelWidget_7->fn->setScheme(Screen_Water_Q_LabelWidget_7, &Scheme_Dark);
            Screen_Water_Q_LabelWidget_8->fn->setScheme(Screen_Water_Q_LabelWidget_8, &Scheme_Dark);
            Screen_Water_Q_LabelWidget_9->fn->setScheme(Screen_Water_Q_LabelWidget_9, &Scheme_Dark);
            Screen_Water_Q_LabelWidget_3_0->fn->setScheme(Screen_Water_Q_LabelWidget_3_0, &Scheme_Dark);
            Screen_Water_Q_LabelWidget_FC->fn->setScheme(Screen_Water_Q_LabelWidget_FC, &Scheme_Dark);
            Screen_Water_Q_LabelWidget_FC_Date->fn->setScheme(Screen_Water_Q_LabelWidget_FC_Date, &Scheme_Dark);
            Screen_Water_Q_LabelWidget_WatCh->fn->setScheme(Screen_Water_Q_LabelWidget_WatCh, &Scheme_Dark);
            Screen_Water_Q_LabelWidget_WatCh_Date->fn->setScheme(Screen_Water_Q_LabelWidget_WatCh_Date, &Scheme_Dark);
            Screen_Water_Q_ButtonWidget_RstFilterClean->fn->setScheme(Screen_Water_Q_ButtonWidget_RstFilterClean, &Scheme_Dark);
            Screen_Water_Q_ButtonWidget_RstWatChg->fn->setScheme(Screen_Water_Q_ButtonWidget_RstWatChg, &Scheme_Dark);
        }
    }
}
/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_scrn_settings.c

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
static leDynamicString *appFahrStr;
static leDynamicString *appCelsStr;
static leDynamicString *appThemeStr;
static bool lastTempType;
static bool lastEcoAct;
static bool curLightTheme = true;

void modify_temp_btns(bool tempFahr);
void modify_eco_btn(bool ecoActivated);
static void update_theme();

void Screen_Settings_OnShow()
{
    bool tempFahr = get_fahr_temp_setting();
    bool ecoActivated = get_eco_setting();
    lastTempType = tempFahr;
    lastEcoAct = ecoActivated;
    curLightTheme = true;
    
    update_theme();
    
    appFahrStr = leDynamicString_New();
    appCelsStr = leDynamicString_New();
    appThemeStr = leDynamicString_New();
    
    Screen_Settings_ButtonWidget_Back->fn->setCornerRadius(Screen_Settings_ButtonWidget_Back, DEFAULT_BTN_CORNER_RADIUS);
    Screen_Settings_ButtonWidget_Fah->fn->setCornerRadius(Screen_Settings_ButtonWidget_Fah, DEFAULT_BTN_CORNER_RADIUS);
    Screen_Settings_ButtonWidget_Cel->fn->setCornerRadius(Screen_Settings_ButtonWidget_Cel, DEFAULT_BTN_CORNER_RADIUS);
    Screen_Settings_ButtonWidget_EcoMode->fn->setCornerRadius(Screen_Settings_ButtonWidget_EcoMode, DEFAULT_BTN_CORNER_RADIUS);
    Screen_Settings_ButtonWidget_OtherNet->fn->setCornerRadius(Screen_Settings_ButtonWidget_OtherNet, DEFAULT_BTN_CORNER_RADIUS);
    Screen_Settings_ButtonWidget_ChgThm->fn->setCornerRadius(Screen_Settings_ButtonWidget_ChgThm, DEFAULT_BTN_CORNER_RADIUS);
     
    sprintf(cStrBuff, "Fahrenheit");
    appFahrStr->fn->setFromCStr(appFahrStr, cStrBuff);
    Screen_Settings_ButtonWidget_Fah->fn->setString(Screen_Settings_ButtonWidget_Fah, (leString *) appFahrStr);
    sprintf(cStrBuff, "Celsius");
    appCelsStr->fn->setFromCStr(appCelsStr, cStrBuff);
    Screen_Settings_ButtonWidget_Cel->fn->setString(Screen_Settings_ButtonWidget_Cel, (leString *) appCelsStr);

    if (get_light_theme())
    {
        sprintf(cStrBuff, "Dark");
    }
    else
    {
        sprintf(cStrBuff, "Light");
    }
    appThemeStr->fn->setFont(appThemeStr, (leFont*) &InterRegular12);
    appThemeStr->fn->setFromCStr(appThemeStr, cStrBuff);
    Screen_Settings_ButtonWidget_ChgThm->fn->setString(Screen_Settings_ButtonWidget_ChgThm, (leString *) appThemeStr);

    modify_temp_btns(tempFahr);
    modify_eco_btn(ecoActivated);
}

void Screen_Settings_OnHide()
{
    leString_Delete((leString *) appFahrStr);
    leString_Delete((leString *) appCelsStr);
    leString_Delete((leString *) appThemeStr);
}

void Screen_Settings_OnUpdate()
{
    bool tempFahr = get_fahr_temp_setting();
    bool ecoActivated = get_eco_setting();
    
    if (tempFahr != lastTempType)
    {
        lastTempType = tempFahr;
        modify_temp_btns(tempFahr);
    }
    
    if (ecoActivated != lastEcoAct)
    {
        lastEcoAct = ecoActivated;
        modify_eco_btn(ecoActivated);
    }
}

void event_Screen_Settings_ButtonWidget_ChgThm_OnReleased(leButtonWidget* btn)
{
    set_light_theme(!get_light_theme());
    if (get_light_theme())
    {
        sprintf(cStrBuff, "Dark");
        appThemeStr->fn->setFromCStr(appThemeStr, cStrBuff);
    }
    else
    {
        sprintf(cStrBuff, "Light");
        appThemeStr->fn->setFromCStr(appThemeStr, cStrBuff);
    }
    update_theme();
}

void event_Screen_Settings_ButtonWidget_Back_OnReleased(leButtonWidget* btn)
{
    legato_showScreen(screenID_Screen_Main);
}

void event_Screen_Settings_ButtonWidget_OtherNet_OnReleased(leButtonWidget* btn)
{
    if (Screen_Settings_ImageWidget_WifiConn->fn->getVisible(Screen_Settings_ImageWidget_WifiConn) == LE_FALSE)
    {
        Screen_Settings_ImageWidget_WifiConn->fn->setVisible(Screen_Settings_ImageWidget_WifiConn, LE_TRUE);
    }
    else
    {
        Screen_Settings_ImageWidget_WifiConn->fn->setVisible(Screen_Settings_ImageWidget_WifiConn, LE_FALSE);        
    }
}

void event_Screen_Settings_ButtonWidget_EcoMode_OnReleased(leButtonWidget* btn)
{
    bool prevEcoMode = get_eco_setting();
    set_eco_setting(!prevEcoMode);
}

void event_Screen_Settings_ButtonWidget_Fah_OnReleased(leButtonWidget* btn)
{
        set_fahr_temp_setting(true);
}
void event_Screen_Settings_ButtonWidget_Cel_OnReleased(leButtonWidget* btn)
{
        set_fahr_temp_setting(false);
}

void modify_temp_btns(bool tempFahr)
{
    if (tempFahr == true)
    {
        appFahrStr->fn->setFont(appFahrStr, (leFont*) &InterBold12);
        appCelsStr->fn->setFont(appCelsStr, (leFont*) &InterRegular12);
        Screen_Settings_ButtonWidget_Fah->fn->setBorderType(Screen_Settings_ButtonWidget_Fah, LE_WIDGET_BORDER_LINE);
        Screen_Settings_ButtonWidget_Cel->fn->setBorderType(Screen_Settings_ButtonWidget_Cel, LE_WIDGET_BORDER_NONE);
    }
    else
    {
        appFahrStr->fn->setFont(appFahrStr, (leFont*) &InterRegular12);
        appCelsStr->fn->setFont(appCelsStr, (leFont*) &InterBold12);
        Screen_Settings_ButtonWidget_Fah->fn->setBorderType(Screen_Settings_ButtonWidget_Fah, LE_WIDGET_BORDER_NONE);
        Screen_Settings_ButtonWidget_Cel->fn->setBorderType(Screen_Settings_ButtonWidget_Cel, LE_WIDGET_BORDER_LINE);
    }
    Screen_Settings_ButtonWidget_Fah->fn->invalidate(Screen_Settings_ButtonWidget_Fah);
    Screen_Settings_ButtonWidget_Cel->fn->invalidate(Screen_Settings_ButtonWidget_Cel);
}

void modify_eco_btn(bool ecoActivated)
{
    if (ecoActivated == true)
    {
        Screen_Settings_ButtonWidget_EcoMode->fn->setBorderType(Screen_Settings_ButtonWidget_EcoMode, LE_WIDGET_BORDER_LINE);
    }
    else
    {
        Screen_Settings_ButtonWidget_EcoMode->fn->setBorderType(Screen_Settings_ButtonWidget_EcoMode, LE_WIDGET_BORDER_NONE);        
    }
    
    Screen_Settings_ButtonWidget_EcoMode->fn->invalidate(Screen_Settings_ButtonWidget_EcoMode);
}

static void update_theme()
{
    if (get_light_theme() != curLightTheme)
    {
        curLightTheme = get_light_theme();
        if (curLightTheme)
        {
            //set to light theme
            Screen_Settings_Panel_0->fn->setScheme(Screen_Settings_Panel_0, &EditPanel);
            Screen_Settings_ImageWidget_0->fn->setImage(Screen_Settings_ImageWidget_0, (leImage*)&vertical_line);
            Screen_Settings_ButtonWidget_Back->fn->setScheme(Screen_Settings_ButtonWidget_Back, &Scheme_Light);
            Screen_Settings_ButtonWidget_ChgThm->fn->setScheme(Screen_Settings_ButtonWidget_ChgThm, &Scheme_Light);
            Screen_Settings_ButtonWidget_Fah->fn->setScheme(Screen_Settings_ButtonWidget_Fah, &Scheme_Light);
            Screen_Settings_ButtonWidget_Cel->fn->setScheme(Screen_Settings_ButtonWidget_Cel, &Scheme_Light);
            Screen_Settings_ButtonWidget_EcoMode->fn->setScheme(Screen_Settings_ButtonWidget_EcoMode, &Scheme_Light);
            Screen_Settings_ButtonWidget_OtherNet->fn->setScheme(Screen_Settings_ButtonWidget_OtherNet, &Scheme_Light);
            Screen_Settings_ButtonWidget_OtherNet->fn->setPressedImage(Screen_Settings_ButtonWidget_OtherNet, (leImage*)&wifi_add);
            Screen_Settings_ButtonWidget_OtherNet->fn->setReleasedImage(Screen_Settings_ButtonWidget_OtherNet, (leImage*)&wifi_add);
            Screen_Settings_ButtonWidget_Back->fn->setPressedImage(Screen_Settings_ButtonWidget_Back, (leImage*)&reply);
            Screen_Settings_ButtonWidget_Back->fn->setReleasedImage(Screen_Settings_ButtonWidget_Back, (leImage*)&reply);

            Screen_Settings_LabelWidget_4->fn->setScheme(Screen_Settings_LabelWidget_4, &Scheme_Light);
            Screen_Settings_LabelWidget_3->fn->setScheme(Screen_Settings_LabelWidget_3, &Scheme_Light);
            Screen_Settings_LabelWidget_2->fn->setScheme(Screen_Settings_LabelWidget_2, &Scheme_Light);
            Screen_Settings_LabelWidget_1->fn->setScheme(Screen_Settings_LabelWidget_1, &Scheme_Light);
            Screen_Settings_LabelWidget_0->fn->setScheme(Screen_Settings_LabelWidget_0, &Scheme_Light);
            
            Screen_Settings_ImageWidget_wifinamebkg->fn->setImage(Screen_Settings_ImageWidget_wifinamebkg, (leImage*)&fnc_example);
            Screen_Settings_ImageWidget_WifiConn->fn->setImage(Screen_Settings_ImageWidget_WifiConn, (leImage*)&check_small);
        }
        else
        {
            //set to dark theme
            Screen_Settings_Panel_0->fn->setScheme(Screen_Settings_Panel_0, &EditPanel_Dark);
            Screen_Settings_ImageWidget_0->fn->setImage(Screen_Settings_ImageWidget_0, (leImage*)&vertical_line_dark);
            Screen_Settings_ButtonWidget_Back->fn->setScheme(Screen_Settings_ButtonWidget_Back, &Scheme_Dark);
            Screen_Settings_ButtonWidget_ChgThm->fn->setScheme(Screen_Settings_ButtonWidget_ChgThm, &Scheme_Dark);
            Screen_Settings_ButtonWidget_Fah->fn->setScheme(Screen_Settings_ButtonWidget_Fah, &Scheme_Dark);
            Screen_Settings_ButtonWidget_Cel->fn->setScheme(Screen_Settings_ButtonWidget_Cel, &Scheme_Dark);
            Screen_Settings_ButtonWidget_EcoMode->fn->setScheme(Screen_Settings_ButtonWidget_EcoMode, &Scheme_Dark);
            Screen_Settings_ButtonWidget_OtherNet->fn->setScheme(Screen_Settings_ButtonWidget_OtherNet, &Scheme_Dark);
            Screen_Settings_ButtonWidget_OtherNet->fn->setPressedImage(Screen_Settings_ButtonWidget_OtherNet, (leImage*)&wifi_add_dark);
            Screen_Settings_ButtonWidget_OtherNet->fn->setReleasedImage(Screen_Settings_ButtonWidget_OtherNet, (leImage*)&wifi_add_dark);
            Screen_Settings_ButtonWidget_Back->fn->setPressedImage(Screen_Settings_ButtonWidget_Back, (leImage*)&reply_dark);
            Screen_Settings_ButtonWidget_Back->fn->setReleasedImage(Screen_Settings_ButtonWidget_Back, (leImage*)&reply_dark);

            Screen_Settings_LabelWidget_4->fn->setScheme(Screen_Settings_LabelWidget_4, &Scheme_Dark);
            Screen_Settings_LabelWidget_3->fn->setScheme(Screen_Settings_LabelWidget_3, &Scheme_Dark);
            Screen_Settings_LabelWidget_2->fn->setScheme(Screen_Settings_LabelWidget_2, &Scheme_Dark);
            Screen_Settings_LabelWidget_1->fn->setScheme(Screen_Settings_LabelWidget_1, &Scheme_Dark);
            Screen_Settings_LabelWidget_0->fn->setScheme(Screen_Settings_LabelWidget_0, &Scheme_Dark);
            
            Screen_Settings_ImageWidget_wifinamebkg->fn->setImage(Screen_Settings_ImageWidget_wifinamebkg, (leImage*)&fnc_example_dark);
            Screen_Settings_ImageWidget_WifiConn->fn->setImage(Screen_Settings_ImageWidget_WifiConn, (leImage*)&check_small_dark);
        }        
    }
}
#include "gfx/legato/generated/screen/le_gen_screen_Screen_Settings.h"

// screen member widget declarations
static leWidget* root0;

leWidget* Screen_Settings_Panel_0;
leButtonWidget* Screen_Settings_ButtonWidget_Back;
leImageWidget* Screen_Settings_ImageWidget_mgsLogo;
leLabelWidget* Screen_Settings_LabelWidget_0;
leImageWidget* Screen_Settings_ImageWidget_0;
leWidget* Screen_Settings_PanelWidget_0;
leWidget* Screen_Settings_PanelWidget_4;
leWidget* Screen_Settings_PanelWidget_1;
leWidget* Screen_Settings_PanelWidget_2;
leWidget* Screen_Settings_PanelWidget_3;
leLabelWidget* Screen_Settings_LabelWidget_1;
leButtonWidget* Screen_Settings_ButtonWidget_ChgThm;
leLabelWidget* Screen_Settings_LabelWidget_2;
leButtonWidget* Screen_Settings_ButtonWidget_Fah;
leButtonWidget* Screen_Settings_ButtonWidget_Cel;
leLabelWidget* Screen_Settings_LabelWidget_3;
leButtonWidget* Screen_Settings_ButtonWidget_EcoMode;
leLabelWidget* Screen_Settings_LabelWidget_4;
leButtonWidget* Screen_Settings_ButtonWidget_OtherNet;
leWidget* Screen_Settings_PanelWidget_5;
leImageWidget* Screen_Settings_ImageWidget_wifinamebkg;
leImageWidget* Screen_Settings_ImageWidget_WifiConn;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_Screen_Settings(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_Screen_Settings(void)
{
    if(showing == LE_TRUE)
        return LE_FAILURE;

    // layer 0
    root0 = leWidget_New();
    root0->fn->setSize(root0, LE_DEFAULT_SCREEN_WIDTH, LE_DEFAULT_SCREEN_HEIGHT);
    root0->fn->setBackgroundType(root0, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->setMargins(root0, 0, 0, 0, 0);
    root0->flags |= LE_WIDGET_IGNOREEVENTS;
    root0->flags |= LE_WIDGET_IGNOREPICK;

    Screen_Settings_Panel_0 = leWidget_New();
    Screen_Settings_Panel_0->fn->setPosition(Screen_Settings_Panel_0, 0, 0);
    Screen_Settings_Panel_0->fn->setSize(Screen_Settings_Panel_0, 1024, 600);
    Screen_Settings_Panel_0->fn->setScheme(Screen_Settings_Panel_0, &EditPanel);
    root0->fn->addChild(root0, (leWidget*)Screen_Settings_Panel_0);

    Screen_Settings_ButtonWidget_Back = leButtonWidget_New();
    Screen_Settings_ButtonWidget_Back->fn->setPosition(Screen_Settings_ButtonWidget_Back, 32, 24);
    Screen_Settings_ButtonWidget_Back->fn->setSize(Screen_Settings_ButtonWidget_Back, 135, 48);
    Screen_Settings_ButtonWidget_Back->fn->setScheme(Screen_Settings_ButtonWidget_Back, &Scheme_Light);
    Screen_Settings_ButtonWidget_Back->fn->setBorderType(Screen_Settings_ButtonWidget_Back, LE_WIDGET_BORDER_NONE);
    Screen_Settings_ButtonWidget_Back->fn->setMargins(Screen_Settings_ButtonWidget_Back, 0, 0, 0, 0);
    Screen_Settings_ButtonWidget_Back->fn->setString(Screen_Settings_ButtonWidget_Back, (leString*)&string_BackLbl);
    Screen_Settings_ButtonWidget_Back->fn->setPressedImage(Screen_Settings_ButtonWidget_Back, (leImage*)&reply);
    Screen_Settings_ButtonWidget_Back->fn->setReleasedImage(Screen_Settings_ButtonWidget_Back, (leImage*)&reply);
    Screen_Settings_ButtonWidget_Back->fn->setImageMargin(Screen_Settings_ButtonWidget_Back, 8);
    Screen_Settings_ButtonWidget_Back->fn->setReleasedEventCallback(Screen_Settings_ButtonWidget_Back, event_Screen_Settings_ButtonWidget_Back_OnReleased);
    root0->fn->addChild(root0, (leWidget*)Screen_Settings_ButtonWidget_Back);

    Screen_Settings_ImageWidget_mgsLogo = leImageWidget_New();
    Screen_Settings_ImageWidget_mgsLogo->fn->setPosition(Screen_Settings_ImageWidget_mgsLogo, 985, 10);
    Screen_Settings_ImageWidget_mgsLogo->fn->setSize(Screen_Settings_ImageWidget_mgsLogo, 29, 24);
    Screen_Settings_ImageWidget_mgsLogo->fn->setBackgroundType(Screen_Settings_ImageWidget_mgsLogo, LE_WIDGET_BACKGROUND_NONE);
    Screen_Settings_ImageWidget_mgsLogo->fn->setBorderType(Screen_Settings_ImageWidget_mgsLogo, LE_WIDGET_BORDER_NONE);
    Screen_Settings_ImageWidget_mgsLogo->fn->setImage(Screen_Settings_ImageWidget_mgsLogo, (leImage*)&mgs_logo);
    root0->fn->addChild(root0, (leWidget*)Screen_Settings_ImageWidget_mgsLogo);

    Screen_Settings_LabelWidget_0 = leLabelWidget_New();
    Screen_Settings_LabelWidget_0->fn->setPosition(Screen_Settings_LabelWidget_0, 444, 26);
    Screen_Settings_LabelWidget_0->fn->setSize(Screen_Settings_LabelWidget_0, 140, 40);
    Screen_Settings_LabelWidget_0->fn->setScheme(Screen_Settings_LabelWidget_0, &Scheme_Light);
    Screen_Settings_LabelWidget_0->fn->setBackgroundType(Screen_Settings_LabelWidget_0, LE_WIDGET_BACKGROUND_NONE);
    Screen_Settings_LabelWidget_0->fn->setVAlignment(Screen_Settings_LabelWidget_0, LE_VALIGN_TOP);
    Screen_Settings_LabelWidget_0->fn->setMargins(Screen_Settings_LabelWidget_0, 0, 0, 0, 0);
    Screen_Settings_LabelWidget_0->fn->setString(Screen_Settings_LabelWidget_0, (leString*)&string_SettingsLbl);
    root0->fn->addChild(root0, (leWidget*)Screen_Settings_LabelWidget_0);

    Screen_Settings_ImageWidget_0 = leImageWidget_New();
    Screen_Settings_ImageWidget_0->fn->setPosition(Screen_Settings_ImageWidget_0, 510, 125);
    Screen_Settings_ImageWidget_0->fn->setSize(Screen_Settings_ImageWidget_0, 4, 345);
    Screen_Settings_ImageWidget_0->fn->setBackgroundType(Screen_Settings_ImageWidget_0, LE_WIDGET_BACKGROUND_NONE);
    Screen_Settings_ImageWidget_0->fn->setBorderType(Screen_Settings_ImageWidget_0, LE_WIDGET_BORDER_NONE);
    Screen_Settings_ImageWidget_0->fn->setMargins(Screen_Settings_ImageWidget_0, 0, 0, 0, 0);
    Screen_Settings_ImageWidget_0->fn->setImage(Screen_Settings_ImageWidget_0, (leImage*)&vertical_line);
    root0->fn->addChild(root0, (leWidget*)Screen_Settings_ImageWidget_0);

    Screen_Settings_PanelWidget_0 = leWidget_New();
    Screen_Settings_PanelWidget_0->fn->setPosition(Screen_Settings_PanelWidget_0, 167, 148);
    Screen_Settings_PanelWidget_0->fn->setSize(Screen_Settings_PanelWidget_0, 240, 319);
    Screen_Settings_PanelWidget_0->fn->setBackgroundType(Screen_Settings_PanelWidget_0, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->addChild(root0, (leWidget*)Screen_Settings_PanelWidget_0);

    Screen_Settings_PanelWidget_1 = leWidget_New();
    Screen_Settings_PanelWidget_1->fn->setPosition(Screen_Settings_PanelWidget_1, 0, 0);
    Screen_Settings_PanelWidget_1->fn->setSize(Screen_Settings_PanelWidget_1, 240, 85);
    Screen_Settings_PanelWidget_1->fn->setBackgroundType(Screen_Settings_PanelWidget_1, LE_WIDGET_BACKGROUND_NONE);
    Screen_Settings_PanelWidget_0->fn->addChild(Screen_Settings_PanelWidget_0, (leWidget*)Screen_Settings_PanelWidget_1);

    Screen_Settings_LabelWidget_1 = leLabelWidget_New();
    Screen_Settings_LabelWidget_1->fn->setPosition(Screen_Settings_LabelWidget_1, 0, 0);
    Screen_Settings_LabelWidget_1->fn->setSize(Screen_Settings_LabelWidget_1, 240, 32);
    Screen_Settings_LabelWidget_1->fn->setScheme(Screen_Settings_LabelWidget_1, &Scheme_Light);
    Screen_Settings_LabelWidget_1->fn->setBackgroundType(Screen_Settings_LabelWidget_1, LE_WIDGET_BACKGROUND_NONE);
    Screen_Settings_LabelWidget_1->fn->setVAlignment(Screen_Settings_LabelWidget_1, LE_VALIGN_TOP);
    Screen_Settings_LabelWidget_1->fn->setMargins(Screen_Settings_LabelWidget_1, 0, 0, 0, 0);
    Screen_Settings_LabelWidget_1->fn->setString(Screen_Settings_LabelWidget_1, (leString*)&string_ChangeTheme);
    Screen_Settings_PanelWidget_1->fn->addChild(Screen_Settings_PanelWidget_1, (leWidget*)Screen_Settings_LabelWidget_1);

    Screen_Settings_ButtonWidget_ChgThm = leButtonWidget_New();
    Screen_Settings_ButtonWidget_ChgThm->fn->setPosition(Screen_Settings_ButtonWidget_ChgThm, 0, 46);
    Screen_Settings_ButtonWidget_ChgThm->fn->setSize(Screen_Settings_ButtonWidget_ChgThm, 82, 40);
    Screen_Settings_ButtonWidget_ChgThm->fn->setScheme(Screen_Settings_ButtonWidget_ChgThm, &Scheme_Light);
    Screen_Settings_ButtonWidget_ChgThm->fn->setBorderType(Screen_Settings_ButtonWidget_ChgThm, LE_WIDGET_BORDER_NONE);
    Screen_Settings_ButtonWidget_ChgThm->fn->setMargins(Screen_Settings_ButtonWidget_ChgThm, 0, 0, 0, 0);
    Screen_Settings_ButtonWidget_ChgThm->fn->setString(Screen_Settings_ButtonWidget_ChgThm, (leString*)&string_ChgThm);
    Screen_Settings_ButtonWidget_ChgThm->fn->setImagePosition(Screen_Settings_ButtonWidget_ChgThm, LE_RELATIVE_POSITION_BEHIND);
    Screen_Settings_ButtonWidget_ChgThm->fn->setImageMargin(Screen_Settings_ButtonWidget_ChgThm, 0);
    Screen_Settings_ButtonWidget_ChgThm->fn->setPressedOffset(Screen_Settings_ButtonWidget_ChgThm, 0);
    Screen_Settings_ButtonWidget_ChgThm->fn->setReleasedEventCallback(Screen_Settings_ButtonWidget_ChgThm, event_Screen_Settings_ButtonWidget_ChgThm_OnReleased);
    Screen_Settings_PanelWidget_1->fn->addChild(Screen_Settings_PanelWidget_1, (leWidget*)Screen_Settings_ButtonWidget_ChgThm);

    Screen_Settings_PanelWidget_2 = leWidget_New();
    Screen_Settings_PanelWidget_2->fn->setPosition(Screen_Settings_PanelWidget_2, 0, 116);
    Screen_Settings_PanelWidget_2->fn->setSize(Screen_Settings_PanelWidget_2, 230, 85);
    Screen_Settings_PanelWidget_2->fn->setBackgroundType(Screen_Settings_PanelWidget_2, LE_WIDGET_BACKGROUND_NONE);
    Screen_Settings_PanelWidget_0->fn->addChild(Screen_Settings_PanelWidget_0, (leWidget*)Screen_Settings_PanelWidget_2);

    Screen_Settings_LabelWidget_2 = leLabelWidget_New();
    Screen_Settings_LabelWidget_2->fn->setPosition(Screen_Settings_LabelWidget_2, 0, 0);
    Screen_Settings_LabelWidget_2->fn->setSize(Screen_Settings_LabelWidget_2, 240, 32);
    Screen_Settings_LabelWidget_2->fn->setScheme(Screen_Settings_LabelWidget_2, &Scheme_Light);
    Screen_Settings_LabelWidget_2->fn->setBackgroundType(Screen_Settings_LabelWidget_2, LE_WIDGET_BACKGROUND_NONE);
    Screen_Settings_LabelWidget_2->fn->setVAlignment(Screen_Settings_LabelWidget_2, LE_VALIGN_TOP);
    Screen_Settings_LabelWidget_2->fn->setMargins(Screen_Settings_LabelWidget_2, 0, 0, 0, 0);
    Screen_Settings_LabelWidget_2->fn->setString(Screen_Settings_LabelWidget_2, (leString*)&string_TempUnits);
    Screen_Settings_PanelWidget_2->fn->addChild(Screen_Settings_PanelWidget_2, (leWidget*)Screen_Settings_LabelWidget_2);

    Screen_Settings_ButtonWidget_Fah = leButtonWidget_New();
    Screen_Settings_ButtonWidget_Fah->fn->setPosition(Screen_Settings_ButtonWidget_Fah, 0, 45);
    Screen_Settings_ButtonWidget_Fah->fn->setSize(Screen_Settings_ButtonWidget_Fah, 112, 40);
    Screen_Settings_ButtonWidget_Fah->fn->setScheme(Screen_Settings_ButtonWidget_Fah, &Scheme_Light);
    Screen_Settings_ButtonWidget_Fah->fn->setBorderType(Screen_Settings_ButtonWidget_Fah, LE_WIDGET_BORDER_NONE);
    Screen_Settings_ButtonWidget_Fah->fn->setString(Screen_Settings_ButtonWidget_Fah, (leString*)&string_Fahrenheit);
    Screen_Settings_ButtonWidget_Fah->fn->setImagePosition(Screen_Settings_ButtonWidget_Fah, LE_RELATIVE_POSITION_BEHIND);
    Screen_Settings_ButtonWidget_Fah->fn->setImageMargin(Screen_Settings_ButtonWidget_Fah, 0);
    Screen_Settings_ButtonWidget_Fah->fn->setPressedOffset(Screen_Settings_ButtonWidget_Fah, 0);
    Screen_Settings_ButtonWidget_Fah->fn->setReleasedEventCallback(Screen_Settings_ButtonWidget_Fah, event_Screen_Settings_ButtonWidget_Fah_OnReleased);
    Screen_Settings_PanelWidget_2->fn->addChild(Screen_Settings_PanelWidget_2, (leWidget*)Screen_Settings_ButtonWidget_Fah);

    Screen_Settings_ButtonWidget_Cel = leButtonWidget_New();
    Screen_Settings_ButtonWidget_Cel->fn->setPosition(Screen_Settings_ButtonWidget_Cel, 118, 45);
    Screen_Settings_ButtonWidget_Cel->fn->setSize(Screen_Settings_ButtonWidget_Cel, 112, 40);
    Screen_Settings_ButtonWidget_Cel->fn->setScheme(Screen_Settings_ButtonWidget_Cel, &Scheme_Light);
    Screen_Settings_ButtonWidget_Cel->fn->setBorderType(Screen_Settings_ButtonWidget_Cel, LE_WIDGET_BORDER_NONE);
    Screen_Settings_ButtonWidget_Cel->fn->setString(Screen_Settings_ButtonWidget_Cel, (leString*)&string_Celsius);
    Screen_Settings_ButtonWidget_Cel->fn->setImagePosition(Screen_Settings_ButtonWidget_Cel, LE_RELATIVE_POSITION_BEHIND);
    Screen_Settings_ButtonWidget_Cel->fn->setImageMargin(Screen_Settings_ButtonWidget_Cel, 0);
    Screen_Settings_ButtonWidget_Cel->fn->setPressedOffset(Screen_Settings_ButtonWidget_Cel, 0);
    Screen_Settings_ButtonWidget_Cel->fn->setReleasedEventCallback(Screen_Settings_ButtonWidget_Cel, event_Screen_Settings_ButtonWidget_Cel_OnReleased);
    Screen_Settings_PanelWidget_2->fn->addChild(Screen_Settings_PanelWidget_2, (leWidget*)Screen_Settings_ButtonWidget_Cel);

    Screen_Settings_PanelWidget_3 = leWidget_New();
    Screen_Settings_PanelWidget_3->fn->setPosition(Screen_Settings_PanelWidget_3, 0, 234);
    Screen_Settings_PanelWidget_3->fn->setSize(Screen_Settings_PanelWidget_3, 116, 85);
    Screen_Settings_PanelWidget_3->fn->setBackgroundType(Screen_Settings_PanelWidget_3, LE_WIDGET_BACKGROUND_NONE);
    Screen_Settings_PanelWidget_0->fn->addChild(Screen_Settings_PanelWidget_0, (leWidget*)Screen_Settings_PanelWidget_3);

    Screen_Settings_LabelWidget_3 = leLabelWidget_New();
    Screen_Settings_LabelWidget_3->fn->setPosition(Screen_Settings_LabelWidget_3, 0, 0);
    Screen_Settings_LabelWidget_3->fn->setSize(Screen_Settings_LabelWidget_3, 120, 32);
    Screen_Settings_LabelWidget_3->fn->setScheme(Screen_Settings_LabelWidget_3, &Scheme_Light);
    Screen_Settings_LabelWidget_3->fn->setBackgroundType(Screen_Settings_LabelWidget_3, LE_WIDGET_BACKGROUND_NONE);
    Screen_Settings_LabelWidget_3->fn->setVAlignment(Screen_Settings_LabelWidget_3, LE_VALIGN_TOP);
    Screen_Settings_LabelWidget_3->fn->setMargins(Screen_Settings_LabelWidget_3, 0, 0, 0, 0);
    Screen_Settings_LabelWidget_3->fn->setString(Screen_Settings_LabelWidget_3, (leString*)&string_EcoMode);
    Screen_Settings_PanelWidget_3->fn->addChild(Screen_Settings_PanelWidget_3, (leWidget*)Screen_Settings_LabelWidget_3);

    Screen_Settings_ButtonWidget_EcoMode = leButtonWidget_New();
    Screen_Settings_ButtonWidget_EcoMode->fn->setPosition(Screen_Settings_ButtonWidget_EcoMode, 0, 45);
    Screen_Settings_ButtonWidget_EcoMode->fn->setSize(Screen_Settings_ButtonWidget_EcoMode, 95, 40);
    Screen_Settings_ButtonWidget_EcoMode->fn->setScheme(Screen_Settings_ButtonWidget_EcoMode, &Scheme_Light);
    Screen_Settings_ButtonWidget_EcoMode->fn->setBorderType(Screen_Settings_ButtonWidget_EcoMode, LE_WIDGET_BORDER_NONE);
    Screen_Settings_ButtonWidget_EcoMode->fn->setString(Screen_Settings_ButtonWidget_EcoMode, (leString*)&string_ActEcoMode);
    Screen_Settings_ButtonWidget_EcoMode->fn->setImagePosition(Screen_Settings_ButtonWidget_EcoMode, LE_RELATIVE_POSITION_BEHIND);
    Screen_Settings_ButtonWidget_EcoMode->fn->setReleasedEventCallback(Screen_Settings_ButtonWidget_EcoMode, event_Screen_Settings_ButtonWidget_EcoMode_OnReleased);
    Screen_Settings_PanelWidget_3->fn->addChild(Screen_Settings_PanelWidget_3, (leWidget*)Screen_Settings_ButtonWidget_EcoMode);

    Screen_Settings_PanelWidget_4 = leWidget_New();
    Screen_Settings_PanelWidget_4->fn->setPosition(Screen_Settings_PanelWidget_4, 612, 168);
    Screen_Settings_PanelWidget_4->fn->setSize(Screen_Settings_PanelWidget_4, 216, 165);
    Screen_Settings_PanelWidget_4->fn->setBackgroundType(Screen_Settings_PanelWidget_4, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->addChild(root0, (leWidget*)Screen_Settings_PanelWidget_4);

    Screen_Settings_LabelWidget_4 = leLabelWidget_New();
    Screen_Settings_LabelWidget_4->fn->setPosition(Screen_Settings_LabelWidget_4, 0, 0);
    Screen_Settings_LabelWidget_4->fn->setSize(Screen_Settings_LabelWidget_4, 56, 32);
    Screen_Settings_LabelWidget_4->fn->setScheme(Screen_Settings_LabelWidget_4, &Scheme_Light);
    Screen_Settings_LabelWidget_4->fn->setBackgroundType(Screen_Settings_LabelWidget_4, LE_WIDGET_BACKGROUND_NONE);
    Screen_Settings_LabelWidget_4->fn->setVAlignment(Screen_Settings_LabelWidget_4, LE_VALIGN_TOP);
    Screen_Settings_LabelWidget_4->fn->setMargins(Screen_Settings_LabelWidget_4, 0, 0, 0, 0);
    Screen_Settings_LabelWidget_4->fn->setString(Screen_Settings_LabelWidget_4, (leString*)&string_Wifi);
    Screen_Settings_PanelWidget_4->fn->addChild(Screen_Settings_PanelWidget_4, (leWidget*)Screen_Settings_LabelWidget_4);

    Screen_Settings_ButtonWidget_OtherNet = leButtonWidget_New();
    Screen_Settings_ButtonWidget_OtherNet->fn->setPosition(Screen_Settings_ButtonWidget_OtherNet, 0, 121);
    Screen_Settings_ButtonWidget_OtherNet->fn->setSize(Screen_Settings_ButtonWidget_OtherNet, 154, 44);
    Screen_Settings_ButtonWidget_OtherNet->fn->setScheme(Screen_Settings_ButtonWidget_OtherNet, &Scheme_Light);
    Screen_Settings_ButtonWidget_OtherNet->fn->setBorderType(Screen_Settings_ButtonWidget_OtherNet, LE_WIDGET_BORDER_NONE);
    Screen_Settings_ButtonWidget_OtherNet->fn->setString(Screen_Settings_ButtonWidget_OtherNet, (leString*)&string_OtherNetworks);
    Screen_Settings_ButtonWidget_OtherNet->fn->setPressedImage(Screen_Settings_ButtonWidget_OtherNet, (leImage*)&wifi_add);
    Screen_Settings_ButtonWidget_OtherNet->fn->setReleasedImage(Screen_Settings_ButtonWidget_OtherNet, (leImage*)&wifi_add);
    Screen_Settings_ButtonWidget_OtherNet->fn->setReleasedEventCallback(Screen_Settings_ButtonWidget_OtherNet, event_Screen_Settings_ButtonWidget_OtherNet_OnReleased);
    Screen_Settings_PanelWidget_4->fn->addChild(Screen_Settings_PanelWidget_4, (leWidget*)Screen_Settings_ButtonWidget_OtherNet);

    Screen_Settings_PanelWidget_5 = leWidget_New();
    Screen_Settings_PanelWidget_5->fn->setPosition(Screen_Settings_PanelWidget_5, 0, 53);
    Screen_Settings_PanelWidget_5->fn->setSize(Screen_Settings_PanelWidget_5, 216, 44);
    Screen_Settings_PanelWidget_5->fn->setBackgroundType(Screen_Settings_PanelWidget_5, LE_WIDGET_BACKGROUND_NONE);
    Screen_Settings_PanelWidget_4->fn->addChild(Screen_Settings_PanelWidget_4, (leWidget*)Screen_Settings_PanelWidget_5);

    Screen_Settings_ImageWidget_wifinamebkg = leImageWidget_New();
    Screen_Settings_ImageWidget_wifinamebkg->fn->setPosition(Screen_Settings_ImageWidget_wifinamebkg, 0, -1);
    Screen_Settings_ImageWidget_wifinamebkg->fn->setSize(Screen_Settings_ImageWidget_wifinamebkg, 216, 44);
    Screen_Settings_ImageWidget_wifinamebkg->fn->setBackgroundType(Screen_Settings_ImageWidget_wifinamebkg, LE_WIDGET_BACKGROUND_NONE);
    Screen_Settings_ImageWidget_wifinamebkg->fn->setBorderType(Screen_Settings_ImageWidget_wifinamebkg, LE_WIDGET_BORDER_NONE);
    Screen_Settings_ImageWidget_wifinamebkg->fn->setImage(Screen_Settings_ImageWidget_wifinamebkg, (leImage*)&fnc_example);
    Screen_Settings_PanelWidget_5->fn->addChild(Screen_Settings_PanelWidget_5, (leWidget*)Screen_Settings_ImageWidget_wifinamebkg);

    Screen_Settings_ImageWidget_WifiConn = leImageWidget_New();
    Screen_Settings_ImageWidget_WifiConn->fn->setPosition(Screen_Settings_ImageWidget_WifiConn, 176, 10);
    Screen_Settings_ImageWidget_WifiConn->fn->setSize(Screen_Settings_ImageWidget_WifiConn, 24, 24);
    Screen_Settings_ImageWidget_WifiConn->fn->setBackgroundType(Screen_Settings_ImageWidget_WifiConn, LE_WIDGET_BACKGROUND_NONE);
    Screen_Settings_ImageWidget_WifiConn->fn->setBorderType(Screen_Settings_ImageWidget_WifiConn, LE_WIDGET_BORDER_NONE);
    Screen_Settings_ImageWidget_WifiConn->fn->setImage(Screen_Settings_ImageWidget_WifiConn, (leImage*)&check_small);
    Screen_Settings_PanelWidget_5->fn->addChild(Screen_Settings_PanelWidget_5, (leWidget*)Screen_Settings_ImageWidget_WifiConn);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    Screen_Settings_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_Screen_Settings(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);

    Screen_Settings_OnUpdate(); // raise event
}

void screenHide_Screen_Settings(void)
{
    Screen_Settings_OnHide(); // raise event


    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    Screen_Settings_Panel_0 = NULL;
    Screen_Settings_ButtonWidget_Back = NULL;
    Screen_Settings_ImageWidget_mgsLogo = NULL;
    Screen_Settings_LabelWidget_0 = NULL;
    Screen_Settings_ImageWidget_0 = NULL;
    Screen_Settings_PanelWidget_0 = NULL;
    Screen_Settings_PanelWidget_4 = NULL;
    Screen_Settings_PanelWidget_1 = NULL;
    Screen_Settings_PanelWidget_2 = NULL;
    Screen_Settings_PanelWidget_3 = NULL;
    Screen_Settings_LabelWidget_1 = NULL;
    Screen_Settings_ButtonWidget_ChgThm = NULL;
    Screen_Settings_LabelWidget_2 = NULL;
    Screen_Settings_ButtonWidget_Fah = NULL;
    Screen_Settings_ButtonWidget_Cel = NULL;
    Screen_Settings_LabelWidget_3 = NULL;
    Screen_Settings_ButtonWidget_EcoMode = NULL;
    Screen_Settings_LabelWidget_4 = NULL;
    Screen_Settings_ButtonWidget_OtherNet = NULL;
    Screen_Settings_PanelWidget_5 = NULL;
    Screen_Settings_ImageWidget_wifinamebkg = NULL;
    Screen_Settings_ImageWidget_WifiConn = NULL;


    showing = LE_FALSE;
}

void screenDestroy_Screen_Settings(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_Screen_Settings(uint32_t lyrIdx)
{
    if(lyrIdx >= LE_LAYER_COUNT)
        return NULL;

    switch(lyrIdx)
    {
        case 0:
        {
            return root0;
        }
        default:
        {
            return NULL;
        }
    }
}


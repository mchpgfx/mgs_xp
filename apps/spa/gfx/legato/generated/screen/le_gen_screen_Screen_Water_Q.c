#include "gfx/legato/generated/screen/le_gen_screen_Screen_Water_Q.h"

// screen member widget declarations
static leWidget* root0;

leWidget* Screen_Water_Q_Panel_0;
leButtonWidget* Screen_Water_Q_ButtonWidget_Back;
leImageWidget* Screen_Water_Q_ImageWidget_mgsLogo;
leLabelWidget* Screen_Water_Q_LabelWidget_0;
leImageWidget* Screen_Water_Q_ImageWidget_0;
leWidget* Screen_Water_Q_PanelWidget_0;
leWidget* Screen_Water_Q_PanelWidget_4;
leWidget* Screen_Water_Q_PanelWidget_4_0;
leWidget* Screen_Water_Q_PanelWidget_1;
leWidget* Screen_Water_Q_PanelWidget_2;
leLabelWidget* Screen_Water_Q_LabelWidget_1;
leButtonWidget* Screen_Water_Q_ButtonWidget_StartCC;
leLabelWidget* Screen_Water_Q_LabelWidget_2;
leButtonWidget* Screen_Water_Q_ButtonWidget_ACCOff;
leButtonWidget* Screen_Water_Q_ButtonWidget_ACCOn;
leWidget* Screen_Water_Q_PanelWidget_3;
leLabelWidget* Screen_Water_Q_LabelWidget_3;
leWidget* Screen_Water_Q_PanelWidget_5;
leLabelWidget* Screen_Water_Q_LabelWidget_4;
leLabelWidget* Screen_Water_Q_LabelWidget_5;
leLabelWidget* Screen_Water_Q_LabelWidget_6;
leLabelWidget* Screen_Water_Q_LabelWidget_7;
leLabelWidget* Screen_Water_Q_LabelWidget_8;
leLabelWidget* Screen_Water_Q_LabelWidget_9;
leLabelWidget* Screen_Water_Q_LabelWidget_3_0;
leWidget* Screen_Water_Q_PanelWidget_5_0;
leLabelWidget* Screen_Water_Q_LabelWidget_FC;
leLabelWidget* Screen_Water_Q_LabelWidget_FC_Date;
leLabelWidget* Screen_Water_Q_LabelWidget_WatCh;
leLabelWidget* Screen_Water_Q_LabelWidget_WatCh_Date;
leButtonWidget* Screen_Water_Q_ButtonWidget_RstFilterClean;
leButtonWidget* Screen_Water_Q_ButtonWidget_RstWatChg;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_Screen_Water_Q(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_Screen_Water_Q(void)
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

    Screen_Water_Q_Panel_0 = leWidget_New();
    Screen_Water_Q_Panel_0->fn->setPosition(Screen_Water_Q_Panel_0, 0, 0);
    Screen_Water_Q_Panel_0->fn->setSize(Screen_Water_Q_Panel_0, 1024, 600);
    Screen_Water_Q_Panel_0->fn->setScheme(Screen_Water_Q_Panel_0, &EditPanel);
    root0->fn->addChild(root0, (leWidget*)Screen_Water_Q_Panel_0);

    Screen_Water_Q_ButtonWidget_Back = leButtonWidget_New();
    Screen_Water_Q_ButtonWidget_Back->fn->setPosition(Screen_Water_Q_ButtonWidget_Back, 32, 24);
    Screen_Water_Q_ButtonWidget_Back->fn->setSize(Screen_Water_Q_ButtonWidget_Back, 135, 48);
    Screen_Water_Q_ButtonWidget_Back->fn->setScheme(Screen_Water_Q_ButtonWidget_Back, &Scheme_Light);
    Screen_Water_Q_ButtonWidget_Back->fn->setBorderType(Screen_Water_Q_ButtonWidget_Back, LE_WIDGET_BORDER_NONE);
    Screen_Water_Q_ButtonWidget_Back->fn->setMargins(Screen_Water_Q_ButtonWidget_Back, 0, 0, 0, 0);
    Screen_Water_Q_ButtonWidget_Back->fn->setString(Screen_Water_Q_ButtonWidget_Back, (leString*)&string_BackLbl);
    Screen_Water_Q_ButtonWidget_Back->fn->setPressedImage(Screen_Water_Q_ButtonWidget_Back, (leImage*)&reply);
    Screen_Water_Q_ButtonWidget_Back->fn->setReleasedImage(Screen_Water_Q_ButtonWidget_Back, (leImage*)&reply);
    Screen_Water_Q_ButtonWidget_Back->fn->setImageMargin(Screen_Water_Q_ButtonWidget_Back, 8);
    Screen_Water_Q_ButtonWidget_Back->fn->setReleasedEventCallback(Screen_Water_Q_ButtonWidget_Back, event_Screen_Water_Q_ButtonWidget_Back_OnReleased);
    root0->fn->addChild(root0, (leWidget*)Screen_Water_Q_ButtonWidget_Back);

    Screen_Water_Q_ImageWidget_mgsLogo = leImageWidget_New();
    Screen_Water_Q_ImageWidget_mgsLogo->fn->setPosition(Screen_Water_Q_ImageWidget_mgsLogo, 985, 10);
    Screen_Water_Q_ImageWidget_mgsLogo->fn->setSize(Screen_Water_Q_ImageWidget_mgsLogo, 29, 24);
    Screen_Water_Q_ImageWidget_mgsLogo->fn->setBackgroundType(Screen_Water_Q_ImageWidget_mgsLogo, LE_WIDGET_BACKGROUND_NONE);
    Screen_Water_Q_ImageWidget_mgsLogo->fn->setBorderType(Screen_Water_Q_ImageWidget_mgsLogo, LE_WIDGET_BORDER_NONE);
    Screen_Water_Q_ImageWidget_mgsLogo->fn->setImage(Screen_Water_Q_ImageWidget_mgsLogo, (leImage*)&mgs_logo);
    root0->fn->addChild(root0, (leWidget*)Screen_Water_Q_ImageWidget_mgsLogo);

    Screen_Water_Q_LabelWidget_0 = leLabelWidget_New();
    Screen_Water_Q_LabelWidget_0->fn->setPosition(Screen_Water_Q_LabelWidget_0, 290, 26);
    Screen_Water_Q_LabelWidget_0->fn->setSize(Screen_Water_Q_LabelWidget_0, 220, 40);
    Screen_Water_Q_LabelWidget_0->fn->setScheme(Screen_Water_Q_LabelWidget_0, &Scheme_Light);
    Screen_Water_Q_LabelWidget_0->fn->setBackgroundType(Screen_Water_Q_LabelWidget_0, LE_WIDGET_BACKGROUND_NONE);
    Screen_Water_Q_LabelWidget_0->fn->setVAlignment(Screen_Water_Q_LabelWidget_0, LE_VALIGN_TOP);
    Screen_Water_Q_LabelWidget_0->fn->setMargins(Screen_Water_Q_LabelWidget_0, 0, 0, 0, 0);
    Screen_Water_Q_LabelWidget_0->fn->setString(Screen_Water_Q_LabelWidget_0, (leString*)&string_WaterQualityLbl);
    root0->fn->addChild(root0, (leWidget*)Screen_Water_Q_LabelWidget_0);

    Screen_Water_Q_ImageWidget_0 = leImageWidget_New();
    Screen_Water_Q_ImageWidget_0->fn->setPosition(Screen_Water_Q_ImageWidget_0, 510, 125);
    Screen_Water_Q_ImageWidget_0->fn->setSize(Screen_Water_Q_ImageWidget_0, 4, 345);
    Screen_Water_Q_ImageWidget_0->fn->setBackgroundType(Screen_Water_Q_ImageWidget_0, LE_WIDGET_BACKGROUND_NONE);
    Screen_Water_Q_ImageWidget_0->fn->setBorderType(Screen_Water_Q_ImageWidget_0, LE_WIDGET_BORDER_NONE);
    Screen_Water_Q_ImageWidget_0->fn->setMargins(Screen_Water_Q_ImageWidget_0, 0, 0, 0, 0);
    Screen_Water_Q_ImageWidget_0->fn->setImage(Screen_Water_Q_ImageWidget_0, (leImage*)&vertical_line);
    root0->fn->addChild(root0, (leWidget*)Screen_Water_Q_ImageWidget_0);

    Screen_Water_Q_PanelWidget_0 = leWidget_New();
    Screen_Water_Q_PanelWidget_0->fn->setPosition(Screen_Water_Q_PanelWidget_0, 207, 171);
    Screen_Water_Q_PanelWidget_0->fn->setSize(Screen_Water_Q_PanelWidget_0, 216, 220);
    Screen_Water_Q_PanelWidget_0->fn->setBackgroundType(Screen_Water_Q_PanelWidget_0, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->addChild(root0, (leWidget*)Screen_Water_Q_PanelWidget_0);

    Screen_Water_Q_PanelWidget_1 = leWidget_New();
    Screen_Water_Q_PanelWidget_1->fn->setPosition(Screen_Water_Q_PanelWidget_1, 0, 0);
    Screen_Water_Q_PanelWidget_1->fn->setSize(Screen_Water_Q_PanelWidget_1, 204, 85);
    Screen_Water_Q_PanelWidget_1->fn->setBackgroundType(Screen_Water_Q_PanelWidget_1, LE_WIDGET_BACKGROUND_NONE);
    Screen_Water_Q_PanelWidget_0->fn->addChild(Screen_Water_Q_PanelWidget_0, (leWidget*)Screen_Water_Q_PanelWidget_1);

    Screen_Water_Q_LabelWidget_1 = leLabelWidget_New();
    Screen_Water_Q_LabelWidget_1->fn->setPosition(Screen_Water_Q_LabelWidget_1, 0, 0);
    Screen_Water_Q_LabelWidget_1->fn->setSize(Screen_Water_Q_LabelWidget_1, 150, 32);
    Screen_Water_Q_LabelWidget_1->fn->setScheme(Screen_Water_Q_LabelWidget_1, &Scheme_Light);
    Screen_Water_Q_LabelWidget_1->fn->setBackgroundType(Screen_Water_Q_LabelWidget_1, LE_WIDGET_BACKGROUND_NONE);
    Screen_Water_Q_LabelWidget_1->fn->setVAlignment(Screen_Water_Q_LabelWidget_1, LE_VALIGN_TOP);
    Screen_Water_Q_LabelWidget_1->fn->setMargins(Screen_Water_Q_LabelWidget_1, 0, 0, 0, 0);
    Screen_Water_Q_LabelWidget_1->fn->setString(Screen_Water_Q_LabelWidget_1, (leString*)&string_CleanCycle);
    Screen_Water_Q_PanelWidget_1->fn->addChild(Screen_Water_Q_PanelWidget_1, (leWidget*)Screen_Water_Q_LabelWidget_1);

    Screen_Water_Q_ButtonWidget_StartCC = leButtonWidget_New();
    Screen_Water_Q_ButtonWidget_StartCC->fn->setPosition(Screen_Water_Q_ButtonWidget_StartCC, 0, 45);
    Screen_Water_Q_ButtonWidget_StartCC->fn->setSize(Screen_Water_Q_ButtonWidget_StartCC, 204, 40);
    Screen_Water_Q_ButtonWidget_StartCC->fn->setScheme(Screen_Water_Q_ButtonWidget_StartCC, &Scheme_Light);
    Screen_Water_Q_ButtonWidget_StartCC->fn->setBorderType(Screen_Water_Q_ButtonWidget_StartCC, LE_WIDGET_BORDER_NONE);
    Screen_Water_Q_ButtonWidget_StartCC->fn->setString(Screen_Water_Q_ButtonWidget_StartCC, (leString*)&string_StartCleanNow);
    Screen_Water_Q_ButtonWidget_StartCC->fn->setReleasedEventCallback(Screen_Water_Q_ButtonWidget_StartCC, event_Screen_Water_Q_ButtonWidget_StartCC_OnReleased);
    Screen_Water_Q_PanelWidget_1->fn->addChild(Screen_Water_Q_PanelWidget_1, (leWidget*)Screen_Water_Q_ButtonWidget_StartCC);

    Screen_Water_Q_PanelWidget_2 = leWidget_New();
    Screen_Water_Q_PanelWidget_2->fn->setPosition(Screen_Water_Q_PanelWidget_2, 0, 133);
    Screen_Water_Q_PanelWidget_2->fn->setSize(Screen_Water_Q_PanelWidget_2, 216, 88);
    Screen_Water_Q_PanelWidget_2->fn->setBackgroundType(Screen_Water_Q_PanelWidget_2, LE_WIDGET_BACKGROUND_NONE);
    Screen_Water_Q_PanelWidget_0->fn->addChild(Screen_Water_Q_PanelWidget_0, (leWidget*)Screen_Water_Q_PanelWidget_2);

    Screen_Water_Q_LabelWidget_2 = leLabelWidget_New();
    Screen_Water_Q_LabelWidget_2->fn->setPosition(Screen_Water_Q_LabelWidget_2, 0, 0);
    Screen_Water_Q_LabelWidget_2->fn->setSize(Screen_Water_Q_LabelWidget_2, 210, 32);
    Screen_Water_Q_LabelWidget_2->fn->setScheme(Screen_Water_Q_LabelWidget_2, &Scheme_Light);
    Screen_Water_Q_LabelWidget_2->fn->setBackgroundType(Screen_Water_Q_LabelWidget_2, LE_WIDGET_BACKGROUND_NONE);
    Screen_Water_Q_LabelWidget_2->fn->setVAlignment(Screen_Water_Q_LabelWidget_2, LE_VALIGN_TOP);
    Screen_Water_Q_LabelWidget_2->fn->setMargins(Screen_Water_Q_LabelWidget_2, 0, 0, 0, 0);
    Screen_Water_Q_LabelWidget_2->fn->setString(Screen_Water_Q_LabelWidget_2, (leString*)&string_AutoCleanCycle);
    Screen_Water_Q_PanelWidget_2->fn->addChild(Screen_Water_Q_PanelWidget_2, (leWidget*)Screen_Water_Q_LabelWidget_2);

    Screen_Water_Q_ButtonWidget_ACCOff = leButtonWidget_New();
    Screen_Water_Q_ButtonWidget_ACCOff->fn->setPosition(Screen_Water_Q_ButtonWidget_ACCOff, 0, 45);
    Screen_Water_Q_ButtonWidget_ACCOff->fn->setSize(Screen_Water_Q_ButtonWidget_ACCOff, 95, 40);
    Screen_Water_Q_ButtonWidget_ACCOff->fn->setScheme(Screen_Water_Q_ButtonWidget_ACCOff, &Scheme_Light);
    Screen_Water_Q_ButtonWidget_ACCOff->fn->setBorderType(Screen_Water_Q_ButtonWidget_ACCOff, LE_WIDGET_BORDER_NONE);
    Screen_Water_Q_ButtonWidget_ACCOff->fn->setString(Screen_Water_Q_ButtonWidget_ACCOff, (leString*)&string_Off);
    Screen_Water_Q_ButtonWidget_ACCOff->fn->setReleasedEventCallback(Screen_Water_Q_ButtonWidget_ACCOff, event_Screen_Water_Q_ButtonWidget_ACCOff_OnReleased);
    Screen_Water_Q_PanelWidget_2->fn->addChild(Screen_Water_Q_PanelWidget_2, (leWidget*)Screen_Water_Q_ButtonWidget_ACCOff);

    Screen_Water_Q_ButtonWidget_ACCOn = leButtonWidget_New();
    Screen_Water_Q_ButtonWidget_ACCOn->fn->setPosition(Screen_Water_Q_ButtonWidget_ACCOn, 118, 45);
    Screen_Water_Q_ButtonWidget_ACCOn->fn->setSize(Screen_Water_Q_ButtonWidget_ACCOn, 95, 40);
    Screen_Water_Q_ButtonWidget_ACCOn->fn->setScheme(Screen_Water_Q_ButtonWidget_ACCOn, &Scheme_Light);
    Screen_Water_Q_ButtonWidget_ACCOn->fn->setBorderType(Screen_Water_Q_ButtonWidget_ACCOn, LE_WIDGET_BORDER_NONE);
    Screen_Water_Q_ButtonWidget_ACCOn->fn->setString(Screen_Water_Q_ButtonWidget_ACCOn, (leString*)&string_On);
    Screen_Water_Q_ButtonWidget_ACCOn->fn->setReleasedEventCallback(Screen_Water_Q_ButtonWidget_ACCOn, event_Screen_Water_Q_ButtonWidget_ACCOn_OnReleased);
    Screen_Water_Q_PanelWidget_2->fn->addChild(Screen_Water_Q_PanelWidget_2, (leWidget*)Screen_Water_Q_ButtonWidget_ACCOn);

    Screen_Water_Q_PanelWidget_4 = leWidget_New();
    Screen_Water_Q_PanelWidget_4->fn->setPosition(Screen_Water_Q_PanelWidget_4, 584, 165);
    Screen_Water_Q_PanelWidget_4->fn->setSize(Screen_Water_Q_PanelWidget_4, 330, 100);
    Screen_Water_Q_PanelWidget_4->fn->setBackgroundType(Screen_Water_Q_PanelWidget_4, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->addChild(root0, (leWidget*)Screen_Water_Q_PanelWidget_4);

    Screen_Water_Q_PanelWidget_3 = leWidget_New();
    Screen_Water_Q_PanelWidget_3->fn->setPosition(Screen_Water_Q_PanelWidget_3, 0, 0);
    Screen_Water_Q_PanelWidget_3->fn->setSize(Screen_Water_Q_PanelWidget_3, 240, 96);
    Screen_Water_Q_PanelWidget_3->fn->setBackgroundType(Screen_Water_Q_PanelWidget_3, LE_WIDGET_BACKGROUND_NONE);
    Screen_Water_Q_PanelWidget_4->fn->addChild(Screen_Water_Q_PanelWidget_4, (leWidget*)Screen_Water_Q_PanelWidget_3);

    Screen_Water_Q_LabelWidget_3 = leLabelWidget_New();
    Screen_Water_Q_LabelWidget_3->fn->setPosition(Screen_Water_Q_LabelWidget_3, 0, 0);
    Screen_Water_Q_LabelWidget_3->fn->setSize(Screen_Water_Q_LabelWidget_3, 176, 32);
    Screen_Water_Q_LabelWidget_3->fn->setScheme(Screen_Water_Q_LabelWidget_3, &Scheme_Light);
    Screen_Water_Q_LabelWidget_3->fn->setBackgroundType(Screen_Water_Q_LabelWidget_3, LE_WIDGET_BACKGROUND_NONE);
    Screen_Water_Q_LabelWidget_3->fn->setVAlignment(Screen_Water_Q_LabelWidget_3, LE_VALIGN_TOP);
    Screen_Water_Q_LabelWidget_3->fn->setMargins(Screen_Water_Q_LabelWidget_3, 0, 0, 0, 0);
    Screen_Water_Q_LabelWidget_3->fn->setString(Screen_Water_Q_LabelWidget_3, (leString*)&string_WaterQuality24);
    Screen_Water_Q_PanelWidget_3->fn->addChild(Screen_Water_Q_PanelWidget_3, (leWidget*)Screen_Water_Q_LabelWidget_3);

    Screen_Water_Q_PanelWidget_5 = leWidget_New();
    Screen_Water_Q_PanelWidget_5->fn->setPosition(Screen_Water_Q_PanelWidget_5, 0, 45);
    Screen_Water_Q_PanelWidget_5->fn->setSize(Screen_Water_Q_PanelWidget_5, 240, 100);
    Screen_Water_Q_PanelWidget_5->fn->setBackgroundType(Screen_Water_Q_PanelWidget_5, LE_WIDGET_BACKGROUND_NONE);
    Screen_Water_Q_PanelWidget_3->fn->addChild(Screen_Water_Q_PanelWidget_3, (leWidget*)Screen_Water_Q_PanelWidget_5);

    Screen_Water_Q_LabelWidget_4 = leLabelWidget_New();
    Screen_Water_Q_LabelWidget_4->fn->setPosition(Screen_Water_Q_LabelWidget_4, 0, 0);
    Screen_Water_Q_LabelWidget_4->fn->setSize(Screen_Water_Q_LabelWidget_4, 26, 24);
    Screen_Water_Q_LabelWidget_4->fn->setScheme(Screen_Water_Q_LabelWidget_4, &Scheme_Light);
    Screen_Water_Q_LabelWidget_4->fn->setBackgroundType(Screen_Water_Q_LabelWidget_4, LE_WIDGET_BACKGROUND_NONE);
    Screen_Water_Q_LabelWidget_4->fn->setVAlignment(Screen_Water_Q_LabelWidget_4, LE_VALIGN_TOP);
    Screen_Water_Q_LabelWidget_4->fn->setMargins(Screen_Water_Q_LabelWidget_4, 0, 0, 0, 0);
    Screen_Water_Q_LabelWidget_4->fn->setString(Screen_Water_Q_LabelWidget_4, (leString*)&string_pH);
    Screen_Water_Q_PanelWidget_5->fn->addChild(Screen_Water_Q_PanelWidget_5, (leWidget*)Screen_Water_Q_LabelWidget_4);

    Screen_Water_Q_LabelWidget_5 = leLabelWidget_New();
    Screen_Water_Q_LabelWidget_5->fn->setPosition(Screen_Water_Q_LabelWidget_5, 0, 28);
    Screen_Water_Q_LabelWidget_5->fn->setSize(Screen_Water_Q_LabelWidget_5, 32, 24);
    Screen_Water_Q_LabelWidget_5->fn->setScheme(Screen_Water_Q_LabelWidget_5, &Scheme_Light);
    Screen_Water_Q_LabelWidget_5->fn->setBackgroundType(Screen_Water_Q_LabelWidget_5, LE_WIDGET_BACKGROUND_NONE);
    Screen_Water_Q_LabelWidget_5->fn->setVAlignment(Screen_Water_Q_LabelWidget_5, LE_VALIGN_TOP);
    Screen_Water_Q_LabelWidget_5->fn->setMargins(Screen_Water_Q_LabelWidget_5, 0, 0, 0, 0);
    Screen_Water_Q_LabelWidget_5->fn->setString(Screen_Water_Q_LabelWidget_5, (leString*)&string_pHDemoVal);
    Screen_Water_Q_PanelWidget_5->fn->addChild(Screen_Water_Q_PanelWidget_5, (leWidget*)Screen_Water_Q_LabelWidget_5);

    Screen_Water_Q_LabelWidget_6 = leLabelWidget_New();
    Screen_Water_Q_LabelWidget_6->fn->setPosition(Screen_Water_Q_LabelWidget_6, 64, 0);
    Screen_Water_Q_LabelWidget_6->fn->setSize(Screen_Water_Q_LabelWidget_6, 72, 25);
    Screen_Water_Q_LabelWidget_6->fn->setScheme(Screen_Water_Q_LabelWidget_6, &Scheme_Light);
    Screen_Water_Q_LabelWidget_6->fn->setBackgroundType(Screen_Water_Q_LabelWidget_6, LE_WIDGET_BACKGROUND_NONE);
    Screen_Water_Q_LabelWidget_6->fn->setVAlignment(Screen_Water_Q_LabelWidget_6, LE_VALIGN_TOP);
    Screen_Water_Q_LabelWidget_6->fn->setMargins(Screen_Water_Q_LabelWidget_6, 0, 0, 0, 0);
    Screen_Water_Q_LabelWidget_6->fn->setString(Screen_Water_Q_LabelWidget_6, (leString*)&string_Chlorine);
    Screen_Water_Q_PanelWidget_5->fn->addChild(Screen_Water_Q_PanelWidget_5, (leWidget*)Screen_Water_Q_LabelWidget_6);

    Screen_Water_Q_LabelWidget_7 = leLabelWidget_New();
    Screen_Water_Q_LabelWidget_7->fn->setPosition(Screen_Water_Q_LabelWidget_7, 64, 28);
    Screen_Water_Q_LabelWidget_7->fn->setSize(Screen_Water_Q_LabelWidget_7, 64, 25);
    Screen_Water_Q_LabelWidget_7->fn->setScheme(Screen_Water_Q_LabelWidget_7, &Scheme_Light);
    Screen_Water_Q_LabelWidget_7->fn->setBackgroundType(Screen_Water_Q_LabelWidget_7, LE_WIDGET_BACKGROUND_NONE);
    Screen_Water_Q_LabelWidget_7->fn->setVAlignment(Screen_Water_Q_LabelWidget_7, LE_VALIGN_TOP);
    Screen_Water_Q_LabelWidget_7->fn->setMargins(Screen_Water_Q_LabelWidget_7, 0, 0, 0, 0);
    Screen_Water_Q_LabelWidget_7->fn->setString(Screen_Water_Q_LabelWidget_7, (leString*)&string_ChlorineDemoVal);
    Screen_Water_Q_PanelWidget_5->fn->addChild(Screen_Water_Q_PanelWidget_5, (leWidget*)Screen_Water_Q_LabelWidget_7);

    Screen_Water_Q_LabelWidget_8 = leLabelWidget_New();
    Screen_Water_Q_LabelWidget_8->fn->setPosition(Screen_Water_Q_LabelWidget_8, 167, 0);
    Screen_Water_Q_LabelWidget_8->fn->setSize(Screen_Water_Q_LabelWidget_8, 80, 25);
    Screen_Water_Q_LabelWidget_8->fn->setScheme(Screen_Water_Q_LabelWidget_8, &Scheme_Light);
    Screen_Water_Q_LabelWidget_8->fn->setBackgroundType(Screen_Water_Q_LabelWidget_8, LE_WIDGET_BACKGROUND_NONE);
    Screen_Water_Q_LabelWidget_8->fn->setVAlignment(Screen_Water_Q_LabelWidget_8, LE_VALIGN_TOP);
    Screen_Water_Q_LabelWidget_8->fn->setMargins(Screen_Water_Q_LabelWidget_8, 0, 0, 0, 0);
    Screen_Water_Q_LabelWidget_8->fn->setString(Screen_Water_Q_LabelWidget_8, (leString*)&string_Alkalinity);
    Screen_Water_Q_PanelWidget_5->fn->addChild(Screen_Water_Q_PanelWidget_5, (leWidget*)Screen_Water_Q_LabelWidget_8);

    Screen_Water_Q_LabelWidget_9 = leLabelWidget_New();
    Screen_Water_Q_LabelWidget_9->fn->setPosition(Screen_Water_Q_LabelWidget_9, 167, 28);
    Screen_Water_Q_LabelWidget_9->fn->setSize(Screen_Water_Q_LabelWidget_9, 80, 25);
    Screen_Water_Q_LabelWidget_9->fn->setScheme(Screen_Water_Q_LabelWidget_9, &Scheme_Light);
    Screen_Water_Q_LabelWidget_9->fn->setBackgroundType(Screen_Water_Q_LabelWidget_9, LE_WIDGET_BACKGROUND_NONE);
    Screen_Water_Q_LabelWidget_9->fn->setVAlignment(Screen_Water_Q_LabelWidget_9, LE_VALIGN_TOP);
    Screen_Water_Q_LabelWidget_9->fn->setMargins(Screen_Water_Q_LabelWidget_9, 0, 0, 0, 0);
    Screen_Water_Q_LabelWidget_9->fn->setString(Screen_Water_Q_LabelWidget_9, (leString*)&string_AlkalinityDemoVal);
    Screen_Water_Q_PanelWidget_5->fn->addChild(Screen_Water_Q_PanelWidget_5, (leWidget*)Screen_Water_Q_LabelWidget_9);

    Screen_Water_Q_PanelWidget_4_0 = leWidget_New();
    Screen_Water_Q_PanelWidget_4_0->fn->setPosition(Screen_Water_Q_PanelWidget_4_0, 584, 290);
    Screen_Water_Q_PanelWidget_4_0->fn->setSize(Screen_Water_Q_PanelWidget_4_0, 336, 116);
    Screen_Water_Q_PanelWidget_4_0->fn->setBackgroundType(Screen_Water_Q_PanelWidget_4_0, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->addChild(root0, (leWidget*)Screen_Water_Q_PanelWidget_4_0);

    Screen_Water_Q_LabelWidget_3_0 = leLabelWidget_New();
    Screen_Water_Q_LabelWidget_3_0->fn->setPosition(Screen_Water_Q_LabelWidget_3_0, 0, 0);
    Screen_Water_Q_LabelWidget_3_0->fn->setSize(Screen_Water_Q_LabelWidget_3_0, 280, 32);
    Screen_Water_Q_LabelWidget_3_0->fn->setScheme(Screen_Water_Q_LabelWidget_3_0, &Scheme_Light);
    Screen_Water_Q_LabelWidget_3_0->fn->setBackgroundType(Screen_Water_Q_LabelWidget_3_0, LE_WIDGET_BACKGROUND_NONE);
    Screen_Water_Q_LabelWidget_3_0->fn->setVAlignment(Screen_Water_Q_LabelWidget_3_0, LE_VALIGN_TOP);
    Screen_Water_Q_LabelWidget_3_0->fn->setMargins(Screen_Water_Q_LabelWidget_3_0, 0, 0, 0, 0);
    Screen_Water_Q_LabelWidget_3_0->fn->setString(Screen_Water_Q_LabelWidget_3_0, (leString*)&string_MaintReminder);
    Screen_Water_Q_PanelWidget_4_0->fn->addChild(Screen_Water_Q_PanelWidget_4_0, (leWidget*)Screen_Water_Q_LabelWidget_3_0);

    Screen_Water_Q_PanelWidget_5_0 = leWidget_New();
    Screen_Water_Q_PanelWidget_5_0->fn->setPosition(Screen_Water_Q_PanelWidget_5_0, 0, 45);
    Screen_Water_Q_PanelWidget_5_0->fn->setSize(Screen_Water_Q_PanelWidget_5_0, 340, 72);
    Screen_Water_Q_PanelWidget_5_0->fn->setBackgroundType(Screen_Water_Q_PanelWidget_5_0, LE_WIDGET_BACKGROUND_NONE);
    Screen_Water_Q_PanelWidget_4_0->fn->addChild(Screen_Water_Q_PanelWidget_4_0, (leWidget*)Screen_Water_Q_PanelWidget_5_0);

    Screen_Water_Q_LabelWidget_FC = leLabelWidget_New();
    Screen_Water_Q_LabelWidget_FC->fn->setPosition(Screen_Water_Q_LabelWidget_FC, 0, 0);
    Screen_Water_Q_LabelWidget_FC->fn->setSize(Screen_Water_Q_LabelWidget_FC, 88, 24);
    Screen_Water_Q_LabelWidget_FC->fn->setScheme(Screen_Water_Q_LabelWidget_FC, &Scheme_Light);
    Screen_Water_Q_LabelWidget_FC->fn->setBackgroundType(Screen_Water_Q_LabelWidget_FC, LE_WIDGET_BACKGROUND_NONE);
    Screen_Water_Q_LabelWidget_FC->fn->setVAlignment(Screen_Water_Q_LabelWidget_FC, LE_VALIGN_TOP);
    Screen_Water_Q_LabelWidget_FC->fn->setMargins(Screen_Water_Q_LabelWidget_FC, 0, 0, 0, 0);
    Screen_Water_Q_LabelWidget_FC->fn->setString(Screen_Water_Q_LabelWidget_FC, (leString*)&string_FilterClean);
    Screen_Water_Q_PanelWidget_5_0->fn->addChild(Screen_Water_Q_PanelWidget_5_0, (leWidget*)Screen_Water_Q_LabelWidget_FC);

    Screen_Water_Q_LabelWidget_FC_Date = leLabelWidget_New();
    Screen_Water_Q_LabelWidget_FC_Date->fn->setPosition(Screen_Water_Q_LabelWidget_FC_Date, -10, 42);
    Screen_Water_Q_LabelWidget_FC_Date->fn->setSize(Screen_Water_Q_LabelWidget_FC_Date, 60, 24);
    Screen_Water_Q_LabelWidget_FC_Date->fn->setScheme(Screen_Water_Q_LabelWidget_FC_Date, &Scheme_Light);
    Screen_Water_Q_LabelWidget_FC_Date->fn->setBackgroundType(Screen_Water_Q_LabelWidget_FC_Date, LE_WIDGET_BACKGROUND_NONE);
    Screen_Water_Q_LabelWidget_FC_Date->fn->setHAlignment(Screen_Water_Q_LabelWidget_FC_Date, LE_HALIGN_RIGHT);
    Screen_Water_Q_LabelWidget_FC_Date->fn->setVAlignment(Screen_Water_Q_LabelWidget_FC_Date, LE_VALIGN_TOP);
    Screen_Water_Q_LabelWidget_FC_Date->fn->setMargins(Screen_Water_Q_LabelWidget_FC_Date, 0, 0, 0, 0);
    Screen_Water_Q_LabelWidget_FC_Date->fn->setString(Screen_Water_Q_LabelWidget_FC_Date, (leString*)&string_FilterCleanDemoVal);
    Screen_Water_Q_PanelWidget_5_0->fn->addChild(Screen_Water_Q_PanelWidget_5_0, (leWidget*)Screen_Water_Q_LabelWidget_FC_Date);

    Screen_Water_Q_LabelWidget_WatCh = leLabelWidget_New();
    Screen_Water_Q_LabelWidget_WatCh->fn->setPosition(Screen_Water_Q_LabelWidget_WatCh, 191, 0);
    Screen_Water_Q_LabelWidget_WatCh->fn->setSize(Screen_Water_Q_LabelWidget_WatCh, 120, 25);
    Screen_Water_Q_LabelWidget_WatCh->fn->setScheme(Screen_Water_Q_LabelWidget_WatCh, &Scheme_Light);
    Screen_Water_Q_LabelWidget_WatCh->fn->setBackgroundType(Screen_Water_Q_LabelWidget_WatCh, LE_WIDGET_BACKGROUND_NONE);
    Screen_Water_Q_LabelWidget_WatCh->fn->setVAlignment(Screen_Water_Q_LabelWidget_WatCh, LE_VALIGN_TOP);
    Screen_Water_Q_LabelWidget_WatCh->fn->setMargins(Screen_Water_Q_LabelWidget_WatCh, 0, 0, 0, 0);
    Screen_Water_Q_LabelWidget_WatCh->fn->setString(Screen_Water_Q_LabelWidget_WatCh, (leString*)&string_WaterChange);
    Screen_Water_Q_PanelWidget_5_0->fn->addChild(Screen_Water_Q_PanelWidget_5_0, (leWidget*)Screen_Water_Q_LabelWidget_WatCh);

    Screen_Water_Q_LabelWidget_WatCh_Date = leLabelWidget_New();
    Screen_Water_Q_LabelWidget_WatCh_Date->fn->setPosition(Screen_Water_Q_LabelWidget_WatCh_Date, 174, 42);
    Screen_Water_Q_LabelWidget_WatCh_Date->fn->setSize(Screen_Water_Q_LabelWidget_WatCh_Date, 60, 24);
    Screen_Water_Q_LabelWidget_WatCh_Date->fn->setScheme(Screen_Water_Q_LabelWidget_WatCh_Date, &Scheme_Light);
    Screen_Water_Q_LabelWidget_WatCh_Date->fn->setBackgroundType(Screen_Water_Q_LabelWidget_WatCh_Date, LE_WIDGET_BACKGROUND_NONE);
    Screen_Water_Q_LabelWidget_WatCh_Date->fn->setHAlignment(Screen_Water_Q_LabelWidget_WatCh_Date, LE_HALIGN_RIGHT);
    Screen_Water_Q_LabelWidget_WatCh_Date->fn->setVAlignment(Screen_Water_Q_LabelWidget_WatCh_Date, LE_VALIGN_TOP);
    Screen_Water_Q_LabelWidget_WatCh_Date->fn->setMargins(Screen_Water_Q_LabelWidget_WatCh_Date, 0, 0, 0, 0);
    Screen_Water_Q_LabelWidget_WatCh_Date->fn->setString(Screen_Water_Q_LabelWidget_WatCh_Date, (leString*)&string_WaterCleanDemoVal);
    Screen_Water_Q_PanelWidget_5_0->fn->addChild(Screen_Water_Q_PanelWidget_5_0, (leWidget*)Screen_Water_Q_LabelWidget_WatCh_Date);

    Screen_Water_Q_ButtonWidget_RstFilterClean = leButtonWidget_New();
    Screen_Water_Q_ButtonWidget_RstFilterClean->fn->setPosition(Screen_Water_Q_ButtonWidget_RstFilterClean, 64, 34);
    Screen_Water_Q_ButtonWidget_RstFilterClean->fn->setSize(Screen_Water_Q_ButtonWidget_RstFilterClean, 82, 40);
    Screen_Water_Q_ButtonWidget_RstFilterClean->fn->setScheme(Screen_Water_Q_ButtonWidget_RstFilterClean, &Scheme_Light);
    Screen_Water_Q_ButtonWidget_RstFilterClean->fn->setBorderType(Screen_Water_Q_ButtonWidget_RstFilterClean, LE_WIDGET_BORDER_NONE);
    Screen_Water_Q_ButtonWidget_RstFilterClean->fn->setString(Screen_Water_Q_ButtonWidget_RstFilterClean, (leString*)&string_ResetLabel);
    Screen_Water_Q_ButtonWidget_RstFilterClean->fn->setReleasedEventCallback(Screen_Water_Q_ButtonWidget_RstFilterClean, event_Screen_Water_Q_ButtonWidget_RstFilterClean_OnReleased);
    Screen_Water_Q_PanelWidget_5_0->fn->addChild(Screen_Water_Q_PanelWidget_5_0, (leWidget*)Screen_Water_Q_ButtonWidget_RstFilterClean);

    Screen_Water_Q_ButtonWidget_RstWatChg = leButtonWidget_New();
    Screen_Water_Q_ButtonWidget_RstWatChg->fn->setPosition(Screen_Water_Q_ButtonWidget_RstWatChg, 248, 34);
    Screen_Water_Q_ButtonWidget_RstWatChg->fn->setSize(Screen_Water_Q_ButtonWidget_RstWatChg, 82, 40);
    Screen_Water_Q_ButtonWidget_RstWatChg->fn->setScheme(Screen_Water_Q_ButtonWidget_RstWatChg, &Scheme_Light);
    Screen_Water_Q_ButtonWidget_RstWatChg->fn->setBorderType(Screen_Water_Q_ButtonWidget_RstWatChg, LE_WIDGET_BORDER_NONE);
    Screen_Water_Q_ButtonWidget_RstWatChg->fn->setString(Screen_Water_Q_ButtonWidget_RstWatChg, (leString*)&string_ResetLabel);
    Screen_Water_Q_ButtonWidget_RstWatChg->fn->setReleasedEventCallback(Screen_Water_Q_ButtonWidget_RstWatChg, event_Screen_Water_Q_ButtonWidget_RstWatChg_OnReleased);
    Screen_Water_Q_PanelWidget_5_0->fn->addChild(Screen_Water_Q_PanelWidget_5_0, (leWidget*)Screen_Water_Q_ButtonWidget_RstWatChg);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    Screen_Water_Q_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_Screen_Water_Q(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);

    Screen_Water_Q_OnUpdate(); // raise event
}

void screenHide_Screen_Water_Q(void)
{
    Screen_Water_Q_OnHide(); // raise event


    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    Screen_Water_Q_Panel_0 = NULL;
    Screen_Water_Q_ButtonWidget_Back = NULL;
    Screen_Water_Q_ImageWidget_mgsLogo = NULL;
    Screen_Water_Q_LabelWidget_0 = NULL;
    Screen_Water_Q_ImageWidget_0 = NULL;
    Screen_Water_Q_PanelWidget_0 = NULL;
    Screen_Water_Q_PanelWidget_4 = NULL;
    Screen_Water_Q_PanelWidget_4_0 = NULL;
    Screen_Water_Q_PanelWidget_1 = NULL;
    Screen_Water_Q_PanelWidget_2 = NULL;
    Screen_Water_Q_LabelWidget_1 = NULL;
    Screen_Water_Q_ButtonWidget_StartCC = NULL;
    Screen_Water_Q_LabelWidget_2 = NULL;
    Screen_Water_Q_ButtonWidget_ACCOff = NULL;
    Screen_Water_Q_ButtonWidget_ACCOn = NULL;
    Screen_Water_Q_PanelWidget_3 = NULL;
    Screen_Water_Q_LabelWidget_3 = NULL;
    Screen_Water_Q_PanelWidget_5 = NULL;
    Screen_Water_Q_LabelWidget_4 = NULL;
    Screen_Water_Q_LabelWidget_5 = NULL;
    Screen_Water_Q_LabelWidget_6 = NULL;
    Screen_Water_Q_LabelWidget_7 = NULL;
    Screen_Water_Q_LabelWidget_8 = NULL;
    Screen_Water_Q_LabelWidget_9 = NULL;
    Screen_Water_Q_LabelWidget_3_0 = NULL;
    Screen_Water_Q_PanelWidget_5_0 = NULL;
    Screen_Water_Q_LabelWidget_FC = NULL;
    Screen_Water_Q_LabelWidget_FC_Date = NULL;
    Screen_Water_Q_LabelWidget_WatCh = NULL;
    Screen_Water_Q_LabelWidget_WatCh_Date = NULL;
    Screen_Water_Q_ButtonWidget_RstFilterClean = NULL;
    Screen_Water_Q_ButtonWidget_RstWatChg = NULL;


    showing = LE_FALSE;
}

void screenDestroy_Screen_Water_Q(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_Screen_Water_Q(uint32_t lyrIdx)
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


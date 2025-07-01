#include "gfx/legato/generated/screen/le_gen_screen_Main.h"

// screen member widget declarations
static leWidget* root0;

leWidget* Main_PanelWidget_0;
leWidget* Main_PanelWidget_0_0;
leButtonWidget* Main_btnInputCh1;
leButtonWidget* Main_btnInputCh2;
leButtonWidget* Main_btnInputCh3;
leButtonWidget* Main_btnInputCh4;
leButtonWidget* Main_btnRun;
leButtonWidget* Main_btnOutputCh1;
leButtonWidget* Main_btnOutputCh2;
leButtonWidget* Main_btnOutputCh3;
leButtonWidget* Main_btnOutputCh4;
leProgressBarWidget* Main_pbarAmpMain;
leWidget* Main_pnlMainGain;
leButtonWidget* Main_btnMainGain;
leButtonWidget* Main_btnMainMute;
leWidget* Main_pnlColorBarMain;
leLabelWidget* Main_lblOutput;
leLabelWidget* Main_lblMain;
leWidget* Main_pnlChnCtrlCh4;
leWidget* Main_pnlChnCtrlCh3;
leWidget* Main_pnlChnCtrlCh2;
leWidget* Main_pnlChnCtrlCh1;
leImageWidget* Main_ImageWidget_1;
leButtonWidget* Main_btnReset;
leImageWidget* Main_ImageWidget_0_1;
leImageWidget* Main_ImageWidget_0_2;
leImageWidget* Main_ImageWidget_0_2_0;
leImageWidget* Main_ImageWidget_0_2_1;
leImageWidget* Main_ImageWidget_0;
leImageWidget* Main_ImageWidget_0_0;
leImageWidget* Main_ImageWidget_0_0_0;
leImageWidget* Main_ImageWidget_0_0_1;
leButtonWidget* Main_btnCue_4;
leWidget* Main_pnlGain_4;
leButtonWidget* Main_btnM_4;
leButtonWidget* Main_btnS_4;
leProgressBarWidget* Main_pbarAmp_4;
leWidget* Main_pnlColorBar_4;
leWidget* Main_pnlLR_4;
leCircleWidget* Main_circLRKnob_4;
leLabelWidget* Main_lblChNum_4;
leLabelWidget* Main_lblL_4;
leLabelWidget* Main_lbl10_4;
leLabelWidget* Main_lblR_4;
leLabelWidget* Main_lbl5_4;
leLabelWidget* Main_lbl0_4;
leLabelWidget* Main_lbln5_4;
leLabelWidget* Main_lbln10_4;
leLabelWidget* Main_lbln15_4;
leLabelWidget* Main_lbln20_4;
leLabelWidget* Main_lbln25_4;
leLabelWidget* Main_lblChName_4;
leButtonWidget* Main_btnGainKnob_4;
leButtonWidget* Main_btnCue_3;
leWidget* Main_pnlGain_3;
leButtonWidget* Main_btnM_3;
leButtonWidget* Main_btnS_3;
leProgressBarWidget* Main_pbarAmp_3;
leWidget* Main_pnlColorBar_3;
leWidget* Main_pnlLR_3;
leCircleWidget* Main_circLRKnob_3;
leLabelWidget* Main_lblChNum_3;
leLabelWidget* Main_lblL_3;
leLabelWidget* Main_lbl10_3;
leLabelWidget* Main_lblR_3;
leLabelWidget* Main_lbl5_3;
leLabelWidget* Main_lbl0_3;
leLabelWidget* Main_lbln5_3;
leLabelWidget* Main_lbln10_3;
leLabelWidget* Main_lbln15_3;
leLabelWidget* Main_lbln20_3;
leLabelWidget* Main_lbln25_3;
leLabelWidget* Main_lblChName_3;
leButtonWidget* Main_btnGainKnob_3;
leButtonWidget* Main_btnCue_2;
leWidget* Main_pnlGain_2;
leButtonWidget* Main_btnM_2;
leButtonWidget* Main_btnS_2;
leProgressBarWidget* Main_pbarAmp_2;
leWidget* Main_pnlColorBar_2;
leWidget* Main_pnlLR_2;
leCircleWidget* Main_circLRKnob_2;
leLabelWidget* Main_lblChNum_2;
leLabelWidget* Main_lblL_2;
leLabelWidget* Main_lbl10_2;
leLabelWidget* Main_lblR_2;
leLabelWidget* Main_lbl5_2;
leLabelWidget* Main_lbl0_2;
leLabelWidget* Main_lbln5_2;
leLabelWidget* Main_lbln10_2;
leLabelWidget* Main_lbln15_2;
leLabelWidget* Main_lbln20_2;
leLabelWidget* Main_lbln25_2;
leLabelWidget* Main_lblChName_2;
leButtonWidget* Main_btnGainKnob_2;
leButtonWidget* Main_btnCue;
leWidget* Main_pnlGain;
leButtonWidget* Main_btnM;
leButtonWidget* Main_btnS;
leProgressBarWidget* Main_pbarAmp;
leWidget* Main_pnlColorBar;
leWidget* Main_pnlLR;
leCircleWidget* Main_circLRKnob;
leLabelWidget* Main_lblChNum;
leLabelWidget* Main_lblL;
leLabelWidget* Main_lbl10;
leLabelWidget* Main_lblR;
leLabelWidget* Main_lbl5;
leLabelWidget* Main_lbl0;
leLabelWidget* Main_lbln5;
leLabelWidget* Main_lbln10;
leLabelWidget* Main_lbln15;
leLabelWidget* Main_lbln20;
leLabelWidget* Main_lbln25;
leLabelWidget* Main_lblChName;
leButtonWidget* Main_btnGainKnob;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_Main(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_Main(void)
{
    if(showing == LE_TRUE)
        return LE_FAILURE;

    // layer 0
    root0 = leWidget_New();
    root0->fn->setSize(root0, 800, 480);
    root0->fn->setBackgroundType(root0, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->setMargins(root0, 0, 0, 0, 0);
    root0->flags |= LE_WIDGET_IGNOREEVENTS;
    root0->flags |= LE_WIDGET_IGNOREPICK;

    Main_PanelWidget_0 = leWidget_New();
    Main_PanelWidget_0->fn->setPosition(Main_PanelWidget_0, 0, 0);
    Main_PanelWidget_0->fn->setSize(Main_PanelWidget_0, 800, 480);
    Main_PanelWidget_0->fn->setScheme(Main_PanelWidget_0, &BaseScheme);
    root0->fn->addChild(root0, (leWidget*)Main_PanelWidget_0);

    Main_PanelWidget_0_0 = leWidget_New();
    Main_PanelWidget_0_0->fn->setPosition(Main_PanelWidget_0_0, 0, 66);
    Main_PanelWidget_0_0->fn->setSize(Main_PanelWidget_0_0, 457, 413);
    Main_PanelWidget_0_0->fn->setScheme(Main_PanelWidget_0_0, &PanelScheme);
    root0->fn->addChild(root0, (leWidget*)Main_PanelWidget_0_0);

    Main_btnInputCh1 = leButtonWidget_New();
    Main_btnInputCh1->fn->setPosition(Main_btnInputCh1, 0, 0);
    Main_btnInputCh1->fn->setSize(Main_btnInputCh1, 110, 65);
    Main_btnInputCh1->fn->setScheme(Main_btnInputCh1, &WhiteTextScheme);
    Main_btnInputCh1->fn->setBackgroundType(Main_btnInputCh1, LE_WIDGET_BACKGROUND_NONE);
    Main_btnInputCh1->fn->setBorderType(Main_btnInputCh1, LE_WIDGET_BORDER_NONE);
    Main_btnInputCh1->fn->setString(Main_btnInputCh1, (leString*)&string_StringI2S);
    Main_btnInputCh1->fn->setPressedImage(Main_btnInputCh1, (leImage*)&Button1Down);
    Main_btnInputCh1->fn->setReleasedImage(Main_btnInputCh1, (leImage*)&Button1Up);
    Main_btnInputCh1->fn->setImagePosition(Main_btnInputCh1, LE_RELATIVE_POSITION_BEHIND);
    Main_btnInputCh1->fn->setPressedOffset(Main_btnInputCh1, 0);
    Main_btnInputCh1->fn->setReleasedEventCallback(Main_btnInputCh1, event_Main_btnInputCh1_OnReleased);
    root0->fn->addChild(root0, (leWidget*)Main_btnInputCh1);

    Main_ImageWidget_0_1 = leImageWidget_New();
    Main_ImageWidget_0_1->fn->setPosition(Main_ImageWidget_0_1, 25, 17);
    Main_ImageWidget_0_1->fn->setSize(Main_ImageWidget_0_1, 30, 32);
    Main_ImageWidget_0_1->fn->setEnabled(Main_ImageWidget_0_1, LE_FALSE);
    Main_ImageWidget_0_1->fn->setBackgroundType(Main_ImageWidget_0_1, LE_WIDGET_BACKGROUND_NONE);
    Main_ImageWidget_0_1->fn->setBorderType(Main_ImageWidget_0_1, LE_WIDGET_BORDER_NONE);
    Main_ImageWidget_0_1->fn->setImage(Main_ImageWidget_0_1, (leImage*)&graphic_eq);
    Main_btnInputCh1->fn->addChild(Main_btnInputCh1, (leWidget*)Main_ImageWidget_0_1);

    Main_btnInputCh2 = leButtonWidget_New();
    Main_btnInputCh2->fn->setPosition(Main_btnInputCh2, 111, 1);
    Main_btnInputCh2->fn->setSize(Main_btnInputCh2, 110, 65);
    Main_btnInputCh2->fn->setScheme(Main_btnInputCh2, &WhiteTextScheme);
    Main_btnInputCh2->fn->setBackgroundType(Main_btnInputCh2, LE_WIDGET_BACKGROUND_NONE);
    Main_btnInputCh2->fn->setBorderType(Main_btnInputCh2, LE_WIDGET_BORDER_NONE);
    Main_btnInputCh2->fn->setString(Main_btnInputCh2, (leString*)&string_StringUSB);
    Main_btnInputCh2->fn->setPressedImage(Main_btnInputCh2, (leImage*)&Button1Down);
    Main_btnInputCh2->fn->setReleasedImage(Main_btnInputCh2, (leImage*)&Button1Up);
    Main_btnInputCh2->fn->setImagePosition(Main_btnInputCh2, LE_RELATIVE_POSITION_BEHIND);
    Main_btnInputCh2->fn->setPressedOffset(Main_btnInputCh2, 0);
    Main_btnInputCh2->fn->setReleasedEventCallback(Main_btnInputCh2, event_Main_btnInputCh2_OnReleased);
    root0->fn->addChild(root0, (leWidget*)Main_btnInputCh2);

    Main_ImageWidget_0_2 = leImageWidget_New();
    Main_ImageWidget_0_2->fn->setPosition(Main_ImageWidget_0_2, 23, 17);
    Main_ImageWidget_0_2->fn->setSize(Main_ImageWidget_0_2, 30, 32);
    Main_ImageWidget_0_2->fn->setEnabled(Main_ImageWidget_0_2, LE_FALSE);
    Main_ImageWidget_0_2->fn->setBackgroundType(Main_ImageWidget_0_2, LE_WIDGET_BACKGROUND_NONE);
    Main_ImageWidget_0_2->fn->setBorderType(Main_ImageWidget_0_2, LE_WIDGET_BORDER_NONE);
    Main_ImageWidget_0_2->fn->setImage(Main_ImageWidget_0_2, (leImage*)&graphic_eq);
    Main_btnInputCh2->fn->addChild(Main_btnInputCh2, (leWidget*)Main_ImageWidget_0_2);

    Main_btnInputCh3 = leButtonWidget_New();
    Main_btnInputCh3->fn->setPosition(Main_btnInputCh3, 225, 1);
    Main_btnInputCh3->fn->setSize(Main_btnInputCh3, 110, 65);
    Main_btnInputCh3->fn->setScheme(Main_btnInputCh3, &WhiteTextScheme);
    Main_btnInputCh3->fn->setBackgroundType(Main_btnInputCh3, LE_WIDGET_BACKGROUND_NONE);
    Main_btnInputCh3->fn->setBorderType(Main_btnInputCh3, LE_WIDGET_BORDER_NONE);
    Main_btnInputCh3->fn->setString(Main_btnInputCh3, (leString*)&string_StringEth);
    Main_btnInputCh3->fn->setPressedImage(Main_btnInputCh3, (leImage*)&Button1Down);
    Main_btnInputCh3->fn->setReleasedImage(Main_btnInputCh3, (leImage*)&Button1Up);
    Main_btnInputCh3->fn->setImagePosition(Main_btnInputCh3, LE_RELATIVE_POSITION_BEHIND);
    Main_btnInputCh3->fn->setPressedOffset(Main_btnInputCh3, 0);
    Main_btnInputCh3->fn->setReleasedEventCallback(Main_btnInputCh3, event_Main_btnInputCh3_OnReleased);
    root0->fn->addChild(root0, (leWidget*)Main_btnInputCh3);

    Main_ImageWidget_0_2_0 = leImageWidget_New();
    Main_ImageWidget_0_2_0->fn->setPosition(Main_ImageWidget_0_2_0, 24, 16);
    Main_ImageWidget_0_2_0->fn->setSize(Main_ImageWidget_0_2_0, 30, 32);
    Main_ImageWidget_0_2_0->fn->setEnabled(Main_ImageWidget_0_2_0, LE_FALSE);
    Main_ImageWidget_0_2_0->fn->setBackgroundType(Main_ImageWidget_0_2_0, LE_WIDGET_BACKGROUND_NONE);
    Main_ImageWidget_0_2_0->fn->setBorderType(Main_ImageWidget_0_2_0, LE_WIDGET_BORDER_NONE);
    Main_ImageWidget_0_2_0->fn->setImage(Main_ImageWidget_0_2_0, (leImage*)&graphic_eq);
    Main_btnInputCh3->fn->addChild(Main_btnInputCh3, (leWidget*)Main_ImageWidget_0_2_0);

    Main_btnInputCh4 = leButtonWidget_New();
    Main_btnInputCh4->fn->setPosition(Main_btnInputCh4, 341, 1);
    Main_btnInputCh4->fn->setSize(Main_btnInputCh4, 110, 65);
    Main_btnInputCh4->fn->setScheme(Main_btnInputCh4, &WhiteTextScheme);
    Main_btnInputCh4->fn->setBackgroundType(Main_btnInputCh4, LE_WIDGET_BACKGROUND_NONE);
    Main_btnInputCh4->fn->setBorderType(Main_btnInputCh4, LE_WIDGET_BORDER_NONE);
    Main_btnInputCh4->fn->setString(Main_btnInputCh4, (leString*)&string_StringPCM);
    Main_btnInputCh4->fn->setPressedImage(Main_btnInputCh4, (leImage*)&Button1Down);
    Main_btnInputCh4->fn->setReleasedImage(Main_btnInputCh4, (leImage*)&Button1Up);
    Main_btnInputCh4->fn->setImagePosition(Main_btnInputCh4, LE_RELATIVE_POSITION_BEHIND);
    Main_btnInputCh4->fn->setPressedOffset(Main_btnInputCh4, 0);
    Main_btnInputCh4->fn->setReleasedEventCallback(Main_btnInputCh4, event_Main_btnInputCh4_OnReleased);
    root0->fn->addChild(root0, (leWidget*)Main_btnInputCh4);

    Main_ImageWidget_0_2_1 = leImageWidget_New();
    Main_ImageWidget_0_2_1->fn->setPosition(Main_ImageWidget_0_2_1, 22, 18);
    Main_ImageWidget_0_2_1->fn->setSize(Main_ImageWidget_0_2_1, 30, 32);
    Main_ImageWidget_0_2_1->fn->setEnabled(Main_ImageWidget_0_2_1, LE_FALSE);
    Main_ImageWidget_0_2_1->fn->setBackgroundType(Main_ImageWidget_0_2_1, LE_WIDGET_BACKGROUND_NONE);
    Main_ImageWidget_0_2_1->fn->setBorderType(Main_ImageWidget_0_2_1, LE_WIDGET_BORDER_NONE);
    Main_ImageWidget_0_2_1->fn->setImage(Main_ImageWidget_0_2_1, (leImage*)&graphic_eq);
    Main_btnInputCh4->fn->addChild(Main_btnInputCh4, (leWidget*)Main_ImageWidget_0_2_1);

    Main_btnRun = leButtonWidget_New();
    Main_btnRun->fn->setPosition(Main_btnRun, 625, 2);
    Main_btnRun->fn->setSize(Main_btnRun, 172, 70);
    Main_btnRun->fn->setScheme(Main_btnRun, &WhiteTextScheme);
    Main_btnRun->fn->setBackgroundType(Main_btnRun, LE_WIDGET_BACKGROUND_NONE);
    Main_btnRun->fn->setBorderType(Main_btnRun, LE_WIDGET_BORDER_NONE);
    Main_btnRun->fn->setMargins(Main_btnRun, 4, 0, 4, 4);
    Main_btnRun->fn->setString(Main_btnRun, (leString*)&string_StringRun);
    Main_btnRun->fn->setPressedImage(Main_btnRun, (leImage*)&Button2Down);
    Main_btnRun->fn->setReleasedImage(Main_btnRun, (leImage*)&Button2Up);
    Main_btnRun->fn->setImagePosition(Main_btnRun, LE_RELATIVE_POSITION_BEHIND);
    Main_btnRun->fn->setPressedOffset(Main_btnRun, 0);
    Main_btnRun->fn->setReleasedEventCallback(Main_btnRun, event_Main_btnRun_OnReleased);
    root0->fn->addChild(root0, (leWidget*)Main_btnRun);

    Main_btnOutputCh1 = leButtonWidget_New();
    Main_btnOutputCh1->fn->setPosition(Main_btnOutputCh1, 473, 134);
    Main_btnOutputCh1->fn->setSize(Main_btnOutputCh1, 213, 70);
    Main_btnOutputCh1->fn->setScheme(Main_btnOutputCh1, &WhiteTextScheme);
    Main_btnOutputCh1->fn->setBackgroundType(Main_btnOutputCh1, LE_WIDGET_BACKGROUND_NONE);
    Main_btnOutputCh1->fn->setBorderType(Main_btnOutputCh1, LE_WIDGET_BORDER_NONE);
    Main_btnOutputCh1->fn->setString(Main_btnOutputCh1, (leString*)&string_StringI2S);
    Main_btnOutputCh1->fn->setPressedImage(Main_btnOutputCh1, (leImage*)&Button3Down);
    Main_btnOutputCh1->fn->setReleasedImage(Main_btnOutputCh1, (leImage*)&Button3Up);
    Main_btnOutputCh1->fn->setImagePosition(Main_btnOutputCh1, LE_RELATIVE_POSITION_BEHIND);
    Main_btnOutputCh1->fn->setPressedOffset(Main_btnOutputCh1, 0);
    Main_btnOutputCh1->fn->setReleasedEventCallback(Main_btnOutputCh1, event_Main_btnOutputCh1_OnReleased);
    root0->fn->addChild(root0, (leWidget*)Main_btnOutputCh1);

    Main_ImageWidget_0 = leImageWidget_New();
    Main_ImageWidget_0->fn->setPosition(Main_ImageWidget_0, 71, 20);
    Main_ImageWidget_0->fn->setSize(Main_ImageWidget_0, 30, 32);
    Main_ImageWidget_0->fn->setEnabled(Main_ImageWidget_0, LE_FALSE);
    Main_ImageWidget_0->fn->setBackgroundType(Main_ImageWidget_0, LE_WIDGET_BACKGROUND_NONE);
    Main_ImageWidget_0->fn->setBorderType(Main_ImageWidget_0, LE_WIDGET_BORDER_NONE);
    Main_ImageWidget_0->fn->setImage(Main_ImageWidget_0, (leImage*)&graphic_eq);
    Main_btnOutputCh1->fn->addChild(Main_btnOutputCh1, (leWidget*)Main_ImageWidget_0);

    Main_btnOutputCh2 = leButtonWidget_New();
    Main_btnOutputCh2->fn->setPosition(Main_btnOutputCh2, 474, 203);
    Main_btnOutputCh2->fn->setSize(Main_btnOutputCh2, 213, 70);
    Main_btnOutputCh2->fn->setScheme(Main_btnOutputCh2, &WhiteTextScheme);
    Main_btnOutputCh2->fn->setBackgroundType(Main_btnOutputCh2, LE_WIDGET_BACKGROUND_NONE);
    Main_btnOutputCh2->fn->setBorderType(Main_btnOutputCh2, LE_WIDGET_BORDER_NONE);
    Main_btnOutputCh2->fn->setString(Main_btnOutputCh2, (leString*)&string_StringUSB);
    Main_btnOutputCh2->fn->setPressedImage(Main_btnOutputCh2, (leImage*)&Button3Down);
    Main_btnOutputCh2->fn->setReleasedImage(Main_btnOutputCh2, (leImage*)&Button3Up);
    Main_btnOutputCh2->fn->setImagePosition(Main_btnOutputCh2, LE_RELATIVE_POSITION_BEHIND);
    Main_btnOutputCh2->fn->setPressedOffset(Main_btnOutputCh2, 0);
    Main_btnOutputCh2->fn->setReleasedEventCallback(Main_btnOutputCh2, event_Main_btnOutputCh2_OnReleased);
    root0->fn->addChild(root0, (leWidget*)Main_btnOutputCh2);

    Main_ImageWidget_0_0 = leImageWidget_New();
    Main_ImageWidget_0_0->fn->setPosition(Main_ImageWidget_0_0, 70, 19);
    Main_ImageWidget_0_0->fn->setSize(Main_ImageWidget_0_0, 30, 32);
    Main_ImageWidget_0_0->fn->setEnabled(Main_ImageWidget_0_0, LE_FALSE);
    Main_ImageWidget_0_0->fn->setBackgroundType(Main_ImageWidget_0_0, LE_WIDGET_BACKGROUND_NONE);
    Main_ImageWidget_0_0->fn->setBorderType(Main_ImageWidget_0_0, LE_WIDGET_BORDER_NONE);
    Main_ImageWidget_0_0->fn->setImage(Main_ImageWidget_0_0, (leImage*)&graphic_eq);
    Main_btnOutputCh2->fn->addChild(Main_btnOutputCh2, (leWidget*)Main_ImageWidget_0_0);

    Main_btnOutputCh3 = leButtonWidget_New();
    Main_btnOutputCh3->fn->setPosition(Main_btnOutputCh3, 474, 272);
    Main_btnOutputCh3->fn->setSize(Main_btnOutputCh3, 213, 70);
    Main_btnOutputCh3->fn->setScheme(Main_btnOutputCh3, &WhiteTextScheme);
    Main_btnOutputCh3->fn->setBackgroundType(Main_btnOutputCh3, LE_WIDGET_BACKGROUND_NONE);
    Main_btnOutputCh3->fn->setBorderType(Main_btnOutputCh3, LE_WIDGET_BORDER_NONE);
    Main_btnOutputCh3->fn->setString(Main_btnOutputCh3, (leString*)&string_StringEth);
    Main_btnOutputCh3->fn->setPressedImage(Main_btnOutputCh3, (leImage*)&Button3Down);
    Main_btnOutputCh3->fn->setReleasedImage(Main_btnOutputCh3, (leImage*)&Button3Up);
    Main_btnOutputCh3->fn->setImagePosition(Main_btnOutputCh3, LE_RELATIVE_POSITION_BEHIND);
    Main_btnOutputCh3->fn->setPressedOffset(Main_btnOutputCh3, 0);
    Main_btnOutputCh3->fn->setReleasedEventCallback(Main_btnOutputCh3, event_Main_btnOutputCh3_OnReleased);
    root0->fn->addChild(root0, (leWidget*)Main_btnOutputCh3);

    Main_ImageWidget_0_0_0 = leImageWidget_New();
    Main_ImageWidget_0_0_0->fn->setPosition(Main_ImageWidget_0_0_0, 69, 20);
    Main_ImageWidget_0_0_0->fn->setSize(Main_ImageWidget_0_0_0, 30, 32);
    Main_ImageWidget_0_0_0->fn->setEnabled(Main_ImageWidget_0_0_0, LE_FALSE);
    Main_ImageWidget_0_0_0->fn->setBackgroundType(Main_ImageWidget_0_0_0, LE_WIDGET_BACKGROUND_NONE);
    Main_ImageWidget_0_0_0->fn->setBorderType(Main_ImageWidget_0_0_0, LE_WIDGET_BORDER_NONE);
    Main_ImageWidget_0_0_0->fn->setImage(Main_ImageWidget_0_0_0, (leImage*)&graphic_eq);
    Main_btnOutputCh3->fn->addChild(Main_btnOutputCh3, (leWidget*)Main_ImageWidget_0_0_0);

    Main_btnOutputCh4 = leButtonWidget_New();
    Main_btnOutputCh4->fn->setPosition(Main_btnOutputCh4, 476, 341);
    Main_btnOutputCh4->fn->setSize(Main_btnOutputCh4, 213, 70);
    Main_btnOutputCh4->fn->setScheme(Main_btnOutputCh4, &WhiteTextScheme);
    Main_btnOutputCh4->fn->setBackgroundType(Main_btnOutputCh4, LE_WIDGET_BACKGROUND_NONE);
    Main_btnOutputCh4->fn->setBorderType(Main_btnOutputCh4, LE_WIDGET_BORDER_NONE);
    Main_btnOutputCh4->fn->setString(Main_btnOutputCh4, (leString*)&string_StringPCM);
    Main_btnOutputCh4->fn->setPressedImage(Main_btnOutputCh4, (leImage*)&Button3Down);
    Main_btnOutputCh4->fn->setReleasedImage(Main_btnOutputCh4, (leImage*)&Button3Up);
    Main_btnOutputCh4->fn->setImagePosition(Main_btnOutputCh4, LE_RELATIVE_POSITION_BEHIND);
    Main_btnOutputCh4->fn->setPressedOffset(Main_btnOutputCh4, 0);
    Main_btnOutputCh4->fn->setReleasedEventCallback(Main_btnOutputCh4, event_Main_btnOutputCh4_OnReleased);
    root0->fn->addChild(root0, (leWidget*)Main_btnOutputCh4);

    Main_ImageWidget_0_0_1 = leImageWidget_New();
    Main_ImageWidget_0_0_1->fn->setPosition(Main_ImageWidget_0_0_1, 69, 21);
    Main_ImageWidget_0_0_1->fn->setSize(Main_ImageWidget_0_0_1, 30, 32);
    Main_ImageWidget_0_0_1->fn->setEnabled(Main_ImageWidget_0_0_1, LE_FALSE);
    Main_ImageWidget_0_0_1->fn->setBackgroundType(Main_ImageWidget_0_0_1, LE_WIDGET_BACKGROUND_NONE);
    Main_ImageWidget_0_0_1->fn->setBorderType(Main_ImageWidget_0_0_1, LE_WIDGET_BORDER_NONE);
    Main_ImageWidget_0_0_1->fn->setImage(Main_ImageWidget_0_0_1, (leImage*)&graphic_eq);
    Main_btnOutputCh4->fn->addChild(Main_btnOutputCh4, (leWidget*)Main_ImageWidget_0_0_1);

    Main_pbarAmpMain = leProgressBarWidget_New();
    Main_pbarAmpMain->fn->setPosition(Main_pbarAmpMain, 717, 150);
    Main_pbarAmpMain->fn->setSize(Main_pbarAmpMain, 16, 270);
    Main_pbarAmpMain->fn->setScheme(Main_pbarAmpMain, &BarScheme);
    Main_pbarAmpMain->fn->setBorderType(Main_pbarAmpMain, LE_WIDGET_BORDER_NONE);
    Main_pbarAmpMain->fn->setDirection(Main_pbarAmpMain, LE_PROGRESSBAR_DIRECTION_UP);
    Main_pbarAmpMain->fn->setValue(Main_pbarAmpMain, 55);
    root0->fn->addChild(root0, (leWidget*)Main_pbarAmpMain);

    Main_pnlMainGain = leWidget_New();
    Main_pnlMainGain->fn->setPosition(Main_pnlMainGain, 755, 150);
    Main_pnlMainGain->fn->setSize(Main_pnlMainGain, 11, 270);
    Main_pnlMainGain->fn->setScheme(Main_pnlMainGain, &BarScheme);
    root0->fn->addChild(root0, (leWidget*)Main_pnlMainGain);

    Main_btnMainGain = leButtonWidget_New();
    Main_btnMainGain->fn->setPosition(Main_btnMainGain, 738, 169);
    Main_btnMainGain->fn->setSize(Main_btnMainGain, 46, 65);
    Main_btnMainGain->fn->setBackgroundType(Main_btnMainGain, LE_WIDGET_BACKGROUND_NONE);
    Main_btnMainGain->fn->setBorderType(Main_btnMainGain, LE_WIDGET_BORDER_NONE);
    Main_btnMainGain->fn->setPressedImage(Main_btnMainGain, (leImage*)&SliderKnob);
    Main_btnMainGain->fn->setReleasedImage(Main_btnMainGain, (leImage*)&SliderKnob);
    root0->fn->addChild(root0, (leWidget*)Main_btnMainGain);

    Main_btnMainMute = leButtonWidget_New();
    Main_btnMainMute->fn->setPosition(Main_btnMainMute, 692, 429);
    Main_btnMainMute->fn->setSize(Main_btnMainMute, 98, 45);
    Main_btnMainMute->fn->setScheme(Main_btnMainMute, &WhiteTextScheme);
    Main_btnMainMute->fn->setBackgroundType(Main_btnMainMute, LE_WIDGET_BACKGROUND_NONE);
    Main_btnMainMute->fn->setBorderType(Main_btnMainMute, LE_WIDGET_BORDER_NONE);
    Main_btnMainMute->fn->setString(Main_btnMainMute, (leString*)&string_StringMute);
    Main_btnMainMute->fn->setPressedImage(Main_btnMainMute, (leImage*)&SmallButtonDown);
    Main_btnMainMute->fn->setReleasedImage(Main_btnMainMute, (leImage*)&SmallButtonUp);
    Main_btnMainMute->fn->setImagePosition(Main_btnMainMute, LE_RELATIVE_POSITION_BEHIND);
    Main_btnMainMute->fn->setPressedOffset(Main_btnMainMute, 0);
    Main_btnMainMute->fn->setReleasedEventCallback(Main_btnMainMute, event_Main_btnMainMute_OnReleased);
    root0->fn->addChild(root0, (leWidget*)Main_btnMainMute);

    Main_pnlColorBarMain = leWidget_New();
    Main_pnlColorBarMain->fn->setPosition(Main_pnlColorBarMain, 708, 94);
    Main_pnlColorBarMain->fn->setSize(Main_pnlColorBarMain, 69, 6);
    Main_pnlColorBarMain->fn->setScheme(Main_pnlColorBarMain, &GrayScheme);
    root0->fn->addChild(root0, (leWidget*)Main_pnlColorBarMain);

    Main_lblOutput = leLabelWidget_New();
    Main_lblOutput->fn->setPosition(Main_lblOutput, 517, 91);
    Main_lblOutput->fn->setSize(Main_lblOutput, 129, 43);
    Main_lblOutput->fn->setScheme(Main_lblOutput, &WhiteTextScheme);
    Main_lblOutput->fn->setBackgroundType(Main_lblOutput, LE_WIDGET_BACKGROUND_NONE);
    Main_lblOutput->fn->setHAlignment(Main_lblOutput, LE_HALIGN_CENTER);
    Main_lblOutput->fn->setString(Main_lblOutput, (leString*)&string_StringOutput);
    root0->fn->addChild(root0, (leWidget*)Main_lblOutput);

    Main_lblMain = leLabelWidget_New();
    Main_lblMain->fn->setPosition(Main_lblMain, 707, 102);
    Main_lblMain->fn->setSize(Main_lblMain, 67, 36);
    Main_lblMain->fn->setScheme(Main_lblMain, &WhiteTextScheme);
    Main_lblMain->fn->setBackgroundType(Main_lblMain, LE_WIDGET_BACKGROUND_NONE);
    Main_lblMain->fn->setHAlignment(Main_lblMain, LE_HALIGN_CENTER);
    Main_lblMain->fn->setString(Main_lblMain, (leString*)&string_StringMain);
    root0->fn->addChild(root0, (leWidget*)Main_lblMain);

    Main_pnlChnCtrlCh4 = leWidget_New();
    Main_pnlChnCtrlCh4->fn->setPosition(Main_pnlChnCtrlCh4, 348, 74);
    Main_pnlChnCtrlCh4->fn->setSize(Main_pnlChnCtrlCh4, 98, 408);
    Main_pnlChnCtrlCh4->fn->setBackgroundType(Main_pnlChnCtrlCh4, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->addChild(root0, (leWidget*)Main_pnlChnCtrlCh4);

    Main_btnCue_4 = leButtonWidget_New();
    Main_btnCue_4->fn->setPosition(Main_btnCue_4, 3, 61);
    Main_btnCue_4->fn->setSize(Main_btnCue_4, 90, 40);
    Main_btnCue_4->fn->setScheme(Main_btnCue_4, &WhiteTextScheme);
    Main_btnCue_4->fn->setBackgroundType(Main_btnCue_4, LE_WIDGET_BACKGROUND_NONE);
    Main_btnCue_4->fn->setBorderType(Main_btnCue_4, LE_WIDGET_BORDER_NONE);
    Main_btnCue_4->fn->setString(Main_btnCue_4, (leString*)&string_StringCue);
    Main_btnCue_4->fn->setPressedImage(Main_btnCue_4, (leImage*)&SmallButtonDown);
    Main_btnCue_4->fn->setReleasedImage(Main_btnCue_4, (leImage*)&SmallButtonUp);
    Main_btnCue_4->fn->setImagePosition(Main_btnCue_4, LE_RELATIVE_POSITION_BEHIND);
    Main_btnCue_4->fn->setPressedOffset(Main_btnCue_4, 0);
    Main_btnCue_4->fn->setReleasedEventCallback(Main_btnCue_4, event_Main_btnCue_4_OnReleased);
    Main_pnlChnCtrlCh4->fn->addChild(Main_pnlChnCtrlCh4, (leWidget*)Main_btnCue_4);

    Main_pnlGain_4 = leWidget_New();
    Main_pnlGain_4->fn->setPosition(Main_pnlGain_4, 64, 141);
    Main_pnlGain_4->fn->setSize(Main_pnlGain_4, 8, 220);
    Main_pnlGain_4->fn->setScheme(Main_pnlGain_4, &BarScheme);
    Main_pnlChnCtrlCh4->fn->addChild(Main_pnlChnCtrlCh4, (leWidget*)Main_pnlGain_4);

    Main_btnM_4 = leButtonWidget_New();
    Main_btnM_4->fn->setPosition(Main_btnM_4, -4, 367);
    Main_btnM_4->fn->setSize(Main_btnM_4, 54, 40);
    Main_btnM_4->fn->setScheme(Main_btnM_4, &WhiteTextScheme);
    Main_btnM_4->fn->setBackgroundType(Main_btnM_4, LE_WIDGET_BACKGROUND_NONE);
    Main_btnM_4->fn->setBorderType(Main_btnM_4, LE_WIDGET_BORDER_NONE);
    Main_btnM_4->fn->setHAlignment(Main_btnM_4, LE_HALIGN_RIGHT);
    Main_btnM_4->fn->setString(Main_btnM_4, (leString*)&string_StringM);
    Main_btnM_4->fn->setPressedImage(Main_btnM_4, (leImage*)&Small2ButtonDown);
    Main_btnM_4->fn->setReleasedImage(Main_btnM_4, (leImage*)&Small2ButtonUp);
    Main_btnM_4->fn->setImagePosition(Main_btnM_4, LE_RELATIVE_POSITION_BEHIND);
    Main_btnM_4->fn->setPressedOffset(Main_btnM_4, 0);
    Main_btnM_4->fn->setReleasedEventCallback(Main_btnM_4, event_Main_btnM_4_OnReleased);
    Main_pnlChnCtrlCh4->fn->addChild(Main_pnlChnCtrlCh4, (leWidget*)Main_btnM_4);

    Main_btnS_4 = leButtonWidget_New();
    Main_btnS_4->fn->setPosition(Main_btnS_4, 48, 367);
    Main_btnS_4->fn->setSize(Main_btnS_4, 50, 40);
    Main_btnS_4->fn->setScheme(Main_btnS_4, &WhiteTextScheme);
    Main_btnS_4->fn->setBackgroundType(Main_btnS_4, LE_WIDGET_BACKGROUND_NONE);
    Main_btnS_4->fn->setBorderType(Main_btnS_4, LE_WIDGET_BORDER_NONE);
    Main_btnS_4->fn->setHAlignment(Main_btnS_4, LE_HALIGN_LEFT);
    Main_btnS_4->fn->setString(Main_btnS_4, (leString*)&string_StringS);
    Main_btnS_4->fn->setPressedImage(Main_btnS_4, (leImage*)&Small2ButtonDown);
    Main_btnS_4->fn->setReleasedImage(Main_btnS_4, (leImage*)&Small2ButtonUp);
    Main_btnS_4->fn->setImagePosition(Main_btnS_4, LE_RELATIVE_POSITION_BEHIND);
    Main_btnS_4->fn->setPressedOffset(Main_btnS_4, 0);
    Main_btnS_4->fn->setReleasedEventCallback(Main_btnS_4, event_Main_btnS_4_OnReleased);
    Main_pnlChnCtrlCh4->fn->addChild(Main_pnlChnCtrlCh4, (leWidget*)Main_btnS_4);

    Main_pbarAmp_4 = leProgressBarWidget_New();
    Main_pbarAmp_4->fn->setPosition(Main_pbarAmp_4, 33, 141);
    Main_pbarAmp_4->fn->setSize(Main_pbarAmp_4, 14, 220);
    Main_pbarAmp_4->fn->setScheme(Main_pbarAmp_4, &BarScheme);
    Main_pbarAmp_4->fn->setBorderType(Main_pbarAmp_4, LE_WIDGET_BORDER_NONE);
    Main_pbarAmp_4->fn->setDirection(Main_pbarAmp_4, LE_PROGRESSBAR_DIRECTION_UP);
    Main_pbarAmp_4->fn->setValue(Main_pbarAmp_4, 70);
    Main_pnlChnCtrlCh4->fn->addChild(Main_pnlChnCtrlCh4, (leWidget*)Main_pbarAmp_4);

    Main_pnlColorBar_4 = leWidget_New();
    Main_pnlColorBar_4->fn->setPosition(Main_pnlColorBar_4, 14, 0);
    Main_pnlColorBar_4->fn->setSize(Main_pnlColorBar_4, 70, 6);
    Main_pnlColorBar_4->fn->setScheme(Main_pnlColorBar_4, &RedScheme);
    Main_pnlChnCtrlCh4->fn->addChild(Main_pnlChnCtrlCh4, (leWidget*)Main_pnlColorBar_4);

    Main_pnlLR_4 = leWidget_New();
    Main_pnlLR_4->fn->setPosition(Main_pnlLR_4, 18, 119);
    Main_pnlLR_4->fn->setSize(Main_pnlLR_4, 60, 8);
    Main_pnlLR_4->fn->setScheme(Main_pnlLR_4, &BarScheme);
    Main_pnlChnCtrlCh4->fn->addChild(Main_pnlChnCtrlCh4, (leWidget*)Main_pnlLR_4);

    Main_circLRKnob_4 = leCircleWidget_New();
    Main_circLRKnob_4->fn->setPosition(Main_circLRKnob_4, 39, 113);
    Main_circLRKnob_4->fn->setSize(Main_circLRKnob_4, 20, 20);
    Main_circLRKnob_4->fn->setScheme(Main_circLRKnob_4, &WhiteTextScheme);
    Main_circLRKnob_4->fn->setRadius(Main_circLRKnob_4, 5);
    Main_circLRKnob_4->fn->setThickness(Main_circLRKnob_4, 3);
    Main_circLRKnob_4->fn->setFilled(Main_circLRKnob_4, LE_TRUE);
    Main_pnlChnCtrlCh4->fn->addChild(Main_pnlChnCtrlCh4, (leWidget*)Main_circLRKnob_4);

    Main_lblChNum_4 = leLabelWidget_New();
    Main_lblChNum_4->fn->setPosition(Main_lblChNum_4, 13, 10);
    Main_lblChNum_4->fn->setSize(Main_lblChNum_4, 71, 19);
    Main_lblChNum_4->fn->setScheme(Main_lblChNum_4, &WhiteTextScheme);
    Main_lblChNum_4->fn->setBackgroundType(Main_lblChNum_4, LE_WIDGET_BACKGROUND_NONE);
    Main_lblChNum_4->fn->setHAlignment(Main_lblChNum_4, LE_HALIGN_CENTER);
    Main_lblChNum_4->fn->setString(Main_lblChNum_4, (leString*)&string_StringCh4);
    Main_pnlChnCtrlCh4->fn->addChild(Main_pnlChnCtrlCh4, (leWidget*)Main_lblChNum_4);

    Main_lblL_4 = leLabelWidget_New();
    Main_lblL_4->fn->setPosition(Main_lblL_4, 14, 98);
    Main_lblL_4->fn->setSize(Main_lblL_4, 20, 20);
    Main_lblL_4->fn->setScheme(Main_lblL_4, &WhiteTextScheme);
    Main_lblL_4->fn->setBackgroundType(Main_lblL_4, LE_WIDGET_BACKGROUND_NONE);
    Main_lblL_4->fn->setHAlignment(Main_lblL_4, LE_HALIGN_CENTER);
    Main_lblL_4->fn->setString(Main_lblL_4, (leString*)&string_StringL);
    Main_pnlChnCtrlCh4->fn->addChild(Main_pnlChnCtrlCh4, (leWidget*)Main_lblL_4);

    Main_lbl10_4 = leLabelWidget_New();
    Main_lbl10_4->fn->setPosition(Main_lbl10_4, 1, 134);
    Main_lbl10_4->fn->setSize(Main_lbl10_4, 26, 20);
    Main_lbl10_4->fn->setScheme(Main_lbl10_4, &GrayScheme);
    Main_lbl10_4->fn->setBackgroundType(Main_lbl10_4, LE_WIDGET_BACKGROUND_NONE);
    Main_lbl10_4->fn->setHAlignment(Main_lbl10_4, LE_HALIGN_RIGHT);
    Main_lbl10_4->fn->setMargins(Main_lbl10_4, 4, 4, 0, 4);
    Main_lbl10_4->fn->setString(Main_lbl10_4, (leString*)&string_String10);
    Main_pnlChnCtrlCh4->fn->addChild(Main_pnlChnCtrlCh4, (leWidget*)Main_lbl10_4);

    Main_lblR_4 = leLabelWidget_New();
    Main_lblR_4->fn->setPosition(Main_lblR_4, 61, 98);
    Main_lblR_4->fn->setSize(Main_lblR_4, 20, 20);
    Main_lblR_4->fn->setScheme(Main_lblR_4, &WhiteTextScheme);
    Main_lblR_4->fn->setBackgroundType(Main_lblR_4, LE_WIDGET_BACKGROUND_NONE);
    Main_lblR_4->fn->setHAlignment(Main_lblR_4, LE_HALIGN_CENTER);
    Main_lblR_4->fn->setString(Main_lblR_4, (leString*)&string_StringR);
    Main_pnlChnCtrlCh4->fn->addChild(Main_pnlChnCtrlCh4, (leWidget*)Main_lblR_4);

    Main_lbl5_4 = leLabelWidget_New();
    Main_lbl5_4->fn->setPosition(Main_lbl5_4, 1, 164);
    Main_lbl5_4->fn->setSize(Main_lbl5_4, 26, 20);
    Main_lbl5_4->fn->setScheme(Main_lbl5_4, &GrayScheme);
    Main_lbl5_4->fn->setBackgroundType(Main_lbl5_4, LE_WIDGET_BACKGROUND_NONE);
    Main_lbl5_4->fn->setHAlignment(Main_lbl5_4, LE_HALIGN_RIGHT);
    Main_lbl5_4->fn->setMargins(Main_lbl5_4, 4, 4, 0, 4);
    Main_lbl5_4->fn->setString(Main_lbl5_4, (leString*)&string_String5);
    Main_pnlChnCtrlCh4->fn->addChild(Main_pnlChnCtrlCh4, (leWidget*)Main_lbl5_4);

    Main_lbl0_4 = leLabelWidget_New();
    Main_lbl0_4->fn->setPosition(Main_lbl0_4, 1, 194);
    Main_lbl0_4->fn->setSize(Main_lbl0_4, 26, 20);
    Main_lbl0_4->fn->setScheme(Main_lbl0_4, &GrayScheme);
    Main_lbl0_4->fn->setBackgroundType(Main_lbl0_4, LE_WIDGET_BACKGROUND_NONE);
    Main_lbl0_4->fn->setHAlignment(Main_lbl0_4, LE_HALIGN_RIGHT);
    Main_lbl0_4->fn->setMargins(Main_lbl0_4, 4, 4, 0, 4);
    Main_lbl0_4->fn->setString(Main_lbl0_4, (leString*)&string_String0);
    Main_pnlChnCtrlCh4->fn->addChild(Main_pnlChnCtrlCh4, (leWidget*)Main_lbl0_4);

    Main_lbln5_4 = leLabelWidget_New();
    Main_lbln5_4->fn->setPosition(Main_lbln5_4, 1, 224);
    Main_lbln5_4->fn->setSize(Main_lbln5_4, 26, 20);
    Main_lbln5_4->fn->setScheme(Main_lbln5_4, &GrayScheme);
    Main_lbln5_4->fn->setBackgroundType(Main_lbln5_4, LE_WIDGET_BACKGROUND_NONE);
    Main_lbln5_4->fn->setHAlignment(Main_lbln5_4, LE_HALIGN_RIGHT);
    Main_lbln5_4->fn->setMargins(Main_lbln5_4, 4, 4, 0, 4);
    Main_lbln5_4->fn->setString(Main_lbln5_4, (leString*)&string_Stringn5);
    Main_pnlChnCtrlCh4->fn->addChild(Main_pnlChnCtrlCh4, (leWidget*)Main_lbln5_4);

    Main_lbln10_4 = leLabelWidget_New();
    Main_lbln10_4->fn->setPosition(Main_lbln10_4, 1, 254);
    Main_lbln10_4->fn->setSize(Main_lbln10_4, 26, 20);
    Main_lbln10_4->fn->setScheme(Main_lbln10_4, &GrayScheme);
    Main_lbln10_4->fn->setBackgroundType(Main_lbln10_4, LE_WIDGET_BACKGROUND_NONE);
    Main_lbln10_4->fn->setHAlignment(Main_lbln10_4, LE_HALIGN_RIGHT);
    Main_lbln10_4->fn->setMargins(Main_lbln10_4, 4, 4, 0, 4);
    Main_lbln10_4->fn->setString(Main_lbln10_4, (leString*)&string_Stringn10);
    Main_pnlChnCtrlCh4->fn->addChild(Main_pnlChnCtrlCh4, (leWidget*)Main_lbln10_4);

    Main_lbln15_4 = leLabelWidget_New();
    Main_lbln15_4->fn->setPosition(Main_lbln15_4, 1, 284);
    Main_lbln15_4->fn->setSize(Main_lbln15_4, 26, 20);
    Main_lbln15_4->fn->setScheme(Main_lbln15_4, &GrayScheme);
    Main_lbln15_4->fn->setBackgroundType(Main_lbln15_4, LE_WIDGET_BACKGROUND_NONE);
    Main_lbln15_4->fn->setHAlignment(Main_lbln15_4, LE_HALIGN_RIGHT);
    Main_lbln15_4->fn->setMargins(Main_lbln15_4, 4, 4, 0, 4);
    Main_lbln15_4->fn->setString(Main_lbln15_4, (leString*)&string_Stringn15);
    Main_pnlChnCtrlCh4->fn->addChild(Main_pnlChnCtrlCh4, (leWidget*)Main_lbln15_4);

    Main_lbln20_4 = leLabelWidget_New();
    Main_lbln20_4->fn->setPosition(Main_lbln20_4, 1, 314);
    Main_lbln20_4->fn->setSize(Main_lbln20_4, 26, 20);
    Main_lbln20_4->fn->setScheme(Main_lbln20_4, &GrayScheme);
    Main_lbln20_4->fn->setBackgroundType(Main_lbln20_4, LE_WIDGET_BACKGROUND_NONE);
    Main_lbln20_4->fn->setHAlignment(Main_lbln20_4, LE_HALIGN_RIGHT);
    Main_lbln20_4->fn->setMargins(Main_lbln20_4, 4, 4, 0, 4);
    Main_lbln20_4->fn->setString(Main_lbln20_4, (leString*)&string_Stringn20);
    Main_pnlChnCtrlCh4->fn->addChild(Main_pnlChnCtrlCh4, (leWidget*)Main_lbln20_4);

    Main_lbln25_4 = leLabelWidget_New();
    Main_lbln25_4->fn->setPosition(Main_lbln25_4, 1, 344);
    Main_lbln25_4->fn->setSize(Main_lbln25_4, 26, 20);
    Main_lbln25_4->fn->setScheme(Main_lbln25_4, &GrayScheme);
    Main_lbln25_4->fn->setBackgroundType(Main_lbln25_4, LE_WIDGET_BACKGROUND_NONE);
    Main_lbln25_4->fn->setHAlignment(Main_lbln25_4, LE_HALIGN_RIGHT);
    Main_lbln25_4->fn->setMargins(Main_lbln25_4, 4, 4, 0, 4);
    Main_lbln25_4->fn->setString(Main_lbln25_4, (leString*)&string_Stringn25);
    Main_pnlChnCtrlCh4->fn->addChild(Main_pnlChnCtrlCh4, (leWidget*)Main_lbln25_4);

    Main_lblChName_4 = leLabelWidget_New();
    Main_lblChName_4->fn->setPosition(Main_lblChName_4, 8, 25);
    Main_lblChName_4->fn->setSize(Main_lblChName_4, 80, 30);
    Main_lblChName_4->fn->setScheme(Main_lblChName_4, &WhiteTextScheme);
    Main_lblChName_4->fn->setBackgroundType(Main_lblChName_4, LE_WIDGET_BACKGROUND_NONE);
    Main_lblChName_4->fn->setHAlignment(Main_lblChName_4, LE_HALIGN_CENTER);
    Main_lblChName_4->fn->setString(Main_lblChName_4, (leString*)&string_StringMTX1);
    Main_pnlChnCtrlCh4->fn->addChild(Main_pnlChnCtrlCh4, (leWidget*)Main_lblChName_4);

    Main_btnGainKnob_4 = leButtonWidget_New();
    Main_btnGainKnob_4->fn->setPosition(Main_btnGainKnob_4, 43, 179);
    Main_btnGainKnob_4->fn->setSize(Main_btnGainKnob_4, 50, 50);
    Main_btnGainKnob_4->fn->setBackgroundType(Main_btnGainKnob_4, LE_WIDGET_BACKGROUND_NONE);
    Main_btnGainKnob_4->fn->setBorderType(Main_btnGainKnob_4, LE_WIDGET_BORDER_NONE);
    Main_btnGainKnob_4->fn->setPressedImage(Main_btnGainKnob_4, (leImage*)&SliderKnob);
    Main_btnGainKnob_4->fn->setReleasedImage(Main_btnGainKnob_4, (leImage*)&SliderKnob);
    Main_pnlChnCtrlCh4->fn->addChild(Main_pnlChnCtrlCh4, (leWidget*)Main_btnGainKnob_4);

    Main_pnlChnCtrlCh3 = leWidget_New();
    Main_pnlChnCtrlCh3->fn->setPosition(Main_pnlChnCtrlCh3, 231, 74);
    Main_pnlChnCtrlCh3->fn->setSize(Main_pnlChnCtrlCh3, 98, 408);
    Main_pnlChnCtrlCh3->fn->setBackgroundType(Main_pnlChnCtrlCh3, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->addChild(root0, (leWidget*)Main_pnlChnCtrlCh3);

    Main_btnCue_3 = leButtonWidget_New();
    Main_btnCue_3->fn->setPosition(Main_btnCue_3, 3, 61);
    Main_btnCue_3->fn->setSize(Main_btnCue_3, 90, 40);
    Main_btnCue_3->fn->setScheme(Main_btnCue_3, &WhiteTextScheme);
    Main_btnCue_3->fn->setBackgroundType(Main_btnCue_3, LE_WIDGET_BACKGROUND_NONE);
    Main_btnCue_3->fn->setBorderType(Main_btnCue_3, LE_WIDGET_BORDER_NONE);
    Main_btnCue_3->fn->setString(Main_btnCue_3, (leString*)&string_StringCue);
    Main_btnCue_3->fn->setPressedImage(Main_btnCue_3, (leImage*)&SmallButtonDown);
    Main_btnCue_3->fn->setReleasedImage(Main_btnCue_3, (leImage*)&SmallButtonUp);
    Main_btnCue_3->fn->setImagePosition(Main_btnCue_3, LE_RELATIVE_POSITION_BEHIND);
    Main_btnCue_3->fn->setPressedOffset(Main_btnCue_3, 0);
    Main_btnCue_3->fn->setReleasedEventCallback(Main_btnCue_3, event_Main_btnCue_3_OnReleased);
    Main_pnlChnCtrlCh3->fn->addChild(Main_pnlChnCtrlCh3, (leWidget*)Main_btnCue_3);

    Main_pnlGain_3 = leWidget_New();
    Main_pnlGain_3->fn->setPosition(Main_pnlGain_3, 64, 141);
    Main_pnlGain_3->fn->setSize(Main_pnlGain_3, 8, 220);
    Main_pnlGain_3->fn->setScheme(Main_pnlGain_3, &BarScheme);
    Main_pnlChnCtrlCh3->fn->addChild(Main_pnlChnCtrlCh3, (leWidget*)Main_pnlGain_3);

    Main_btnM_3 = leButtonWidget_New();
    Main_btnM_3->fn->setPosition(Main_btnM_3, -4, 367);
    Main_btnM_3->fn->setSize(Main_btnM_3, 54, 40);
    Main_btnM_3->fn->setScheme(Main_btnM_3, &WhiteTextScheme);
    Main_btnM_3->fn->setBackgroundType(Main_btnM_3, LE_WIDGET_BACKGROUND_NONE);
    Main_btnM_3->fn->setBorderType(Main_btnM_3, LE_WIDGET_BORDER_NONE);
    Main_btnM_3->fn->setHAlignment(Main_btnM_3, LE_HALIGN_RIGHT);
    Main_btnM_3->fn->setString(Main_btnM_3, (leString*)&string_StringM);
    Main_btnM_3->fn->setPressedImage(Main_btnM_3, (leImage*)&Small2ButtonDown);
    Main_btnM_3->fn->setReleasedImage(Main_btnM_3, (leImage*)&Small2ButtonUp);
    Main_btnM_3->fn->setImagePosition(Main_btnM_3, LE_RELATIVE_POSITION_BEHIND);
    Main_btnM_3->fn->setPressedOffset(Main_btnM_3, 0);
    Main_btnM_3->fn->setReleasedEventCallback(Main_btnM_3, event_Main_btnM_3_OnReleased);
    Main_pnlChnCtrlCh3->fn->addChild(Main_pnlChnCtrlCh3, (leWidget*)Main_btnM_3);

    Main_btnS_3 = leButtonWidget_New();
    Main_btnS_3->fn->setPosition(Main_btnS_3, 48, 367);
    Main_btnS_3->fn->setSize(Main_btnS_3, 50, 40);
    Main_btnS_3->fn->setScheme(Main_btnS_3, &WhiteTextScheme);
    Main_btnS_3->fn->setBackgroundType(Main_btnS_3, LE_WIDGET_BACKGROUND_NONE);
    Main_btnS_3->fn->setBorderType(Main_btnS_3, LE_WIDGET_BORDER_NONE);
    Main_btnS_3->fn->setHAlignment(Main_btnS_3, LE_HALIGN_LEFT);
    Main_btnS_3->fn->setString(Main_btnS_3, (leString*)&string_StringS);
    Main_btnS_3->fn->setPressedImage(Main_btnS_3, (leImage*)&Small2ButtonDown);
    Main_btnS_3->fn->setReleasedImage(Main_btnS_3, (leImage*)&Small2ButtonUp);
    Main_btnS_3->fn->setImagePosition(Main_btnS_3, LE_RELATIVE_POSITION_BEHIND);
    Main_btnS_3->fn->setPressedOffset(Main_btnS_3, 0);
    Main_btnS_3->fn->setReleasedEventCallback(Main_btnS_3, event_Main_btnS_3_OnReleased);
    Main_pnlChnCtrlCh3->fn->addChild(Main_pnlChnCtrlCh3, (leWidget*)Main_btnS_3);

    Main_pbarAmp_3 = leProgressBarWidget_New();
    Main_pbarAmp_3->fn->setPosition(Main_pbarAmp_3, 33, 141);
    Main_pbarAmp_3->fn->setSize(Main_pbarAmp_3, 14, 220);
    Main_pbarAmp_3->fn->setScheme(Main_pbarAmp_3, &BarScheme);
    Main_pbarAmp_3->fn->setBorderType(Main_pbarAmp_3, LE_WIDGET_BORDER_NONE);
    Main_pbarAmp_3->fn->setDirection(Main_pbarAmp_3, LE_PROGRESSBAR_DIRECTION_UP);
    Main_pbarAmp_3->fn->setValue(Main_pbarAmp_3, 35);
    Main_pnlChnCtrlCh3->fn->addChild(Main_pnlChnCtrlCh3, (leWidget*)Main_pbarAmp_3);

    Main_pnlColorBar_3 = leWidget_New();
    Main_pnlColorBar_3->fn->setPosition(Main_pnlColorBar_3, 14, 0);
    Main_pnlColorBar_3->fn->setSize(Main_pnlColorBar_3, 70, 6);
    Main_pnlColorBar_3->fn->setScheme(Main_pnlColorBar_3, &RedScheme);
    Main_pnlChnCtrlCh3->fn->addChild(Main_pnlChnCtrlCh3, (leWidget*)Main_pnlColorBar_3);

    Main_pnlLR_3 = leWidget_New();
    Main_pnlLR_3->fn->setPosition(Main_pnlLR_3, 18, 119);
    Main_pnlLR_3->fn->setSize(Main_pnlLR_3, 60, 8);
    Main_pnlLR_3->fn->setScheme(Main_pnlLR_3, &BarScheme);
    Main_pnlChnCtrlCh3->fn->addChild(Main_pnlChnCtrlCh3, (leWidget*)Main_pnlLR_3);

    Main_circLRKnob_3 = leCircleWidget_New();
    Main_circLRKnob_3->fn->setPosition(Main_circLRKnob_3, 39, 113);
    Main_circLRKnob_3->fn->setSize(Main_circLRKnob_3, 20, 20);
    Main_circLRKnob_3->fn->setScheme(Main_circLRKnob_3, &WhiteTextScheme);
    Main_circLRKnob_3->fn->setRadius(Main_circLRKnob_3, 5);
    Main_circLRKnob_3->fn->setThickness(Main_circLRKnob_3, 3);
    Main_circLRKnob_3->fn->setFilled(Main_circLRKnob_3, LE_TRUE);
    Main_pnlChnCtrlCh3->fn->addChild(Main_pnlChnCtrlCh3, (leWidget*)Main_circLRKnob_3);

    Main_lblChNum_3 = leLabelWidget_New();
    Main_lblChNum_3->fn->setPosition(Main_lblChNum_3, 13, 10);
    Main_lblChNum_3->fn->setSize(Main_lblChNum_3, 71, 19);
    Main_lblChNum_3->fn->setScheme(Main_lblChNum_3, &WhiteTextScheme);
    Main_lblChNum_3->fn->setBackgroundType(Main_lblChNum_3, LE_WIDGET_BACKGROUND_NONE);
    Main_lblChNum_3->fn->setHAlignment(Main_lblChNum_3, LE_HALIGN_CENTER);
    Main_lblChNum_3->fn->setString(Main_lblChNum_3, (leString*)&string_StringCh3);
    Main_pnlChnCtrlCh3->fn->addChild(Main_pnlChnCtrlCh3, (leWidget*)Main_lblChNum_3);

    Main_lblL_3 = leLabelWidget_New();
    Main_lblL_3->fn->setPosition(Main_lblL_3, 14, 98);
    Main_lblL_3->fn->setSize(Main_lblL_3, 20, 20);
    Main_lblL_3->fn->setScheme(Main_lblL_3, &WhiteTextScheme);
    Main_lblL_3->fn->setBackgroundType(Main_lblL_3, LE_WIDGET_BACKGROUND_NONE);
    Main_lblL_3->fn->setHAlignment(Main_lblL_3, LE_HALIGN_CENTER);
    Main_lblL_3->fn->setString(Main_lblL_3, (leString*)&string_StringL);
    Main_pnlChnCtrlCh3->fn->addChild(Main_pnlChnCtrlCh3, (leWidget*)Main_lblL_3);

    Main_lbl10_3 = leLabelWidget_New();
    Main_lbl10_3->fn->setPosition(Main_lbl10_3, 1, 134);
    Main_lbl10_3->fn->setSize(Main_lbl10_3, 26, 20);
    Main_lbl10_3->fn->setScheme(Main_lbl10_3, &GrayScheme);
    Main_lbl10_3->fn->setBackgroundType(Main_lbl10_3, LE_WIDGET_BACKGROUND_NONE);
    Main_lbl10_3->fn->setHAlignment(Main_lbl10_3, LE_HALIGN_RIGHT);
    Main_lbl10_3->fn->setMargins(Main_lbl10_3, 4, 4, 0, 4);
    Main_lbl10_3->fn->setString(Main_lbl10_3, (leString*)&string_String10);
    Main_pnlChnCtrlCh3->fn->addChild(Main_pnlChnCtrlCh3, (leWidget*)Main_lbl10_3);

    Main_lblR_3 = leLabelWidget_New();
    Main_lblR_3->fn->setPosition(Main_lblR_3, 61, 98);
    Main_lblR_3->fn->setSize(Main_lblR_3, 20, 20);
    Main_lblR_3->fn->setScheme(Main_lblR_3, &WhiteTextScheme);
    Main_lblR_3->fn->setBackgroundType(Main_lblR_3, LE_WIDGET_BACKGROUND_NONE);
    Main_lblR_3->fn->setHAlignment(Main_lblR_3, LE_HALIGN_CENTER);
    Main_lblR_3->fn->setString(Main_lblR_3, (leString*)&string_StringR);
    Main_pnlChnCtrlCh3->fn->addChild(Main_pnlChnCtrlCh3, (leWidget*)Main_lblR_3);

    Main_lbl5_3 = leLabelWidget_New();
    Main_lbl5_3->fn->setPosition(Main_lbl5_3, 1, 164);
    Main_lbl5_3->fn->setSize(Main_lbl5_3, 26, 20);
    Main_lbl5_3->fn->setScheme(Main_lbl5_3, &GrayScheme);
    Main_lbl5_3->fn->setBackgroundType(Main_lbl5_3, LE_WIDGET_BACKGROUND_NONE);
    Main_lbl5_3->fn->setHAlignment(Main_lbl5_3, LE_HALIGN_RIGHT);
    Main_lbl5_3->fn->setMargins(Main_lbl5_3, 4, 4, 0, 4);
    Main_lbl5_3->fn->setString(Main_lbl5_3, (leString*)&string_String5);
    Main_pnlChnCtrlCh3->fn->addChild(Main_pnlChnCtrlCh3, (leWidget*)Main_lbl5_3);

    Main_lbl0_3 = leLabelWidget_New();
    Main_lbl0_3->fn->setPosition(Main_lbl0_3, 1, 194);
    Main_lbl0_3->fn->setSize(Main_lbl0_3, 26, 20);
    Main_lbl0_3->fn->setScheme(Main_lbl0_3, &GrayScheme);
    Main_lbl0_3->fn->setBackgroundType(Main_lbl0_3, LE_WIDGET_BACKGROUND_NONE);
    Main_lbl0_3->fn->setHAlignment(Main_lbl0_3, LE_HALIGN_RIGHT);
    Main_lbl0_3->fn->setMargins(Main_lbl0_3, 4, 4, 0, 4);
    Main_lbl0_3->fn->setString(Main_lbl0_3, (leString*)&string_String0);
    Main_pnlChnCtrlCh3->fn->addChild(Main_pnlChnCtrlCh3, (leWidget*)Main_lbl0_3);

    Main_lbln5_3 = leLabelWidget_New();
    Main_lbln5_3->fn->setPosition(Main_lbln5_3, 1, 224);
    Main_lbln5_3->fn->setSize(Main_lbln5_3, 26, 20);
    Main_lbln5_3->fn->setScheme(Main_lbln5_3, &GrayScheme);
    Main_lbln5_3->fn->setBackgroundType(Main_lbln5_3, LE_WIDGET_BACKGROUND_NONE);
    Main_lbln5_3->fn->setHAlignment(Main_lbln5_3, LE_HALIGN_RIGHT);
    Main_lbln5_3->fn->setMargins(Main_lbln5_3, 4, 4, 0, 4);
    Main_lbln5_3->fn->setString(Main_lbln5_3, (leString*)&string_Stringn5);
    Main_pnlChnCtrlCh3->fn->addChild(Main_pnlChnCtrlCh3, (leWidget*)Main_lbln5_3);

    Main_lbln10_3 = leLabelWidget_New();
    Main_lbln10_3->fn->setPosition(Main_lbln10_3, 1, 254);
    Main_lbln10_3->fn->setSize(Main_lbln10_3, 26, 20);
    Main_lbln10_3->fn->setScheme(Main_lbln10_3, &GrayScheme);
    Main_lbln10_3->fn->setBackgroundType(Main_lbln10_3, LE_WIDGET_BACKGROUND_NONE);
    Main_lbln10_3->fn->setHAlignment(Main_lbln10_3, LE_HALIGN_RIGHT);
    Main_lbln10_3->fn->setMargins(Main_lbln10_3, 4, 4, 0, 4);
    Main_lbln10_3->fn->setString(Main_lbln10_3, (leString*)&string_Stringn10);
    Main_pnlChnCtrlCh3->fn->addChild(Main_pnlChnCtrlCh3, (leWidget*)Main_lbln10_3);

    Main_lbln15_3 = leLabelWidget_New();
    Main_lbln15_3->fn->setPosition(Main_lbln15_3, 1, 284);
    Main_lbln15_3->fn->setSize(Main_lbln15_3, 26, 20);
    Main_lbln15_3->fn->setScheme(Main_lbln15_3, &GrayScheme);
    Main_lbln15_3->fn->setBackgroundType(Main_lbln15_3, LE_WIDGET_BACKGROUND_NONE);
    Main_lbln15_3->fn->setHAlignment(Main_lbln15_3, LE_HALIGN_RIGHT);
    Main_lbln15_3->fn->setMargins(Main_lbln15_3, 4, 4, 0, 4);
    Main_lbln15_3->fn->setString(Main_lbln15_3, (leString*)&string_Stringn15);
    Main_pnlChnCtrlCh3->fn->addChild(Main_pnlChnCtrlCh3, (leWidget*)Main_lbln15_3);

    Main_lbln20_3 = leLabelWidget_New();
    Main_lbln20_3->fn->setPosition(Main_lbln20_3, 1, 314);
    Main_lbln20_3->fn->setSize(Main_lbln20_3, 26, 20);
    Main_lbln20_3->fn->setScheme(Main_lbln20_3, &GrayScheme);
    Main_lbln20_3->fn->setBackgroundType(Main_lbln20_3, LE_WIDGET_BACKGROUND_NONE);
    Main_lbln20_3->fn->setHAlignment(Main_lbln20_3, LE_HALIGN_RIGHT);
    Main_lbln20_3->fn->setMargins(Main_lbln20_3, 4, 4, 0, 4);
    Main_lbln20_3->fn->setString(Main_lbln20_3, (leString*)&string_Stringn20);
    Main_pnlChnCtrlCh3->fn->addChild(Main_pnlChnCtrlCh3, (leWidget*)Main_lbln20_3);

    Main_lbln25_3 = leLabelWidget_New();
    Main_lbln25_3->fn->setPosition(Main_lbln25_3, 1, 344);
    Main_lbln25_3->fn->setSize(Main_lbln25_3, 26, 20);
    Main_lbln25_3->fn->setScheme(Main_lbln25_3, &GrayScheme);
    Main_lbln25_3->fn->setBackgroundType(Main_lbln25_3, LE_WIDGET_BACKGROUND_NONE);
    Main_lbln25_3->fn->setHAlignment(Main_lbln25_3, LE_HALIGN_RIGHT);
    Main_lbln25_3->fn->setMargins(Main_lbln25_3, 4, 4, 0, 4);
    Main_lbln25_3->fn->setString(Main_lbln25_3, (leString*)&string_Stringn25);
    Main_pnlChnCtrlCh3->fn->addChild(Main_pnlChnCtrlCh3, (leWidget*)Main_lbln25_3);

    Main_lblChName_3 = leLabelWidget_New();
    Main_lblChName_3->fn->setPosition(Main_lblChName_3, 8, 25);
    Main_lblChName_3->fn->setSize(Main_lblChName_3, 80, 30);
    Main_lblChName_3->fn->setScheme(Main_lblChName_3, &WhiteTextScheme);
    Main_lblChName_3->fn->setBackgroundType(Main_lblChName_3, LE_WIDGET_BACKGROUND_NONE);
    Main_lblChName_3->fn->setHAlignment(Main_lblChName_3, LE_HALIGN_CENTER);
    Main_lblChName_3->fn->setString(Main_lblChName_3, (leString*)&string_StringMain);
    Main_pnlChnCtrlCh3->fn->addChild(Main_pnlChnCtrlCh3, (leWidget*)Main_lblChName_3);

    Main_btnGainKnob_3 = leButtonWidget_New();
    Main_btnGainKnob_3->fn->setPosition(Main_btnGainKnob_3, 43, 179);
    Main_btnGainKnob_3->fn->setSize(Main_btnGainKnob_3, 50, 50);
    Main_btnGainKnob_3->fn->setBackgroundType(Main_btnGainKnob_3, LE_WIDGET_BACKGROUND_NONE);
    Main_btnGainKnob_3->fn->setBorderType(Main_btnGainKnob_3, LE_WIDGET_BORDER_NONE);
    Main_btnGainKnob_3->fn->setPressedImage(Main_btnGainKnob_3, (leImage*)&SliderKnob);
    Main_btnGainKnob_3->fn->setReleasedImage(Main_btnGainKnob_3, (leImage*)&SliderKnob);
    Main_pnlChnCtrlCh3->fn->addChild(Main_pnlChnCtrlCh3, (leWidget*)Main_btnGainKnob_3);

    Main_pnlChnCtrlCh2 = leWidget_New();
    Main_pnlChnCtrlCh2->fn->setPosition(Main_pnlChnCtrlCh2, 116, 74);
    Main_pnlChnCtrlCh2->fn->setSize(Main_pnlChnCtrlCh2, 98, 408);
    Main_pnlChnCtrlCh2->fn->setBackgroundType(Main_pnlChnCtrlCh2, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->addChild(root0, (leWidget*)Main_pnlChnCtrlCh2);

    Main_btnCue_2 = leButtonWidget_New();
    Main_btnCue_2->fn->setPosition(Main_btnCue_2, 3, 61);
    Main_btnCue_2->fn->setSize(Main_btnCue_2, 90, 40);
    Main_btnCue_2->fn->setScheme(Main_btnCue_2, &WhiteTextScheme);
    Main_btnCue_2->fn->setBackgroundType(Main_btnCue_2, LE_WIDGET_BACKGROUND_NONE);
    Main_btnCue_2->fn->setBorderType(Main_btnCue_2, LE_WIDGET_BORDER_NONE);
    Main_btnCue_2->fn->setString(Main_btnCue_2, (leString*)&string_StringCue);
    Main_btnCue_2->fn->setPressedImage(Main_btnCue_2, (leImage*)&SmallButtonDown);
    Main_btnCue_2->fn->setReleasedImage(Main_btnCue_2, (leImage*)&SmallButtonUp);
    Main_btnCue_2->fn->setImagePosition(Main_btnCue_2, LE_RELATIVE_POSITION_BEHIND);
    Main_btnCue_2->fn->setPressedOffset(Main_btnCue_2, 0);
    Main_btnCue_2->fn->setReleasedEventCallback(Main_btnCue_2, event_Main_btnCue_2_OnReleased);
    Main_pnlChnCtrlCh2->fn->addChild(Main_pnlChnCtrlCh2, (leWidget*)Main_btnCue_2);

    Main_pnlGain_2 = leWidget_New();
    Main_pnlGain_2->fn->setPosition(Main_pnlGain_2, 64, 141);
    Main_pnlGain_2->fn->setSize(Main_pnlGain_2, 8, 220);
    Main_pnlGain_2->fn->setScheme(Main_pnlGain_2, &BarScheme);
    Main_pnlChnCtrlCh2->fn->addChild(Main_pnlChnCtrlCh2, (leWidget*)Main_pnlGain_2);

    Main_btnM_2 = leButtonWidget_New();
    Main_btnM_2->fn->setPosition(Main_btnM_2, -4, 366);
    Main_btnM_2->fn->setSize(Main_btnM_2, 54, 40);
    Main_btnM_2->fn->setScheme(Main_btnM_2, &WhiteTextScheme);
    Main_btnM_2->fn->setBackgroundType(Main_btnM_2, LE_WIDGET_BACKGROUND_NONE);
    Main_btnM_2->fn->setBorderType(Main_btnM_2, LE_WIDGET_BORDER_NONE);
    Main_btnM_2->fn->setHAlignment(Main_btnM_2, LE_HALIGN_RIGHT);
    Main_btnM_2->fn->setString(Main_btnM_2, (leString*)&string_StringM);
    Main_btnM_2->fn->setPressedImage(Main_btnM_2, (leImage*)&Small2ButtonDown);
    Main_btnM_2->fn->setReleasedImage(Main_btnM_2, (leImage*)&Small2ButtonUp);
    Main_btnM_2->fn->setImagePosition(Main_btnM_2, LE_RELATIVE_POSITION_BEHIND);
    Main_btnM_2->fn->setPressedOffset(Main_btnM_2, 0);
    Main_btnM_2->fn->setReleasedEventCallback(Main_btnM_2, event_Main_btnM_2_OnReleased);
    Main_pnlChnCtrlCh2->fn->addChild(Main_pnlChnCtrlCh2, (leWidget*)Main_btnM_2);

    Main_btnS_2 = leButtonWidget_New();
    Main_btnS_2->fn->setPosition(Main_btnS_2, 48, 367);
    Main_btnS_2->fn->setSize(Main_btnS_2, 50, 40);
    Main_btnS_2->fn->setScheme(Main_btnS_2, &WhiteTextScheme);
    Main_btnS_2->fn->setBackgroundType(Main_btnS_2, LE_WIDGET_BACKGROUND_NONE);
    Main_btnS_2->fn->setBorderType(Main_btnS_2, LE_WIDGET_BORDER_NONE);
    Main_btnS_2->fn->setHAlignment(Main_btnS_2, LE_HALIGN_LEFT);
    Main_btnS_2->fn->setString(Main_btnS_2, (leString*)&string_StringS);
    Main_btnS_2->fn->setPressedImage(Main_btnS_2, (leImage*)&Small2ButtonDown);
    Main_btnS_2->fn->setReleasedImage(Main_btnS_2, (leImage*)&Small2ButtonUp);
    Main_btnS_2->fn->setImagePosition(Main_btnS_2, LE_RELATIVE_POSITION_BEHIND);
    Main_btnS_2->fn->setPressedOffset(Main_btnS_2, 0);
    Main_btnS_2->fn->setReleasedEventCallback(Main_btnS_2, event_Main_btnS_2_OnReleased);
    Main_pnlChnCtrlCh2->fn->addChild(Main_pnlChnCtrlCh2, (leWidget*)Main_btnS_2);

    Main_pbarAmp_2 = leProgressBarWidget_New();
    Main_pbarAmp_2->fn->setPosition(Main_pbarAmp_2, 33, 141);
    Main_pbarAmp_2->fn->setSize(Main_pbarAmp_2, 14, 220);
    Main_pbarAmp_2->fn->setScheme(Main_pbarAmp_2, &BarScheme);
    Main_pbarAmp_2->fn->setBorderType(Main_pbarAmp_2, LE_WIDGET_BORDER_NONE);
    Main_pbarAmp_2->fn->setDirection(Main_pbarAmp_2, LE_PROGRESSBAR_DIRECTION_UP);
    Main_pbarAmp_2->fn->setValue(Main_pbarAmp_2, 60);
    Main_pnlChnCtrlCh2->fn->addChild(Main_pnlChnCtrlCh2, (leWidget*)Main_pbarAmp_2);

    Main_pnlColorBar_2 = leWidget_New();
    Main_pnlColorBar_2->fn->setPosition(Main_pnlColorBar_2, 14, 0);
    Main_pnlColorBar_2->fn->setSize(Main_pnlColorBar_2, 70, 6);
    Main_pnlColorBar_2->fn->setScheme(Main_pnlColorBar_2, &RedScheme);
    Main_pnlChnCtrlCh2->fn->addChild(Main_pnlChnCtrlCh2, (leWidget*)Main_pnlColorBar_2);

    Main_pnlLR_2 = leWidget_New();
    Main_pnlLR_2->fn->setPosition(Main_pnlLR_2, 18, 119);
    Main_pnlLR_2->fn->setSize(Main_pnlLR_2, 60, 8);
    Main_pnlLR_2->fn->setScheme(Main_pnlLR_2, &BarScheme);
    Main_pnlChnCtrlCh2->fn->addChild(Main_pnlChnCtrlCh2, (leWidget*)Main_pnlLR_2);

    Main_circLRKnob_2 = leCircleWidget_New();
    Main_circLRKnob_2->fn->setPosition(Main_circLRKnob_2, 39, 113);
    Main_circLRKnob_2->fn->setSize(Main_circLRKnob_2, 20, 20);
    Main_circLRKnob_2->fn->setScheme(Main_circLRKnob_2, &WhiteTextScheme);
    Main_circLRKnob_2->fn->setRadius(Main_circLRKnob_2, 5);
    Main_circLRKnob_2->fn->setThickness(Main_circLRKnob_2, 3);
    Main_circLRKnob_2->fn->setFilled(Main_circLRKnob_2, LE_TRUE);
    Main_pnlChnCtrlCh2->fn->addChild(Main_pnlChnCtrlCh2, (leWidget*)Main_circLRKnob_2);

    Main_lblChNum_2 = leLabelWidget_New();
    Main_lblChNum_2->fn->setPosition(Main_lblChNum_2, 13, 10);
    Main_lblChNum_2->fn->setSize(Main_lblChNum_2, 71, 19);
    Main_lblChNum_2->fn->setScheme(Main_lblChNum_2, &WhiteTextScheme);
    Main_lblChNum_2->fn->setBackgroundType(Main_lblChNum_2, LE_WIDGET_BACKGROUND_NONE);
    Main_lblChNum_2->fn->setHAlignment(Main_lblChNum_2, LE_HALIGN_CENTER);
    Main_lblChNum_2->fn->setString(Main_lblChNum_2, (leString*)&string_StringCh2);
    Main_pnlChnCtrlCh2->fn->addChild(Main_pnlChnCtrlCh2, (leWidget*)Main_lblChNum_2);

    Main_lblL_2 = leLabelWidget_New();
    Main_lblL_2->fn->setPosition(Main_lblL_2, 14, 98);
    Main_lblL_2->fn->setSize(Main_lblL_2, 20, 20);
    Main_lblL_2->fn->setScheme(Main_lblL_2, &WhiteTextScheme);
    Main_lblL_2->fn->setBackgroundType(Main_lblL_2, LE_WIDGET_BACKGROUND_NONE);
    Main_lblL_2->fn->setHAlignment(Main_lblL_2, LE_HALIGN_CENTER);
    Main_lblL_2->fn->setString(Main_lblL_2, (leString*)&string_StringL);
    Main_pnlChnCtrlCh2->fn->addChild(Main_pnlChnCtrlCh2, (leWidget*)Main_lblL_2);

    Main_lbl10_2 = leLabelWidget_New();
    Main_lbl10_2->fn->setPosition(Main_lbl10_2, 1, 134);
    Main_lbl10_2->fn->setSize(Main_lbl10_2, 26, 20);
    Main_lbl10_2->fn->setScheme(Main_lbl10_2, &GrayScheme);
    Main_lbl10_2->fn->setBackgroundType(Main_lbl10_2, LE_WIDGET_BACKGROUND_NONE);
    Main_lbl10_2->fn->setHAlignment(Main_lbl10_2, LE_HALIGN_RIGHT);
    Main_lbl10_2->fn->setMargins(Main_lbl10_2, 4, 4, 0, 4);
    Main_lbl10_2->fn->setString(Main_lbl10_2, (leString*)&string_String10);
    Main_pnlChnCtrlCh2->fn->addChild(Main_pnlChnCtrlCh2, (leWidget*)Main_lbl10_2);

    Main_lblR_2 = leLabelWidget_New();
    Main_lblR_2->fn->setPosition(Main_lblR_2, 61, 98);
    Main_lblR_2->fn->setSize(Main_lblR_2, 20, 20);
    Main_lblR_2->fn->setScheme(Main_lblR_2, &WhiteTextScheme);
    Main_lblR_2->fn->setBackgroundType(Main_lblR_2, LE_WIDGET_BACKGROUND_NONE);
    Main_lblR_2->fn->setHAlignment(Main_lblR_2, LE_HALIGN_CENTER);
    Main_lblR_2->fn->setString(Main_lblR_2, (leString*)&string_StringR);
    Main_pnlChnCtrlCh2->fn->addChild(Main_pnlChnCtrlCh2, (leWidget*)Main_lblR_2);

    Main_lbl5_2 = leLabelWidget_New();
    Main_lbl5_2->fn->setPosition(Main_lbl5_2, 1, 164);
    Main_lbl5_2->fn->setSize(Main_lbl5_2, 26, 20);
    Main_lbl5_2->fn->setScheme(Main_lbl5_2, &GrayScheme);
    Main_lbl5_2->fn->setBackgroundType(Main_lbl5_2, LE_WIDGET_BACKGROUND_NONE);
    Main_lbl5_2->fn->setHAlignment(Main_lbl5_2, LE_HALIGN_RIGHT);
    Main_lbl5_2->fn->setMargins(Main_lbl5_2, 4, 4, 0, 4);
    Main_lbl5_2->fn->setString(Main_lbl5_2, (leString*)&string_String5);
    Main_pnlChnCtrlCh2->fn->addChild(Main_pnlChnCtrlCh2, (leWidget*)Main_lbl5_2);

    Main_lbl0_2 = leLabelWidget_New();
    Main_lbl0_2->fn->setPosition(Main_lbl0_2, 1, 194);
    Main_lbl0_2->fn->setSize(Main_lbl0_2, 26, 20);
    Main_lbl0_2->fn->setScheme(Main_lbl0_2, &GrayScheme);
    Main_lbl0_2->fn->setBackgroundType(Main_lbl0_2, LE_WIDGET_BACKGROUND_NONE);
    Main_lbl0_2->fn->setHAlignment(Main_lbl0_2, LE_HALIGN_RIGHT);
    Main_lbl0_2->fn->setMargins(Main_lbl0_2, 4, 4, 0, 4);
    Main_lbl0_2->fn->setString(Main_lbl0_2, (leString*)&string_String0);
    Main_pnlChnCtrlCh2->fn->addChild(Main_pnlChnCtrlCh2, (leWidget*)Main_lbl0_2);

    Main_lbln5_2 = leLabelWidget_New();
    Main_lbln5_2->fn->setPosition(Main_lbln5_2, 1, 224);
    Main_lbln5_2->fn->setSize(Main_lbln5_2, 26, 20);
    Main_lbln5_2->fn->setScheme(Main_lbln5_2, &GrayScheme);
    Main_lbln5_2->fn->setBackgroundType(Main_lbln5_2, LE_WIDGET_BACKGROUND_NONE);
    Main_lbln5_2->fn->setHAlignment(Main_lbln5_2, LE_HALIGN_RIGHT);
    Main_lbln5_2->fn->setMargins(Main_lbln5_2, 4, 4, 0, 4);
    Main_lbln5_2->fn->setString(Main_lbln5_2, (leString*)&string_Stringn5);
    Main_pnlChnCtrlCh2->fn->addChild(Main_pnlChnCtrlCh2, (leWidget*)Main_lbln5_2);

    Main_lbln10_2 = leLabelWidget_New();
    Main_lbln10_2->fn->setPosition(Main_lbln10_2, 1, 254);
    Main_lbln10_2->fn->setSize(Main_lbln10_2, 26, 20);
    Main_lbln10_2->fn->setScheme(Main_lbln10_2, &GrayScheme);
    Main_lbln10_2->fn->setBackgroundType(Main_lbln10_2, LE_WIDGET_BACKGROUND_NONE);
    Main_lbln10_2->fn->setHAlignment(Main_lbln10_2, LE_HALIGN_RIGHT);
    Main_lbln10_2->fn->setMargins(Main_lbln10_2, 4, 4, 0, 4);
    Main_lbln10_2->fn->setString(Main_lbln10_2, (leString*)&string_Stringn10);
    Main_pnlChnCtrlCh2->fn->addChild(Main_pnlChnCtrlCh2, (leWidget*)Main_lbln10_2);

    Main_lbln15_2 = leLabelWidget_New();
    Main_lbln15_2->fn->setPosition(Main_lbln15_2, 1, 284);
    Main_lbln15_2->fn->setSize(Main_lbln15_2, 26, 20);
    Main_lbln15_2->fn->setScheme(Main_lbln15_2, &GrayScheme);
    Main_lbln15_2->fn->setBackgroundType(Main_lbln15_2, LE_WIDGET_BACKGROUND_NONE);
    Main_lbln15_2->fn->setHAlignment(Main_lbln15_2, LE_HALIGN_RIGHT);
    Main_lbln15_2->fn->setMargins(Main_lbln15_2, 4, 4, 0, 4);
    Main_lbln15_2->fn->setString(Main_lbln15_2, (leString*)&string_Stringn15);
    Main_pnlChnCtrlCh2->fn->addChild(Main_pnlChnCtrlCh2, (leWidget*)Main_lbln15_2);

    Main_lbln20_2 = leLabelWidget_New();
    Main_lbln20_2->fn->setPosition(Main_lbln20_2, 1, 314);
    Main_lbln20_2->fn->setSize(Main_lbln20_2, 26, 20);
    Main_lbln20_2->fn->setScheme(Main_lbln20_2, &GrayScheme);
    Main_lbln20_2->fn->setBackgroundType(Main_lbln20_2, LE_WIDGET_BACKGROUND_NONE);
    Main_lbln20_2->fn->setHAlignment(Main_lbln20_2, LE_HALIGN_RIGHT);
    Main_lbln20_2->fn->setMargins(Main_lbln20_2, 4, 4, 0, 4);
    Main_lbln20_2->fn->setString(Main_lbln20_2, (leString*)&string_Stringn20);
    Main_pnlChnCtrlCh2->fn->addChild(Main_pnlChnCtrlCh2, (leWidget*)Main_lbln20_2);

    Main_lbln25_2 = leLabelWidget_New();
    Main_lbln25_2->fn->setPosition(Main_lbln25_2, 1, 344);
    Main_lbln25_2->fn->setSize(Main_lbln25_2, 26, 20);
    Main_lbln25_2->fn->setScheme(Main_lbln25_2, &GrayScheme);
    Main_lbln25_2->fn->setBackgroundType(Main_lbln25_2, LE_WIDGET_BACKGROUND_NONE);
    Main_lbln25_2->fn->setHAlignment(Main_lbln25_2, LE_HALIGN_RIGHT);
    Main_lbln25_2->fn->setMargins(Main_lbln25_2, 4, 4, 0, 4);
    Main_lbln25_2->fn->setString(Main_lbln25_2, (leString*)&string_Stringn25);
    Main_pnlChnCtrlCh2->fn->addChild(Main_pnlChnCtrlCh2, (leWidget*)Main_lbln25_2);

    Main_lblChName_2 = leLabelWidget_New();
    Main_lblChName_2->fn->setPosition(Main_lblChName_2, 8, 25);
    Main_lblChName_2->fn->setSize(Main_lblChName_2, 80, 30);
    Main_lblChName_2->fn->setScheme(Main_lblChName_2, &WhiteTextScheme);
    Main_lblChName_2->fn->setBackgroundType(Main_lblChName_2, LE_WIDGET_BACKGROUND_NONE);
    Main_lblChName_2->fn->setHAlignment(Main_lblChName_2, LE_HALIGN_CENTER);
    Main_lblChName_2->fn->setString(Main_lblChName_2, (leString*)&string_StringLead);
    Main_pnlChnCtrlCh2->fn->addChild(Main_pnlChnCtrlCh2, (leWidget*)Main_lblChName_2);

    Main_btnGainKnob_2 = leButtonWidget_New();
    Main_btnGainKnob_2->fn->setPosition(Main_btnGainKnob_2, 43, 179);
    Main_btnGainKnob_2->fn->setSize(Main_btnGainKnob_2, 50, 50);
    Main_btnGainKnob_2->fn->setBackgroundType(Main_btnGainKnob_2, LE_WIDGET_BACKGROUND_NONE);
    Main_btnGainKnob_2->fn->setBorderType(Main_btnGainKnob_2, LE_WIDGET_BORDER_NONE);
    Main_btnGainKnob_2->fn->setPressedImage(Main_btnGainKnob_2, (leImage*)&SliderKnob);
    Main_btnGainKnob_2->fn->setReleasedImage(Main_btnGainKnob_2, (leImage*)&SliderKnob);
    Main_pnlChnCtrlCh2->fn->addChild(Main_pnlChnCtrlCh2, (leWidget*)Main_btnGainKnob_2);

    Main_pnlChnCtrlCh1 = leWidget_New();
    Main_pnlChnCtrlCh1->fn->setPosition(Main_pnlChnCtrlCh1, 7, 74);
    Main_pnlChnCtrlCh1->fn->setSize(Main_pnlChnCtrlCh1, 98, 408);
    Main_pnlChnCtrlCh1->fn->setBackgroundType(Main_pnlChnCtrlCh1, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->addChild(root0, (leWidget*)Main_pnlChnCtrlCh1);

    Main_btnCue = leButtonWidget_New();
    Main_btnCue->fn->setPosition(Main_btnCue, 3, 61);
    Main_btnCue->fn->setSize(Main_btnCue, 90, 40);
    Main_btnCue->fn->setScheme(Main_btnCue, &WhiteTextScheme);
    Main_btnCue->fn->setBackgroundType(Main_btnCue, LE_WIDGET_BACKGROUND_NONE);
    Main_btnCue->fn->setBorderType(Main_btnCue, LE_WIDGET_BORDER_NONE);
    Main_btnCue->fn->setString(Main_btnCue, (leString*)&string_StringCue);
    Main_btnCue->fn->setPressedImage(Main_btnCue, (leImage*)&SmallButtonDown);
    Main_btnCue->fn->setReleasedImage(Main_btnCue, (leImage*)&SmallButtonUp);
    Main_btnCue->fn->setImagePosition(Main_btnCue, LE_RELATIVE_POSITION_BEHIND);
    Main_btnCue->fn->setPressedOffset(Main_btnCue, 0);
    Main_btnCue->fn->setReleasedEventCallback(Main_btnCue, event_Main_btnCue_OnReleased);
    Main_pnlChnCtrlCh1->fn->addChild(Main_pnlChnCtrlCh1, (leWidget*)Main_btnCue);

    Main_pnlGain = leWidget_New();
    Main_pnlGain->fn->setPosition(Main_pnlGain, 64, 141);
    Main_pnlGain->fn->setSize(Main_pnlGain, 8, 220);
    Main_pnlGain->fn->setScheme(Main_pnlGain, &BarScheme);
    Main_pnlChnCtrlCh1->fn->addChild(Main_pnlChnCtrlCh1, (leWidget*)Main_pnlGain);

    Main_btnM = leButtonWidget_New();
    Main_btnM->fn->setPosition(Main_btnM, -4, 367);
    Main_btnM->fn->setSize(Main_btnM, 54, 40);
    Main_btnM->fn->setScheme(Main_btnM, &WhiteTextScheme);
    Main_btnM->fn->setBackgroundType(Main_btnM, LE_WIDGET_BACKGROUND_NONE);
    Main_btnM->fn->setBorderType(Main_btnM, LE_WIDGET_BORDER_NONE);
    Main_btnM->fn->setHAlignment(Main_btnM, LE_HALIGN_RIGHT);
    Main_btnM->fn->setString(Main_btnM, (leString*)&string_StringM);
    Main_btnM->fn->setPressedImage(Main_btnM, (leImage*)&Small2ButtonDown);
    Main_btnM->fn->setReleasedImage(Main_btnM, (leImage*)&Small2ButtonUp);
    Main_btnM->fn->setImagePosition(Main_btnM, LE_RELATIVE_POSITION_BEHIND);
    Main_btnM->fn->setPressedOffset(Main_btnM, 0);
    Main_btnM->fn->setReleasedEventCallback(Main_btnM, event_Main_btnM_OnReleased);
    Main_pnlChnCtrlCh1->fn->addChild(Main_pnlChnCtrlCh1, (leWidget*)Main_btnM);

    Main_btnS = leButtonWidget_New();
    Main_btnS->fn->setPosition(Main_btnS, 48, 367);
    Main_btnS->fn->setSize(Main_btnS, 50, 40);
    Main_btnS->fn->setScheme(Main_btnS, &WhiteTextScheme);
    Main_btnS->fn->setBackgroundType(Main_btnS, LE_WIDGET_BACKGROUND_NONE);
    Main_btnS->fn->setBorderType(Main_btnS, LE_WIDGET_BORDER_NONE);
    Main_btnS->fn->setHAlignment(Main_btnS, LE_HALIGN_LEFT);
    Main_btnS->fn->setString(Main_btnS, (leString*)&string_StringS);
    Main_btnS->fn->setPressedImage(Main_btnS, (leImage*)&Small2ButtonDown);
    Main_btnS->fn->setReleasedImage(Main_btnS, (leImage*)&Small2ButtonUp);
    Main_btnS->fn->setImagePosition(Main_btnS, LE_RELATIVE_POSITION_BEHIND);
    Main_btnS->fn->setPressedOffset(Main_btnS, 0);
    Main_btnS->fn->setReleasedEventCallback(Main_btnS, event_Main_btnS_OnReleased);
    Main_pnlChnCtrlCh1->fn->addChild(Main_pnlChnCtrlCh1, (leWidget*)Main_btnS);

    Main_pbarAmp = leProgressBarWidget_New();
    Main_pbarAmp->fn->setPosition(Main_pbarAmp, 33, 141);
    Main_pbarAmp->fn->setSize(Main_pbarAmp, 14, 220);
    Main_pbarAmp->fn->setScheme(Main_pbarAmp, &BarScheme);
    Main_pbarAmp->fn->setBorderType(Main_pbarAmp, LE_WIDGET_BORDER_NONE);
    Main_pbarAmp->fn->setDirection(Main_pbarAmp, LE_PROGRESSBAR_DIRECTION_UP);
    Main_pbarAmp->fn->setValue(Main_pbarAmp, 40);
    Main_pnlChnCtrlCh1->fn->addChild(Main_pnlChnCtrlCh1, (leWidget*)Main_pbarAmp);

    Main_pnlColorBar = leWidget_New();
    Main_pnlColorBar->fn->setPosition(Main_pnlColorBar, 14, 0);
    Main_pnlColorBar->fn->setSize(Main_pnlColorBar, 70, 6);
    Main_pnlColorBar->fn->setScheme(Main_pnlColorBar, &RedScheme);
    Main_pnlChnCtrlCh1->fn->addChild(Main_pnlChnCtrlCh1, (leWidget*)Main_pnlColorBar);

    Main_pnlLR = leWidget_New();
    Main_pnlLR->fn->setPosition(Main_pnlLR, 18, 119);
    Main_pnlLR->fn->setSize(Main_pnlLR, 60, 8);
    Main_pnlLR->fn->setScheme(Main_pnlLR, &BarScheme);
    Main_pnlChnCtrlCh1->fn->addChild(Main_pnlChnCtrlCh1, (leWidget*)Main_pnlLR);

    Main_circLRKnob = leCircleWidget_New();
    Main_circLRKnob->fn->setPosition(Main_circLRKnob, 39, 113);
    Main_circLRKnob->fn->setSize(Main_circLRKnob, 20, 20);
    Main_circLRKnob->fn->setScheme(Main_circLRKnob, &WhiteTextScheme);
    Main_circLRKnob->fn->setRadius(Main_circLRKnob, 5);
    Main_circLRKnob->fn->setThickness(Main_circLRKnob, 3);
    Main_circLRKnob->fn->setFilled(Main_circLRKnob, LE_TRUE);
    Main_pnlChnCtrlCh1->fn->addChild(Main_pnlChnCtrlCh1, (leWidget*)Main_circLRKnob);

    Main_lblChNum = leLabelWidget_New();
    Main_lblChNum->fn->setPosition(Main_lblChNum, 13, 10);
    Main_lblChNum->fn->setSize(Main_lblChNum, 71, 19);
    Main_lblChNum->fn->setScheme(Main_lblChNum, &WhiteTextScheme);
    Main_lblChNum->fn->setBackgroundType(Main_lblChNum, LE_WIDGET_BACKGROUND_NONE);
    Main_lblChNum->fn->setHAlignment(Main_lblChNum, LE_HALIGN_CENTER);
    Main_lblChNum->fn->setString(Main_lblChNum, (leString*)&string_StringCh1);
    Main_pnlChnCtrlCh1->fn->addChild(Main_pnlChnCtrlCh1, (leWidget*)Main_lblChNum);

    Main_lblL = leLabelWidget_New();
    Main_lblL->fn->setPosition(Main_lblL, 14, 98);
    Main_lblL->fn->setSize(Main_lblL, 20, 20);
    Main_lblL->fn->setScheme(Main_lblL, &WhiteTextScheme);
    Main_lblL->fn->setBackgroundType(Main_lblL, LE_WIDGET_BACKGROUND_NONE);
    Main_lblL->fn->setHAlignment(Main_lblL, LE_HALIGN_CENTER);
    Main_lblL->fn->setString(Main_lblL, (leString*)&string_StringL);
    Main_pnlChnCtrlCh1->fn->addChild(Main_pnlChnCtrlCh1, (leWidget*)Main_lblL);

    Main_lbl10 = leLabelWidget_New();
    Main_lbl10->fn->setPosition(Main_lbl10, 1, 134);
    Main_lbl10->fn->setSize(Main_lbl10, 26, 20);
    Main_lbl10->fn->setScheme(Main_lbl10, &GrayScheme);
    Main_lbl10->fn->setBackgroundType(Main_lbl10, LE_WIDGET_BACKGROUND_NONE);
    Main_lbl10->fn->setHAlignment(Main_lbl10, LE_HALIGN_RIGHT);
    Main_lbl10->fn->setMargins(Main_lbl10, 4, 4, 0, 4);
    Main_lbl10->fn->setString(Main_lbl10, (leString*)&string_String10);
    Main_pnlChnCtrlCh1->fn->addChild(Main_pnlChnCtrlCh1, (leWidget*)Main_lbl10);

    Main_lblR = leLabelWidget_New();
    Main_lblR->fn->setPosition(Main_lblR, 61, 98);
    Main_lblR->fn->setSize(Main_lblR, 20, 20);
    Main_lblR->fn->setScheme(Main_lblR, &WhiteTextScheme);
    Main_lblR->fn->setBackgroundType(Main_lblR, LE_WIDGET_BACKGROUND_NONE);
    Main_lblR->fn->setHAlignment(Main_lblR, LE_HALIGN_CENTER);
    Main_lblR->fn->setString(Main_lblR, (leString*)&string_StringR);
    Main_pnlChnCtrlCh1->fn->addChild(Main_pnlChnCtrlCh1, (leWidget*)Main_lblR);

    Main_lbl5 = leLabelWidget_New();
    Main_lbl5->fn->setPosition(Main_lbl5, 1, 164);
    Main_lbl5->fn->setSize(Main_lbl5, 26, 20);
    Main_lbl5->fn->setScheme(Main_lbl5, &GrayScheme);
    Main_lbl5->fn->setBackgroundType(Main_lbl5, LE_WIDGET_BACKGROUND_NONE);
    Main_lbl5->fn->setHAlignment(Main_lbl5, LE_HALIGN_RIGHT);
    Main_lbl5->fn->setMargins(Main_lbl5, 4, 4, 0, 4);
    Main_lbl5->fn->setString(Main_lbl5, (leString*)&string_String5);
    Main_pnlChnCtrlCh1->fn->addChild(Main_pnlChnCtrlCh1, (leWidget*)Main_lbl5);

    Main_lbl0 = leLabelWidget_New();
    Main_lbl0->fn->setPosition(Main_lbl0, 1, 194);
    Main_lbl0->fn->setSize(Main_lbl0, 26, 20);
    Main_lbl0->fn->setScheme(Main_lbl0, &GrayScheme);
    Main_lbl0->fn->setBackgroundType(Main_lbl0, LE_WIDGET_BACKGROUND_NONE);
    Main_lbl0->fn->setHAlignment(Main_lbl0, LE_HALIGN_RIGHT);
    Main_lbl0->fn->setMargins(Main_lbl0, 4, 4, 0, 4);
    Main_lbl0->fn->setString(Main_lbl0, (leString*)&string_String0);
    Main_pnlChnCtrlCh1->fn->addChild(Main_pnlChnCtrlCh1, (leWidget*)Main_lbl0);

    Main_lbln5 = leLabelWidget_New();
    Main_lbln5->fn->setPosition(Main_lbln5, 1, 224);
    Main_lbln5->fn->setSize(Main_lbln5, 26, 20);
    Main_lbln5->fn->setScheme(Main_lbln5, &GrayScheme);
    Main_lbln5->fn->setBackgroundType(Main_lbln5, LE_WIDGET_BACKGROUND_NONE);
    Main_lbln5->fn->setHAlignment(Main_lbln5, LE_HALIGN_RIGHT);
    Main_lbln5->fn->setMargins(Main_lbln5, 4, 4, 0, 4);
    Main_lbln5->fn->setString(Main_lbln5, (leString*)&string_Stringn5);
    Main_pnlChnCtrlCh1->fn->addChild(Main_pnlChnCtrlCh1, (leWidget*)Main_lbln5);

    Main_lbln10 = leLabelWidget_New();
    Main_lbln10->fn->setPosition(Main_lbln10, 1, 254);
    Main_lbln10->fn->setSize(Main_lbln10, 26, 20);
    Main_lbln10->fn->setScheme(Main_lbln10, &GrayScheme);
    Main_lbln10->fn->setBackgroundType(Main_lbln10, LE_WIDGET_BACKGROUND_NONE);
    Main_lbln10->fn->setHAlignment(Main_lbln10, LE_HALIGN_RIGHT);
    Main_lbln10->fn->setMargins(Main_lbln10, 4, 4, 0, 4);
    Main_lbln10->fn->setString(Main_lbln10, (leString*)&string_Stringn10);
    Main_pnlChnCtrlCh1->fn->addChild(Main_pnlChnCtrlCh1, (leWidget*)Main_lbln10);

    Main_lbln15 = leLabelWidget_New();
    Main_lbln15->fn->setPosition(Main_lbln15, 1, 284);
    Main_lbln15->fn->setSize(Main_lbln15, 26, 20);
    Main_lbln15->fn->setScheme(Main_lbln15, &GrayScheme);
    Main_lbln15->fn->setBackgroundType(Main_lbln15, LE_WIDGET_BACKGROUND_NONE);
    Main_lbln15->fn->setHAlignment(Main_lbln15, LE_HALIGN_RIGHT);
    Main_lbln15->fn->setMargins(Main_lbln15, 4, 4, 0, 4);
    Main_lbln15->fn->setString(Main_lbln15, (leString*)&string_Stringn15);
    Main_pnlChnCtrlCh1->fn->addChild(Main_pnlChnCtrlCh1, (leWidget*)Main_lbln15);

    Main_lbln20 = leLabelWidget_New();
    Main_lbln20->fn->setPosition(Main_lbln20, 1, 314);
    Main_lbln20->fn->setSize(Main_lbln20, 26, 20);
    Main_lbln20->fn->setScheme(Main_lbln20, &GrayScheme);
    Main_lbln20->fn->setBackgroundType(Main_lbln20, LE_WIDGET_BACKGROUND_NONE);
    Main_lbln20->fn->setHAlignment(Main_lbln20, LE_HALIGN_RIGHT);
    Main_lbln20->fn->setMargins(Main_lbln20, 4, 4, 0, 4);
    Main_lbln20->fn->setString(Main_lbln20, (leString*)&string_Stringn20);
    Main_pnlChnCtrlCh1->fn->addChild(Main_pnlChnCtrlCh1, (leWidget*)Main_lbln20);

    Main_lbln25 = leLabelWidget_New();
    Main_lbln25->fn->setPosition(Main_lbln25, 1, 344);
    Main_lbln25->fn->setSize(Main_lbln25, 26, 20);
    Main_lbln25->fn->setScheme(Main_lbln25, &GrayScheme);
    Main_lbln25->fn->setBackgroundType(Main_lbln25, LE_WIDGET_BACKGROUND_NONE);
    Main_lbln25->fn->setHAlignment(Main_lbln25, LE_HALIGN_RIGHT);
    Main_lbln25->fn->setMargins(Main_lbln25, 4, 4, 0, 4);
    Main_lbln25->fn->setString(Main_lbln25, (leString*)&string_Stringn25);
    Main_pnlChnCtrlCh1->fn->addChild(Main_pnlChnCtrlCh1, (leWidget*)Main_lbln25);

    Main_lblChName = leLabelWidget_New();
    Main_lblChName->fn->setPosition(Main_lblChName, 8, 25);
    Main_lblChName->fn->setSize(Main_lblChName, 80, 30);
    Main_lblChName->fn->setScheme(Main_lblChName, &WhiteTextScheme);
    Main_lblChName->fn->setBackgroundType(Main_lblChName, LE_WIDGET_BACKGROUND_NONE);
    Main_lblChName->fn->setHAlignment(Main_lblChName, LE_HALIGN_CENTER);
    Main_lblChName->fn->setString(Main_lblChName, (leString*)&string_StringHost);
    Main_pnlChnCtrlCh1->fn->addChild(Main_pnlChnCtrlCh1, (leWidget*)Main_lblChName);

    Main_btnGainKnob = leButtonWidget_New();
    Main_btnGainKnob->fn->setPosition(Main_btnGainKnob, 43, 179);
    Main_btnGainKnob->fn->setSize(Main_btnGainKnob, 50, 50);
    Main_btnGainKnob->fn->setBackgroundType(Main_btnGainKnob, LE_WIDGET_BACKGROUND_NONE);
    Main_btnGainKnob->fn->setBorderType(Main_btnGainKnob, LE_WIDGET_BORDER_NONE);
    Main_btnGainKnob->fn->setPressedImage(Main_btnGainKnob, (leImage*)&SliderKnob);
    Main_btnGainKnob->fn->setReleasedImage(Main_btnGainKnob, (leImage*)&SliderKnob);
    Main_pnlChnCtrlCh1->fn->addChild(Main_pnlChnCtrlCh1, (leWidget*)Main_btnGainKnob);

    Main_ImageWidget_1 = leImageWidget_New();
    Main_ImageWidget_1->fn->setPosition(Main_ImageWidget_1, 495, 23);
    Main_ImageWidget_1->fn->setSize(Main_ImageWidget_1, 126, 33);
    Main_ImageWidget_1->fn->setBackgroundType(Main_ImageWidget_1, LE_WIDGET_BACKGROUND_NONE);
    Main_ImageWidget_1->fn->setBorderType(Main_ImageWidget_1, LE_WIDGET_BORDER_NONE);
    Main_ImageWidget_1->fn->setImage(Main_ImageWidget_1, (leImage*)&ButtonsAccs);
    root0->fn->addChild(root0, (leWidget*)Main_ImageWidget_1);

    Main_btnReset = leButtonWidget_New();
    Main_btnReset->fn->setPosition(Main_btnReset, 519, 432);
    Main_btnReset->fn->setSize(Main_btnReset, 142, 40);
    Main_btnReset->fn->setScheme(Main_btnReset, &WhiteTextScheme);
    Main_btnReset->fn->setBackgroundType(Main_btnReset, LE_WIDGET_BACKGROUND_NONE);
    Main_btnReset->fn->setBorderType(Main_btnReset, LE_WIDGET_BORDER_NONE);
    Main_btnReset->fn->setString(Main_btnReset, (leString*)&string_StringReset);
    Main_btnReset->fn->setPressedImage(Main_btnReset, (leImage*)&SmallButtonDown);
    Main_btnReset->fn->setReleasedImage(Main_btnReset, (leImage*)&SmallButtonUp);
    Main_btnReset->fn->setImagePosition(Main_btnReset, LE_RELATIVE_POSITION_BEHIND);
    Main_btnReset->fn->setPressedOffset(Main_btnReset, 0);
    Main_btnReset->fn->setReleasedEventCallback(Main_btnReset, event_Main_btnReset_OnReleased);
    root0->fn->addChild(root0, (leWidget*)Main_btnReset);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGBA_8888);

    Main_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_Main(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);

    Main_OnUpdate(); // raise event
}

void screenHide_Main(void)
{
    Main_OnHide(); // raise event


    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    Main_PanelWidget_0 = NULL;
    Main_PanelWidget_0_0 = NULL;
    Main_btnInputCh1 = NULL;
    Main_btnInputCh2 = NULL;
    Main_btnInputCh3 = NULL;
    Main_btnInputCh4 = NULL;
    Main_btnRun = NULL;
    Main_btnOutputCh1 = NULL;
    Main_btnOutputCh2 = NULL;
    Main_btnOutputCh3 = NULL;
    Main_btnOutputCh4 = NULL;
    Main_pbarAmpMain = NULL;
    Main_pnlMainGain = NULL;
    Main_btnMainGain = NULL;
    Main_btnMainMute = NULL;
    Main_pnlColorBarMain = NULL;
    Main_lblOutput = NULL;
    Main_lblMain = NULL;
    Main_pnlChnCtrlCh4 = NULL;
    Main_pnlChnCtrlCh3 = NULL;
    Main_pnlChnCtrlCh2 = NULL;
    Main_pnlChnCtrlCh1 = NULL;
    Main_ImageWidget_1 = NULL;
    Main_btnReset = NULL;
    Main_ImageWidget_0_1 = NULL;
    Main_ImageWidget_0_2 = NULL;
    Main_ImageWidget_0_2_0 = NULL;
    Main_ImageWidget_0_2_1 = NULL;
    Main_ImageWidget_0 = NULL;
    Main_ImageWidget_0_0 = NULL;
    Main_ImageWidget_0_0_0 = NULL;
    Main_ImageWidget_0_0_1 = NULL;
    Main_btnCue_4 = NULL;
    Main_pnlGain_4 = NULL;
    Main_btnM_4 = NULL;
    Main_btnS_4 = NULL;
    Main_pbarAmp_4 = NULL;
    Main_pnlColorBar_4 = NULL;
    Main_pnlLR_4 = NULL;
    Main_circLRKnob_4 = NULL;
    Main_lblChNum_4 = NULL;
    Main_lblL_4 = NULL;
    Main_lbl10_4 = NULL;
    Main_lblR_4 = NULL;
    Main_lbl5_4 = NULL;
    Main_lbl0_4 = NULL;
    Main_lbln5_4 = NULL;
    Main_lbln10_4 = NULL;
    Main_lbln15_4 = NULL;
    Main_lbln20_4 = NULL;
    Main_lbln25_4 = NULL;
    Main_lblChName_4 = NULL;
    Main_btnGainKnob_4 = NULL;
    Main_btnCue_3 = NULL;
    Main_pnlGain_3 = NULL;
    Main_btnM_3 = NULL;
    Main_btnS_3 = NULL;
    Main_pbarAmp_3 = NULL;
    Main_pnlColorBar_3 = NULL;
    Main_pnlLR_3 = NULL;
    Main_circLRKnob_3 = NULL;
    Main_lblChNum_3 = NULL;
    Main_lblL_3 = NULL;
    Main_lbl10_3 = NULL;
    Main_lblR_3 = NULL;
    Main_lbl5_3 = NULL;
    Main_lbl0_3 = NULL;
    Main_lbln5_3 = NULL;
    Main_lbln10_3 = NULL;
    Main_lbln15_3 = NULL;
    Main_lbln20_3 = NULL;
    Main_lbln25_3 = NULL;
    Main_lblChName_3 = NULL;
    Main_btnGainKnob_3 = NULL;
    Main_btnCue_2 = NULL;
    Main_pnlGain_2 = NULL;
    Main_btnM_2 = NULL;
    Main_btnS_2 = NULL;
    Main_pbarAmp_2 = NULL;
    Main_pnlColorBar_2 = NULL;
    Main_pnlLR_2 = NULL;
    Main_circLRKnob_2 = NULL;
    Main_lblChNum_2 = NULL;
    Main_lblL_2 = NULL;
    Main_lbl10_2 = NULL;
    Main_lblR_2 = NULL;
    Main_lbl5_2 = NULL;
    Main_lbl0_2 = NULL;
    Main_lbln5_2 = NULL;
    Main_lbln10_2 = NULL;
    Main_lbln15_2 = NULL;
    Main_lbln20_2 = NULL;
    Main_lbln25_2 = NULL;
    Main_lblChName_2 = NULL;
    Main_btnGainKnob_2 = NULL;
    Main_btnCue = NULL;
    Main_pnlGain = NULL;
    Main_btnM = NULL;
    Main_btnS = NULL;
    Main_pbarAmp = NULL;
    Main_pnlColorBar = NULL;
    Main_pnlLR = NULL;
    Main_circLRKnob = NULL;
    Main_lblChNum = NULL;
    Main_lblL = NULL;
    Main_lbl10 = NULL;
    Main_lblR = NULL;
    Main_lbl5 = NULL;
    Main_lbl0 = NULL;
    Main_lbln5 = NULL;
    Main_lbln10 = NULL;
    Main_lbln15 = NULL;
    Main_lbln20 = NULL;
    Main_lbln25 = NULL;
    Main_lblChName = NULL;
    Main_btnGainKnob = NULL;


    showing = LE_FALSE;
}

void screenDestroy_Main(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_Main(uint32_t lyrIdx)
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


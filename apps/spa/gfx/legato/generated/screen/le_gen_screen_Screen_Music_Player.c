#include "gfx/legato/generated/screen/le_gen_screen_Screen_Music_Player.h"

// screen member widget declarations
static leWidget* root0;

leWidget* Screen_Music_Player_Panel_0;
leImageWidget* Screen_Music_Player_ImageWidget_mgsLogo;
leLabelWidget* Screen_Music_Player_LabelWidget_0;
leImageWidget* Screen_Music_Player_ImageWidget_0;
leWidget* Screen_Music_Player_PanelWidget_0;
leWidget* Screen_Music_Player_PanelWidget_4;
leButtonWidget* Screen_Music_Player_ButtonWidget_Back;
leWidget* Screen_Music_Player_PanelWidget_2;
leWidget* Screen_Music_Player_PanelWidget_3;
leLabelWidget* Screen_Music_Player_LabelWidget_2;
leWidget* Screen_Music_Player_PanelWidget_5_0;
leImageWidget* Screen_Music_Player_ImageWidget_selBT;
leImageWidget* Screen_Music_Player_ImageWidget_2_0;
leLabelWidget* Screen_Music_Player_LabelWidget_3;
leButtonWidget* Screen_Music_Player_ButtonWidget_SearchBT;
leWidget* Screen_Music_Player_PanelWidget_BT1;
leWidget* Screen_Music_Player_PanelWidget_BT2;
leWidget* Screen_Music_Player_PanelWidget_BT3;
leButtonWidget* Screen_Music_Player_ButtonWidget_BT1;
leButtonWidget* Screen_Music_Player_ButtonWidget_BT2;
leButtonWidget* Screen_Music_Player_ButtonWidget_BT3;
leImageWidget* Screen_Music_Player_ImageWidget_SongPIc;
leLabelWidget* Screen_Music_Player_LabelWidget_ST;
leLabelWidget* Screen_Music_Player_LabelWidget_AN;
leWidget* Screen_Music_Player_PanelWidget_MP;
leImageWidget* Screen_Music_Player_ImageWidget_Volume;
leButtonWidget* Screen_Music_Player_ButtonWidget_Prev;
leButtonWidget* Screen_Music_Player_ButtonWidget_PlayPause;
leButtonWidget* Screen_Music_Player_ButtonWidget_Next;
leWidget* Screen_Music_Player_PanelWidget_Vol;
leWidget* Screen_Music_Player_PanelWidget_VolLight;
leWidget* Screen_Music_Player_PanelWidget_VolDark;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_Screen_Music_Player(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_Screen_Music_Player(void)
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

    Screen_Music_Player_Panel_0 = leWidget_New();
    Screen_Music_Player_Panel_0->fn->setPosition(Screen_Music_Player_Panel_0, 0, 0);
    Screen_Music_Player_Panel_0->fn->setSize(Screen_Music_Player_Panel_0, 1024, 600);
    Screen_Music_Player_Panel_0->fn->setScheme(Screen_Music_Player_Panel_0, &EditPanel);
    root0->fn->addChild(root0, (leWidget*)Screen_Music_Player_Panel_0);

    Screen_Music_Player_ImageWidget_mgsLogo = leImageWidget_New();
    Screen_Music_Player_ImageWidget_mgsLogo->fn->setPosition(Screen_Music_Player_ImageWidget_mgsLogo, 985, 10);
    Screen_Music_Player_ImageWidget_mgsLogo->fn->setSize(Screen_Music_Player_ImageWidget_mgsLogo, 29, 24);
    Screen_Music_Player_ImageWidget_mgsLogo->fn->setBackgroundType(Screen_Music_Player_ImageWidget_mgsLogo, LE_WIDGET_BACKGROUND_NONE);
    Screen_Music_Player_ImageWidget_mgsLogo->fn->setBorderType(Screen_Music_Player_ImageWidget_mgsLogo, LE_WIDGET_BORDER_NONE);
    Screen_Music_Player_ImageWidget_mgsLogo->fn->setImage(Screen_Music_Player_ImageWidget_mgsLogo, (leImage*)&mgs_logo);
    root0->fn->addChild(root0, (leWidget*)Screen_Music_Player_ImageWidget_mgsLogo);

    Screen_Music_Player_LabelWidget_0 = leLabelWidget_New();
    Screen_Music_Player_LabelWidget_0->fn->setPosition(Screen_Music_Player_LabelWidget_0, 410, 26);
    Screen_Music_Player_LabelWidget_0->fn->setSize(Screen_Music_Player_LabelWidget_0, 208, 40);
    Screen_Music_Player_LabelWidget_0->fn->setScheme(Screen_Music_Player_LabelWidget_0, &Scheme_Light);
    Screen_Music_Player_LabelWidget_0->fn->setBackgroundType(Screen_Music_Player_LabelWidget_0, LE_WIDGET_BACKGROUND_NONE);
    Screen_Music_Player_LabelWidget_0->fn->setVAlignment(Screen_Music_Player_LabelWidget_0, LE_VALIGN_TOP);
    Screen_Music_Player_LabelWidget_0->fn->setMargins(Screen_Music_Player_LabelWidget_0, 0, 0, 0, 0);
    Screen_Music_Player_LabelWidget_0->fn->setString(Screen_Music_Player_LabelWidget_0, (leString*)&string_MusicPlayerLbl);
    root0->fn->addChild(root0, (leWidget*)Screen_Music_Player_LabelWidget_0);

    Screen_Music_Player_ImageWidget_0 = leImageWidget_New();
    Screen_Music_Player_ImageWidget_0->fn->setPosition(Screen_Music_Player_ImageWidget_0, 510, 115);
    Screen_Music_Player_ImageWidget_0->fn->setSize(Screen_Music_Player_ImageWidget_0, 4, 345);
    Screen_Music_Player_ImageWidget_0->fn->setBackgroundType(Screen_Music_Player_ImageWidget_0, LE_WIDGET_BACKGROUND_NONE);
    Screen_Music_Player_ImageWidget_0->fn->setBorderType(Screen_Music_Player_ImageWidget_0, LE_WIDGET_BORDER_NONE);
    Screen_Music_Player_ImageWidget_0->fn->setMargins(Screen_Music_Player_ImageWidget_0, 0, 0, 0, 0);
    Screen_Music_Player_ImageWidget_0->fn->setImage(Screen_Music_Player_ImageWidget_0, (leImage*)&vertical_line);
    root0->fn->addChild(root0, (leWidget*)Screen_Music_Player_ImageWidget_0);

    Screen_Music_Player_PanelWidget_0 = leWidget_New();
    Screen_Music_Player_PanelWidget_0->fn->setPosition(Screen_Music_Player_PanelWidget_0, 120, 116);
    Screen_Music_Player_PanelWidget_0->fn->setSize(Screen_Music_Player_PanelWidget_0, 286, 366);
    Screen_Music_Player_PanelWidget_0->fn->setBackgroundType(Screen_Music_Player_PanelWidget_0, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->addChild(root0, (leWidget*)Screen_Music_Player_PanelWidget_0);

    Screen_Music_Player_PanelWidget_2 = leWidget_New();
    Screen_Music_Player_PanelWidget_2->fn->setPosition(Screen_Music_Player_PanelWidget_2, 0, 0);
    Screen_Music_Player_PanelWidget_2->fn->setSize(Screen_Music_Player_PanelWidget_2, 230, 104);
    Screen_Music_Player_PanelWidget_2->fn->setBackgroundType(Screen_Music_Player_PanelWidget_2, LE_WIDGET_BACKGROUND_NONE);
    Screen_Music_Player_PanelWidget_0->fn->addChild(Screen_Music_Player_PanelWidget_0, (leWidget*)Screen_Music_Player_PanelWidget_2);

    Screen_Music_Player_LabelWidget_2 = leLabelWidget_New();
    Screen_Music_Player_LabelWidget_2->fn->setPosition(Screen_Music_Player_LabelWidget_2, 0, 0);
    Screen_Music_Player_LabelWidget_2->fn->setSize(Screen_Music_Player_LabelWidget_2, 220, 32);
    Screen_Music_Player_LabelWidget_2->fn->setScheme(Screen_Music_Player_LabelWidget_2, &Scheme_Light);
    Screen_Music_Player_LabelWidget_2->fn->setBackgroundType(Screen_Music_Player_LabelWidget_2, LE_WIDGET_BACKGROUND_NONE);
    Screen_Music_Player_LabelWidget_2->fn->setVAlignment(Screen_Music_Player_LabelWidget_2, LE_VALIGN_TOP);
    Screen_Music_Player_LabelWidget_2->fn->setMargins(Screen_Music_Player_LabelWidget_2, 0, 0, 0, 0);
    Screen_Music_Player_LabelWidget_2->fn->setString(Screen_Music_Player_LabelWidget_2, (leString*)&string_BluetoothDevLbl);
    Screen_Music_Player_PanelWidget_2->fn->addChild(Screen_Music_Player_PanelWidget_2, (leWidget*)Screen_Music_Player_LabelWidget_2);

    Screen_Music_Player_PanelWidget_5_0 = leWidget_New();
    Screen_Music_Player_PanelWidget_5_0->fn->setPosition(Screen_Music_Player_PanelWidget_5_0, 0, 40);
    Screen_Music_Player_PanelWidget_5_0->fn->setSize(Screen_Music_Player_PanelWidget_5_0, 216, 44);
    Screen_Music_Player_PanelWidget_5_0->fn->setBackgroundType(Screen_Music_Player_PanelWidget_5_0, LE_WIDGET_BACKGROUND_NONE);
    Screen_Music_Player_PanelWidget_2->fn->addChild(Screen_Music_Player_PanelWidget_2, (leWidget*)Screen_Music_Player_PanelWidget_5_0);

    Screen_Music_Player_ImageWidget_selBT = leImageWidget_New();
    Screen_Music_Player_ImageWidget_selBT->fn->setPosition(Screen_Music_Player_ImageWidget_selBT, 0, 0);
    Screen_Music_Player_ImageWidget_selBT->fn->setSize(Screen_Music_Player_ImageWidget_selBT, 170, 44);
    Screen_Music_Player_ImageWidget_selBT->fn->setBackgroundType(Screen_Music_Player_ImageWidget_selBT, LE_WIDGET_BACKGROUND_NONE);
    Screen_Music_Player_ImageWidget_selBT->fn->setBorderType(Screen_Music_Player_ImageWidget_selBT, LE_WIDGET_BORDER_NONE);
    Screen_Music_Player_ImageWidget_selBT->fn->setImage(Screen_Music_Player_ImageWidget_selBT, (leImage*)&lee_iphone);
    Screen_Music_Player_PanelWidget_5_0->fn->addChild(Screen_Music_Player_PanelWidget_5_0, (leWidget*)Screen_Music_Player_ImageWidget_selBT);

    Screen_Music_Player_ImageWidget_2_0 = leImageWidget_New();
    Screen_Music_Player_ImageWidget_2_0->fn->setPosition(Screen_Music_Player_ImageWidget_2_0, 130, 10);
    Screen_Music_Player_ImageWidget_2_0->fn->setSize(Screen_Music_Player_ImageWidget_2_0, 24, 24);
    Screen_Music_Player_ImageWidget_2_0->fn->setBackgroundType(Screen_Music_Player_ImageWidget_2_0, LE_WIDGET_BACKGROUND_NONE);
    Screen_Music_Player_ImageWidget_2_0->fn->setBorderType(Screen_Music_Player_ImageWidget_2_0, LE_WIDGET_BORDER_NONE);
    Screen_Music_Player_ImageWidget_2_0->fn->setImage(Screen_Music_Player_ImageWidget_2_0, (leImage*)&check_small);
    Screen_Music_Player_PanelWidget_5_0->fn->addChild(Screen_Music_Player_PanelWidget_5_0, (leWidget*)Screen_Music_Player_ImageWidget_2_0);

    Screen_Music_Player_PanelWidget_3 = leWidget_New();
    Screen_Music_Player_PanelWidget_3->fn->setPosition(Screen_Music_Player_PanelWidget_3, 0, 112);
    Screen_Music_Player_PanelWidget_3->fn->setSize(Screen_Music_Player_PanelWidget_3, 292, 245);
    Screen_Music_Player_PanelWidget_3->fn->setBackgroundType(Screen_Music_Player_PanelWidget_3, LE_WIDGET_BACKGROUND_NONE);
    Screen_Music_Player_PanelWidget_0->fn->addChild(Screen_Music_Player_PanelWidget_0, (leWidget*)Screen_Music_Player_PanelWidget_3);

    Screen_Music_Player_LabelWidget_3 = leLabelWidget_New();
    Screen_Music_Player_LabelWidget_3->fn->setPosition(Screen_Music_Player_LabelWidget_3, 0, 0);
    Screen_Music_Player_LabelWidget_3->fn->setSize(Screen_Music_Player_LabelWidget_3, 296, 32);
    Screen_Music_Player_LabelWidget_3->fn->setScheme(Screen_Music_Player_LabelWidget_3, &Scheme_Light);
    Screen_Music_Player_LabelWidget_3->fn->setBackgroundType(Screen_Music_Player_LabelWidget_3, LE_WIDGET_BACKGROUND_NONE);
    Screen_Music_Player_LabelWidget_3->fn->setVAlignment(Screen_Music_Player_LabelWidget_3, LE_VALIGN_TOP);
    Screen_Music_Player_LabelWidget_3->fn->setMargins(Screen_Music_Player_LabelWidget_3, 0, 0, 0, 0);
    Screen_Music_Player_LabelWidget_3->fn->setString(Screen_Music_Player_LabelWidget_3, (leString*)&string_BluetoothOtherDevAvlbLbl);
    Screen_Music_Player_PanelWidget_3->fn->addChild(Screen_Music_Player_PanelWidget_3, (leWidget*)Screen_Music_Player_LabelWidget_3);

    Screen_Music_Player_ButtonWidget_SearchBT = leButtonWidget_New();
    Screen_Music_Player_ButtonWidget_SearchBT->fn->setPosition(Screen_Music_Player_ButtonWidget_SearchBT, 0, 40);
    Screen_Music_Player_ButtonWidget_SearchBT->fn->setSize(Screen_Music_Player_ButtonWidget_SearchBT, 184, 36);
    Screen_Music_Player_ButtonWidget_SearchBT->fn->setScheme(Screen_Music_Player_ButtonWidget_SearchBT, &Scheme_Light);
    Screen_Music_Player_ButtonWidget_SearchBT->fn->setBorderType(Screen_Music_Player_ButtonWidget_SearchBT, LE_WIDGET_BORDER_NONE);
    Screen_Music_Player_ButtonWidget_SearchBT->fn->setString(Screen_Music_Player_ButtonWidget_SearchBT, (leString*)&string_ScanDevBT);
    Screen_Music_Player_ButtonWidget_SearchBT->fn->setPressedImage(Screen_Music_Player_ButtonWidget_SearchBT, (leImage*)&wifi_scan);
    Screen_Music_Player_ButtonWidget_SearchBT->fn->setReleasedImage(Screen_Music_Player_ButtonWidget_SearchBT, (leImage*)&wifi_scan);
    Screen_Music_Player_ButtonWidget_SearchBT->fn->setPressedEventCallback(Screen_Music_Player_ButtonWidget_SearchBT, event_Screen_Music_Player_ButtonWidget_SearchBT_OnPressed);
    Screen_Music_Player_ButtonWidget_SearchBT->fn->setReleasedEventCallback(Screen_Music_Player_ButtonWidget_SearchBT, event_Screen_Music_Player_ButtonWidget_SearchBT_OnReleased);
    Screen_Music_Player_PanelWidget_3->fn->addChild(Screen_Music_Player_PanelWidget_3, (leWidget*)Screen_Music_Player_ButtonWidget_SearchBT);

    Screen_Music_Player_PanelWidget_BT1 = leWidget_New();
    Screen_Music_Player_PanelWidget_BT1->fn->setPosition(Screen_Music_Player_PanelWidget_BT1, 0, 88);
    Screen_Music_Player_PanelWidget_BT1->fn->setSize(Screen_Music_Player_PanelWidget_BT1, 156, 48);
    Screen_Music_Player_PanelWidget_BT1->fn->setBackgroundType(Screen_Music_Player_PanelWidget_BT1, LE_WIDGET_BACKGROUND_NONE);
    Screen_Music_Player_PanelWidget_3->fn->addChild(Screen_Music_Player_PanelWidget_3, (leWidget*)Screen_Music_Player_PanelWidget_BT1);

    Screen_Music_Player_ButtonWidget_BT1 = leButtonWidget_New();
    Screen_Music_Player_ButtonWidget_BT1->fn->setPosition(Screen_Music_Player_ButtonWidget_BT1, 0, 0);
    Screen_Music_Player_ButtonWidget_BT1->fn->setSize(Screen_Music_Player_ButtonWidget_BT1, 154, 44);
    Screen_Music_Player_ButtonWidget_BT1->fn->setScheme(Screen_Music_Player_ButtonWidget_BT1, &Scheme_Light);
    Screen_Music_Player_ButtonWidget_BT1->fn->setBorderType(Screen_Music_Player_ButtonWidget_BT1, LE_WIDGET_BORDER_NONE);
    Screen_Music_Player_ButtonWidget_BT1->fn->setString(Screen_Music_Player_ButtonWidget_BT1, (leString*)&string_BTDev1);
    Screen_Music_Player_ButtonWidget_BT1->fn->setPressedImage(Screen_Music_Player_ButtonWidget_BT1, (leImage*)&phone_iphone);
    Screen_Music_Player_ButtonWidget_BT1->fn->setReleasedImage(Screen_Music_Player_ButtonWidget_BT1, (leImage*)&phone_iphone);
    Screen_Music_Player_PanelWidget_BT1->fn->addChild(Screen_Music_Player_PanelWidget_BT1, (leWidget*)Screen_Music_Player_ButtonWidget_BT1);

    Screen_Music_Player_PanelWidget_BT2 = leWidget_New();
    Screen_Music_Player_PanelWidget_BT2->fn->setPosition(Screen_Music_Player_PanelWidget_BT2, 0, 144);
    Screen_Music_Player_PanelWidget_BT2->fn->setSize(Screen_Music_Player_PanelWidget_BT2, 156, 48);
    Screen_Music_Player_PanelWidget_BT2->fn->setBackgroundType(Screen_Music_Player_PanelWidget_BT2, LE_WIDGET_BACKGROUND_NONE);
    Screen_Music_Player_PanelWidget_3->fn->addChild(Screen_Music_Player_PanelWidget_3, (leWidget*)Screen_Music_Player_PanelWidget_BT2);

    Screen_Music_Player_ButtonWidget_BT2 = leButtonWidget_New();
    Screen_Music_Player_ButtonWidget_BT2->fn->setPosition(Screen_Music_Player_ButtonWidget_BT2, 0, 0);
    Screen_Music_Player_ButtonWidget_BT2->fn->setSize(Screen_Music_Player_ButtonWidget_BT2, 154, 44);
    Screen_Music_Player_ButtonWidget_BT2->fn->setScheme(Screen_Music_Player_ButtonWidget_BT2, &Scheme_Light);
    Screen_Music_Player_ButtonWidget_BT2->fn->setBorderType(Screen_Music_Player_ButtonWidget_BT2, LE_WIDGET_BORDER_NONE);
    Screen_Music_Player_ButtonWidget_BT2->fn->setString(Screen_Music_Player_ButtonWidget_BT2, (leString*)&string_BTDev2);
    Screen_Music_Player_ButtonWidget_BT2->fn->setPressedImage(Screen_Music_Player_ButtonWidget_BT2, (leImage*)&phone_iphone);
    Screen_Music_Player_ButtonWidget_BT2->fn->setReleasedImage(Screen_Music_Player_ButtonWidget_BT2, (leImage*)&phone_iphone);
    Screen_Music_Player_PanelWidget_BT2->fn->addChild(Screen_Music_Player_PanelWidget_BT2, (leWidget*)Screen_Music_Player_ButtonWidget_BT2);

    Screen_Music_Player_PanelWidget_BT3 = leWidget_New();
    Screen_Music_Player_PanelWidget_BT3->fn->setPosition(Screen_Music_Player_PanelWidget_BT3, 0, 200);
    Screen_Music_Player_PanelWidget_BT3->fn->setSize(Screen_Music_Player_PanelWidget_BT3, 156, 48);
    Screen_Music_Player_PanelWidget_BT3->fn->setBackgroundType(Screen_Music_Player_PanelWidget_BT3, LE_WIDGET_BACKGROUND_NONE);
    Screen_Music_Player_PanelWidget_3->fn->addChild(Screen_Music_Player_PanelWidget_3, (leWidget*)Screen_Music_Player_PanelWidget_BT3);

    Screen_Music_Player_ButtonWidget_BT3 = leButtonWidget_New();
    Screen_Music_Player_ButtonWidget_BT3->fn->setPosition(Screen_Music_Player_ButtonWidget_BT3, 0, 0);
    Screen_Music_Player_ButtonWidget_BT3->fn->setSize(Screen_Music_Player_ButtonWidget_BT3, 154, 44);
    Screen_Music_Player_ButtonWidget_BT3->fn->setScheme(Screen_Music_Player_ButtonWidget_BT3, &Scheme_Light);
    Screen_Music_Player_ButtonWidget_BT3->fn->setBorderType(Screen_Music_Player_ButtonWidget_BT3, LE_WIDGET_BORDER_NONE);
    Screen_Music_Player_ButtonWidget_BT3->fn->setString(Screen_Music_Player_ButtonWidget_BT3, (leString*)&string_BTDev3);
    Screen_Music_Player_ButtonWidget_BT3->fn->setPressedImage(Screen_Music_Player_ButtonWidget_BT3, (leImage*)&phone_iphone);
    Screen_Music_Player_ButtonWidget_BT3->fn->setReleasedImage(Screen_Music_Player_ButtonWidget_BT3, (leImage*)&phone_iphone);
    Screen_Music_Player_PanelWidget_BT3->fn->addChild(Screen_Music_Player_PanelWidget_BT3, (leWidget*)Screen_Music_Player_ButtonWidget_BT3);

    Screen_Music_Player_PanelWidget_4 = leWidget_New();
    Screen_Music_Player_PanelWidget_4->fn->setPosition(Screen_Music_Player_PanelWidget_4, 620, 127);
    Screen_Music_Player_PanelWidget_4->fn->setSize(Screen_Music_Player_PanelWidget_4, 250, 360);
    Screen_Music_Player_PanelWidget_4->fn->setBackgroundType(Screen_Music_Player_PanelWidget_4, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->addChild(root0, (leWidget*)Screen_Music_Player_PanelWidget_4);

    Screen_Music_Player_ImageWidget_SongPIc = leImageWidget_New();
    Screen_Music_Player_ImageWidget_SongPIc->fn->setPosition(Screen_Music_Player_ImageWidget_SongPIc, 42, 0);
    Screen_Music_Player_ImageWidget_SongPIc->fn->setSize(Screen_Music_Player_ImageWidget_SongPIc, 180, 180);
    Screen_Music_Player_ImageWidget_SongPIc->fn->setBorderType(Screen_Music_Player_ImageWidget_SongPIc, LE_WIDGET_BORDER_NONE);
    Screen_Music_Player_ImageWidget_SongPIc->fn->setImage(Screen_Music_Player_ImageWidget_SongPIc, (leImage*)&Song_Pic_large);
    Screen_Music_Player_PanelWidget_4->fn->addChild(Screen_Music_Player_PanelWidget_4, (leWidget*)Screen_Music_Player_ImageWidget_SongPIc);

    Screen_Music_Player_LabelWidget_ST = leLabelWidget_New();
    Screen_Music_Player_LabelWidget_ST->fn->setPosition(Screen_Music_Player_LabelWidget_ST, 82, 206);
    Screen_Music_Player_LabelWidget_ST->fn->setSize(Screen_Music_Player_LabelWidget_ST, 104, 26);
    Screen_Music_Player_LabelWidget_ST->fn->setScheme(Screen_Music_Player_LabelWidget_ST, &Scheme_Light);
    Screen_Music_Player_LabelWidget_ST->fn->setBackgroundType(Screen_Music_Player_LabelWidget_ST, LE_WIDGET_BACKGROUND_NONE);
    Screen_Music_Player_LabelWidget_ST->fn->setVAlignment(Screen_Music_Player_LabelWidget_ST, LE_VALIGN_TOP);
    Screen_Music_Player_LabelWidget_ST->fn->setMargins(Screen_Music_Player_LabelWidget_ST, 0, 0, 0, 0);
    Screen_Music_Player_LabelWidget_ST->fn->setString(Screen_Music_Player_LabelWidget_ST, (leString*)&string_SongTitle);
    Screen_Music_Player_PanelWidget_4->fn->addChild(Screen_Music_Player_PanelWidget_4, (leWidget*)Screen_Music_Player_LabelWidget_ST);

    Screen_Music_Player_LabelWidget_AN = leLabelWidget_New();
    Screen_Music_Player_LabelWidget_AN->fn->setPosition(Screen_Music_Player_LabelWidget_AN, 100, 232);
    Screen_Music_Player_LabelWidget_AN->fn->setSize(Screen_Music_Player_LabelWidget_AN, 72, 20);
    Screen_Music_Player_LabelWidget_AN->fn->setScheme(Screen_Music_Player_LabelWidget_AN, &Scheme_Light);
    Screen_Music_Player_LabelWidget_AN->fn->setBackgroundType(Screen_Music_Player_LabelWidget_AN, LE_WIDGET_BACKGROUND_NONE);
    Screen_Music_Player_LabelWidget_AN->fn->setVAlignment(Screen_Music_Player_LabelWidget_AN, LE_VALIGN_TOP);
    Screen_Music_Player_LabelWidget_AN->fn->setMargins(Screen_Music_Player_LabelWidget_AN, 0, 0, 0, 0);
    Screen_Music_Player_LabelWidget_AN->fn->setString(Screen_Music_Player_LabelWidget_AN, (leString*)&string_ArtistName);
    Screen_Music_Player_PanelWidget_4->fn->addChild(Screen_Music_Player_PanelWidget_4, (leWidget*)Screen_Music_Player_LabelWidget_AN);

    Screen_Music_Player_PanelWidget_MP = leWidget_New();
    Screen_Music_Player_PanelWidget_MP->fn->setPosition(Screen_Music_Player_PanelWidget_MP, 0, 264);
    Screen_Music_Player_PanelWidget_MP->fn->setSize(Screen_Music_Player_PanelWidget_MP, 252, 86);
    Screen_Music_Player_PanelWidget_MP->fn->setBackgroundType(Screen_Music_Player_PanelWidget_MP, LE_WIDGET_BACKGROUND_NONE);
    Screen_Music_Player_PanelWidget_4->fn->addChild(Screen_Music_Player_PanelWidget_4, (leWidget*)Screen_Music_Player_PanelWidget_MP);

    Screen_Music_Player_ImageWidget_Volume = leImageWidget_New();
    Screen_Music_Player_ImageWidget_Volume->fn->setPosition(Screen_Music_Player_ImageWidget_Volume, 0, 64);
    Screen_Music_Player_ImageWidget_Volume->fn->setSize(Screen_Music_Player_ImageWidget_Volume, 16, 16);
    Screen_Music_Player_ImageWidget_Volume->fn->setBackgroundType(Screen_Music_Player_ImageWidget_Volume, LE_WIDGET_BACKGROUND_NONE);
    Screen_Music_Player_ImageWidget_Volume->fn->setBorderType(Screen_Music_Player_ImageWidget_Volume, LE_WIDGET_BORDER_NONE);
    Screen_Music_Player_ImageWidget_Volume->fn->setImage(Screen_Music_Player_ImageWidget_Volume, (leImage*)&volume_16x16);
    Screen_Music_Player_PanelWidget_MP->fn->addChild(Screen_Music_Player_PanelWidget_MP, (leWidget*)Screen_Music_Player_ImageWidget_Volume);

    Screen_Music_Player_ButtonWidget_Prev = leButtonWidget_New();
    Screen_Music_Player_ButtonWidget_Prev->fn->setPosition(Screen_Music_Player_ButtonWidget_Prev, 28, 0);
    Screen_Music_Player_ButtonWidget_Prev->fn->setSize(Screen_Music_Player_ButtonWidget_Prev, 48, 48);
    Screen_Music_Player_ButtonWidget_Prev->fn->setBackgroundType(Screen_Music_Player_ButtonWidget_Prev, LE_WIDGET_BACKGROUND_NONE);
    Screen_Music_Player_ButtonWidget_Prev->fn->setBorderType(Screen_Music_Player_ButtonWidget_Prev, LE_WIDGET_BORDER_NONE);
    Screen_Music_Player_ButtonWidget_Prev->fn->setPressedImage(Screen_Music_Player_ButtonWidget_Prev, (leImage*)&skip_previous_48x48);
    Screen_Music_Player_ButtonWidget_Prev->fn->setReleasedImage(Screen_Music_Player_ButtonWidget_Prev, (leImage*)&skip_previous_48x48);
    Screen_Music_Player_ButtonWidget_Prev->fn->setReleasedEventCallback(Screen_Music_Player_ButtonWidget_Prev, event_Screen_Music_Player_ButtonWidget_Prev_OnReleased);
    Screen_Music_Player_PanelWidget_MP->fn->addChild(Screen_Music_Player_PanelWidget_MP, (leWidget*)Screen_Music_Player_ButtonWidget_Prev);

    Screen_Music_Player_ButtonWidget_PlayPause = leButtonWidget_New();
    Screen_Music_Player_ButtonWidget_PlayPause->fn->setPosition(Screen_Music_Player_ButtonWidget_PlayPause, 108, 0);
    Screen_Music_Player_ButtonWidget_PlayPause->fn->setSize(Screen_Music_Player_ButtonWidget_PlayPause, 48, 48);
    Screen_Music_Player_ButtonWidget_PlayPause->fn->setBackgroundType(Screen_Music_Player_ButtonWidget_PlayPause, LE_WIDGET_BACKGROUND_NONE);
    Screen_Music_Player_ButtonWidget_PlayPause->fn->setBorderType(Screen_Music_Player_ButtonWidget_PlayPause, LE_WIDGET_BORDER_NONE);
    Screen_Music_Player_ButtonWidget_PlayPause->fn->setToggleable(Screen_Music_Player_ButtonWidget_PlayPause, LE_TRUE);
    Screen_Music_Player_ButtonWidget_PlayPause->fn->setPressedImage(Screen_Music_Player_ButtonWidget_PlayPause, (leImage*)&play_circle_48x48);
    Screen_Music_Player_ButtonWidget_PlayPause->fn->setReleasedImage(Screen_Music_Player_ButtonWidget_PlayPause, (leImage*)&pause_circle_48x48);
    Screen_Music_Player_ButtonWidget_PlayPause->fn->setPressedOffset(Screen_Music_Player_ButtonWidget_PlayPause, 0);
    Screen_Music_Player_ButtonWidget_PlayPause->fn->setPressedEventCallback(Screen_Music_Player_ButtonWidget_PlayPause, event_Screen_Music_Player_ButtonWidget_PlayPause_OnPressed);
    Screen_Music_Player_ButtonWidget_PlayPause->fn->setReleasedEventCallback(Screen_Music_Player_ButtonWidget_PlayPause, event_Screen_Music_Player_ButtonWidget_PlayPause_OnReleased);
    Screen_Music_Player_PanelWidget_MP->fn->addChild(Screen_Music_Player_PanelWidget_MP, (leWidget*)Screen_Music_Player_ButtonWidget_PlayPause);

    Screen_Music_Player_ButtonWidget_Next = leButtonWidget_New();
    Screen_Music_Player_ButtonWidget_Next->fn->setPosition(Screen_Music_Player_ButtonWidget_Next, 188, 0);
    Screen_Music_Player_ButtonWidget_Next->fn->setSize(Screen_Music_Player_ButtonWidget_Next, 48, 48);
    Screen_Music_Player_ButtonWidget_Next->fn->setBackgroundType(Screen_Music_Player_ButtonWidget_Next, LE_WIDGET_BACKGROUND_NONE);
    Screen_Music_Player_ButtonWidget_Next->fn->setBorderType(Screen_Music_Player_ButtonWidget_Next, LE_WIDGET_BORDER_NONE);
    Screen_Music_Player_ButtonWidget_Next->fn->setPressedImage(Screen_Music_Player_ButtonWidget_Next, (leImage*)&skip_next_48x48);
    Screen_Music_Player_ButtonWidget_Next->fn->setReleasedImage(Screen_Music_Player_ButtonWidget_Next, (leImage*)&skip_next_48x48);
    Screen_Music_Player_ButtonWidget_Next->fn->setReleasedEventCallback(Screen_Music_Player_ButtonWidget_Next, event_Screen_Music_Player_ButtonWidget_Next_OnReleased);
    Screen_Music_Player_PanelWidget_MP->fn->addChild(Screen_Music_Player_PanelWidget_MP, (leWidget*)Screen_Music_Player_ButtonWidget_Next);

    Screen_Music_Player_PanelWidget_Vol = leWidget_New();
    Screen_Music_Player_PanelWidget_Vol->fn->setPosition(Screen_Music_Player_PanelWidget_Vol, 12, 44);
    Screen_Music_Player_PanelWidget_Vol->fn->setSize(Screen_Music_Player_PanelWidget_Vol, 240, 56);
    Screen_Music_Player_PanelWidget_Vol->fn->setBackgroundType(Screen_Music_Player_PanelWidget_Vol, LE_WIDGET_BACKGROUND_NONE);
    Screen_Music_Player_PanelWidget_MP->fn->addChild(Screen_Music_Player_PanelWidget_MP, (leWidget*)Screen_Music_Player_PanelWidget_Vol);

    Screen_Music_Player_PanelWidget_VolLight = leWidget_New();
    Screen_Music_Player_PanelWidget_VolLight->fn->setPosition(Screen_Music_Player_PanelWidget_VolLight, 10, 24);
    Screen_Music_Player_PanelWidget_VolLight->fn->setSize(Screen_Music_Player_PanelWidget_VolLight, 220, 8);
    Screen_Music_Player_PanelWidget_VolLight->fn->setEnabled(Screen_Music_Player_PanelWidget_VolLight, LE_FALSE);
    Screen_Music_Player_PanelWidget_VolLight->fn->setScheme(Screen_Music_Player_PanelWidget_VolLight, &SliderLightScheme);
    Screen_Music_Player_PanelWidget_Vol->fn->addChild(Screen_Music_Player_PanelWidget_Vol, (leWidget*)Screen_Music_Player_PanelWidget_VolLight);

    Screen_Music_Player_PanelWidget_VolDark = leWidget_New();
    Screen_Music_Player_PanelWidget_VolDark->fn->setPosition(Screen_Music_Player_PanelWidget_VolDark, 10, 24);
    Screen_Music_Player_PanelWidget_VolDark->fn->setSize(Screen_Music_Player_PanelWidget_VolDark, 110, 8);
    Screen_Music_Player_PanelWidget_VolDark->fn->setEnabled(Screen_Music_Player_PanelWidget_VolDark, LE_FALSE);
    Screen_Music_Player_PanelWidget_VolDark->fn->setScheme(Screen_Music_Player_PanelWidget_VolDark, &SliderDarkScheme);
    Screen_Music_Player_PanelWidget_Vol->fn->addChild(Screen_Music_Player_PanelWidget_Vol, (leWidget*)Screen_Music_Player_PanelWidget_VolDark);

    Screen_Music_Player_ButtonWidget_Back = leButtonWidget_New();
    Screen_Music_Player_ButtonWidget_Back->fn->setPosition(Screen_Music_Player_ButtonWidget_Back, 32, 24);
    Screen_Music_Player_ButtonWidget_Back->fn->setSize(Screen_Music_Player_ButtonWidget_Back, 135, 48);
    Screen_Music_Player_ButtonWidget_Back->fn->setScheme(Screen_Music_Player_ButtonWidget_Back, &Scheme_Light);
    Screen_Music_Player_ButtonWidget_Back->fn->setBorderType(Screen_Music_Player_ButtonWidget_Back, LE_WIDGET_BORDER_NONE);
    Screen_Music_Player_ButtonWidget_Back->fn->setMargins(Screen_Music_Player_ButtonWidget_Back, 0, 0, 0, 0);
    Screen_Music_Player_ButtonWidget_Back->fn->setString(Screen_Music_Player_ButtonWidget_Back, (leString*)&string_BackLbl);
    Screen_Music_Player_ButtonWidget_Back->fn->setPressedImage(Screen_Music_Player_ButtonWidget_Back, (leImage*)&reply);
    Screen_Music_Player_ButtonWidget_Back->fn->setReleasedImage(Screen_Music_Player_ButtonWidget_Back, (leImage*)&reply);
    Screen_Music_Player_ButtonWidget_Back->fn->setImageMargin(Screen_Music_Player_ButtonWidget_Back, 8);
    Screen_Music_Player_ButtonWidget_Back->fn->setReleasedEventCallback(Screen_Music_Player_ButtonWidget_Back, event_Screen_Music_Player_ButtonWidget_Back_OnReleased);
    root0->fn->addChild(root0, (leWidget*)Screen_Music_Player_ButtonWidget_Back);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    Screen_Music_Player_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_Screen_Music_Player(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);

    Screen_Music_Player_OnUpdate(); // raise event
}

void screenHide_Screen_Music_Player(void)
{
    Screen_Music_Player_OnHide(); // raise event


    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    Screen_Music_Player_Panel_0 = NULL;
    Screen_Music_Player_ImageWidget_mgsLogo = NULL;
    Screen_Music_Player_LabelWidget_0 = NULL;
    Screen_Music_Player_ImageWidget_0 = NULL;
    Screen_Music_Player_PanelWidget_0 = NULL;
    Screen_Music_Player_PanelWidget_4 = NULL;
    Screen_Music_Player_ButtonWidget_Back = NULL;
    Screen_Music_Player_PanelWidget_2 = NULL;
    Screen_Music_Player_PanelWidget_3 = NULL;
    Screen_Music_Player_LabelWidget_2 = NULL;
    Screen_Music_Player_PanelWidget_5_0 = NULL;
    Screen_Music_Player_ImageWidget_selBT = NULL;
    Screen_Music_Player_ImageWidget_2_0 = NULL;
    Screen_Music_Player_LabelWidget_3 = NULL;
    Screen_Music_Player_ButtonWidget_SearchBT = NULL;
    Screen_Music_Player_PanelWidget_BT1 = NULL;
    Screen_Music_Player_PanelWidget_BT2 = NULL;
    Screen_Music_Player_PanelWidget_BT3 = NULL;
    Screen_Music_Player_ButtonWidget_BT1 = NULL;
    Screen_Music_Player_ButtonWidget_BT2 = NULL;
    Screen_Music_Player_ButtonWidget_BT3 = NULL;
    Screen_Music_Player_ImageWidget_SongPIc = NULL;
    Screen_Music_Player_LabelWidget_ST = NULL;
    Screen_Music_Player_LabelWidget_AN = NULL;
    Screen_Music_Player_PanelWidget_MP = NULL;
    Screen_Music_Player_ImageWidget_Volume = NULL;
    Screen_Music_Player_ButtonWidget_Prev = NULL;
    Screen_Music_Player_ButtonWidget_PlayPause = NULL;
    Screen_Music_Player_ButtonWidget_Next = NULL;
    Screen_Music_Player_PanelWidget_Vol = NULL;
    Screen_Music_Player_PanelWidget_VolLight = NULL;
    Screen_Music_Player_PanelWidget_VolDark = NULL;


    showing = LE_FALSE;
}

void screenDestroy_Screen_Music_Player(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_Screen_Music_Player(uint32_t lyrIdx)
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


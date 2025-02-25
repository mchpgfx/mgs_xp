#include "gfx/legato/generated/screen/le_gen_screen_Screen_Main.h"

// screen member widget declarations
static leWidget* root0;

leWidget* Screen_Main_BackgroundPanel;
leButtonWidget* Screen_Main_ButtonWidget_Settings;
leButtonWidget* Screen_Main_ButtonWidget_WaterQ;
leLabelWidget* Screen_Main_LabelWidget_SelectReg;
leLabelWidget* Screen_Main_LabelWidget_ControlDisp;
leImageWidget* Screen_Main_ImageWidget_Regions;
leButtonWidget* Screen_Main_ButtonWidget_Reg2;
leButtonWidget* Screen_Main_ButtonWidget_Reg1;
leButtonWidget* Screen_Main_ButtonWidget_Reg3;
leButtonWidget* Screen_Main_ButtonWidget_Reg4;
leWidget* Screen_Main_EditPanelWidget;
leWidget* Screen_Main_PanelWidget_0;
leWidget* Screen_Main_PanelWidget_1;
leImageWidget* Screen_Main_ImageWidget_mgsLogo;
leWidget* Screen_Main_PanelWidget_WaterTemp;
leWidget* Screen_Main_PanelWidget_SelColors;
leWidget* Screen_Main_PanelWidget_JetCtrl;
leWidget* Screen_Main_PanelWidget_MP;
leButtonWidget* Screen_Main_ButtonWidget_MP;
leLabelWidget* Screen_Main_LabelWidget_WaterTemp;
leButtonWidget* Screen_Main_ButtonWidget_IncTemp;
leButtonWidget* Screen_Main_ButtonWidget_DecTemp;
leLabelWidget* Screen_Main_LabelWidget_Deg;
leLabelWidget* Screen_Main_LabelWidget_SelectedReg;
leLabelWidget* Screen_Main_LabelWidget_Brightness;
leButtonWidget* Screen_Main_ButtonWidget_Red;
leButtonWidget* Screen_Main_ButtonWidget_Orange;
leButtonWidget* Screen_Main_ButtonWidget_Yellow;
leButtonWidget* Screen_Main_ButtonWidget_Green;
leButtonWidget* Screen_Main_ButtonWidget_Cyan;
leButtonWidget* Screen_Main_ButtonWidget_Purple;
leButtonWidget* Screen_Main_ButtonWidget_Pink;
leButtonWidget* Screen_Main_ButtonWidget_Radial;
leWidget* Screen_Main_PanelWidget_BrgGen;
leWidget* Screen_Main_PanelWidget_BrgLight;
leWidget* Screen_Main_PanelWidget_BrgDark;
leButtonWidget* Screen_Main_ButtonWidget_Brg;
leButtonWidget* Screen_Main_ButtonWidget_JetDec;
leButtonWidget* Screen_Main_ButtonWidget_JetInc;
leImageWidget* Screen_Main_ImageWidget_bubbles;
leLabelWidget* Screen_Main_LabelWidget_BubbleLevel;
leWidget* Screen_Main_PanelWidget_Bkg;
leImageWidget* Screen_Main_ImageWidget_SongCover;
leLabelWidget* Screen_Main_LabelWidget_SongTitle;
leLabelWidget* Screen_Main_LabelWidget_ArtistName;
leWidget* Screen_Main_PanelWidget_4;
leButtonWidget* Screen_Main_ButtonWidget_Prev;
leButtonWidget* Screen_Main_ButtonWidget_PlayPause;
leButtonWidget* Screen_Main_ButtonWidget_Next;
leImageWidget* Screen_Main_ImageWidget_Volume;
leWidget* Screen_Main_PanelWidget_Vol;
leWidget* Screen_Main_PanelWidget_VolLight;
leWidget* Screen_Main_PanelWidget_VolDark;
leImageWidget* Screen_Main_MicrochipLogo;
leImageWidget* Screen_Main_MGSLogo;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_Screen_Main(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_Screen_Main(void)
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

    Screen_Main_BackgroundPanel = leWidget_New();
    Screen_Main_BackgroundPanel->fn->setPosition(Screen_Main_BackgroundPanel, 0, 0);
    Screen_Main_BackgroundPanel->fn->setSize(Screen_Main_BackgroundPanel, 1024, 600);
    Screen_Main_BackgroundPanel->fn->setScheme(Screen_Main_BackgroundPanel, &BkgScheme);
    root0->fn->addChild(root0, (leWidget*)Screen_Main_BackgroundPanel);

    Screen_Main_ButtonWidget_Settings = leButtonWidget_New();
    Screen_Main_ButtonWidget_Settings->fn->setPosition(Screen_Main_ButtonWidget_Settings, 105, 72);
    Screen_Main_ButtonWidget_Settings->fn->setSize(Screen_Main_ButtonWidget_Settings, 135, 80);
    Screen_Main_ButtonWidget_Settings->fn->setScheme(Screen_Main_ButtonWidget_Settings, &Scheme_Light);
    Screen_Main_ButtonWidget_Settings->fn->setBorderType(Screen_Main_ButtonWidget_Settings, LE_WIDGET_BORDER_NONE);
    Screen_Main_ButtonWidget_Settings->fn->setPressedImage(Screen_Main_ButtonWidget_Settings, (leImage*)&settings);
    Screen_Main_ButtonWidget_Settings->fn->setReleasedImage(Screen_Main_ButtonWidget_Settings, (leImage*)&settings);
    Screen_Main_ButtonWidget_Settings->fn->setReleasedEventCallback(Screen_Main_ButtonWidget_Settings, event_Screen_Main_ButtonWidget_Settings_OnReleased);
    root0->fn->addChild(root0, (leWidget*)Screen_Main_ButtonWidget_Settings);

    Screen_Main_ButtonWidget_WaterQ = leButtonWidget_New();
    Screen_Main_ButtonWidget_WaterQ->fn->setPosition(Screen_Main_ButtonWidget_WaterQ, 248, 72);
    Screen_Main_ButtonWidget_WaterQ->fn->setSize(Screen_Main_ButtonWidget_WaterQ, 135, 80);
    Screen_Main_ButtonWidget_WaterQ->fn->setScheme(Screen_Main_ButtonWidget_WaterQ, &Scheme_Light);
    Screen_Main_ButtonWidget_WaterQ->fn->setBorderType(Screen_Main_ButtonWidget_WaterQ, LE_WIDGET_BORDER_NONE);
    Screen_Main_ButtonWidget_WaterQ->fn->setPressedImage(Screen_Main_ButtonWidget_WaterQ, (leImage*)&water_drop);
    Screen_Main_ButtonWidget_WaterQ->fn->setReleasedImage(Screen_Main_ButtonWidget_WaterQ, (leImage*)&water_drop);
    Screen_Main_ButtonWidget_WaterQ->fn->setReleasedEventCallback(Screen_Main_ButtonWidget_WaterQ, event_Screen_Main_ButtonWidget_WaterQ_OnReleased);
    root0->fn->addChild(root0, (leWidget*)Screen_Main_ButtonWidget_WaterQ);

    Screen_Main_LabelWidget_SelectReg = leLabelWidget_New();
    Screen_Main_LabelWidget_SelectReg->fn->setPosition(Screen_Main_LabelWidget_SelectReg, 140, 176);
    Screen_Main_LabelWidget_SelectReg->fn->setSize(Screen_Main_LabelWidget_SelectReg, 223, 24);
    Screen_Main_LabelWidget_SelectReg->fn->setScheme(Screen_Main_LabelWidget_SelectReg, &Scheme_Light);
    Screen_Main_LabelWidget_SelectReg->fn->setBackgroundType(Screen_Main_LabelWidget_SelectReg, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_LabelWidget_SelectReg->fn->setMargins(Screen_Main_LabelWidget_SelectReg, 0, 0, 0, 0);
    Screen_Main_LabelWidget_SelectReg->fn->setString(Screen_Main_LabelWidget_SelectReg, (leString*)&string_SelectRegion);
    root0->fn->addChild(root0, (leWidget*)Screen_Main_LabelWidget_SelectReg);

    Screen_Main_LabelWidget_ControlDisp = leLabelWidget_New();
    Screen_Main_LabelWidget_ControlDisp->fn->setPosition(Screen_Main_LabelWidget_ControlDisp, 190, 494);
    Screen_Main_LabelWidget_ControlDisp->fn->setSize(Screen_Main_LabelWidget_ControlDisp, 124, 24);
    Screen_Main_LabelWidget_ControlDisp->fn->setScheme(Screen_Main_LabelWidget_ControlDisp, &Scheme_Light);
    Screen_Main_LabelWidget_ControlDisp->fn->setBackgroundType(Screen_Main_LabelWidget_ControlDisp, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_LabelWidget_ControlDisp->fn->setMargins(Screen_Main_LabelWidget_ControlDisp, 0, 0, 0, 0);
    Screen_Main_LabelWidget_ControlDisp->fn->setString(Screen_Main_LabelWidget_ControlDisp, (leString*)&string_ControlDisplay);
    root0->fn->addChild(root0, (leWidget*)Screen_Main_LabelWidget_ControlDisp);

    Screen_Main_ImageWidget_Regions = leImageWidget_New();
    Screen_Main_ImageWidget_Regions->fn->setPosition(Screen_Main_ImageWidget_Regions, 113, 210);
    Screen_Main_ImageWidget_Regions->fn->setSize(Screen_Main_ImageWidget_Regions, 269, 268);
    Screen_Main_ImageWidget_Regions->fn->setBackgroundType(Screen_Main_ImageWidget_Regions, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_ImageWidget_Regions->fn->setBorderType(Screen_Main_ImageWidget_Regions, LE_WIDGET_BORDER_NONE);
    Screen_Main_ImageWidget_Regions->fn->setImage(Screen_Main_ImageWidget_Regions, (leImage*)&all_reg);
    root0->fn->addChild(root0, (leWidget*)Screen_Main_ImageWidget_Regions);

    Screen_Main_ButtonWidget_Reg2 = leButtonWidget_New();
    Screen_Main_ButtonWidget_Reg2->fn->setPosition(Screen_Main_ButtonWidget_Reg2, 249, 220);
    Screen_Main_ButtonWidget_Reg2->fn->setSize(Screen_Main_ButtonWidget_Reg2, 120, 122);
    Screen_Main_ButtonWidget_Reg2->fn->setBackgroundType(Screen_Main_ButtonWidget_Reg2, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_ButtonWidget_Reg2->fn->setBorderType(Screen_Main_ButtonWidget_Reg2, LE_WIDGET_BORDER_NONE);
    Screen_Main_ButtonWidget_Reg2->fn->setReleasedEventCallback(Screen_Main_ButtonWidget_Reg2, event_Screen_Main_ButtonWidget_Reg2_OnReleased);
    root0->fn->addChild(root0, (leWidget*)Screen_Main_ButtonWidget_Reg2);

    Screen_Main_ButtonWidget_Reg1 = leButtonWidget_New();
    Screen_Main_ButtonWidget_Reg1->fn->setPosition(Screen_Main_ButtonWidget_Reg1, 125, 220);
    Screen_Main_ButtonWidget_Reg1->fn->setSize(Screen_Main_ButtonWidget_Reg1, 120, 122);
    Screen_Main_ButtonWidget_Reg1->fn->setBackgroundType(Screen_Main_ButtonWidget_Reg1, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_ButtonWidget_Reg1->fn->setBorderType(Screen_Main_ButtonWidget_Reg1, LE_WIDGET_BORDER_NONE);
    Screen_Main_ButtonWidget_Reg1->fn->setReleasedEventCallback(Screen_Main_ButtonWidget_Reg1, event_Screen_Main_ButtonWidget_Reg1_OnReleased);
    root0->fn->addChild(root0, (leWidget*)Screen_Main_ButtonWidget_Reg1);

    Screen_Main_ButtonWidget_Reg3 = leButtonWidget_New();
    Screen_Main_ButtonWidget_Reg3->fn->setPosition(Screen_Main_ButtonWidget_Reg3, 125, 344);
    Screen_Main_ButtonWidget_Reg3->fn->setSize(Screen_Main_ButtonWidget_Reg3, 120, 122);
    Screen_Main_ButtonWidget_Reg3->fn->setBackgroundType(Screen_Main_ButtonWidget_Reg3, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_ButtonWidget_Reg3->fn->setBorderType(Screen_Main_ButtonWidget_Reg3, LE_WIDGET_BORDER_NONE);
    Screen_Main_ButtonWidget_Reg3->fn->setReleasedEventCallback(Screen_Main_ButtonWidget_Reg3, event_Screen_Main_ButtonWidget_Reg3_OnReleased);
    root0->fn->addChild(root0, (leWidget*)Screen_Main_ButtonWidget_Reg3);

    Screen_Main_ButtonWidget_Reg4 = leButtonWidget_New();
    Screen_Main_ButtonWidget_Reg4->fn->setPosition(Screen_Main_ButtonWidget_Reg4, 249, 344);
    Screen_Main_ButtonWidget_Reg4->fn->setSize(Screen_Main_ButtonWidget_Reg4, 120, 122);
    Screen_Main_ButtonWidget_Reg4->fn->setBackgroundType(Screen_Main_ButtonWidget_Reg4, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_ButtonWidget_Reg4->fn->setBorderType(Screen_Main_ButtonWidget_Reg4, LE_WIDGET_BORDER_NONE);
    Screen_Main_ButtonWidget_Reg4->fn->setReleasedEventCallback(Screen_Main_ButtonWidget_Reg4, event_Screen_Main_ButtonWidget_Reg4_OnReleased);
    root0->fn->addChild(root0, (leWidget*)Screen_Main_ButtonWidget_Reg4);

    Screen_Main_EditPanelWidget = leWidget_New();
    Screen_Main_EditPanelWidget->fn->setPosition(Screen_Main_EditPanelWidget, 510, 65);
    Screen_Main_EditPanelWidget->fn->setSize(Screen_Main_EditPanelWidget, 483, 480);
    Screen_Main_EditPanelWidget->fn->setScheme(Screen_Main_EditPanelWidget, &EditPanel);
    root0->fn->addChild(root0, (leWidget*)Screen_Main_EditPanelWidget);

    Screen_Main_PanelWidget_WaterTemp = leWidget_New();
    Screen_Main_PanelWidget_WaterTemp->fn->setPosition(Screen_Main_PanelWidget_WaterTemp, 32, 6);
    Screen_Main_PanelWidget_WaterTemp->fn->setSize(Screen_Main_PanelWidget_WaterTemp, 415, 195);
    Screen_Main_PanelWidget_WaterTemp->fn->setBackgroundType(Screen_Main_PanelWidget_WaterTemp, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_EditPanelWidget->fn->addChild(Screen_Main_EditPanelWidget, (leWidget*)Screen_Main_PanelWidget_WaterTemp);

    Screen_Main_LabelWidget_WaterTemp = leLabelWidget_New();
    Screen_Main_LabelWidget_WaterTemp->fn->setPosition(Screen_Main_LabelWidget_WaterTemp, 112, 51);
    Screen_Main_LabelWidget_WaterTemp->fn->setSize(Screen_Main_LabelWidget_WaterTemp, 186, 27);
    Screen_Main_LabelWidget_WaterTemp->fn->setScheme(Screen_Main_LabelWidget_WaterTemp, &Scheme_Light);
    Screen_Main_LabelWidget_WaterTemp->fn->setBackgroundType(Screen_Main_LabelWidget_WaterTemp, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_LabelWidget_WaterTemp->fn->setHAlignment(Screen_Main_LabelWidget_WaterTemp, LE_HALIGN_CENTER);
    Screen_Main_LabelWidget_WaterTemp->fn->setVAlignment(Screen_Main_LabelWidget_WaterTemp, LE_VALIGN_TOP);
    Screen_Main_LabelWidget_WaterTemp->fn->setMargins(Screen_Main_LabelWidget_WaterTemp, 0, 0, 0, 0);
    Screen_Main_LabelWidget_WaterTemp->fn->setString(Screen_Main_LabelWidget_WaterTemp, (leString*)&string_WaterTemp);
    Screen_Main_PanelWidget_WaterTemp->fn->addChild(Screen_Main_PanelWidget_WaterTemp, (leWidget*)Screen_Main_LabelWidget_WaterTemp);

    Screen_Main_ButtonWidget_IncTemp = leButtonWidget_New();
    Screen_Main_ButtonWidget_IncTemp->fn->setPosition(Screen_Main_ButtonWidget_IncTemp, 298, 81);
    Screen_Main_ButtonWidget_IncTemp->fn->setSize(Screen_Main_ButtonWidget_IncTemp, 88, 96);
    Screen_Main_ButtonWidget_IncTemp->fn->setScheme(Screen_Main_ButtonWidget_IncTemp, &Scheme_Light);
    Screen_Main_ButtonWidget_IncTemp->fn->setBorderType(Screen_Main_ButtonWidget_IncTemp, LE_WIDGET_BORDER_NONE);
    Screen_Main_ButtonWidget_IncTemp->fn->setPressedImage(Screen_Main_ButtonWidget_IncTemp, (leImage*)&chevron_right15x24);
    Screen_Main_ButtonWidget_IncTemp->fn->setReleasedImage(Screen_Main_ButtonWidget_IncTemp, (leImage*)&chevron_right15x24);
    Screen_Main_ButtonWidget_IncTemp->fn->setPressedEventCallback(Screen_Main_ButtonWidget_IncTemp, event_Screen_Main_ButtonWidget_IncTemp_OnPressed);
    Screen_Main_ButtonWidget_IncTemp->fn->setReleasedEventCallback(Screen_Main_ButtonWidget_IncTemp, event_Screen_Main_ButtonWidget_IncTemp_OnReleased);
    Screen_Main_PanelWidget_WaterTemp->fn->addChild(Screen_Main_PanelWidget_WaterTemp, (leWidget*)Screen_Main_ButtonWidget_IncTemp);

    Screen_Main_ButtonWidget_DecTemp = leButtonWidget_New();
    Screen_Main_ButtonWidget_DecTemp->fn->setPosition(Screen_Main_ButtonWidget_DecTemp, 24, 81);
    Screen_Main_ButtonWidget_DecTemp->fn->setSize(Screen_Main_ButtonWidget_DecTemp, 88, 96);
    Screen_Main_ButtonWidget_DecTemp->fn->setScheme(Screen_Main_ButtonWidget_DecTemp, &Scheme_Light);
    Screen_Main_ButtonWidget_DecTemp->fn->setBorderType(Screen_Main_ButtonWidget_DecTemp, LE_WIDGET_BORDER_NONE);
    Screen_Main_ButtonWidget_DecTemp->fn->setPressedImage(Screen_Main_ButtonWidget_DecTemp, (leImage*)&chevron_left15x24);
    Screen_Main_ButtonWidget_DecTemp->fn->setReleasedImage(Screen_Main_ButtonWidget_DecTemp, (leImage*)&chevron_left15x24);
    Screen_Main_ButtonWidget_DecTemp->fn->setPressedEventCallback(Screen_Main_ButtonWidget_DecTemp, event_Screen_Main_ButtonWidget_DecTemp_OnPressed);
    Screen_Main_ButtonWidget_DecTemp->fn->setReleasedEventCallback(Screen_Main_ButtonWidget_DecTemp, event_Screen_Main_ButtonWidget_DecTemp_OnReleased);
    Screen_Main_PanelWidget_WaterTemp->fn->addChild(Screen_Main_PanelWidget_WaterTemp, (leWidget*)Screen_Main_ButtonWidget_DecTemp);

    Screen_Main_LabelWidget_Deg = leLabelWidget_New();
    Screen_Main_LabelWidget_Deg->fn->setPosition(Screen_Main_LabelWidget_Deg, 117, 82);
    Screen_Main_LabelWidget_Deg->fn->setSize(Screen_Main_LabelWidget_Deg, 186, 100);
    Screen_Main_LabelWidget_Deg->fn->setScheme(Screen_Main_LabelWidget_Deg, &Scheme_Light);
    Screen_Main_LabelWidget_Deg->fn->setBackgroundType(Screen_Main_LabelWidget_Deg, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_LabelWidget_Deg->fn->setHAlignment(Screen_Main_LabelWidget_Deg, LE_HALIGN_CENTER);
    Screen_Main_LabelWidget_Deg->fn->setMargins(Screen_Main_LabelWidget_Deg, 0, 0, 0, 0);
    Screen_Main_LabelWidget_Deg->fn->setString(Screen_Main_LabelWidget_Deg, (leString*)&string_DegreesValue);
    Screen_Main_PanelWidget_WaterTemp->fn->addChild(Screen_Main_PanelWidget_WaterTemp, (leWidget*)Screen_Main_LabelWidget_Deg);

    Screen_Main_LabelWidget_SelectedReg = leLabelWidget_New();
    Screen_Main_LabelWidget_SelectedReg->fn->setPosition(Screen_Main_LabelWidget_SelectedReg, 112, 4);
    Screen_Main_LabelWidget_SelectedReg->fn->setSize(Screen_Main_LabelWidget_SelectedReg, 192, 43);
    Screen_Main_LabelWidget_SelectedReg->fn->setScheme(Screen_Main_LabelWidget_SelectedReg, &Scheme_Light);
    Screen_Main_LabelWidget_SelectedReg->fn->setBackgroundType(Screen_Main_LabelWidget_SelectedReg, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_LabelWidget_SelectedReg->fn->setHAlignment(Screen_Main_LabelWidget_SelectedReg, LE_HALIGN_CENTER);
    Screen_Main_LabelWidget_SelectedReg->fn->setVAlignment(Screen_Main_LabelWidget_SelectedReg, LE_VALIGN_TOP);
    Screen_Main_LabelWidget_SelectedReg->fn->setMargins(Screen_Main_LabelWidget_SelectedReg, 0, 0, 0, 0);
    Screen_Main_LabelWidget_SelectedReg->fn->setString(Screen_Main_LabelWidget_SelectedReg, (leString*)&string_AllRegions);
    Screen_Main_PanelWidget_WaterTemp->fn->addChild(Screen_Main_PanelWidget_WaterTemp, (leWidget*)Screen_Main_LabelWidget_SelectedReg);

    Screen_Main_PanelWidget_SelColors = leWidget_New();
    Screen_Main_PanelWidget_SelColors->fn->setPosition(Screen_Main_PanelWidget_SelColors, 56, 207);
    Screen_Main_PanelWidget_SelColors->fn->setSize(Screen_Main_PanelWidget_SelColors, 386, 72);
    Screen_Main_PanelWidget_SelColors->fn->setBackgroundType(Screen_Main_PanelWidget_SelColors, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_PanelWidget_SelColors->fn->setMargins(Screen_Main_PanelWidget_SelColors, 0, 0, 0, 0);
    Screen_Main_EditPanelWidget->fn->addChild(Screen_Main_EditPanelWidget, (leWidget*)Screen_Main_PanelWidget_SelColors);

    Screen_Main_LabelWidget_Brightness = leLabelWidget_New();
    Screen_Main_LabelWidget_Brightness->fn->setPosition(Screen_Main_LabelWidget_Brightness, 1, 48);
    Screen_Main_LabelWidget_Brightness->fn->setScheme(Screen_Main_LabelWidget_Brightness, &Scheme_Light);
    Screen_Main_LabelWidget_Brightness->fn->setBackgroundType(Screen_Main_LabelWidget_Brightness, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_LabelWidget_Brightness->fn->setVAlignment(Screen_Main_LabelWidget_Brightness, LE_VALIGN_TOP);
    Screen_Main_LabelWidget_Brightness->fn->setMargins(Screen_Main_LabelWidget_Brightness, 0, 0, 0, 0);
    Screen_Main_LabelWidget_Brightness->fn->setString(Screen_Main_LabelWidget_Brightness, (leString*)&string_Brightness);
    Screen_Main_PanelWidget_SelColors->fn->addChild(Screen_Main_PanelWidget_SelColors, (leWidget*)Screen_Main_LabelWidget_Brightness);

    Screen_Main_ButtonWidget_Red = leButtonWidget_New();
    Screen_Main_ButtonWidget_Red->fn->setPosition(Screen_Main_ButtonWidget_Red, 0, 0);
    Screen_Main_ButtonWidget_Red->fn->setSize(Screen_Main_ButtonWidget_Red, 32, 32);
    Screen_Main_ButtonWidget_Red->fn->setBackgroundType(Screen_Main_ButtonWidget_Red, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_ButtonWidget_Red->fn->setBorderType(Screen_Main_ButtonWidget_Red, LE_WIDGET_BORDER_NONE);
    Screen_Main_ButtonWidget_Red->fn->setToggleable(Screen_Main_ButtonWidget_Red, LE_TRUE);
    Screen_Main_ButtonWidget_Red->fn->setPressedImage(Screen_Main_ButtonWidget_Red, (leImage*)&Color_EF8F8F_sel);
    Screen_Main_ButtonWidget_Red->fn->setReleasedImage(Screen_Main_ButtonWidget_Red, (leImage*)&Color_EF8F8F);
    Screen_Main_ButtonWidget_Red->fn->setPressedOffset(Screen_Main_ButtonWidget_Red, 0);
    Screen_Main_ButtonWidget_Red->fn->setPressedEventCallback(Screen_Main_ButtonWidget_Red, event_Screen_Main_ButtonWidget_Red_OnPressed);
    Screen_Main_PanelWidget_SelColors->fn->addChild(Screen_Main_PanelWidget_SelColors, (leWidget*)Screen_Main_ButtonWidget_Red);

    Screen_Main_ButtonWidget_Orange = leButtonWidget_New();
    Screen_Main_ButtonWidget_Orange->fn->setPosition(Screen_Main_ButtonWidget_Orange, 48, 0);
    Screen_Main_ButtonWidget_Orange->fn->setSize(Screen_Main_ButtonWidget_Orange, 32, 32);
    Screen_Main_ButtonWidget_Orange->fn->setBackgroundType(Screen_Main_ButtonWidget_Orange, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_ButtonWidget_Orange->fn->setBorderType(Screen_Main_ButtonWidget_Orange, LE_WIDGET_BORDER_NONE);
    Screen_Main_ButtonWidget_Orange->fn->setToggleable(Screen_Main_ButtonWidget_Orange, LE_TRUE);
    Screen_Main_ButtonWidget_Orange->fn->setPressedImage(Screen_Main_ButtonWidget_Orange, (leImage*)&Color_EFB88F_sel);
    Screen_Main_ButtonWidget_Orange->fn->setReleasedImage(Screen_Main_ButtonWidget_Orange, (leImage*)&Color_EFB88F);
    Screen_Main_ButtonWidget_Orange->fn->setPressedOffset(Screen_Main_ButtonWidget_Orange, 0);
    Screen_Main_ButtonWidget_Orange->fn->setPressedEventCallback(Screen_Main_ButtonWidget_Orange, event_Screen_Main_ButtonWidget_Orange_OnPressed);
    Screen_Main_PanelWidget_SelColors->fn->addChild(Screen_Main_PanelWidget_SelColors, (leWidget*)Screen_Main_ButtonWidget_Orange);

    Screen_Main_ButtonWidget_Yellow = leButtonWidget_New();
    Screen_Main_ButtonWidget_Yellow->fn->setPosition(Screen_Main_ButtonWidget_Yellow, 96, 0);
    Screen_Main_ButtonWidget_Yellow->fn->setSize(Screen_Main_ButtonWidget_Yellow, 32, 32);
    Screen_Main_ButtonWidget_Yellow->fn->setBackgroundType(Screen_Main_ButtonWidget_Yellow, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_ButtonWidget_Yellow->fn->setBorderType(Screen_Main_ButtonWidget_Yellow, LE_WIDGET_BORDER_NONE);
    Screen_Main_ButtonWidget_Yellow->fn->setToggleable(Screen_Main_ButtonWidget_Yellow, LE_TRUE);
    Screen_Main_ButtonWidget_Yellow->fn->setPressedImage(Screen_Main_ButtonWidget_Yellow, (leImage*)&Color_EFEB8F_sel);
    Screen_Main_ButtonWidget_Yellow->fn->setReleasedImage(Screen_Main_ButtonWidget_Yellow, (leImage*)&Color_EFEB8F);
    Screen_Main_ButtonWidget_Yellow->fn->setPressedOffset(Screen_Main_ButtonWidget_Yellow, 0);
    Screen_Main_ButtonWidget_Yellow->fn->setPressedEventCallback(Screen_Main_ButtonWidget_Yellow, event_Screen_Main_ButtonWidget_Yellow_OnPressed);
    Screen_Main_PanelWidget_SelColors->fn->addChild(Screen_Main_PanelWidget_SelColors, (leWidget*)Screen_Main_ButtonWidget_Yellow);

    Screen_Main_ButtonWidget_Green = leButtonWidget_New();
    Screen_Main_ButtonWidget_Green->fn->setPosition(Screen_Main_ButtonWidget_Green, 144, 0);
    Screen_Main_ButtonWidget_Green->fn->setSize(Screen_Main_ButtonWidget_Green, 32, 32);
    Screen_Main_ButtonWidget_Green->fn->setBackgroundType(Screen_Main_ButtonWidget_Green, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_ButtonWidget_Green->fn->setBorderType(Screen_Main_ButtonWidget_Green, LE_WIDGET_BORDER_NONE);
    Screen_Main_ButtonWidget_Green->fn->setToggleable(Screen_Main_ButtonWidget_Green, LE_TRUE);
    Screen_Main_ButtonWidget_Green->fn->setPressedImage(Screen_Main_ButtonWidget_Green, (leImage*)&Color_97EF8F_sel);
    Screen_Main_ButtonWidget_Green->fn->setReleasedImage(Screen_Main_ButtonWidget_Green, (leImage*)&Color_97EF8F);
    Screen_Main_ButtonWidget_Green->fn->setPressedOffset(Screen_Main_ButtonWidget_Green, 0);
    Screen_Main_ButtonWidget_Green->fn->setPressedEventCallback(Screen_Main_ButtonWidget_Green, event_Screen_Main_ButtonWidget_Green_OnPressed);
    Screen_Main_PanelWidget_SelColors->fn->addChild(Screen_Main_PanelWidget_SelColors, (leWidget*)Screen_Main_ButtonWidget_Green);

    Screen_Main_ButtonWidget_Cyan = leButtonWidget_New();
    Screen_Main_ButtonWidget_Cyan->fn->setPosition(Screen_Main_ButtonWidget_Cyan, 192, 0);
    Screen_Main_ButtonWidget_Cyan->fn->setSize(Screen_Main_ButtonWidget_Cyan, 32, 32);
    Screen_Main_ButtonWidget_Cyan->fn->setBackgroundType(Screen_Main_ButtonWidget_Cyan, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_ButtonWidget_Cyan->fn->setBorderType(Screen_Main_ButtonWidget_Cyan, LE_WIDGET_BORDER_NONE);
    Screen_Main_ButtonWidget_Cyan->fn->setToggleable(Screen_Main_ButtonWidget_Cyan, LE_TRUE);
    Screen_Main_ButtonWidget_Cyan->fn->setPressedImage(Screen_Main_ButtonWidget_Cyan, (leImage*)&Color_8FEFDE_sel);
    Screen_Main_ButtonWidget_Cyan->fn->setReleasedImage(Screen_Main_ButtonWidget_Cyan, (leImage*)&Color_8FEFDE);
    Screen_Main_ButtonWidget_Cyan->fn->setPressedOffset(Screen_Main_ButtonWidget_Cyan, 0);
    Screen_Main_ButtonWidget_Cyan->fn->setPressedEventCallback(Screen_Main_ButtonWidget_Cyan, event_Screen_Main_ButtonWidget_Cyan_OnPressed);
    Screen_Main_PanelWidget_SelColors->fn->addChild(Screen_Main_PanelWidget_SelColors, (leWidget*)Screen_Main_ButtonWidget_Cyan);

    Screen_Main_ButtonWidget_Purple = leButtonWidget_New();
    Screen_Main_ButtonWidget_Purple->fn->setPosition(Screen_Main_ButtonWidget_Purple, 240, 0);
    Screen_Main_ButtonWidget_Purple->fn->setSize(Screen_Main_ButtonWidget_Purple, 32, 32);
    Screen_Main_ButtonWidget_Purple->fn->setBackgroundType(Screen_Main_ButtonWidget_Purple, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_ButtonWidget_Purple->fn->setBorderType(Screen_Main_ButtonWidget_Purple, LE_WIDGET_BORDER_NONE);
    Screen_Main_ButtonWidget_Purple->fn->setMargins(Screen_Main_ButtonWidget_Purple, 0, 0, 0, 0);
    Screen_Main_ButtonWidget_Purple->fn->setToggleable(Screen_Main_ButtonWidget_Purple, LE_TRUE);
    Screen_Main_ButtonWidget_Purple->fn->setPressedImage(Screen_Main_ButtonWidget_Purple, (leImage*)&Color_8F93EF_sel);
    Screen_Main_ButtonWidget_Purple->fn->setReleasedImage(Screen_Main_ButtonWidget_Purple, (leImage*)&Color_8F93EF);
    Screen_Main_ButtonWidget_Purple->fn->setPressedOffset(Screen_Main_ButtonWidget_Purple, 0);
    Screen_Main_ButtonWidget_Purple->fn->setPressedEventCallback(Screen_Main_ButtonWidget_Purple, event_Screen_Main_ButtonWidget_Purple_OnPressed);
    Screen_Main_PanelWidget_SelColors->fn->addChild(Screen_Main_PanelWidget_SelColors, (leWidget*)Screen_Main_ButtonWidget_Purple);

    Screen_Main_ButtonWidget_Pink = leButtonWidget_New();
    Screen_Main_ButtonWidget_Pink->fn->setPosition(Screen_Main_ButtonWidget_Pink, 288, 0);
    Screen_Main_ButtonWidget_Pink->fn->setSize(Screen_Main_ButtonWidget_Pink, 32, 32);
    Screen_Main_ButtonWidget_Pink->fn->setBackgroundType(Screen_Main_ButtonWidget_Pink, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_ButtonWidget_Pink->fn->setBorderType(Screen_Main_ButtonWidget_Pink, LE_WIDGET_BORDER_NONE);
    Screen_Main_ButtonWidget_Pink->fn->setToggleable(Screen_Main_ButtonWidget_Pink, LE_TRUE);
    Screen_Main_ButtonWidget_Pink->fn->setPressedImage(Screen_Main_ButtonWidget_Pink, (leImage*)&Color_EF8FE6_sel);
    Screen_Main_ButtonWidget_Pink->fn->setReleasedImage(Screen_Main_ButtonWidget_Pink, (leImage*)&Color_EF8FE6);
    Screen_Main_ButtonWidget_Pink->fn->setPressedOffset(Screen_Main_ButtonWidget_Pink, 0);
    Screen_Main_ButtonWidget_Pink->fn->setPressedEventCallback(Screen_Main_ButtonWidget_Pink, event_Screen_Main_ButtonWidget_Pink_OnPressed);
    Screen_Main_PanelWidget_SelColors->fn->addChild(Screen_Main_PanelWidget_SelColors, (leWidget*)Screen_Main_ButtonWidget_Pink);

    Screen_Main_ButtonWidget_Radial = leButtonWidget_New();
    Screen_Main_ButtonWidget_Radial->fn->setPosition(Screen_Main_ButtonWidget_Radial, 336, 0);
    Screen_Main_ButtonWidget_Radial->fn->setSize(Screen_Main_ButtonWidget_Radial, 32, 32);
    Screen_Main_ButtonWidget_Radial->fn->setBackgroundType(Screen_Main_ButtonWidget_Radial, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_ButtonWidget_Radial->fn->setBorderType(Screen_Main_ButtonWidget_Radial, LE_WIDGET_BORDER_NONE);
    Screen_Main_ButtonWidget_Radial->fn->setToggleable(Screen_Main_ButtonWidget_Radial, LE_TRUE);
    Screen_Main_ButtonWidget_Radial->fn->setPressedImage(Screen_Main_ButtonWidget_Radial, (leImage*)&Color_radial_sel);
    Screen_Main_ButtonWidget_Radial->fn->setReleasedImage(Screen_Main_ButtonWidget_Radial, (leImage*)&Color_radial);
    Screen_Main_ButtonWidget_Radial->fn->setPressedOffset(Screen_Main_ButtonWidget_Radial, 0);
    Screen_Main_ButtonWidget_Radial->fn->setPressedEventCallback(Screen_Main_ButtonWidget_Radial, event_Screen_Main_ButtonWidget_Radial_OnPressed);
    Screen_Main_PanelWidget_SelColors->fn->addChild(Screen_Main_PanelWidget_SelColors, (leWidget*)Screen_Main_ButtonWidget_Radial);

    Screen_Main_PanelWidget_BrgGen = leWidget_New();
    Screen_Main_PanelWidget_BrgGen->fn->setPosition(Screen_Main_PanelWidget_BrgGen, 64, 40);
    Screen_Main_PanelWidget_BrgGen->fn->setSize(Screen_Main_PanelWidget_BrgGen, 324, 32);
    Screen_Main_PanelWidget_BrgGen->fn->setBackgroundType(Screen_Main_PanelWidget_BrgGen, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_PanelWidget_SelColors->fn->addChild(Screen_Main_PanelWidget_SelColors, (leWidget*)Screen_Main_PanelWidget_BrgGen);

    Screen_Main_PanelWidget_BrgLight = leWidget_New();
    Screen_Main_PanelWidget_BrgLight->fn->setPosition(Screen_Main_PanelWidget_BrgLight, 8, 14);
    Screen_Main_PanelWidget_BrgLight->fn->setSize(Screen_Main_PanelWidget_BrgLight, 302, 8);
    Screen_Main_PanelWidget_BrgLight->fn->setEnabled(Screen_Main_PanelWidget_BrgLight, LE_FALSE);
    Screen_Main_PanelWidget_BrgLight->fn->setScheme(Screen_Main_PanelWidget_BrgLight, &SliderLightScheme);
    Screen_Main_PanelWidget_BrgGen->fn->addChild(Screen_Main_PanelWidget_BrgGen, (leWidget*)Screen_Main_PanelWidget_BrgLight);

    Screen_Main_PanelWidget_BrgDark = leWidget_New();
    Screen_Main_PanelWidget_BrgDark->fn->setPosition(Screen_Main_PanelWidget_BrgDark, 8, 14);
    Screen_Main_PanelWidget_BrgDark->fn->setSize(Screen_Main_PanelWidget_BrgDark, 148, 8);
    Screen_Main_PanelWidget_BrgDark->fn->setEnabled(Screen_Main_PanelWidget_BrgDark, LE_FALSE);
    Screen_Main_PanelWidget_BrgDark->fn->setScheme(Screen_Main_PanelWidget_BrgDark, &SliderDarkScheme);
    Screen_Main_PanelWidget_BrgGen->fn->addChild(Screen_Main_PanelWidget_BrgGen, (leWidget*)Screen_Main_PanelWidget_BrgDark);

    Screen_Main_ButtonWidget_Brg = leButtonWidget_New();
    Screen_Main_ButtonWidget_Brg->fn->setPosition(Screen_Main_ButtonWidget_Brg, 148, 9);
    Screen_Main_ButtonWidget_Brg->fn->setSize(Screen_Main_ButtonWidget_Brg, 16, 16);
    Screen_Main_ButtonWidget_Brg->fn->setEnabled(Screen_Main_ButtonWidget_Brg, LE_FALSE);
    Screen_Main_ButtonWidget_Brg->fn->setBackgroundType(Screen_Main_ButtonWidget_Brg, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_ButtonWidget_Brg->fn->setBorderType(Screen_Main_ButtonWidget_Brg, LE_WIDGET_BORDER_NONE);
    Screen_Main_ButtonWidget_Brg->fn->setPressedImage(Screen_Main_ButtonWidget_Brg, (leImage*)&brg_btn);
    Screen_Main_ButtonWidget_Brg->fn->setReleasedImage(Screen_Main_ButtonWidget_Brg, (leImage*)&brg_btn);
    Screen_Main_PanelWidget_BrgGen->fn->addChild(Screen_Main_PanelWidget_BrgGen, (leWidget*)Screen_Main_ButtonWidget_Brg);

    Screen_Main_PanelWidget_JetCtrl = leWidget_New();
    Screen_Main_PanelWidget_JetCtrl->fn->setPosition(Screen_Main_PanelWidget_JetCtrl, 150, 296);
    Screen_Main_PanelWidget_JetCtrl->fn->setSize(Screen_Main_PanelWidget_JetCtrl, 184, 40);
    Screen_Main_PanelWidget_JetCtrl->fn->setBackgroundType(Screen_Main_PanelWidget_JetCtrl, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_PanelWidget_JetCtrl->fn->setMargins(Screen_Main_PanelWidget_JetCtrl, 0, 0, 0, 0);
    Screen_Main_EditPanelWidget->fn->addChild(Screen_Main_EditPanelWidget, (leWidget*)Screen_Main_PanelWidget_JetCtrl);

    Screen_Main_ButtonWidget_JetDec = leButtonWidget_New();
    Screen_Main_ButtonWidget_JetDec->fn->setPosition(Screen_Main_ButtonWidget_JetDec, 0, 0);
    Screen_Main_ButtonWidget_JetDec->fn->setSize(Screen_Main_ButtonWidget_JetDec, 40, 40);
    Screen_Main_ButtonWidget_JetDec->fn->setScheme(Screen_Main_ButtonWidget_JetDec, &Scheme_Light);
    Screen_Main_ButtonWidget_JetDec->fn->setBorderType(Screen_Main_ButtonWidget_JetDec, LE_WIDGET_BORDER_NONE);
    Screen_Main_ButtonWidget_JetDec->fn->setPressedImage(Screen_Main_ButtonWidget_JetDec, (leImage*)&chevron_left11x16);
    Screen_Main_ButtonWidget_JetDec->fn->setReleasedImage(Screen_Main_ButtonWidget_JetDec, (leImage*)&chevron_left11x16);
    Screen_Main_ButtonWidget_JetDec->fn->setPressedEventCallback(Screen_Main_ButtonWidget_JetDec, event_Screen_Main_ButtonWidget_JetDec_OnPressed);
    Screen_Main_ButtonWidget_JetDec->fn->setReleasedEventCallback(Screen_Main_ButtonWidget_JetDec, event_Screen_Main_ButtonWidget_JetDec_OnReleased);
    Screen_Main_PanelWidget_JetCtrl->fn->addChild(Screen_Main_PanelWidget_JetCtrl, (leWidget*)Screen_Main_ButtonWidget_JetDec);

    Screen_Main_ButtonWidget_JetInc = leButtonWidget_New();
    Screen_Main_ButtonWidget_JetInc->fn->setPosition(Screen_Main_ButtonWidget_JetInc, 144, 0);
    Screen_Main_ButtonWidget_JetInc->fn->setSize(Screen_Main_ButtonWidget_JetInc, 40, 40);
    Screen_Main_ButtonWidget_JetInc->fn->setScheme(Screen_Main_ButtonWidget_JetInc, &Scheme_Light);
    Screen_Main_ButtonWidget_JetInc->fn->setBorderType(Screen_Main_ButtonWidget_JetInc, LE_WIDGET_BORDER_NONE);
    Screen_Main_ButtonWidget_JetInc->fn->setPressedImage(Screen_Main_ButtonWidget_JetInc, (leImage*)&chevron_right11x16);
    Screen_Main_ButtonWidget_JetInc->fn->setReleasedImage(Screen_Main_ButtonWidget_JetInc, (leImage*)&chevron_right11x16);
    Screen_Main_ButtonWidget_JetInc->fn->setPressedEventCallback(Screen_Main_ButtonWidget_JetInc, event_Screen_Main_ButtonWidget_JetInc_OnPressed);
    Screen_Main_ButtonWidget_JetInc->fn->setReleasedEventCallback(Screen_Main_ButtonWidget_JetInc, event_Screen_Main_ButtonWidget_JetInc_OnReleased);
    Screen_Main_PanelWidget_JetCtrl->fn->addChild(Screen_Main_PanelWidget_JetCtrl, (leWidget*)Screen_Main_ButtonWidget_JetInc);

    Screen_Main_ImageWidget_bubbles = leImageWidget_New();
    Screen_Main_ImageWidget_bubbles->fn->setPosition(Screen_Main_ImageWidget_bubbles, 56, 0);
    Screen_Main_ImageWidget_bubbles->fn->setSize(Screen_Main_ImageWidget_bubbles, 40, 40);
    Screen_Main_ImageWidget_bubbles->fn->setBackgroundType(Screen_Main_ImageWidget_bubbles, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_ImageWidget_bubbles->fn->setBorderType(Screen_Main_ImageWidget_bubbles, LE_WIDGET_BORDER_NONE);
    Screen_Main_ImageWidget_bubbles->fn->setMargins(Screen_Main_ImageWidget_bubbles, 0, 0, 0, 0);
    Screen_Main_ImageWidget_bubbles->fn->setImage(Screen_Main_ImageWidget_bubbles, (leImage*)&bubble_chart_40x40);
    Screen_Main_PanelWidget_JetCtrl->fn->addChild(Screen_Main_PanelWidget_JetCtrl, (leWidget*)Screen_Main_ImageWidget_bubbles);

    Screen_Main_LabelWidget_BubbleLevel = leLabelWidget_New();
    Screen_Main_LabelWidget_BubbleLevel->fn->setPosition(Screen_Main_LabelWidget_BubbleLevel, 104, 0);
    Screen_Main_LabelWidget_BubbleLevel->fn->setSize(Screen_Main_LabelWidget_BubbleLevel, 40, 40);
    Screen_Main_LabelWidget_BubbleLevel->fn->setScheme(Screen_Main_LabelWidget_BubbleLevel, &Scheme_Light);
    Screen_Main_LabelWidget_BubbleLevel->fn->setBackgroundType(Screen_Main_LabelWidget_BubbleLevel, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_LabelWidget_BubbleLevel->fn->setMargins(Screen_Main_LabelWidget_BubbleLevel, 0, 0, 0, 0);
    Screen_Main_LabelWidget_BubbleLevel->fn->setString(Screen_Main_LabelWidget_BubbleLevel, (leString*)&string_BubbleLevel);
    Screen_Main_PanelWidget_JetCtrl->fn->addChild(Screen_Main_PanelWidget_JetCtrl, (leWidget*)Screen_Main_LabelWidget_BubbleLevel);

    Screen_Main_PanelWidget_MP = leWidget_New();
    Screen_Main_PanelWidget_MP->fn->setPosition(Screen_Main_PanelWidget_MP, 56, 360);
    Screen_Main_PanelWidget_MP->fn->setSize(Screen_Main_PanelWidget_MP, 371, 92);
    Screen_Main_PanelWidget_MP->fn->setBackgroundType(Screen_Main_PanelWidget_MP, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_EditPanelWidget->fn->addChild(Screen_Main_EditPanelWidget, (leWidget*)Screen_Main_PanelWidget_MP);

    Screen_Main_PanelWidget_Bkg = leWidget_New();
    Screen_Main_PanelWidget_Bkg->fn->setPosition(Screen_Main_PanelWidget_Bkg, 1, 0);
    Screen_Main_PanelWidget_Bkg->fn->setSize(Screen_Main_PanelWidget_Bkg, 371, 80);
    Screen_Main_PanelWidget_Bkg->fn->setEnabled(Screen_Main_PanelWidget_Bkg, LE_FALSE);
    Screen_Main_PanelWidget_Bkg->fn->setScheme(Screen_Main_PanelWidget_Bkg, &Scheme_Light);
    Screen_Main_PanelWidget_MP->fn->addChild(Screen_Main_PanelWidget_MP, (leWidget*)Screen_Main_PanelWidget_Bkg);

    Screen_Main_ImageWidget_SongCover = leImageWidget_New();
    Screen_Main_ImageWidget_SongCover->fn->setPosition(Screen_Main_ImageWidget_SongCover, 8, 8);
    Screen_Main_ImageWidget_SongCover->fn->setSize(Screen_Main_ImageWidget_SongCover, 64, 64);
    Screen_Main_ImageWidget_SongCover->fn->setBackgroundType(Screen_Main_ImageWidget_SongCover, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_ImageWidget_SongCover->fn->setBorderType(Screen_Main_ImageWidget_SongCover, LE_WIDGET_BORDER_NONE);
    Screen_Main_ImageWidget_SongCover->fn->setMargins(Screen_Main_ImageWidget_SongCover, 0, 0, 0, 0);
    Screen_Main_ImageWidget_SongCover->fn->setImage(Screen_Main_ImageWidget_SongCover, (leImage*)&Song_Pic_Example);
    Screen_Main_PanelWidget_MP->fn->addChild(Screen_Main_PanelWidget_MP, (leWidget*)Screen_Main_ImageWidget_SongCover);

    Screen_Main_LabelWidget_SongTitle = leLabelWidget_New();
    Screen_Main_LabelWidget_SongTitle->fn->setPosition(Screen_Main_LabelWidget_SongTitle, 88, 24);
    Screen_Main_LabelWidget_SongTitle->fn->setSize(Screen_Main_LabelWidget_SongTitle, 100, 30);
    Screen_Main_LabelWidget_SongTitle->fn->setScheme(Screen_Main_LabelWidget_SongTitle, &Scheme_Light);
    Screen_Main_LabelWidget_SongTitle->fn->setBackgroundType(Screen_Main_LabelWidget_SongTitle, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_LabelWidget_SongTitle->fn->setVAlignment(Screen_Main_LabelWidget_SongTitle, LE_VALIGN_TOP);
    Screen_Main_LabelWidget_SongTitle->fn->setMargins(Screen_Main_LabelWidget_SongTitle, 0, 0, 0, 0);
    Screen_Main_LabelWidget_SongTitle->fn->setString(Screen_Main_LabelWidget_SongTitle, (leString*)&string_SongTitle);
    Screen_Main_PanelWidget_MP->fn->addChild(Screen_Main_PanelWidget_MP, (leWidget*)Screen_Main_LabelWidget_SongTitle);

    Screen_Main_LabelWidget_ArtistName = leLabelWidget_New();
    Screen_Main_LabelWidget_ArtistName->fn->setPosition(Screen_Main_LabelWidget_ArtistName, 88, 47);
    Screen_Main_LabelWidget_ArtistName->fn->setScheme(Screen_Main_LabelWidget_ArtistName, &Scheme_Light);
    Screen_Main_LabelWidget_ArtistName->fn->setBackgroundType(Screen_Main_LabelWidget_ArtistName, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_LabelWidget_ArtistName->fn->setMargins(Screen_Main_LabelWidget_ArtistName, 0, 0, 0, 0);
    Screen_Main_LabelWidget_ArtistName->fn->setString(Screen_Main_LabelWidget_ArtistName, (leString*)&string_ArtistName);
    Screen_Main_PanelWidget_MP->fn->addChild(Screen_Main_PanelWidget_MP, (leWidget*)Screen_Main_LabelWidget_ArtistName);

    Screen_Main_PanelWidget_4 = leWidget_New();
    Screen_Main_PanelWidget_4->fn->setPosition(Screen_Main_PanelWidget_4, 205, 16);
    Screen_Main_PanelWidget_4->fn->setSize(Screen_Main_PanelWidget_4, 146, 80);
    Screen_Main_PanelWidget_4->fn->setBackgroundType(Screen_Main_PanelWidget_4, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_PanelWidget_4->fn->setMargins(Screen_Main_PanelWidget_4, 0, 0, 0, 0);
    Screen_Main_PanelWidget_MP->fn->addChild(Screen_Main_PanelWidget_MP, (leWidget*)Screen_Main_PanelWidget_4);

    Screen_Main_ButtonWidget_Prev = leButtonWidget_New();
    Screen_Main_ButtonWidget_Prev->fn->setPosition(Screen_Main_ButtonWidget_Prev, 22, 0);
    Screen_Main_ButtonWidget_Prev->fn->setSize(Screen_Main_ButtonWidget_Prev, 32, 32);
    Screen_Main_ButtonWidget_Prev->fn->setBackgroundType(Screen_Main_ButtonWidget_Prev, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_ButtonWidget_Prev->fn->setBorderType(Screen_Main_ButtonWidget_Prev, LE_WIDGET_BORDER_NONE);
    Screen_Main_ButtonWidget_Prev->fn->setMargins(Screen_Main_ButtonWidget_Prev, 0, 0, 0, 0);
    Screen_Main_ButtonWidget_Prev->fn->setPressedImage(Screen_Main_ButtonWidget_Prev, (leImage*)&skip_previous);
    Screen_Main_ButtonWidget_Prev->fn->setReleasedImage(Screen_Main_ButtonWidget_Prev, (leImage*)&skip_previous);
    Screen_Main_ButtonWidget_Prev->fn->setImagePosition(Screen_Main_ButtonWidget_Prev, LE_RELATIVE_POSITION_ABOVE);
    Screen_Main_ButtonWidget_Prev->fn->setImageMargin(Screen_Main_ButtonWidget_Prev, 0);
    Screen_Main_ButtonWidget_Prev->fn->setReleasedEventCallback(Screen_Main_ButtonWidget_Prev, event_Screen_Main_ButtonWidget_Prev_OnReleased);
    Screen_Main_PanelWidget_4->fn->addChild(Screen_Main_PanelWidget_4, (leWidget*)Screen_Main_ButtonWidget_Prev);

    Screen_Main_ButtonWidget_PlayPause = leButtonWidget_New();
    Screen_Main_ButtonWidget_PlayPause->fn->setPosition(Screen_Main_ButtonWidget_PlayPause, 66, 0);
    Screen_Main_ButtonWidget_PlayPause->fn->setSize(Screen_Main_ButtonWidget_PlayPause, 32, 32);
    Screen_Main_ButtonWidget_PlayPause->fn->setBackgroundType(Screen_Main_ButtonWidget_PlayPause, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_ButtonWidget_PlayPause->fn->setBorderType(Screen_Main_ButtonWidget_PlayPause, LE_WIDGET_BORDER_NONE);
    Screen_Main_ButtonWidget_PlayPause->fn->setMargins(Screen_Main_ButtonWidget_PlayPause, 0, 0, 0, 0);
    Screen_Main_ButtonWidget_PlayPause->fn->setToggleable(Screen_Main_ButtonWidget_PlayPause, LE_TRUE);
    Screen_Main_ButtonWidget_PlayPause->fn->setPressedImage(Screen_Main_ButtonWidget_PlayPause, (leImage*)&play_circle);
    Screen_Main_ButtonWidget_PlayPause->fn->setReleasedImage(Screen_Main_ButtonWidget_PlayPause, (leImage*)&pause_circle);
    Screen_Main_ButtonWidget_PlayPause->fn->setPressedOffset(Screen_Main_ButtonWidget_PlayPause, 0);
    Screen_Main_ButtonWidget_PlayPause->fn->setPressedEventCallback(Screen_Main_ButtonWidget_PlayPause, event_Screen_Main_ButtonWidget_PlayPause_OnPressed);
    Screen_Main_ButtonWidget_PlayPause->fn->setReleasedEventCallback(Screen_Main_ButtonWidget_PlayPause, event_Screen_Main_ButtonWidget_PlayPause_OnReleased);
    Screen_Main_PanelWidget_4->fn->addChild(Screen_Main_PanelWidget_4, (leWidget*)Screen_Main_ButtonWidget_PlayPause);

    Screen_Main_ButtonWidget_Next = leButtonWidget_New();
    Screen_Main_ButtonWidget_Next->fn->setPosition(Screen_Main_ButtonWidget_Next, 110, 0);
    Screen_Main_ButtonWidget_Next->fn->setSize(Screen_Main_ButtonWidget_Next, 32, 32);
    Screen_Main_ButtonWidget_Next->fn->setBackgroundType(Screen_Main_ButtonWidget_Next, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_ButtonWidget_Next->fn->setBorderType(Screen_Main_ButtonWidget_Next, LE_WIDGET_BORDER_NONE);
    Screen_Main_ButtonWidget_Next->fn->setMargins(Screen_Main_ButtonWidget_Next, 0, 0, 0, 0);
    Screen_Main_ButtonWidget_Next->fn->setPressedImage(Screen_Main_ButtonWidget_Next, (leImage*)&skip_next);
    Screen_Main_ButtonWidget_Next->fn->setReleasedImage(Screen_Main_ButtonWidget_Next, (leImage*)&skip_next);
    Screen_Main_ButtonWidget_Next->fn->setImagePosition(Screen_Main_ButtonWidget_Next, LE_RELATIVE_POSITION_ABOVE);
    Screen_Main_ButtonWidget_Next->fn->setImageMargin(Screen_Main_ButtonWidget_Next, 0);
    Screen_Main_ButtonWidget_Next->fn->setReleasedEventCallback(Screen_Main_ButtonWidget_Next, event_Screen_Main_ButtonWidget_Next_OnReleased);
    Screen_Main_PanelWidget_4->fn->addChild(Screen_Main_PanelWidget_4, (leWidget*)Screen_Main_ButtonWidget_Next);

    Screen_Main_ImageWidget_Volume = leImageWidget_New();
    Screen_Main_ImageWidget_Volume->fn->setPosition(Screen_Main_ImageWidget_Volume, 0, 40);
    Screen_Main_ImageWidget_Volume->fn->setSize(Screen_Main_ImageWidget_Volume, 16, 16);
    Screen_Main_ImageWidget_Volume->fn->setBackgroundType(Screen_Main_ImageWidget_Volume, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_ImageWidget_Volume->fn->setBorderType(Screen_Main_ImageWidget_Volume, LE_WIDGET_BORDER_NONE);
    Screen_Main_ImageWidget_Volume->fn->setMargins(Screen_Main_ImageWidget_Volume, 0, 0, 0, 0);
    Screen_Main_ImageWidget_Volume->fn->setImage(Screen_Main_ImageWidget_Volume, (leImage*)&volume_16x16);
    Screen_Main_PanelWidget_4->fn->addChild(Screen_Main_PanelWidget_4, (leWidget*)Screen_Main_ImageWidget_Volume);

    Screen_Main_PanelWidget_Vol = leWidget_New();
    Screen_Main_PanelWidget_Vol->fn->setPosition(Screen_Main_PanelWidget_Vol, 12, 28);
    Screen_Main_PanelWidget_Vol->fn->setSize(Screen_Main_PanelWidget_Vol, 140, 50);
    Screen_Main_PanelWidget_Vol->fn->setBackgroundType(Screen_Main_PanelWidget_Vol, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_PanelWidget_4->fn->addChild(Screen_Main_PanelWidget_4, (leWidget*)Screen_Main_PanelWidget_Vol);

    Screen_Main_PanelWidget_VolLight = leWidget_New();
    Screen_Main_PanelWidget_VolLight->fn->setPosition(Screen_Main_PanelWidget_VolLight, 10, 16);
    Screen_Main_PanelWidget_VolLight->fn->setSize(Screen_Main_PanelWidget_VolLight, 120, 8);
    Screen_Main_PanelWidget_VolLight->fn->setEnabled(Screen_Main_PanelWidget_VolLight, LE_FALSE);
    Screen_Main_PanelWidget_VolLight->fn->setScheme(Screen_Main_PanelWidget_VolLight, &SliderLightScheme);
    Screen_Main_PanelWidget_Vol->fn->addChild(Screen_Main_PanelWidget_Vol, (leWidget*)Screen_Main_PanelWidget_VolLight);

    Screen_Main_PanelWidget_VolDark = leWidget_New();
    Screen_Main_PanelWidget_VolDark->fn->setPosition(Screen_Main_PanelWidget_VolDark, 10, 16);
    Screen_Main_PanelWidget_VolDark->fn->setSize(Screen_Main_PanelWidget_VolDark, 60, 8);
    Screen_Main_PanelWidget_VolDark->fn->setEnabled(Screen_Main_PanelWidget_VolDark, LE_FALSE);
    Screen_Main_PanelWidget_VolDark->fn->setScheme(Screen_Main_PanelWidget_VolDark, &SliderDarkScheme);
    Screen_Main_PanelWidget_Vol->fn->addChild(Screen_Main_PanelWidget_Vol, (leWidget*)Screen_Main_PanelWidget_VolDark);

    Screen_Main_ButtonWidget_MP = leButtonWidget_New();
    Screen_Main_ButtonWidget_MP->fn->setPosition(Screen_Main_ButtonWidget_MP, 56, 360);
    Screen_Main_ButtonWidget_MP->fn->setSize(Screen_Main_ButtonWidget_MP, 199, 80);
    Screen_Main_ButtonWidget_MP->fn->setBackgroundType(Screen_Main_ButtonWidget_MP, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_ButtonWidget_MP->fn->setBorderType(Screen_Main_ButtonWidget_MP, LE_WIDGET_BORDER_NONE);
    Screen_Main_ButtonWidget_MP->fn->setReleasedEventCallback(Screen_Main_ButtonWidget_MP, event_Screen_Main_ButtonWidget_MP_OnReleased);
    Screen_Main_EditPanelWidget->fn->addChild(Screen_Main_EditPanelWidget, (leWidget*)Screen_Main_ButtonWidget_MP);

    Screen_Main_PanelWidget_0 = leWidget_New();
    Screen_Main_PanelWidget_0->fn->setPosition(Screen_Main_PanelWidget_0, 0, 494);
    Screen_Main_PanelWidget_0->fn->setSize(Screen_Main_PanelWidget_0, 1024, 75);
    Screen_Main_PanelWidget_0->fn->setEnabled(Screen_Main_PanelWidget_0, LE_FALSE);
    Screen_Main_PanelWidget_0->fn->setBackgroundType(Screen_Main_PanelWidget_0, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->addChild(root0, (leWidget*)Screen_Main_PanelWidget_0);

    Screen_Main_MicrochipLogo = leImageWidget_New();
    Screen_Main_MicrochipLogo->fn->setPosition(Screen_Main_MicrochipLogo, 52, 16);
    Screen_Main_MicrochipLogo->fn->setSize(Screen_Main_MicrochipLogo, 220, 40);
    Screen_Main_MicrochipLogo->fn->setBackgroundType(Screen_Main_MicrochipLogo, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_MicrochipLogo->fn->setBorderType(Screen_Main_MicrochipLogo, LE_WIDGET_BORDER_NONE);
    Screen_Main_MicrochipLogo->fn->setImage(Screen_Main_MicrochipLogo, (leImage*)&mchp_logo);
    Screen_Main_PanelWidget_0->fn->addChild(Screen_Main_PanelWidget_0, (leWidget*)Screen_Main_MicrochipLogo);

    Screen_Main_PanelWidget_1 = leWidget_New();
    Screen_Main_PanelWidget_1->fn->setPosition(Screen_Main_PanelWidget_1, 320, 470);
    Screen_Main_PanelWidget_1->fn->setSize(Screen_Main_PanelWidget_1, 704, 120);
    Screen_Main_PanelWidget_1->fn->setEnabled(Screen_Main_PanelWidget_1, LE_FALSE);
    Screen_Main_PanelWidget_1->fn->setBackgroundType(Screen_Main_PanelWidget_1, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->addChild(root0, (leWidget*)Screen_Main_PanelWidget_1);

    Screen_Main_MGSLogo = leImageWidget_New();
    Screen_Main_MGSLogo->fn->setPosition(Screen_Main_MGSLogo, 46, 27);
    Screen_Main_MGSLogo->fn->setSize(Screen_Main_MGSLogo, 225, 69);
    Screen_Main_MGSLogo->fn->setBackgroundType(Screen_Main_MGSLogo, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_MGSLogo->fn->setBorderType(Screen_Main_MGSLogo, LE_WIDGET_BORDER_NONE);
    Screen_Main_MGSLogo->fn->setImage(Screen_Main_MGSLogo, (leImage*)&mgs_mega_logo);
    Screen_Main_PanelWidget_1->fn->addChild(Screen_Main_PanelWidget_1, (leWidget*)Screen_Main_MGSLogo);

    Screen_Main_ImageWidget_mgsLogo = leImageWidget_New();
    Screen_Main_ImageWidget_mgsLogo->fn->setPosition(Screen_Main_ImageWidget_mgsLogo, 985, 10);
    Screen_Main_ImageWidget_mgsLogo->fn->setSize(Screen_Main_ImageWidget_mgsLogo, 29, 24);
    Screen_Main_ImageWidget_mgsLogo->fn->setBackgroundType(Screen_Main_ImageWidget_mgsLogo, LE_WIDGET_BACKGROUND_NONE);
    Screen_Main_ImageWidget_mgsLogo->fn->setBorderType(Screen_Main_ImageWidget_mgsLogo, LE_WIDGET_BORDER_NONE);
    Screen_Main_ImageWidget_mgsLogo->fn->setImage(Screen_Main_ImageWidget_mgsLogo, (leImage*)&mgs_logo);
    root0->fn->addChild(root0, (leWidget*)Screen_Main_ImageWidget_mgsLogo);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    Screen_Main_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_Screen_Main(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);

    Screen_Main_OnUpdate(); // raise event
}

void screenHide_Screen_Main(void)
{
    Screen_Main_OnHide(); // raise event


    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    Screen_Main_BackgroundPanel = NULL;
    Screen_Main_ButtonWidget_Settings = NULL;
    Screen_Main_ButtonWidget_WaterQ = NULL;
    Screen_Main_LabelWidget_SelectReg = NULL;
    Screen_Main_LabelWidget_ControlDisp = NULL;
    Screen_Main_ImageWidget_Regions = NULL;
    Screen_Main_ButtonWidget_Reg2 = NULL;
    Screen_Main_ButtonWidget_Reg1 = NULL;
    Screen_Main_ButtonWidget_Reg3 = NULL;
    Screen_Main_ButtonWidget_Reg4 = NULL;
    Screen_Main_EditPanelWidget = NULL;
    Screen_Main_PanelWidget_0 = NULL;
    Screen_Main_PanelWidget_1 = NULL;
    Screen_Main_ImageWidget_mgsLogo = NULL;
    Screen_Main_PanelWidget_WaterTemp = NULL;
    Screen_Main_PanelWidget_SelColors = NULL;
    Screen_Main_PanelWidget_JetCtrl = NULL;
    Screen_Main_PanelWidget_MP = NULL;
    Screen_Main_ButtonWidget_MP = NULL;
    Screen_Main_LabelWidget_WaterTemp = NULL;
    Screen_Main_ButtonWidget_IncTemp = NULL;
    Screen_Main_ButtonWidget_DecTemp = NULL;
    Screen_Main_LabelWidget_Deg = NULL;
    Screen_Main_LabelWidget_SelectedReg = NULL;
    Screen_Main_LabelWidget_Brightness = NULL;
    Screen_Main_ButtonWidget_Red = NULL;
    Screen_Main_ButtonWidget_Orange = NULL;
    Screen_Main_ButtonWidget_Yellow = NULL;
    Screen_Main_ButtonWidget_Green = NULL;
    Screen_Main_ButtonWidget_Cyan = NULL;
    Screen_Main_ButtonWidget_Purple = NULL;
    Screen_Main_ButtonWidget_Pink = NULL;
    Screen_Main_ButtonWidget_Radial = NULL;
    Screen_Main_PanelWidget_BrgGen = NULL;
    Screen_Main_PanelWidget_BrgLight = NULL;
    Screen_Main_PanelWidget_BrgDark = NULL;
    Screen_Main_ButtonWidget_Brg = NULL;
    Screen_Main_ButtonWidget_JetDec = NULL;
    Screen_Main_ButtonWidget_JetInc = NULL;
    Screen_Main_ImageWidget_bubbles = NULL;
    Screen_Main_LabelWidget_BubbleLevel = NULL;
    Screen_Main_PanelWidget_Bkg = NULL;
    Screen_Main_ImageWidget_SongCover = NULL;
    Screen_Main_LabelWidget_SongTitle = NULL;
    Screen_Main_LabelWidget_ArtistName = NULL;
    Screen_Main_PanelWidget_4 = NULL;
    Screen_Main_ButtonWidget_Prev = NULL;
    Screen_Main_ButtonWidget_PlayPause = NULL;
    Screen_Main_ButtonWidget_Next = NULL;
    Screen_Main_ImageWidget_Volume = NULL;
    Screen_Main_PanelWidget_Vol = NULL;
    Screen_Main_PanelWidget_VolLight = NULL;
    Screen_Main_PanelWidget_VolDark = NULL;
    Screen_Main_MicrochipLogo = NULL;
    Screen_Main_MGSLogo = NULL;


    showing = LE_FALSE;
}

void screenDestroy_Screen_Main(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_Screen_Main(uint32_t lyrIdx)
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


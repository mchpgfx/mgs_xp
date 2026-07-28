#include "gfx/legato/generated/screen/le_gen_screen_Home.h"

// screen member widget declarations
static leWidget* root0;
static leWidget* root1;
static leWidget* root2;

leWidget* Home_BackgroundPanelBase;
leWidget* Home_panel_electric_moto_cluster;
leWidget* Home_panel_Status_Bar;
leImageWidget* Home_image_imgRegenFullBar;
leImageWidget* Home_imgRegenBar;
leWidget* Home_panel_Drive_Modes;
leImageWidget* Home_image_iconBattery;
leImageWidget* Home_image_iconTemp;
leWidget* Home_panel_Shortcut_Bar;
leImageWidget* Home_image_imgEnergyFlow;
leLabelWidget* Home_label_REGEN;
leImageWidget* Home_image_imgMeterTrack;
leLabelWidget* Home_label_DISCHARGE;
leImageWidget* Home_image_imgPowerTrack;
leImageWidget* Home_image_imgPowerProg;
leImageWidget* Home_image_imgBatTrack;
leImageWidget* Home_image_imgBatProg;
leLabelWidget* Home_label_Battery;
leLabelWidget* Home_label_0;
leLabelWidget* Home_label_BattValue;
leLabelWidget* Home_label_Power;
leLabelWidget* Home_label_PowerValue;
leLabelWidget* Home_label_kW;
leLabelWidget* Home_lblGauge;
leLabelWidget* Home_label_MPH;
leWidget* Home_panel_Battery_Temp;
leLabelWidget* Home_label_Est_Range;
leLabelWidget* Home_label_Range;
leLabelWidget* Home_label_KM;
leWidget* Home_panel_Motor_Temp;
leImageWidget* Home_image_RegenBar;
leImageWidget* Home_image_DischargeBar;
leWidget* Home_touchPanel;
leImageWidget* Home_imgMGS;
leWidget* Home_pnlMetrics;
leWidget* Home_panel_Status_Left;
leWidget* Home_panel_Status_Center;
leWidget* Home_panel_Status_Right;
leImageWidget* Home_image_iconLeftOn;
leLabelWidget* Home_odo;
leLabelWidget* Home_label_OdoValue;
leImageWidget* Home_image_iconHazard;
leImageWidget* Home_image_iconArrow;
leImageWidget* Home_image_iconCancel;
leImageWidget* Home_image_iconPlug;
leLabelWidget* Home_label_TRIP_A;
leLabelWidget* Home_label_TripValue;
leLabelWidget* Home_label__Time;
leImageWidget* Home_image_iconRightOff;
leImageWidget* Home_image_imgEcoOff;
leImageWidget* Home_image_imgTourOff;
leImageWidget* Home_image_imgSportOff;
leImageWidget* Home_image_imgBoostOn;
leLabelWidget* Home_label_ECO;
leLabelWidget* Home_label_TOUR;
leLabelWidget* Home_label_SPORT;
leLabelWidget* Home_label_BOOST;
leButtonWidget* Home_btnPhone;
leButtonWidget* Home_btnCamera;
leButtonWidget* Home_btnHome;
leButtonWidget* Home_btnMusic;
leButtonWidget* Home_btnMap;
leButtonWidget* Home_btnLight;
leLabelWidget* Home_label_Battery;
leLabelWidget* Home_label_BattTemp;
leLabelWidget* Home_label_Motor;
leLabelWidget* Home_label_MotorTempValue;
leLabelWidget* Home_lblUpdatePct;
leLabelWidget* Home_lblDrawPct;
leLabelWidget* Home_lblFPSValue;
leLabelWidget* Home_lblUpdate;
leLabelWidget* Home_lblDraw;
leLabelWidget* Home_lblFPS;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_Home(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_Home(void)
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

    Home_BackgroundPanelBase = leWidget_New();
    Home_BackgroundPanelBase->fn->setPosition(Home_BackgroundPanelBase, 0, 0);
    Home_BackgroundPanelBase->fn->setSize(Home_BackgroundPanelBase, 800, 480);
    Home_BackgroundPanelBase->fn->setVisible(Home_BackgroundPanelBase, LE_FALSE);
    Home_BackgroundPanelBase->fn->setScheme(Home_BackgroundPanelBase, &GaugeScheme);
    root0->fn->addChild(root0, (leWidget*)Home_BackgroundPanelBase);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGBA_8888);

    // layer 1
    root1 = leWidget_New();
    root1->fn->setSize(root1, LE_DEFAULT_SCREEN_WIDTH, LE_DEFAULT_SCREEN_HEIGHT);
    root1->fn->setBackgroundType(root1, LE_WIDGET_BACKGROUND_NONE);
    root1->fn->setMargins(root1, 0, 0, 0, 0);
    root1->flags |= LE_WIDGET_IGNOREEVENTS;
    root1->flags |= LE_WIDGET_IGNOREPICK;

    leAddRootWidget(root1, 1);
    leSetLayerColorMode(1, LE_COLOR_MODE_RGBA_8888);

    // layer 2
    root2 = leWidget_New();
    root2->fn->setSize(root2, LE_DEFAULT_SCREEN_WIDTH, LE_DEFAULT_SCREEN_HEIGHT);
    root2->fn->setBackgroundType(root2, LE_WIDGET_BACKGROUND_NONE);
    root2->fn->setMargins(root2, 0, 0, 0, 0);
    root2->flags |= LE_WIDGET_IGNOREEVENTS;
    root2->flags |= LE_WIDGET_IGNOREPICK;

    Home_panel_electric_moto_cluster = leWidget_New();
    Home_panel_electric_moto_cluster->fn->setPosition(Home_panel_electric_moto_cluster, 0, 0);
    Home_panel_electric_moto_cluster->fn->setSize(Home_panel_electric_moto_cluster, 800, 480);
    Home_panel_electric_moto_cluster->fn->setScheme(Home_panel_electric_moto_cluster, &ClearScheme);
    root2->fn->addChild(root2, (leWidget*)Home_panel_electric_moto_cluster);

    Home_panel_Status_Bar = leWidget_New();
    Home_panel_Status_Bar->fn->setPosition(Home_panel_Status_Bar, 0, 0);
    Home_panel_Status_Bar->fn->setSize(Home_panel_Status_Bar, 800, 50);
    Home_panel_Status_Bar->fn->setBackgroundType(Home_panel_Status_Bar, LE_WIDGET_BACKGROUND_NONE);
    root2->fn->addChild(root2, (leWidget*)Home_panel_Status_Bar);

    Home_panel_Status_Left = leWidget_New();
    Home_panel_Status_Left->fn->setPosition(Home_panel_Status_Left, 24, 9);
    Home_panel_Status_Left->fn->setSize(Home_panel_Status_Left, 124, 32);
    Home_panel_Status_Left->fn->setBackgroundType(Home_panel_Status_Left, LE_WIDGET_BACKGROUND_NONE);
    Home_panel_Status_Bar->fn->addChild(Home_panel_Status_Bar, (leWidget*)Home_panel_Status_Left);

    Home_image_iconLeftOn = leImageWidget_New();
    Home_image_iconLeftOn->fn->setPosition(Home_image_iconLeftOn, 6, 7);
    Home_image_iconLeftOn->fn->setSize(Home_image_iconLeftOn, 20, 20);
    Home_image_iconLeftOn->fn->setBackgroundType(Home_image_iconLeftOn, LE_WIDGET_BACKGROUND_NONE);
    Home_image_iconLeftOn->fn->setBorderType(Home_image_iconLeftOn, LE_WIDGET_BORDER_NONE);
    Home_image_iconLeftOn->fn->setImage(Home_image_iconLeftOn, (leImage*)&figmaImg_iconLeftOn);
    Home_panel_Status_Left->fn->addChild(Home_panel_Status_Left, (leWidget*)Home_image_iconLeftOn);

    Home_odo = leLabelWidget_New();
    Home_odo->fn->setPosition(Home_odo, 48, 1);
    Home_odo->fn->setSize(Home_odo, 26, 13);
    Home_odo->fn->setScheme(Home_odo, &text_darkslategray);
    Home_odo->fn->setBackgroundType(Home_odo, LE_WIDGET_BACKGROUND_NONE);
    Home_odo->fn->setMargins(Home_odo, 0, 0, 0, 0);
    Home_odo->fn->setString(Home_odo, (leString*)&string_figmaStr_ODO);
    Home_panel_Status_Left->fn->addChild(Home_panel_Status_Left, (leWidget*)Home_odo);

    Home_label_OdoValue = leLabelWidget_New();
    Home_label_OdoValue->fn->setPosition(Home_label_OdoValue, 48, 14);
    Home_label_OdoValue->fn->setSize(Home_label_OdoValue, 76, 18);
    Home_label_OdoValue->fn->setScheme(Home_label_OdoValue, &text_lightslategray);
    Home_label_OdoValue->fn->setBackgroundType(Home_label_OdoValue, LE_WIDGET_BACKGROUND_NONE);
    Home_label_OdoValue->fn->setVAlignment(Home_label_OdoValue, LE_VALIGN_TOP);
    Home_label_OdoValue->fn->setMargins(Home_label_OdoValue, 0, 0, 0, 0);
    Home_label_OdoValue->fn->setString(Home_label_OdoValue, (leString*)&string_figmaStr_001240_mi);
    Home_panel_Status_Left->fn->addChild(Home_panel_Status_Left, (leWidget*)Home_label_OdoValue);

    Home_panel_Status_Center = leWidget_New();
    Home_panel_Status_Center->fn->setPosition(Home_panel_Status_Center, 287, 9);
    Home_panel_Status_Center->fn->setSize(Home_panel_Status_Center, 164, 32);
    Home_panel_Status_Center->fn->setBackgroundType(Home_panel_Status_Center, LE_WIDGET_BACKGROUND_NONE);
    Home_panel_Status_Bar->fn->addChild(Home_panel_Status_Bar, (leWidget*)Home_panel_Status_Center);

    Home_image_iconHazard = leImageWidget_New();
    Home_image_iconHazard->fn->setPosition(Home_image_iconHazard, 7, 9);
    Home_image_iconHazard->fn->setSize(Home_image_iconHazard, 20, 20);
    Home_image_iconHazard->fn->setBackgroundType(Home_image_iconHazard, LE_WIDGET_BACKGROUND_NONE);
    Home_image_iconHazard->fn->setBorderType(Home_image_iconHazard, LE_WIDGET_BORDER_NONE);
    Home_image_iconHazard->fn->setImage(Home_image_iconHazard, (leImage*)&figmaImg_iconHazard);
    Home_panel_Status_Center->fn->addChild(Home_panel_Status_Center, (leWidget*)Home_image_iconHazard);

    Home_image_iconArrow = leImageWidget_New();
    Home_image_iconArrow->fn->setPosition(Home_image_iconArrow, 53, 7);
    Home_image_iconArrow->fn->setSize(Home_image_iconArrow, 20, 20);
    Home_image_iconArrow->fn->setBackgroundType(Home_image_iconArrow, LE_WIDGET_BACKGROUND_NONE);
    Home_image_iconArrow->fn->setBorderType(Home_image_iconArrow, LE_WIDGET_BORDER_NONE);
    Home_image_iconArrow->fn->setImage(Home_image_iconArrow, (leImage*)&figmaImg_iconArrow);
    Home_panel_Status_Center->fn->addChild(Home_panel_Status_Center, (leWidget*)Home_image_iconArrow);

    Home_image_iconCancel = leImageWidget_New();
    Home_image_iconCancel->fn->setPosition(Home_image_iconCancel, 98, 8);
    Home_image_iconCancel->fn->setSize(Home_image_iconCancel, 20, 20);
    Home_image_iconCancel->fn->setBackgroundType(Home_image_iconCancel, LE_WIDGET_BACKGROUND_NONE);
    Home_image_iconCancel->fn->setBorderType(Home_image_iconCancel, LE_WIDGET_BORDER_NONE);
    Home_image_iconCancel->fn->setImage(Home_image_iconCancel, (leImage*)&figmaImg_iconCancel);
    Home_panel_Status_Center->fn->addChild(Home_panel_Status_Center, (leWidget*)Home_image_iconCancel);

    Home_image_iconPlug = leImageWidget_New();
    Home_image_iconPlug->fn->setPosition(Home_image_iconPlug, 143, 8);
    Home_image_iconPlug->fn->setSize(Home_image_iconPlug, 20, 20);
    Home_image_iconPlug->fn->setBackgroundType(Home_image_iconPlug, LE_WIDGET_BACKGROUND_NONE);
    Home_image_iconPlug->fn->setBorderType(Home_image_iconPlug, LE_WIDGET_BORDER_NONE);
    Home_image_iconPlug->fn->setImage(Home_image_iconPlug, (leImage*)&figmaImg_iconPlug);
    Home_panel_Status_Center->fn->addChild(Home_panel_Status_Center, (leWidget*)Home_image_iconPlug);

    Home_panel_Status_Right = leWidget_New();
    Home_panel_Status_Right->fn->setPosition(Home_panel_Status_Right, 590, 9);
    Home_panel_Status_Right->fn->setSize(Home_panel_Status_Right, 193, 32);
    Home_panel_Status_Right->fn->setBackgroundType(Home_panel_Status_Right, LE_WIDGET_BACKGROUND_NONE);
    Home_panel_Status_Bar->fn->addChild(Home_panel_Status_Bar, (leWidget*)Home_panel_Status_Right);

    Home_label_TRIP_A = leLabelWidget_New();
    Home_label_TRIP_A->fn->setPosition(Home_label_TRIP_A, 23, 1);
    Home_label_TRIP_A->fn->setSize(Home_label_TRIP_A, 45, 13);
    Home_label_TRIP_A->fn->setScheme(Home_label_TRIP_A, &text_darkslategray);
    Home_label_TRIP_A->fn->setBackgroundType(Home_label_TRIP_A, LE_WIDGET_BACKGROUND_NONE);
    Home_label_TRIP_A->fn->setHAlignment(Home_label_TRIP_A, LE_HALIGN_RIGHT);
    Home_label_TRIP_A->fn->setMargins(Home_label_TRIP_A, 0, 0, 0, 0);
    Home_label_TRIP_A->fn->setString(Home_label_TRIP_A, (leString*)&string_figmaStr_TRIP_A);
    Home_panel_Status_Right->fn->addChild(Home_panel_Status_Right, (leWidget*)Home_label_TRIP_A);

    Home_label_TripValue = leLabelWidget_New();
    Home_label_TripValue->fn->setPosition(Home_label_TripValue, 0, 14);
    Home_label_TripValue->fn->setSize(Home_label_TripValue, 68, 18);
    Home_label_TripValue->fn->setScheme(Home_label_TripValue, &text_lightslategray);
    Home_label_TripValue->fn->setBackgroundType(Home_label_TripValue, LE_WIDGET_BACKGROUND_NONE);
    Home_label_TripValue->fn->setHAlignment(Home_label_TripValue, LE_HALIGN_RIGHT);
    Home_label_TripValue->fn->setVAlignment(Home_label_TripValue, LE_VALIGN_TOP);
    Home_label_TripValue->fn->setMargins(Home_label_TripValue, 0, 0, 0, 0);
    Home_label_TripValue->fn->setString(Home_label_TripValue, (leString*)&string_figmaStr_042_8_mi);
    Home_panel_Status_Right->fn->addChild(Home_panel_Status_Right, (leWidget*)Home_label_TripValue);

    Home_label__Time = leLabelWidget_New();
    Home_label__Time->fn->setPosition(Home_label__Time, 84, 5);
    Home_label__Time->fn->setSize(Home_label__Time, 54, 23);
    Home_label__Time->fn->setScheme(Home_label__Time, &text_white);
    Home_label__Time->fn->setBackgroundType(Home_label__Time, LE_WIDGET_BACKGROUND_NONE);
    Home_label__Time->fn->setVAlignment(Home_label__Time, LE_VALIGN_TOP);
    Home_label__Time->fn->setMargins(Home_label__Time, 0, 0, 0, 0);
    Home_label__Time->fn->setString(Home_label__Time, (leString*)&string_figmaStr_20_45);
    Home_panel_Status_Right->fn->addChild(Home_panel_Status_Right, (leWidget*)Home_label__Time);

    Home_image_iconRightOff = leImageWidget_New();
    Home_image_iconRightOff->fn->setPosition(Home_image_iconRightOff, 164, 6);
    Home_image_iconRightOff->fn->setSize(Home_image_iconRightOff, 20, 20);
    Home_image_iconRightOff->fn->setBackgroundType(Home_image_iconRightOff, LE_WIDGET_BACKGROUND_NONE);
    Home_image_iconRightOff->fn->setBorderType(Home_image_iconRightOff, LE_WIDGET_BORDER_NONE);
    Home_image_iconRightOff->fn->setImage(Home_image_iconRightOff, (leImage*)&figmaImg_iconRightOff);
    Home_panel_Status_Right->fn->addChild(Home_panel_Status_Right, (leWidget*)Home_image_iconRightOff);

    Home_image_imgRegenFullBar = leImageWidget_New();
    Home_image_imgRegenFullBar->fn->setPosition(Home_image_imgRegenFullBar, 0, 80);
    Home_image_imgRegenFullBar->fn->setSize(Home_image_imgRegenFullBar, 10, 320);
    Home_image_imgRegenFullBar->fn->setBackgroundType(Home_image_imgRegenFullBar, LE_WIDGET_BACKGROUND_NONE);
    Home_image_imgRegenFullBar->fn->setBorderType(Home_image_imgRegenFullBar, LE_WIDGET_BORDER_NONE);
    Home_image_imgRegenFullBar->fn->setImage(Home_image_imgRegenFullBar, (leImage*)&figmaImg_imgRegenFullBar);
    root2->fn->addChild(root2, (leWidget*)Home_image_imgRegenFullBar);

    Home_imgRegenBar = leImageWidget_New();
    Home_imgRegenBar->fn->setPosition(Home_imgRegenBar, 0, 270);
    Home_imgRegenBar->fn->setSize(Home_imgRegenBar, 25, 145);
    Home_imgRegenBar->fn->setBackgroundType(Home_imgRegenBar, LE_WIDGET_BACKGROUND_NONE);
    Home_imgRegenBar->fn->setBorderType(Home_imgRegenBar, LE_WIDGET_BORDER_NONE);
    Home_imgRegenBar->fn->setImage(Home_imgRegenBar, (leImage*)&figmaImg_imgRegenBar);
    root2->fn->addChild(root2, (leWidget*)Home_imgRegenBar);

    Home_panel_Drive_Modes = leWidget_New();
    Home_panel_Drive_Modes->fn->setPosition(Home_panel_Drive_Modes, 279, 340);
    Home_panel_Drive_Modes->fn->setSize(Home_panel_Drive_Modes, 243, 24);
    Home_panel_Drive_Modes->fn->setBackgroundType(Home_panel_Drive_Modes, LE_WIDGET_BACKGROUND_NONE);
    root2->fn->addChild(root2, (leWidget*)Home_panel_Drive_Modes);

    Home_image_imgEcoOff = leImageWidget_New();
    Home_image_imgEcoOff->fn->setPosition(Home_image_imgEcoOff, 0, 0);
    Home_image_imgEcoOff->fn->setSize(Home_image_imgEcoOff, 46, 24);
    Home_image_imgEcoOff->fn->setBackgroundType(Home_image_imgEcoOff, LE_WIDGET_BACKGROUND_NONE);
    Home_image_imgEcoOff->fn->setBorderType(Home_image_imgEcoOff, LE_WIDGET_BORDER_NONE);
    Home_image_imgEcoOff->fn->setImage(Home_image_imgEcoOff, (leImage*)&figmaImg_imgEcoOff);
    Home_panel_Drive_Modes->fn->addChild(Home_panel_Drive_Modes, (leWidget*)Home_image_imgEcoOff);

    Home_image_imgTourOff = leImageWidget_New();
    Home_image_imgTourOff->fn->setPosition(Home_image_imgTourOff, 54, 0);
    Home_image_imgTourOff->fn->setSize(Home_image_imgTourOff, 53, 24);
    Home_image_imgTourOff->fn->setBackgroundType(Home_image_imgTourOff, LE_WIDGET_BACKGROUND_NONE);
    Home_image_imgTourOff->fn->setBorderType(Home_image_imgTourOff, LE_WIDGET_BORDER_NONE);
    Home_image_imgTourOff->fn->setImage(Home_image_imgTourOff, (leImage*)&figmaImg_imgTourOff);
    Home_panel_Drive_Modes->fn->addChild(Home_panel_Drive_Modes, (leWidget*)Home_image_imgTourOff);

    Home_image_imgSportOff = leImageWidget_New();
    Home_image_imgSportOff->fn->setPosition(Home_image_imgSportOff, 115, 0);
    Home_image_imgSportOff->fn->setSize(Home_image_imgSportOff, 60, 24);
    Home_image_imgSportOff->fn->setBackgroundType(Home_image_imgSportOff, LE_WIDGET_BACKGROUND_NONE);
    Home_image_imgSportOff->fn->setBorderType(Home_image_imgSportOff, LE_WIDGET_BORDER_NONE);
    Home_image_imgSportOff->fn->setImage(Home_image_imgSportOff, (leImage*)&figmaImg_imgSportOff);
    Home_panel_Drive_Modes->fn->addChild(Home_panel_Drive_Modes, (leWidget*)Home_image_imgSportOff);

    Home_image_imgBoostOn = leImageWidget_New();
    Home_image_imgBoostOn->fn->setPosition(Home_image_imgBoostOn, 183, 0);
    Home_image_imgBoostOn->fn->setSize(Home_image_imgBoostOn, 60, 24);
    Home_image_imgBoostOn->fn->setBackgroundType(Home_image_imgBoostOn, LE_WIDGET_BACKGROUND_NONE);
    Home_image_imgBoostOn->fn->setBorderType(Home_image_imgBoostOn, LE_WIDGET_BORDER_NONE);
    Home_image_imgBoostOn->fn->setImage(Home_image_imgBoostOn, (leImage*)&figmaImg_imgBoostOn);
    Home_panel_Drive_Modes->fn->addChild(Home_panel_Drive_Modes, (leWidget*)Home_image_imgBoostOn);

    Home_label_ECO = leLabelWidget_New();
    Home_label_ECO->fn->setPosition(Home_label_ECO, 8, 4);
    Home_label_ECO->fn->setSize(Home_label_ECO, 29, 16);
    Home_label_ECO->fn->setScheme(Home_label_ECO, &text_lightslategray);
    Home_label_ECO->fn->setBackgroundType(Home_label_ECO, LE_WIDGET_BACKGROUND_NONE);
    Home_label_ECO->fn->setHAlignment(Home_label_ECO, LE_HALIGN_CENTER);
    Home_label_ECO->fn->setVAlignment(Home_label_ECO, LE_VALIGN_TOP);
    Home_label_ECO->fn->setMargins(Home_label_ECO, 0, 0, 0, 0);
    Home_label_ECO->fn->setString(Home_label_ECO, (leString*)&string_figmaStr_ECO);
    Home_panel_Drive_Modes->fn->addChild(Home_panel_Drive_Modes, (leWidget*)Home_label_ECO);

    Home_label_TOUR = leLabelWidget_New();
    Home_label_TOUR->fn->setPosition(Home_label_TOUR, 62, 4);
    Home_label_TOUR->fn->setSize(Home_label_TOUR, 35, 16);
    Home_label_TOUR->fn->setScheme(Home_label_TOUR, &text_lightslategray);
    Home_label_TOUR->fn->setBackgroundType(Home_label_TOUR, LE_WIDGET_BACKGROUND_NONE);
    Home_label_TOUR->fn->setHAlignment(Home_label_TOUR, LE_HALIGN_CENTER);
    Home_label_TOUR->fn->setVAlignment(Home_label_TOUR, LE_VALIGN_TOP);
    Home_label_TOUR->fn->setMargins(Home_label_TOUR, 0, 0, 0, 0);
    Home_label_TOUR->fn->setString(Home_label_TOUR, (leString*)&string_figmaStr_TOUR);
    Home_panel_Drive_Modes->fn->addChild(Home_panel_Drive_Modes, (leWidget*)Home_label_TOUR);

    Home_label_SPORT = leLabelWidget_New();
    Home_label_SPORT->fn->setPosition(Home_label_SPORT, 126, 4);
    Home_label_SPORT->fn->setSize(Home_label_SPORT, 36, 16);
    Home_label_SPORT->fn->setScheme(Home_label_SPORT, &text_lightslategray);
    Home_label_SPORT->fn->setBackgroundType(Home_label_SPORT, LE_WIDGET_BACKGROUND_NONE);
    Home_label_SPORT->fn->setHAlignment(Home_label_SPORT, LE_HALIGN_CENTER);
    Home_label_SPORT->fn->setVAlignment(Home_label_SPORT, LE_VALIGN_TOP);
    Home_label_SPORT->fn->setMargins(Home_label_SPORT, 0, 0, 0, 0);
    Home_label_SPORT->fn->setString(Home_label_SPORT, (leString*)&string_figmaStr_SPORT);
    Home_panel_Drive_Modes->fn->addChild(Home_panel_Drive_Modes, (leWidget*)Home_label_SPORT);

    Home_label_BOOST = leLabelWidget_New();
    Home_label_BOOST->fn->setPosition(Home_label_BOOST, 193, 4);
    Home_label_BOOST->fn->setSize(Home_label_BOOST, 42, 16);
    Home_label_BOOST->fn->setScheme(Home_label_BOOST, &text_black);
    Home_label_BOOST->fn->setBackgroundType(Home_label_BOOST, LE_WIDGET_BACKGROUND_NONE);
    Home_label_BOOST->fn->setHAlignment(Home_label_BOOST, LE_HALIGN_CENTER);
    Home_label_BOOST->fn->setMargins(Home_label_BOOST, 0, 0, 0, 0);
    Home_label_BOOST->fn->setString(Home_label_BOOST, (leString*)&string_figmaStr_BOOST);
    Home_panel_Drive_Modes->fn->addChild(Home_panel_Drive_Modes, (leWidget*)Home_label_BOOST);

    Home_image_iconBattery = leImageWidget_New();
    Home_image_iconBattery->fn->setPosition(Home_image_iconBattery, 75, 62);
    Home_image_iconBattery->fn->setSize(Home_image_iconBattery, 23, 15);
    Home_image_iconBattery->fn->setBackgroundType(Home_image_iconBattery, LE_WIDGET_BACKGROUND_NONE);
    Home_image_iconBattery->fn->setBorderType(Home_image_iconBattery, LE_WIDGET_BORDER_NONE);
    Home_image_iconBattery->fn->setImage(Home_image_iconBattery, (leImage*)&figmaImg_iconBattery);
    root2->fn->addChild(root2, (leWidget*)Home_image_iconBattery);

    Home_image_iconTemp = leImageWidget_New();
    Home_image_iconTemp->fn->setPosition(Home_image_iconTemp, 105, 59);
    Home_image_iconTemp->fn->setSize(Home_image_iconTemp, 20, 20);
    Home_image_iconTemp->fn->setBackgroundType(Home_image_iconTemp, LE_WIDGET_BACKGROUND_NONE);
    Home_image_iconTemp->fn->setBorderType(Home_image_iconTemp, LE_WIDGET_BORDER_NONE);
    Home_image_iconTemp->fn->setImage(Home_image_iconTemp, (leImage*)&figmaImg_iconTemp);
    root2->fn->addChild(root2, (leWidget*)Home_image_iconTemp);

    Home_panel_Shortcut_Bar = leWidget_New();
    Home_panel_Shortcut_Bar->fn->setPosition(Home_panel_Shortcut_Bar, 0, 430);
    Home_panel_Shortcut_Bar->fn->setSize(Home_panel_Shortcut_Bar, 800, 50);
    Home_panel_Shortcut_Bar->fn->setScheme(Home_panel_Shortcut_Bar, &GrayScheme);
    root2->fn->addChild(root2, (leWidget*)Home_panel_Shortcut_Bar);

    Home_btnPhone = leButtonWidget_New();
    Home_btnPhone->fn->setPosition(Home_btnPhone, 570, 10);
    Home_btnPhone->fn->setSize(Home_btnPhone, 40, 40);
    Home_btnPhone->fn->setBackgroundType(Home_btnPhone, LE_WIDGET_BACKGROUND_NONE);
    Home_btnPhone->fn->setBorderType(Home_btnPhone, LE_WIDGET_BORDER_NONE);
    Home_btnPhone->fn->setPressedImage(Home_btnPhone, (leImage*)&figmaImg_iconPhone);
    Home_btnPhone->fn->setReleasedImage(Home_btnPhone, (leImage*)&figmaImg_iconPhone);
    Home_btnPhone->fn->setPressedEventCallback(Home_btnPhone, event_Home_btnPhone_OnPressed);
    Home_panel_Shortcut_Bar->fn->addChild(Home_panel_Shortcut_Bar, (leWidget*)Home_btnPhone);

    Home_btnCamera = leButtonWidget_New();
    Home_btnCamera->fn->setPosition(Home_btnCamera, 444, 10);
    Home_btnCamera->fn->setSize(Home_btnCamera, 40, 40);
    Home_btnCamera->fn->setBackgroundType(Home_btnCamera, LE_WIDGET_BACKGROUND_NONE);
    Home_btnCamera->fn->setBorderType(Home_btnCamera, LE_WIDGET_BORDER_NONE);
    Home_btnCamera->fn->setPressedImage(Home_btnCamera, (leImage*)&figmaImg_iconCamera);
    Home_btnCamera->fn->setReleasedImage(Home_btnCamera, (leImage*)&figmaImg_iconCamera);
    Home_btnCamera->fn->setPressedEventCallback(Home_btnCamera, event_Home_btnCamera_OnPressed);
    Home_panel_Shortcut_Bar->fn->addChild(Home_panel_Shortcut_Bar, (leWidget*)Home_btnCamera);

    Home_btnHome = leButtonWidget_New();
    Home_btnHome->fn->setPosition(Home_btnHome, 693, 10);
    Home_btnHome->fn->setSize(Home_btnHome, 40, 40);
    Home_btnHome->fn->setBackgroundType(Home_btnHome, LE_WIDGET_BACKGROUND_NONE);
    Home_btnHome->fn->setBorderType(Home_btnHome, LE_WIDGET_BORDER_NONE);
    Home_btnHome->fn->setPressedImage(Home_btnHome, (leImage*)&figmaImg_iconHome);
    Home_btnHome->fn->setReleasedImage(Home_btnHome, (leImage*)&figmaImg_iconHome);
    Home_btnHome->fn->setPressedEventCallback(Home_btnHome, event_Home_btnHome_OnPressed);
    Home_panel_Shortcut_Bar->fn->addChild(Home_panel_Shortcut_Bar, (leWidget*)Home_btnHome);

    Home_btnMusic = leButtonWidget_New();
    Home_btnMusic->fn->setPosition(Home_btnMusic, 191, 10);
    Home_btnMusic->fn->setSize(Home_btnMusic, 40, 40);
    Home_btnMusic->fn->setBackgroundType(Home_btnMusic, LE_WIDGET_BACKGROUND_NONE);
    Home_btnMusic->fn->setBorderType(Home_btnMusic, LE_WIDGET_BORDER_NONE);
    Home_btnMusic->fn->setPressedImage(Home_btnMusic, (leImage*)&figmaImg_iconMusic);
    Home_btnMusic->fn->setReleasedImage(Home_btnMusic, (leImage*)&figmaImg_iconMusic);
    Home_btnMusic->fn->setPressedEventCallback(Home_btnMusic, event_Home_btnMusic_OnPressed);
    Home_panel_Shortcut_Bar->fn->addChild(Home_panel_Shortcut_Bar, (leWidget*)Home_btnMusic);

    Home_btnMap = leButtonWidget_New();
    Home_btnMap->fn->setPosition(Home_btnMap, 317, 10);
    Home_btnMap->fn->setSize(Home_btnMap, 40, 40);
    Home_btnMap->fn->setBackgroundType(Home_btnMap, LE_WIDGET_BACKGROUND_NONE);
    Home_btnMap->fn->setBorderType(Home_btnMap, LE_WIDGET_BORDER_NONE);
    Home_btnMap->fn->setPressedImage(Home_btnMap, (leImage*)&figmaImg_iconMap);
    Home_btnMap->fn->setReleasedImage(Home_btnMap, (leImage*)&figmaImg_iconMap);
    Home_btnMap->fn->setPressedEventCallback(Home_btnMap, event_Home_btnMap_OnPressed);
    Home_panel_Shortcut_Bar->fn->addChild(Home_panel_Shortcut_Bar, (leWidget*)Home_btnMap);

    Home_btnLight = leButtonWidget_New();
    Home_btnLight->fn->setPosition(Home_btnLight, 67, 10);
    Home_btnLight->fn->setSize(Home_btnLight, 40, 40);
    Home_btnLight->fn->setBackgroundType(Home_btnLight, LE_WIDGET_BACKGROUND_NONE);
    Home_btnLight->fn->setBorderType(Home_btnLight, LE_WIDGET_BORDER_NONE);
    Home_btnLight->fn->setPressedImage(Home_btnLight, (leImage*)&figmaImg_iconLight);
    Home_btnLight->fn->setReleasedImage(Home_btnLight, (leImage*)&figmaImg_iconLight);
    Home_btnLight->fn->setPressedEventCallback(Home_btnLight, event_Home_btnLight_OnPressed);
    Home_panel_Shortcut_Bar->fn->addChild(Home_panel_Shortcut_Bar, (leWidget*)Home_btnLight);

    Home_image_imgEnergyFlow = leImageWidget_New();
    Home_image_imgEnergyFlow->fn->setPosition(Home_image_imgEnergyFlow, 280, 310);
    Home_image_imgEnergyFlow->fn->setSize(Home_image_imgEnergyFlow, 240, 30);
    Home_image_imgEnergyFlow->fn->setBackgroundType(Home_image_imgEnergyFlow, LE_WIDGET_BACKGROUND_NONE);
    Home_image_imgEnergyFlow->fn->setBorderType(Home_image_imgEnergyFlow, LE_WIDGET_BORDER_NONE);
    Home_image_imgEnergyFlow->fn->setImage(Home_image_imgEnergyFlow, (leImage*)&figmaImg_imgEnergyFlow);
    root2->fn->addChild(root2, (leWidget*)Home_image_imgEnergyFlow);

    Home_label_REGEN = leLabelWidget_New();
    Home_label_REGEN->fn->setPosition(Home_label_REGEN, 288, 319);
    Home_label_REGEN->fn->setSize(Home_label_REGEN, 34, 13);
    Home_label_REGEN->fn->setScheme(Home_label_REGEN, &text_chartreuse);
    Home_label_REGEN->fn->setBackgroundType(Home_label_REGEN, LE_WIDGET_BACKGROUND_NONE);
    Home_label_REGEN->fn->setVAlignment(Home_label_REGEN, LE_VALIGN_TOP);
    Home_label_REGEN->fn->setMargins(Home_label_REGEN, 0, 0, 0, 0);
    Home_label_REGEN->fn->setString(Home_label_REGEN, (leString*)&string_figmaStr_REGEN);
    root2->fn->addChild(root2, (leWidget*)Home_label_REGEN);

    Home_image_imgMeterTrack = leImageWidget_New();
    Home_image_imgMeterTrack->fn->setPosition(Home_image_imgMeterTrack, 328, 323);
    Home_image_imgMeterTrack->fn->setSize(Home_image_imgMeterTrack, 120, 4);
    Home_image_imgMeterTrack->fn->setBackgroundType(Home_image_imgMeterTrack, LE_WIDGET_BACKGROUND_NONE);
    Home_image_imgMeterTrack->fn->setBorderType(Home_image_imgMeterTrack, LE_WIDGET_BORDER_NONE);
    Home_image_imgMeterTrack->fn->setImage(Home_image_imgMeterTrack, (leImage*)&figmaImg_imgMeterTrack);
    root2->fn->addChild(root2, (leWidget*)Home_image_imgMeterTrack);

    Home_label_DISCHARGE = leLabelWidget_New();
    Home_label_DISCHARGE->fn->setPosition(Home_label_DISCHARGE, 458, 319);
    Home_label_DISCHARGE->fn->setSize(Home_label_DISCHARGE, 54, 13);
    Home_label_DISCHARGE->fn->setScheme(Home_label_DISCHARGE, &text_darkorange);
    Home_label_DISCHARGE->fn->setBackgroundType(Home_label_DISCHARGE, LE_WIDGET_BACKGROUND_NONE);
    Home_label_DISCHARGE->fn->setVAlignment(Home_label_DISCHARGE, LE_VALIGN_TOP);
    Home_label_DISCHARGE->fn->setMargins(Home_label_DISCHARGE, 0, 0, 0, 0);
    Home_label_DISCHARGE->fn->setString(Home_label_DISCHARGE, (leString*)&string_figmaStr_DISCHARGE);
    root2->fn->addChild(root2, (leWidget*)Home_label_DISCHARGE);

    Home_image_imgPowerTrack = leImageWidget_New();
    Home_image_imgPowerTrack->fn->setPosition(Home_image_imgPowerTrack, 40, 143);
    Home_image_imgPowerTrack->fn->setSize(Home_image_imgPowerTrack, 58, 215);
    Home_image_imgPowerTrack->fn->setBackgroundType(Home_image_imgPowerTrack, LE_WIDGET_BACKGROUND_NONE);
    Home_image_imgPowerTrack->fn->setBorderType(Home_image_imgPowerTrack, LE_WIDGET_BORDER_NONE);
    Home_image_imgPowerTrack->fn->setImage(Home_image_imgPowerTrack, (leImage*)&figmaImg_imgPowerTrack);
    root2->fn->addChild(root2, (leWidget*)Home_image_imgPowerTrack);

    Home_image_imgPowerProg = leImageWidget_New();
    Home_image_imgPowerProg->fn->setPosition(Home_image_imgPowerProg, 34, 141);
    Home_image_imgPowerProg->fn->setSize(Home_image_imgPowerProg, 70, 220);
    Home_image_imgPowerProg->fn->setBackgroundType(Home_image_imgPowerProg, LE_WIDGET_BACKGROUND_NONE);
    Home_image_imgPowerProg->fn->setBorderType(Home_image_imgPowerProg, LE_WIDGET_BORDER_NONE);
    Home_image_imgPowerProg->fn->setVAlignment(Home_image_imgPowerProg, LE_VALIGN_BOTTOM);
    Home_image_imgPowerProg->fn->setImage(Home_image_imgPowerProg, (leImage*)&PowerActiveTrack);
    root2->fn->addChild(root2, (leWidget*)Home_image_imgPowerProg);

    Home_image_imgBatTrack = leImageWidget_New();
    Home_image_imgBatTrack->fn->setPosition(Home_image_imgBatTrack, 703, 143);
    Home_image_imgBatTrack->fn->setSize(Home_image_imgBatTrack, 58, 215);
    Home_image_imgBatTrack->fn->setBackgroundType(Home_image_imgBatTrack, LE_WIDGET_BACKGROUND_NONE);
    Home_image_imgBatTrack->fn->setBorderType(Home_image_imgBatTrack, LE_WIDGET_BORDER_NONE);
    Home_image_imgBatTrack->fn->setImage(Home_image_imgBatTrack, (leImage*)&figmaImg_imgBatTrack);
    root2->fn->addChild(root2, (leWidget*)Home_image_imgBatTrack);

    Home_image_imgBatProg = leImageWidget_New();
    Home_image_imgBatProg->fn->setPosition(Home_image_imgBatProg, 697, 142);
    Home_image_imgBatProg->fn->setSize(Home_image_imgBatProg, 70, 220);
    Home_image_imgBatProg->fn->setBackgroundType(Home_image_imgBatProg, LE_WIDGET_BACKGROUND_NONE);
    Home_image_imgBatProg->fn->setBorderType(Home_image_imgBatProg, LE_WIDGET_BORDER_NONE);
    Home_image_imgBatProg->fn->setVAlignment(Home_image_imgBatProg, LE_VALIGN_BOTTOM);
    Home_image_imgBatProg->fn->setImage(Home_image_imgBatProg, (leImage*)&BatteryActiveTrack);
    root2->fn->addChild(root2, (leWidget*)Home_image_imgBatProg);

    Home_label_Battery = leLabelWidget_New();
    Home_label_Battery->fn->setPosition(Home_label_Battery, 669, 224);
    Home_label_Battery->fn->setSize(Home_label_Battery, 51, 16);
    Home_label_Battery->fn->setScheme(Home_label_Battery, &text_lightslategray);
    Home_label_Battery->fn->setBackgroundType(Home_label_Battery, LE_WIDGET_BACKGROUND_NONE);
    Home_label_Battery->fn->setVAlignment(Home_label_Battery, LE_VALIGN_TOP);
    Home_label_Battery->fn->setMargins(Home_label_Battery, 0, 0, 0, 0);
    Home_label_Battery->fn->setString(Home_label_Battery, (leString*)&string_figmaStr_Battery);
    root2->fn->addChild(root2, (leWidget*)Home_label_Battery);

    Home_label_0 = leLabelWidget_New();
    Home_label_0->fn->setPosition(Home_label_0, 721, 256);
    Home_label_0->fn->setSize(Home_label_0, 16, 18);
    Home_label_0->fn->setScheme(Home_label_0, &text_lightslategray);
    Home_label_0->fn->setBackgroundType(Home_label_0, LE_WIDGET_BACKGROUND_NONE);
    Home_label_0->fn->setHAlignment(Home_label_0, LE_HALIGN_CENTER);
    Home_label_0->fn->setVAlignment(Home_label_0, LE_VALIGN_TOP);
    Home_label_0->fn->setMargins(Home_label_0, 0, 0, 0, 0);
    Home_label_0->fn->setString(Home_label_0, (leString*)&string_figmaStr__Pct);
    root2->fn->addChild(root2, (leWidget*)Home_label_0);

    Home_label_BattValue = leLabelWidget_New();
    Home_label_BattValue->fn->setPosition(Home_label_BattValue, 650, 242);
    Home_label_BattValue->fn->setSize(Home_label_BattValue, 67, 35);
    Home_label_BattValue->fn->setScheme(Home_label_BattValue, &text_white);
    Home_label_BattValue->fn->setBackgroundType(Home_label_BattValue, LE_WIDGET_BACKGROUND_NONE);
    Home_label_BattValue->fn->setHAlignment(Home_label_BattValue, LE_HALIGN_RIGHT);
    Home_label_BattValue->fn->setMargins(Home_label_BattValue, 0, 0, 0, 0);
    Home_label_BattValue->fn->setString(Home_label_BattValue, (leString*)&string_figmaStr_72);
    root2->fn->addChild(root2, (leWidget*)Home_label_BattValue);

    Home_label_Power = leLabelWidget_New();
    Home_label_Power->fn->setPosition(Home_label_Power, 94, 224);
    Home_label_Power->fn->setSize(Home_label_Power, 41, 16);
    Home_label_Power->fn->setScheme(Home_label_Power, &text_lightslategray);
    Home_label_Power->fn->setBackgroundType(Home_label_Power, LE_WIDGET_BACKGROUND_NONE);
    Home_label_Power->fn->setHAlignment(Home_label_Power, LE_HALIGN_CENTER);
    Home_label_Power->fn->setVAlignment(Home_label_Power, LE_VALIGN_TOP);
    Home_label_Power->fn->setMargins(Home_label_Power, 0, 0, 0, 0);
    Home_label_Power->fn->setString(Home_label_Power, (leString*)&string_figmaStr_Power);
    root2->fn->addChild(root2, (leWidget*)Home_label_Power);

    Home_label_PowerValue = leLabelWidget_New();
    Home_label_PowerValue->fn->setPosition(Home_label_PowerValue, 95, 242);
    Home_label_PowerValue->fn->setSize(Home_label_PowerValue, 92, 35);
    Home_label_PowerValue->fn->setScheme(Home_label_PowerValue, &text_white);
    Home_label_PowerValue->fn->setBackgroundType(Home_label_PowerValue, LE_WIDGET_BACKGROUND_NONE);
    Home_label_PowerValue->fn->setMargins(Home_label_PowerValue, 0, 0, 0, 0);
    Home_label_PowerValue->fn->setString(Home_label_PowerValue, (leString*)&string_figmaStr_42_5);
    root2->fn->addChild(root2, (leWidget*)Home_label_PowerValue);

    Home_label_kW = leLabelWidget_New();
    Home_label_kW->fn->setPosition(Home_label_kW, 58, 256);
    Home_label_kW->fn->setSize(Home_label_kW, 25, 18);
    Home_label_kW->fn->setScheme(Home_label_kW, &text_lightslategray);
    Home_label_kW->fn->setBackgroundType(Home_label_kW, LE_WIDGET_BACKGROUND_NONE);
    Home_label_kW->fn->setHAlignment(Home_label_kW, LE_HALIGN_RIGHT);
    Home_label_kW->fn->setVAlignment(Home_label_kW, LE_VALIGN_TOP);
    Home_label_kW->fn->setMargins(Home_label_kW, 0, 0, 0, 0);
    Home_label_kW->fn->setString(Home_label_kW, (leString*)&string_figmaStr_kW);
    root2->fn->addChild(root2, (leWidget*)Home_label_kW);

    Home_lblGauge = leLabelWidget_New();
    Home_lblGauge->fn->setPosition(Home_lblGauge, 229, 180);
    Home_lblGauge->fn->setSize(Home_lblGauge, 332, 114);
    Home_lblGauge->fn->setScheme(Home_lblGauge, &text_white);
    Home_lblGauge->fn->setBackgroundType(Home_lblGauge, LE_WIDGET_BACKGROUND_NONE);
    Home_lblGauge->fn->setHAlignment(Home_lblGauge, LE_HALIGN_CENTER);
    Home_lblGauge->fn->setMargins(Home_lblGauge, 0, 0, 0, 0);
    Home_lblGauge->fn->setString(Home_lblGauge, (leString*)&string_figmaStr_124);
    root2->fn->addChild(root2, (leWidget*)Home_lblGauge);

    Home_label_MPH = leLabelWidget_New();
    Home_label_MPH->fn->setPosition(Home_label_MPH, 464, 154);
    Home_label_MPH->fn->setSize(Home_label_MPH, 58, 25);
    Home_label_MPH->fn->setScheme(Home_label_MPH, &text_deepskyblue);
    Home_label_MPH->fn->setBackgroundType(Home_label_MPH, LE_WIDGET_BACKGROUND_NONE);
    Home_label_MPH->fn->setVAlignment(Home_label_MPH, LE_VALIGN_TOP);
    Home_label_MPH->fn->setMargins(Home_label_MPH, 0, 0, 0, 0);
    Home_label_MPH->fn->setString(Home_label_MPH, (leString*)&string_figmaStr_KPH);
    root2->fn->addChild(root2, (leWidget*)Home_label_MPH);

    Home_panel_Battery_Temp = leWidget_New();
    Home_panel_Battery_Temp->fn->setPosition(Home_panel_Battery_Temp, 36, 378);
    Home_panel_Battery_Temp->fn->setSize(Home_panel_Battery_Temp, 54, 31);
    Home_panel_Battery_Temp->fn->setBackgroundType(Home_panel_Battery_Temp, LE_WIDGET_BACKGROUND_NONE);
    root2->fn->addChild(root2, (leWidget*)Home_panel_Battery_Temp);

    Home_label_Battery = leLabelWidget_New();
    Home_label_Battery->fn->setPosition(Home_label_Battery, 4, 2);
    Home_label_Battery->fn->setSize(Home_label_Battery, 42, 13);
    Home_label_Battery->fn->setScheme(Home_label_Battery, &text_lightslategray);
    Home_label_Battery->fn->setBackgroundType(Home_label_Battery, LE_WIDGET_BACKGROUND_NONE);
    Home_label_Battery->fn->setVAlignment(Home_label_Battery, LE_VALIGN_TOP);
    Home_label_Battery->fn->setMargins(Home_label_Battery, 0, 0, 0, 0);
    Home_label_Battery->fn->setString(Home_label_Battery, (leString*)&string_figmaStr_Battery_0);
    Home_panel_Battery_Temp->fn->addChild(Home_panel_Battery_Temp, (leWidget*)Home_label_Battery);

    Home_label_BattTemp = leLabelWidget_New();
    Home_label_BattTemp->fn->setPosition(Home_label_BattTemp, 4, 15);
    Home_label_BattTemp->fn->setSize(Home_label_BattTemp, 34, 18);
    Home_label_BattTemp->fn->setScheme(Home_label_BattTemp, &text_white);
    Home_label_BattTemp->fn->setBackgroundType(Home_label_BattTemp, LE_WIDGET_BACKGROUND_NONE);
    Home_label_BattTemp->fn->setVAlignment(Home_label_BattTemp, LE_VALIGN_TOP);
    Home_label_BattTemp->fn->setMargins(Home_label_BattTemp, 0, 0, 0, 0);
    Home_label_BattTemp->fn->setString(Home_label_BattTemp, (leString*)&string_figmaStr_38_C);
    Home_panel_Battery_Temp->fn->addChild(Home_panel_Battery_Temp, (leWidget*)Home_label_BattTemp);

    Home_label_Est_Range = leLabelWidget_New();
    Home_label_Est_Range->fn->setPosition(Home_label_Est_Range, 374, 374);
    Home_label_Est_Range->fn->setSize(Home_label_Est_Range, 60, 13);
    Home_label_Est_Range->fn->setScheme(Home_label_Est_Range, &text_lightslategray);
    Home_label_Est_Range->fn->setBackgroundType(Home_label_Est_Range, LE_WIDGET_BACKGROUND_NONE);
    Home_label_Est_Range->fn->setVAlignment(Home_label_Est_Range, LE_VALIGN_TOP);
    Home_label_Est_Range->fn->setMargins(Home_label_Est_Range, 0, 0, 0, 0);
    Home_label_Est_Range->fn->setString(Home_label_Est_Range, (leString*)&string_figmaStr_Est__Range);
    root2->fn->addChild(root2, (leWidget*)Home_label_Est_Range);

    Home_label_Range = leLabelWidget_New();
    Home_label_Range->fn->setPosition(Home_label_Range, 327, 387);
    Home_label_Range->fn->setSize(Home_label_Range, 100, 40);
    Home_label_Range->fn->setScheme(Home_label_Range, &text_white);
    Home_label_Range->fn->setBackgroundType(Home_label_Range, LE_WIDGET_BACKGROUND_NONE);
    Home_label_Range->fn->setHAlignment(Home_label_Range, LE_HALIGN_RIGHT);
    Home_label_Range->fn->setMargins(Home_label_Range, 0, 0, 0, 0);
    Home_label_Range->fn->setString(Home_label_Range, (leString*)&string_figmaStr_184);
    root2->fn->addChild(root2, (leWidget*)Home_label_Range);

    Home_label_KM = leLabelWidget_New();
    Home_label_KM->fn->setPosition(Home_label_KM, 435, 403);
    Home_label_KM->fn->setSize(Home_label_KM, 28, 21);
    Home_label_KM->fn->setScheme(Home_label_KM, &text_deepskyblue);
    Home_label_KM->fn->setBackgroundType(Home_label_KM, LE_WIDGET_BACKGROUND_NONE);
    Home_label_KM->fn->setVAlignment(Home_label_KM, LE_VALIGN_TOP);
    Home_label_KM->fn->setMargins(Home_label_KM, 0, 0, 0, 0);
    Home_label_KM->fn->setString(Home_label_KM, (leString*)&string_figmaStr_KM);
    root2->fn->addChild(root2, (leWidget*)Home_label_KM);

    Home_panel_Motor_Temp = leWidget_New();
    Home_panel_Motor_Temp->fn->setPosition(Home_panel_Motor_Temp, 735, 379);
    Home_panel_Motor_Temp->fn->setSize(Home_panel_Motor_Temp, 46, 31);
    Home_panel_Motor_Temp->fn->setBackgroundType(Home_panel_Motor_Temp, LE_WIDGET_BACKGROUND_NONE);
    root2->fn->addChild(root2, (leWidget*)Home_panel_Motor_Temp);

    Home_label_Motor = leLabelWidget_New();
    Home_label_Motor->fn->setPosition(Home_label_Motor, 12, 1);
    Home_label_Motor->fn->setSize(Home_label_Motor, 30, 13);
    Home_label_Motor->fn->setScheme(Home_label_Motor, &text_lightslategray);
    Home_label_Motor->fn->setBackgroundType(Home_label_Motor, LE_WIDGET_BACKGROUND_NONE);
    Home_label_Motor->fn->setVAlignment(Home_label_Motor, LE_VALIGN_TOP);
    Home_label_Motor->fn->setMargins(Home_label_Motor, 0, 0, 0, 0);
    Home_label_Motor->fn->setString(Home_label_Motor, (leString*)&string_figmaStr_Motor);
    Home_panel_Motor_Temp->fn->addChild(Home_panel_Motor_Temp, (leWidget*)Home_label_Motor);

    Home_label_MotorTempValue = leLabelWidget_New();
    Home_label_MotorTempValue->fn->setPosition(Home_label_MotorTempValue, 5, 14);
    Home_label_MotorTempValue->fn->setSize(Home_label_MotorTempValue, 37, 18);
    Home_label_MotorTempValue->fn->setScheme(Home_label_MotorTempValue, &text_white);
    Home_label_MotorTempValue->fn->setBackgroundType(Home_label_MotorTempValue, LE_WIDGET_BACKGROUND_NONE);
    Home_label_MotorTempValue->fn->setVAlignment(Home_label_MotorTempValue, LE_VALIGN_TOP);
    Home_label_MotorTempValue->fn->setMargins(Home_label_MotorTempValue, 0, 0, 0, 0);
    Home_label_MotorTempValue->fn->setString(Home_label_MotorTempValue, (leString*)&string_figmaStr_62_C);
    Home_panel_Motor_Temp->fn->addChild(Home_panel_Motor_Temp, (leWidget*)Home_label_MotorTempValue);

    Home_image_RegenBar = leImageWidget_New();
    Home_image_RegenBar->fn->setPosition(Home_image_RegenBar, 328, 323);
    Home_image_RegenBar->fn->setSize(Home_image_RegenBar, 60, 4);
    Home_image_RegenBar->fn->setBackgroundType(Home_image_RegenBar, LE_WIDGET_BACKGROUND_NONE);
    Home_image_RegenBar->fn->setBorderType(Home_image_RegenBar, LE_WIDGET_BORDER_NONE);
    Home_image_RegenBar->fn->setHAlignment(Home_image_RegenBar, LE_HALIGN_LEFT);
    Home_image_RegenBar->fn->setMargins(Home_image_RegenBar, 0, 4, 4, 4);
    Home_image_RegenBar->fn->setImage(Home_image_RegenBar, (leImage*)&imgregendischarge);
    root2->fn->addChild(root2, (leWidget*)Home_image_RegenBar);

    Home_image_DischargeBar = leImageWidget_New();
    Home_image_DischargeBar->fn->setPosition(Home_image_DischargeBar, 388, 323);
    Home_image_DischargeBar->fn->setSize(Home_image_DischargeBar, 60, 4);
    Home_image_DischargeBar->fn->setBackgroundType(Home_image_DischargeBar, LE_WIDGET_BACKGROUND_NONE);
    Home_image_DischargeBar->fn->setBorderType(Home_image_DischargeBar, LE_WIDGET_BORDER_NONE);
    Home_image_DischargeBar->fn->setHAlignment(Home_image_DischargeBar, LE_HALIGN_RIGHT);
    Home_image_DischargeBar->fn->setMargins(Home_image_DischargeBar, 0, 4, 0, 4);
    Home_image_DischargeBar->fn->setImage(Home_image_DischargeBar, (leImage*)&imgregendischarge);
    root2->fn->addChild(root2, (leWidget*)Home_image_DischargeBar);

    Home_touchPanel = leWidget_New();
    Home_touchPanel->fn->setPosition(Home_touchPanel, 115, 119);
    Home_touchPanel->fn->setSize(Home_touchPanel, 575, 260);
    Home_touchPanel->fn->setBackgroundType(Home_touchPanel, LE_WIDGET_BACKGROUND_NONE);
    root2->fn->addChild(root2, (leWidget*)Home_touchPanel);

    Home_imgMGS = leImageWidget_New();
    Home_imgMGS->fn->setPosition(Home_imgMGS, 680, 63);
    Home_imgMGS->fn->setSize(Home_imgMGS, 48, 40);
    Home_imgMGS->fn->setBackgroundType(Home_imgMGS, LE_WIDGET_BACKGROUND_NONE);
    Home_imgMGS->fn->setBorderType(Home_imgMGS, LE_WIDGET_BORDER_NONE);
    Home_imgMGS->fn->setHAlignment(Home_imgMGS, LE_HALIGN_LEFT);
    Home_imgMGS->fn->setImage(Home_imgMGS, (leImage*)&Image1);
    root2->fn->addChild(root2, (leWidget*)Home_imgMGS);

    Home_pnlMetrics = leWidget_New();
    Home_pnlMetrics->fn->setPosition(Home_pnlMetrics, 136, 342);
    Home_pnlMetrics->fn->setSize(Home_pnlMetrics, 120, 61);
    Home_pnlMetrics->fn->setBackgroundType(Home_pnlMetrics, LE_WIDGET_BACKGROUND_NONE);
    root2->fn->addChild(root2, (leWidget*)Home_pnlMetrics);

    Home_lblUpdatePct = leLabelWidget_New();
    Home_lblUpdatePct->fn->setPosition(Home_lblUpdatePct, 72, 0);
    Home_lblUpdatePct->fn->setSize(Home_lblUpdatePct, 45, 18);
    Home_lblUpdatePct->fn->setScheme(Home_lblUpdatePct, &text_lightslategray);
    Home_lblUpdatePct->fn->setBackgroundType(Home_lblUpdatePct, LE_WIDGET_BACKGROUND_NONE);
    Home_lblUpdatePct->fn->setMargins(Home_lblUpdatePct, 0, 0, 0, 0);
    Home_lblUpdatePct->fn->setString(Home_lblUpdatePct, (leString*)&string_figmaStr_042_8_mi);
    Home_pnlMetrics->fn->addChild(Home_pnlMetrics, (leWidget*)Home_lblUpdatePct);

    Home_lblDrawPct = leLabelWidget_New();
    Home_lblDrawPct->fn->setPosition(Home_lblDrawPct, 72, 21);
    Home_lblDrawPct->fn->setSize(Home_lblDrawPct, 45, 18);
    Home_lblDrawPct->fn->setScheme(Home_lblDrawPct, &text_lightslategray);
    Home_lblDrawPct->fn->setBackgroundType(Home_lblDrawPct, LE_WIDGET_BACKGROUND_NONE);
    Home_lblDrawPct->fn->setMargins(Home_lblDrawPct, 0, 0, 0, 0);
    Home_lblDrawPct->fn->setString(Home_lblDrawPct, (leString*)&string_figmaStr_042_8_mi);
    Home_pnlMetrics->fn->addChild(Home_pnlMetrics, (leWidget*)Home_lblDrawPct);

    Home_lblFPSValue = leLabelWidget_New();
    Home_lblFPSValue->fn->setPosition(Home_lblFPSValue, 72, 42);
    Home_lblFPSValue->fn->setSize(Home_lblFPSValue, 45, 18);
    Home_lblFPSValue->fn->setScheme(Home_lblFPSValue, &text_lightslategray);
    Home_lblFPSValue->fn->setBackgroundType(Home_lblFPSValue, LE_WIDGET_BACKGROUND_NONE);
    Home_lblFPSValue->fn->setMargins(Home_lblFPSValue, 0, 0, 0, 0);
    Home_lblFPSValue->fn->setString(Home_lblFPSValue, (leString*)&string_figmaStr_042_8_mi);
    Home_pnlMetrics->fn->addChild(Home_pnlMetrics, (leWidget*)Home_lblFPSValue);

    Home_lblUpdate = leLabelWidget_New();
    Home_lblUpdate->fn->setPosition(Home_lblUpdate, 0, 1);
    Home_lblUpdate->fn->setSize(Home_lblUpdate, 61, 18);
    Home_lblUpdate->fn->setScheme(Home_lblUpdate, &text_lightslategray);
    Home_lblUpdate->fn->setBackgroundType(Home_lblUpdate, LE_WIDGET_BACKGROUND_NONE);
    Home_lblUpdate->fn->setHAlignment(Home_lblUpdate, LE_HALIGN_RIGHT);
    Home_lblUpdate->fn->setMargins(Home_lblUpdate, 0, 0, 0, 0);
    Home_lblUpdate->fn->setString(Home_lblUpdate, (leString*)&string_strAnim);
    Home_pnlMetrics->fn->addChild(Home_pnlMetrics, (leWidget*)Home_lblUpdate);

    Home_lblDraw = leLabelWidget_New();
    Home_lblDraw->fn->setPosition(Home_lblDraw, 0, 22);
    Home_lblDraw->fn->setSize(Home_lblDraw, 60, 18);
    Home_lblDraw->fn->setScheme(Home_lblDraw, &text_lightslategray);
    Home_lblDraw->fn->setBackgroundType(Home_lblDraw, LE_WIDGET_BACKGROUND_NONE);
    Home_lblDraw->fn->setHAlignment(Home_lblDraw, LE_HALIGN_RIGHT);
    Home_lblDraw->fn->setMargins(Home_lblDraw, 0, 0, 0, 0);
    Home_lblDraw->fn->setString(Home_lblDraw, (leString*)&string_strCPUDraw);
    Home_pnlMetrics->fn->addChild(Home_pnlMetrics, (leWidget*)Home_lblDraw);

    Home_lblFPS = leLabelWidget_New();
    Home_lblFPS->fn->setPosition(Home_lblFPS, 0, 43);
    Home_lblFPS->fn->setSize(Home_lblFPS, 60, 18);
    Home_lblFPS->fn->setScheme(Home_lblFPS, &text_lightslategray);
    Home_lblFPS->fn->setBackgroundType(Home_lblFPS, LE_WIDGET_BACKGROUND_NONE);
    Home_lblFPS->fn->setHAlignment(Home_lblFPS, LE_HALIGN_RIGHT);
    Home_lblFPS->fn->setMargins(Home_lblFPS, 0, 0, 0, 0);
    Home_lblFPS->fn->setString(Home_lblFPS, (leString*)&string_strFPS);
    Home_pnlMetrics->fn->addChild(Home_pnlMetrics, (leWidget*)Home_lblFPS);

    leAddRootWidget(root2, 2);
    leSetLayerColorMode(2, LE_COLOR_MODE_RGBA_8888);

    Home_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_Home(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
    root1->fn->setSize(root1, root1->rect.width, root1->rect.height);
    root2->fn->setSize(root2, root2->rect.width, root2->rect.height);

    Home_OnUpdate(); // raise event
}

void screenHide_Home(void)
{
    Home_OnHide(); // raise event


    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    Home_BackgroundPanelBase = NULL;

    leRemoveRootWidget(root1, 1);
    leWidget_Delete(root1);
    root1 = NULL;

    leRemoveRootWidget(root2, 2);
    leWidget_Delete(root2);
    root2 = NULL;

    Home_panel_electric_moto_cluster = NULL;
    Home_panel_Status_Bar = NULL;
    Home_image_imgRegenFullBar = NULL;
    Home_imgRegenBar = NULL;
    Home_panel_Drive_Modes = NULL;
    Home_image_iconBattery = NULL;
    Home_image_iconTemp = NULL;
    Home_panel_Shortcut_Bar = NULL;
    Home_image_imgEnergyFlow = NULL;
    Home_label_REGEN = NULL;
    Home_image_imgMeterTrack = NULL;
    Home_label_DISCHARGE = NULL;
    Home_image_imgPowerTrack = NULL;
    Home_image_imgPowerProg = NULL;
    Home_image_imgBatTrack = NULL;
    Home_image_imgBatProg = NULL;
    Home_label_Battery = NULL;
    Home_label_0 = NULL;
    Home_label_BattValue = NULL;
    Home_label_Power = NULL;
    Home_label_PowerValue = NULL;
    Home_label_kW = NULL;
    Home_lblGauge = NULL;
    Home_label_MPH = NULL;
    Home_panel_Battery_Temp = NULL;
    Home_label_Est_Range = NULL;
    Home_label_Range = NULL;
    Home_label_KM = NULL;
    Home_panel_Motor_Temp = NULL;
    Home_image_RegenBar = NULL;
    Home_image_DischargeBar = NULL;
    Home_touchPanel = NULL;
    Home_imgMGS = NULL;
    Home_pnlMetrics = NULL;
    Home_panel_Status_Left = NULL;
    Home_panel_Status_Center = NULL;
    Home_panel_Status_Right = NULL;
    Home_image_iconLeftOn = NULL;
    Home_odo = NULL;
    Home_label_OdoValue = NULL;
    Home_image_iconHazard = NULL;
    Home_image_iconArrow = NULL;
    Home_image_iconCancel = NULL;
    Home_image_iconPlug = NULL;
    Home_label_TRIP_A = NULL;
    Home_label_TripValue = NULL;
    Home_label__Time = NULL;
    Home_image_iconRightOff = NULL;
    Home_image_imgEcoOff = NULL;
    Home_image_imgTourOff = NULL;
    Home_image_imgSportOff = NULL;
    Home_image_imgBoostOn = NULL;
    Home_label_ECO = NULL;
    Home_label_TOUR = NULL;
    Home_label_SPORT = NULL;
    Home_label_BOOST = NULL;
    Home_btnPhone = NULL;
    Home_btnCamera = NULL;
    Home_btnHome = NULL;
    Home_btnMusic = NULL;
    Home_btnMap = NULL;
    Home_btnLight = NULL;
    Home_label_Battery = NULL;
    Home_label_BattTemp = NULL;
    Home_label_Motor = NULL;
    Home_label_MotorTempValue = NULL;
    Home_lblUpdatePct = NULL;
    Home_lblDrawPct = NULL;
    Home_lblFPSValue = NULL;
    Home_lblUpdate = NULL;
    Home_lblDraw = NULL;
    Home_lblFPS = NULL;


    showing = LE_FALSE;
}

void screenDestroy_Home(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_Home(uint32_t lyrIdx)
{
    if(lyrIdx >= LE_LAYER_COUNT)
        return NULL;

    switch(lyrIdx)
    {
        case 0:
        {
            return root0;
        }
        case 1:
        {
            return root1;
        }
        case 2:
        {
            return root2;
        }
        default:
        {
            return NULL;
        }
    }
}


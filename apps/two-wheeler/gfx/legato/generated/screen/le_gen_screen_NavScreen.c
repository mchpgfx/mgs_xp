#include "gfx/legato/generated/screen/le_gen_screen_NavScreen.h"

// screen member widget declarations
static leWidget* root0;
static leWidget* root1;
static leWidget* root2;

leWidget* NavScreen_BackgroundPanelBase;
leDrawSurfaceWidget* NavScreen_drawNav;
leWidget* NavScreen_panel_electric_moto_cluster;
leWidget* NavScreen_panel_Status_Bar;
leImageWidget* NavScreen_image_imgRegenFullBar;
leImageWidget* NavScreen_imgRegenBar;
leImageWidget* NavScreen_image_iconBattery;
leImageWidget* NavScreen_image_iconTemp;
leWidget* NavScreen_panel_Shortcut_Bar;
leImageWidget* NavScreen_image_imgPowerTrack;
leImageWidget* NavScreen_image_imgPowerProg;
leImageWidget* NavScreen_image_imgBatTrack;
leImageWidget* NavScreen_image_imgBatProg;
leLabelWidget* NavScreen_label_Battery;
leLabelWidget* NavScreen_label_0;
leLabelWidget* NavScreen_label_BattValue;
leLabelWidget* NavScreen_label_Power;
leLabelWidget* NavScreen_label_PowerValue;
leLabelWidget* NavScreen_label_kW;
leWidget* NavScreen_panel_Battery_Temp;
leWidget* NavScreen_panel_Motor_Temp;
leWidget* NavScreen_StatPanel;
leLabelWidget* NavScreen_lblDistance;
leLabelWidget* NavScreen_lblStreet;
leImageWidget* NavScreen_imgDirection;
leWidget* NavScreen_panel_Drive_Modes;
leImageWidget* NavScreen_imgDirIcon;
leWidget* NavScreen_PanelRegenDischarge;
leWidget* NavScreen_RangePanel;
leWidget* NavScreen_touchPanel;
leImageWidget* NavScreen_imgMGS;
leWidget* NavScreen_pnlMetrics;
leWidget* NavScreen_panel_Status_Left;
leWidget* NavScreen_panel_Status_Center;
leWidget* NavScreen_panel_Status_Right;
leImageWidget* NavScreen_image_iconLeftOn;
leLabelWidget* NavScreen_odo;
leLabelWidget* NavScreen_label_OdoValue;
leImageWidget* NavScreen_image_iconHazard;
leImageWidget* NavScreen_image_iconArrow;
leImageWidget* NavScreen_image_iconCancel;
leImageWidget* NavScreen_image_iconPlug;
leLabelWidget* NavScreen_label_TRIP_A;
leLabelWidget* NavScreen_label_TripValue;
leLabelWidget* NavScreen_label__Time;
leImageWidget* NavScreen_image_iconRightOff;
leButtonWidget* NavScreen_btnPhone;
leButtonWidget* NavScreen_btnCamera;
leButtonWidget* NavScreen_btnHome;
leButtonWidget* NavScreen_btnMusic;
leButtonWidget* NavScreen_btnMap;
leButtonWidget* NavScreen_btnLight;
leLabelWidget* NavScreen_label_Battery;
leLabelWidget* NavScreen_label_BattTemp;
leLabelWidget* NavScreen_label_Motor;
leLabelWidget* NavScreen_label__MotorTempValue;
leLabelWidget* NavScreen_label_kph;
leLabelWidget* NavScreen_lblGauge;
leImageWidget* NavScreen_image_imgEcoOff;
leImageWidget* NavScreen_image_imgTourOff;
leImageWidget* NavScreen_image_imgSportOff;
leImageWidget* NavScreen_image_imgBoostOn;
leLabelWidget* NavScreen_label_ECO;
leLabelWidget* NavScreen_label_TOUR;
leLabelWidget* NavScreen_label_SPORT;
leLabelWidget* NavScreen_label_BOOST;
leImageWidget* NavScreen_image_imgMeterTrack;
leImageWidget* NavScreen_image_RegenBar;
leImageWidget* NavScreen_image_DischargeBar;
leImageWidget* NavScreen_image_imgEnergyFlow;
leLabelWidget* NavScreen_label_REGEN;
leLabelWidget* NavScreen_label_DISCHARGE;
leLabelWidget* NavScreen_label_Est_Range;
leLabelWidget* NavScreen_label_Range;
leLabelWidget* NavScreen_label_KM;
leLabelWidget* NavScreen_lblUpdatePct;
leLabelWidget* NavScreen_lblDrawPct;
leLabelWidget* NavScreen_lblFPSValue;
leLabelWidget* NavScreen_lblUpdate;
leLabelWidget* NavScreen_lblDraw;
leLabelWidget* NavScreen_lblFPS;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_NavScreen(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_NavScreen(void)
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

    NavScreen_BackgroundPanelBase = leWidget_New();
    NavScreen_BackgroundPanelBase->fn->setPosition(NavScreen_BackgroundPanelBase, 0, 0);
    NavScreen_BackgroundPanelBase->fn->setSize(NavScreen_BackgroundPanelBase, 800, 480);
    NavScreen_BackgroundPanelBase->fn->setScheme(NavScreen_BackgroundPanelBase, &GaugeScheme);
    root0->fn->addChild(root0, (leWidget*)NavScreen_BackgroundPanelBase);

    NavScreen_drawNav = leDrawSurfaceWidget_New();
    NavScreen_drawNav->fn->setPosition(NavScreen_drawNav, 175, 130);
    NavScreen_drawNav->fn->setSize(NavScreen_drawNav, 480, 250);
    NavScreen_drawNav->fn->setScheme(NavScreen_drawNav, &GaugeScheme);
    NavScreen_drawNav->fn->setDrawCallback(NavScreen_drawNav, event_NavScreen_drawNav_OnDraw);
    root0->fn->addChild(root0, (leWidget*)NavScreen_drawNav);

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

    NavScreen_panel_electric_moto_cluster = leWidget_New();
    NavScreen_panel_electric_moto_cluster->fn->setPosition(NavScreen_panel_electric_moto_cluster, 0, 0);
    NavScreen_panel_electric_moto_cluster->fn->setSize(NavScreen_panel_electric_moto_cluster, 800, 480);
    NavScreen_panel_electric_moto_cluster->fn->setScheme(NavScreen_panel_electric_moto_cluster, &ClearScheme);
    root2->fn->addChild(root2, (leWidget*)NavScreen_panel_electric_moto_cluster);

    NavScreen_panel_Status_Bar = leWidget_New();
    NavScreen_panel_Status_Bar->fn->setPosition(NavScreen_panel_Status_Bar, 0, 0);
    NavScreen_panel_Status_Bar->fn->setSize(NavScreen_panel_Status_Bar, 800, 50);
    NavScreen_panel_Status_Bar->fn->setBackgroundType(NavScreen_panel_Status_Bar, LE_WIDGET_BACKGROUND_NONE);
    root2->fn->addChild(root2, (leWidget*)NavScreen_panel_Status_Bar);

    NavScreen_panel_Status_Left = leWidget_New();
    NavScreen_panel_Status_Left->fn->setPosition(NavScreen_panel_Status_Left, 24, 9);
    NavScreen_panel_Status_Left->fn->setSize(NavScreen_panel_Status_Left, 124, 32);
    NavScreen_panel_Status_Left->fn->setBackgroundType(NavScreen_panel_Status_Left, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_panel_Status_Bar->fn->addChild(NavScreen_panel_Status_Bar, (leWidget*)NavScreen_panel_Status_Left);

    NavScreen_image_iconLeftOn = leImageWidget_New();
    NavScreen_image_iconLeftOn->fn->setPosition(NavScreen_image_iconLeftOn, 6, 7);
    NavScreen_image_iconLeftOn->fn->setSize(NavScreen_image_iconLeftOn, 20, 20);
    NavScreen_image_iconLeftOn->fn->setBackgroundType(NavScreen_image_iconLeftOn, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_image_iconLeftOn->fn->setBorderType(NavScreen_image_iconLeftOn, LE_WIDGET_BORDER_NONE);
    NavScreen_image_iconLeftOn->fn->setImage(NavScreen_image_iconLeftOn, (leImage*)&figmaImg_iconLeftOn);
    NavScreen_panel_Status_Left->fn->addChild(NavScreen_panel_Status_Left, (leWidget*)NavScreen_image_iconLeftOn);

    NavScreen_odo = leLabelWidget_New();
    NavScreen_odo->fn->setPosition(NavScreen_odo, 48, 1);
    NavScreen_odo->fn->setSize(NavScreen_odo, 26, 13);
    NavScreen_odo->fn->setScheme(NavScreen_odo, &text_darkslategray);
    NavScreen_odo->fn->setBackgroundType(NavScreen_odo, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_odo->fn->setMargins(NavScreen_odo, 0, 0, 0, 0);
    NavScreen_odo->fn->setString(NavScreen_odo, (leString*)&string_figmaStr_ODO);
    NavScreen_panel_Status_Left->fn->addChild(NavScreen_panel_Status_Left, (leWidget*)NavScreen_odo);

    NavScreen_label_OdoValue = leLabelWidget_New();
    NavScreen_label_OdoValue->fn->setPosition(NavScreen_label_OdoValue, 48, 14);
    NavScreen_label_OdoValue->fn->setSize(NavScreen_label_OdoValue, 76, 18);
    NavScreen_label_OdoValue->fn->setScheme(NavScreen_label_OdoValue, &text_lightslategray);
    NavScreen_label_OdoValue->fn->setBackgroundType(NavScreen_label_OdoValue, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_label_OdoValue->fn->setVAlignment(NavScreen_label_OdoValue, LE_VALIGN_TOP);
    NavScreen_label_OdoValue->fn->setMargins(NavScreen_label_OdoValue, 0, 0, 0, 0);
    NavScreen_label_OdoValue->fn->setString(NavScreen_label_OdoValue, (leString*)&string_figmaStr_001240_mi);
    NavScreen_panel_Status_Left->fn->addChild(NavScreen_panel_Status_Left, (leWidget*)NavScreen_label_OdoValue);

    NavScreen_panel_Status_Center = leWidget_New();
    NavScreen_panel_Status_Center->fn->setPosition(NavScreen_panel_Status_Center, 287, 9);
    NavScreen_panel_Status_Center->fn->setSize(NavScreen_panel_Status_Center, 164, 32);
    NavScreen_panel_Status_Center->fn->setBackgroundType(NavScreen_panel_Status_Center, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_panel_Status_Bar->fn->addChild(NavScreen_panel_Status_Bar, (leWidget*)NavScreen_panel_Status_Center);

    NavScreen_image_iconHazard = leImageWidget_New();
    NavScreen_image_iconHazard->fn->setPosition(NavScreen_image_iconHazard, 7, 9);
    NavScreen_image_iconHazard->fn->setSize(NavScreen_image_iconHazard, 20, 20);
    NavScreen_image_iconHazard->fn->setBackgroundType(NavScreen_image_iconHazard, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_image_iconHazard->fn->setBorderType(NavScreen_image_iconHazard, LE_WIDGET_BORDER_NONE);
    NavScreen_image_iconHazard->fn->setImage(NavScreen_image_iconHazard, (leImage*)&figmaImg_iconHazard);
    NavScreen_panel_Status_Center->fn->addChild(NavScreen_panel_Status_Center, (leWidget*)NavScreen_image_iconHazard);

    NavScreen_image_iconArrow = leImageWidget_New();
    NavScreen_image_iconArrow->fn->setPosition(NavScreen_image_iconArrow, 53, 7);
    NavScreen_image_iconArrow->fn->setSize(NavScreen_image_iconArrow, 20, 20);
    NavScreen_image_iconArrow->fn->setBackgroundType(NavScreen_image_iconArrow, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_image_iconArrow->fn->setBorderType(NavScreen_image_iconArrow, LE_WIDGET_BORDER_NONE);
    NavScreen_image_iconArrow->fn->setImage(NavScreen_image_iconArrow, (leImage*)&figmaImg_iconArrow);
    NavScreen_panel_Status_Center->fn->addChild(NavScreen_panel_Status_Center, (leWidget*)NavScreen_image_iconArrow);

    NavScreen_image_iconCancel = leImageWidget_New();
    NavScreen_image_iconCancel->fn->setPosition(NavScreen_image_iconCancel, 98, 8);
    NavScreen_image_iconCancel->fn->setSize(NavScreen_image_iconCancel, 20, 20);
    NavScreen_image_iconCancel->fn->setBackgroundType(NavScreen_image_iconCancel, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_image_iconCancel->fn->setBorderType(NavScreen_image_iconCancel, LE_WIDGET_BORDER_NONE);
    NavScreen_image_iconCancel->fn->setImage(NavScreen_image_iconCancel, (leImage*)&figmaImg_iconCancel);
    NavScreen_panel_Status_Center->fn->addChild(NavScreen_panel_Status_Center, (leWidget*)NavScreen_image_iconCancel);

    NavScreen_image_iconPlug = leImageWidget_New();
    NavScreen_image_iconPlug->fn->setPosition(NavScreen_image_iconPlug, 143, 8);
    NavScreen_image_iconPlug->fn->setSize(NavScreen_image_iconPlug, 20, 20);
    NavScreen_image_iconPlug->fn->setBackgroundType(NavScreen_image_iconPlug, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_image_iconPlug->fn->setBorderType(NavScreen_image_iconPlug, LE_WIDGET_BORDER_NONE);
    NavScreen_image_iconPlug->fn->setImage(NavScreen_image_iconPlug, (leImage*)&figmaImg_iconPlug);
    NavScreen_panel_Status_Center->fn->addChild(NavScreen_panel_Status_Center, (leWidget*)NavScreen_image_iconPlug);

    NavScreen_panel_Status_Right = leWidget_New();
    NavScreen_panel_Status_Right->fn->setPosition(NavScreen_panel_Status_Right, 590, 9);
    NavScreen_panel_Status_Right->fn->setSize(NavScreen_panel_Status_Right, 193, 32);
    NavScreen_panel_Status_Right->fn->setBackgroundType(NavScreen_panel_Status_Right, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_panel_Status_Bar->fn->addChild(NavScreen_panel_Status_Bar, (leWidget*)NavScreen_panel_Status_Right);

    NavScreen_label_TRIP_A = leLabelWidget_New();
    NavScreen_label_TRIP_A->fn->setPosition(NavScreen_label_TRIP_A, 23, 1);
    NavScreen_label_TRIP_A->fn->setSize(NavScreen_label_TRIP_A, 45, 13);
    NavScreen_label_TRIP_A->fn->setScheme(NavScreen_label_TRIP_A, &text_darkslategray);
    NavScreen_label_TRIP_A->fn->setBackgroundType(NavScreen_label_TRIP_A, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_label_TRIP_A->fn->setHAlignment(NavScreen_label_TRIP_A, LE_HALIGN_RIGHT);
    NavScreen_label_TRIP_A->fn->setMargins(NavScreen_label_TRIP_A, 0, 0, 0, 0);
    NavScreen_label_TRIP_A->fn->setString(NavScreen_label_TRIP_A, (leString*)&string_figmaStr_TRIP_A);
    NavScreen_panel_Status_Right->fn->addChild(NavScreen_panel_Status_Right, (leWidget*)NavScreen_label_TRIP_A);

    NavScreen_label_TripValue = leLabelWidget_New();
    NavScreen_label_TripValue->fn->setPosition(NavScreen_label_TripValue, 0, 14);
    NavScreen_label_TripValue->fn->setSize(NavScreen_label_TripValue, 68, 18);
    NavScreen_label_TripValue->fn->setScheme(NavScreen_label_TripValue, &text_lightslategray);
    NavScreen_label_TripValue->fn->setBackgroundType(NavScreen_label_TripValue, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_label_TripValue->fn->setHAlignment(NavScreen_label_TripValue, LE_HALIGN_RIGHT);
    NavScreen_label_TripValue->fn->setVAlignment(NavScreen_label_TripValue, LE_VALIGN_TOP);
    NavScreen_label_TripValue->fn->setMargins(NavScreen_label_TripValue, 0, 0, 0, 0);
    NavScreen_label_TripValue->fn->setString(NavScreen_label_TripValue, (leString*)&string_figmaStr_042_8_mi);
    NavScreen_panel_Status_Right->fn->addChild(NavScreen_panel_Status_Right, (leWidget*)NavScreen_label_TripValue);

    NavScreen_label__Time = leLabelWidget_New();
    NavScreen_label__Time->fn->setPosition(NavScreen_label__Time, 84, 5);
    NavScreen_label__Time->fn->setSize(NavScreen_label__Time, 54, 23);
    NavScreen_label__Time->fn->setScheme(NavScreen_label__Time, &text_white);
    NavScreen_label__Time->fn->setBackgroundType(NavScreen_label__Time, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_label__Time->fn->setVAlignment(NavScreen_label__Time, LE_VALIGN_TOP);
    NavScreen_label__Time->fn->setMargins(NavScreen_label__Time, 0, 0, 0, 0);
    NavScreen_label__Time->fn->setString(NavScreen_label__Time, (leString*)&string_figmaStr_20_45);
    NavScreen_panel_Status_Right->fn->addChild(NavScreen_panel_Status_Right, (leWidget*)NavScreen_label__Time);

    NavScreen_image_iconRightOff = leImageWidget_New();
    NavScreen_image_iconRightOff->fn->setPosition(NavScreen_image_iconRightOff, 164, 6);
    NavScreen_image_iconRightOff->fn->setSize(NavScreen_image_iconRightOff, 20, 20);
    NavScreen_image_iconRightOff->fn->setBackgroundType(NavScreen_image_iconRightOff, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_image_iconRightOff->fn->setBorderType(NavScreen_image_iconRightOff, LE_WIDGET_BORDER_NONE);
    NavScreen_image_iconRightOff->fn->setImage(NavScreen_image_iconRightOff, (leImage*)&figmaImg_iconRightOff);
    NavScreen_panel_Status_Right->fn->addChild(NavScreen_panel_Status_Right, (leWidget*)NavScreen_image_iconRightOff);

    NavScreen_image_imgRegenFullBar = leImageWidget_New();
    NavScreen_image_imgRegenFullBar->fn->setPosition(NavScreen_image_imgRegenFullBar, 0, 80);
    NavScreen_image_imgRegenFullBar->fn->setSize(NavScreen_image_imgRegenFullBar, 10, 320);
    NavScreen_image_imgRegenFullBar->fn->setBackgroundType(NavScreen_image_imgRegenFullBar, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_image_imgRegenFullBar->fn->setBorderType(NavScreen_image_imgRegenFullBar, LE_WIDGET_BORDER_NONE);
    NavScreen_image_imgRegenFullBar->fn->setImage(NavScreen_image_imgRegenFullBar, (leImage*)&figmaImg_imgRegenFullBar);
    root2->fn->addChild(root2, (leWidget*)NavScreen_image_imgRegenFullBar);

    NavScreen_imgRegenBar = leImageWidget_New();
    NavScreen_imgRegenBar->fn->setPosition(NavScreen_imgRegenBar, 0, 270);
    NavScreen_imgRegenBar->fn->setSize(NavScreen_imgRegenBar, 25, 145);
    NavScreen_imgRegenBar->fn->setBackgroundType(NavScreen_imgRegenBar, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_imgRegenBar->fn->setBorderType(NavScreen_imgRegenBar, LE_WIDGET_BORDER_NONE);
    NavScreen_imgRegenBar->fn->setImage(NavScreen_imgRegenBar, (leImage*)&figmaImg_imgRegenBar);
    root2->fn->addChild(root2, (leWidget*)NavScreen_imgRegenBar);

    NavScreen_image_iconBattery = leImageWidget_New();
    NavScreen_image_iconBattery->fn->setPosition(NavScreen_image_iconBattery, 477, 22);
    NavScreen_image_iconBattery->fn->setSize(NavScreen_image_iconBattery, 23, 15);
    NavScreen_image_iconBattery->fn->setBackgroundType(NavScreen_image_iconBattery, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_image_iconBattery->fn->setBorderType(NavScreen_image_iconBattery, LE_WIDGET_BORDER_NONE);
    NavScreen_image_iconBattery->fn->setImage(NavScreen_image_iconBattery, (leImage*)&figmaImg_iconBattery);
    root2->fn->addChild(root2, (leWidget*)NavScreen_image_iconBattery);

    NavScreen_image_iconTemp = leImageWidget_New();
    NavScreen_image_iconTemp->fn->setPosition(NavScreen_image_iconTemp, 515, 18);
    NavScreen_image_iconTemp->fn->setSize(NavScreen_image_iconTemp, 20, 20);
    NavScreen_image_iconTemp->fn->setBackgroundType(NavScreen_image_iconTemp, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_image_iconTemp->fn->setBorderType(NavScreen_image_iconTemp, LE_WIDGET_BORDER_NONE);
    NavScreen_image_iconTemp->fn->setImage(NavScreen_image_iconTemp, (leImage*)&figmaImg_iconTemp);
    root2->fn->addChild(root2, (leWidget*)NavScreen_image_iconTemp);

    NavScreen_panel_Shortcut_Bar = leWidget_New();
    NavScreen_panel_Shortcut_Bar->fn->setPosition(NavScreen_panel_Shortcut_Bar, 0, 430);
    NavScreen_panel_Shortcut_Bar->fn->setSize(NavScreen_panel_Shortcut_Bar, 800, 50);
    NavScreen_panel_Shortcut_Bar->fn->setScheme(NavScreen_panel_Shortcut_Bar, &GrayScheme);
    root2->fn->addChild(root2, (leWidget*)NavScreen_panel_Shortcut_Bar);

    NavScreen_btnPhone = leButtonWidget_New();
    NavScreen_btnPhone->fn->setPosition(NavScreen_btnPhone, 570, 10);
    NavScreen_btnPhone->fn->setSize(NavScreen_btnPhone, 40, 40);
    NavScreen_btnPhone->fn->setBackgroundType(NavScreen_btnPhone, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_btnPhone->fn->setBorderType(NavScreen_btnPhone, LE_WIDGET_BORDER_NONE);
    NavScreen_btnPhone->fn->setPressedImage(NavScreen_btnPhone, (leImage*)&figmaImg_iconPhone);
    NavScreen_btnPhone->fn->setReleasedImage(NavScreen_btnPhone, (leImage*)&figmaImg_iconPhone);
    NavScreen_btnPhone->fn->setPressedEventCallback(NavScreen_btnPhone, event_NavScreen_btnPhone_OnPressed);
    NavScreen_panel_Shortcut_Bar->fn->addChild(NavScreen_panel_Shortcut_Bar, (leWidget*)NavScreen_btnPhone);

    NavScreen_btnCamera = leButtonWidget_New();
    NavScreen_btnCamera->fn->setPosition(NavScreen_btnCamera, 444, 10);
    NavScreen_btnCamera->fn->setSize(NavScreen_btnCamera, 40, 40);
    NavScreen_btnCamera->fn->setBackgroundType(NavScreen_btnCamera, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_btnCamera->fn->setBorderType(NavScreen_btnCamera, LE_WIDGET_BORDER_NONE);
    NavScreen_btnCamera->fn->setPressedImage(NavScreen_btnCamera, (leImage*)&figmaImg_iconCamera);
    NavScreen_btnCamera->fn->setReleasedImage(NavScreen_btnCamera, (leImage*)&figmaImg_iconCamera);
    NavScreen_btnCamera->fn->setPressedEventCallback(NavScreen_btnCamera, event_NavScreen_btnCamera_OnPressed);
    NavScreen_panel_Shortcut_Bar->fn->addChild(NavScreen_panel_Shortcut_Bar, (leWidget*)NavScreen_btnCamera);

    NavScreen_btnHome = leButtonWidget_New();
    NavScreen_btnHome->fn->setPosition(NavScreen_btnHome, 693, 10);
    NavScreen_btnHome->fn->setSize(NavScreen_btnHome, 40, 40);
    NavScreen_btnHome->fn->setBackgroundType(NavScreen_btnHome, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_btnHome->fn->setBorderType(NavScreen_btnHome, LE_WIDGET_BORDER_NONE);
    NavScreen_btnHome->fn->setPressedImage(NavScreen_btnHome, (leImage*)&figmaImg_iconHome);
    NavScreen_btnHome->fn->setReleasedImage(NavScreen_btnHome, (leImage*)&figmaImg_iconHome);
    NavScreen_btnHome->fn->setPressedEventCallback(NavScreen_btnHome, event_NavScreen_btnHome_OnPressed);
    NavScreen_panel_Shortcut_Bar->fn->addChild(NavScreen_panel_Shortcut_Bar, (leWidget*)NavScreen_btnHome);

    NavScreen_btnMusic = leButtonWidget_New();
    NavScreen_btnMusic->fn->setPosition(NavScreen_btnMusic, 191, 10);
    NavScreen_btnMusic->fn->setSize(NavScreen_btnMusic, 40, 40);
    NavScreen_btnMusic->fn->setBackgroundType(NavScreen_btnMusic, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_btnMusic->fn->setBorderType(NavScreen_btnMusic, LE_WIDGET_BORDER_NONE);
    NavScreen_btnMusic->fn->setPressedImage(NavScreen_btnMusic, (leImage*)&figmaImg_iconMusic);
    NavScreen_btnMusic->fn->setReleasedImage(NavScreen_btnMusic, (leImage*)&figmaImg_iconMusic);
    NavScreen_btnMusic->fn->setPressedEventCallback(NavScreen_btnMusic, event_NavScreen_btnMusic_OnPressed);
    NavScreen_panel_Shortcut_Bar->fn->addChild(NavScreen_panel_Shortcut_Bar, (leWidget*)NavScreen_btnMusic);

    NavScreen_btnMap = leButtonWidget_New();
    NavScreen_btnMap->fn->setPosition(NavScreen_btnMap, 317, 10);
    NavScreen_btnMap->fn->setSize(NavScreen_btnMap, 40, 40);
    NavScreen_btnMap->fn->setBackgroundType(NavScreen_btnMap, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_btnMap->fn->setBorderType(NavScreen_btnMap, LE_WIDGET_BORDER_NONE);
    NavScreen_btnMap->fn->setPressedImage(NavScreen_btnMap, (leImage*)&figmaImg_iconMap);
    NavScreen_btnMap->fn->setReleasedImage(NavScreen_btnMap, (leImage*)&figmaImg_iconMap);
    NavScreen_btnMap->fn->setPressedEventCallback(NavScreen_btnMap, event_NavScreen_btnMap_OnPressed);
    NavScreen_panel_Shortcut_Bar->fn->addChild(NavScreen_panel_Shortcut_Bar, (leWidget*)NavScreen_btnMap);

    NavScreen_btnLight = leButtonWidget_New();
    NavScreen_btnLight->fn->setPosition(NavScreen_btnLight, 67, 10);
    NavScreen_btnLight->fn->setSize(NavScreen_btnLight, 40, 40);
    NavScreen_btnLight->fn->setBackgroundType(NavScreen_btnLight, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_btnLight->fn->setBorderType(NavScreen_btnLight, LE_WIDGET_BORDER_NONE);
    NavScreen_btnLight->fn->setPressedImage(NavScreen_btnLight, (leImage*)&figmaImg_iconLight);
    NavScreen_btnLight->fn->setReleasedImage(NavScreen_btnLight, (leImage*)&figmaImg_iconLight);
    NavScreen_btnLight->fn->setPressedEventCallback(NavScreen_btnLight, event_NavScreen_btnLight_OnPressed);
    NavScreen_panel_Shortcut_Bar->fn->addChild(NavScreen_panel_Shortcut_Bar, (leWidget*)NavScreen_btnLight);

    NavScreen_image_imgPowerTrack = leImageWidget_New();
    NavScreen_image_imgPowerTrack->fn->setPosition(NavScreen_image_imgPowerTrack, 40, 143);
    NavScreen_image_imgPowerTrack->fn->setSize(NavScreen_image_imgPowerTrack, 58, 215);
    NavScreen_image_imgPowerTrack->fn->setBackgroundType(NavScreen_image_imgPowerTrack, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_image_imgPowerTrack->fn->setBorderType(NavScreen_image_imgPowerTrack, LE_WIDGET_BORDER_NONE);
    NavScreen_image_imgPowerTrack->fn->setImage(NavScreen_image_imgPowerTrack, (leImage*)&figmaImg_imgPowerTrack);
    root2->fn->addChild(root2, (leWidget*)NavScreen_image_imgPowerTrack);

    NavScreen_image_imgPowerProg = leImageWidget_New();
    NavScreen_image_imgPowerProg->fn->setPosition(NavScreen_image_imgPowerProg, 34, 141);
    NavScreen_image_imgPowerProg->fn->setSize(NavScreen_image_imgPowerProg, 70, 220);
    NavScreen_image_imgPowerProg->fn->setBackgroundType(NavScreen_image_imgPowerProg, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_image_imgPowerProg->fn->setBorderType(NavScreen_image_imgPowerProg, LE_WIDGET_BORDER_NONE);
    NavScreen_image_imgPowerProg->fn->setVAlignment(NavScreen_image_imgPowerProg, LE_VALIGN_BOTTOM);
    NavScreen_image_imgPowerProg->fn->setImage(NavScreen_image_imgPowerProg, (leImage*)&PowerActiveTrack);
    root2->fn->addChild(root2, (leWidget*)NavScreen_image_imgPowerProg);

    NavScreen_image_imgBatTrack = leImageWidget_New();
    NavScreen_image_imgBatTrack->fn->setPosition(NavScreen_image_imgBatTrack, 703, 143);
    NavScreen_image_imgBatTrack->fn->setSize(NavScreen_image_imgBatTrack, 58, 215);
    NavScreen_image_imgBatTrack->fn->setBackgroundType(NavScreen_image_imgBatTrack, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_image_imgBatTrack->fn->setBorderType(NavScreen_image_imgBatTrack, LE_WIDGET_BORDER_NONE);
    NavScreen_image_imgBatTrack->fn->setImage(NavScreen_image_imgBatTrack, (leImage*)&figmaImg_imgBatTrack);
    root2->fn->addChild(root2, (leWidget*)NavScreen_image_imgBatTrack);

    NavScreen_image_imgBatProg = leImageWidget_New();
    NavScreen_image_imgBatProg->fn->setPosition(NavScreen_image_imgBatProg, 697, 142);
    NavScreen_image_imgBatProg->fn->setSize(NavScreen_image_imgBatProg, 70, 220);
    NavScreen_image_imgBatProg->fn->setBackgroundType(NavScreen_image_imgBatProg, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_image_imgBatProg->fn->setBorderType(NavScreen_image_imgBatProg, LE_WIDGET_BORDER_NONE);
    NavScreen_image_imgBatProg->fn->setVAlignment(NavScreen_image_imgBatProg, LE_VALIGN_BOTTOM);
    NavScreen_image_imgBatProg->fn->setImage(NavScreen_image_imgBatProg, (leImage*)&BatteryActiveTrack);
    root2->fn->addChild(root2, (leWidget*)NavScreen_image_imgBatProg);

    NavScreen_label_Battery = leLabelWidget_New();
    NavScreen_label_Battery->fn->setPosition(NavScreen_label_Battery, 669, 224);
    NavScreen_label_Battery->fn->setSize(NavScreen_label_Battery, 51, 16);
    NavScreen_label_Battery->fn->setScheme(NavScreen_label_Battery, &text_lightslategray);
    NavScreen_label_Battery->fn->setBackgroundType(NavScreen_label_Battery, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_label_Battery->fn->setVAlignment(NavScreen_label_Battery, LE_VALIGN_TOP);
    NavScreen_label_Battery->fn->setMargins(NavScreen_label_Battery, 0, 0, 0, 0);
    NavScreen_label_Battery->fn->setString(NavScreen_label_Battery, (leString*)&string_figmaStr_Battery);
    root2->fn->addChild(root2, (leWidget*)NavScreen_label_Battery);

    NavScreen_label_0 = leLabelWidget_New();
    NavScreen_label_0->fn->setPosition(NavScreen_label_0, 721, 256);
    NavScreen_label_0->fn->setSize(NavScreen_label_0, 16, 18);
    NavScreen_label_0->fn->setScheme(NavScreen_label_0, &text_lightslategray);
    NavScreen_label_0->fn->setBackgroundType(NavScreen_label_0, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_label_0->fn->setHAlignment(NavScreen_label_0, LE_HALIGN_CENTER);
    NavScreen_label_0->fn->setVAlignment(NavScreen_label_0, LE_VALIGN_TOP);
    NavScreen_label_0->fn->setMargins(NavScreen_label_0, 0, 0, 0, 0);
    NavScreen_label_0->fn->setString(NavScreen_label_0, (leString*)&string_figmaStr__Pct);
    root2->fn->addChild(root2, (leWidget*)NavScreen_label_0);

    NavScreen_label_BattValue = leLabelWidget_New();
    NavScreen_label_BattValue->fn->setPosition(NavScreen_label_BattValue, 650, 242);
    NavScreen_label_BattValue->fn->setSize(NavScreen_label_BattValue, 67, 35);
    NavScreen_label_BattValue->fn->setScheme(NavScreen_label_BattValue, &text_white);
    NavScreen_label_BattValue->fn->setBackgroundType(NavScreen_label_BattValue, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_label_BattValue->fn->setHAlignment(NavScreen_label_BattValue, LE_HALIGN_RIGHT);
    NavScreen_label_BattValue->fn->setMargins(NavScreen_label_BattValue, 0, 0, 0, 0);
    NavScreen_label_BattValue->fn->setString(NavScreen_label_BattValue, (leString*)&string_figmaStr_72);
    root2->fn->addChild(root2, (leWidget*)NavScreen_label_BattValue);

    NavScreen_label_Power = leLabelWidget_New();
    NavScreen_label_Power->fn->setPosition(NavScreen_label_Power, 94, 224);
    NavScreen_label_Power->fn->setSize(NavScreen_label_Power, 41, 16);
    NavScreen_label_Power->fn->setScheme(NavScreen_label_Power, &text_lightslategray);
    NavScreen_label_Power->fn->setBackgroundType(NavScreen_label_Power, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_label_Power->fn->setHAlignment(NavScreen_label_Power, LE_HALIGN_CENTER);
    NavScreen_label_Power->fn->setVAlignment(NavScreen_label_Power, LE_VALIGN_TOP);
    NavScreen_label_Power->fn->setMargins(NavScreen_label_Power, 0, 0, 0, 0);
    NavScreen_label_Power->fn->setString(NavScreen_label_Power, (leString*)&string_figmaStr_Power);
    root2->fn->addChild(root2, (leWidget*)NavScreen_label_Power);

    NavScreen_label_PowerValue = leLabelWidget_New();
    NavScreen_label_PowerValue->fn->setPosition(NavScreen_label_PowerValue, 95, 242);
    NavScreen_label_PowerValue->fn->setSize(NavScreen_label_PowerValue, 92, 35);
    NavScreen_label_PowerValue->fn->setScheme(NavScreen_label_PowerValue, &text_white);
    NavScreen_label_PowerValue->fn->setBackgroundType(NavScreen_label_PowerValue, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_label_PowerValue->fn->setMargins(NavScreen_label_PowerValue, 0, 0, 0, 0);
    NavScreen_label_PowerValue->fn->setString(NavScreen_label_PowerValue, (leString*)&string_figmaStr_42_5);
    root2->fn->addChild(root2, (leWidget*)NavScreen_label_PowerValue);

    NavScreen_label_kW = leLabelWidget_New();
    NavScreen_label_kW->fn->setPosition(NavScreen_label_kW, 58, 256);
    NavScreen_label_kW->fn->setSize(NavScreen_label_kW, 25, 18);
    NavScreen_label_kW->fn->setScheme(NavScreen_label_kW, &text_lightslategray);
    NavScreen_label_kW->fn->setBackgroundType(NavScreen_label_kW, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_label_kW->fn->setHAlignment(NavScreen_label_kW, LE_HALIGN_RIGHT);
    NavScreen_label_kW->fn->setVAlignment(NavScreen_label_kW, LE_VALIGN_TOP);
    NavScreen_label_kW->fn->setMargins(NavScreen_label_kW, 0, 0, 0, 0);
    NavScreen_label_kW->fn->setString(NavScreen_label_kW, (leString*)&string_figmaStr_kW);
    root2->fn->addChild(root2, (leWidget*)NavScreen_label_kW);

    NavScreen_panel_Battery_Temp = leWidget_New();
    NavScreen_panel_Battery_Temp->fn->setPosition(NavScreen_panel_Battery_Temp, 35, 378);
    NavScreen_panel_Battery_Temp->fn->setSize(NavScreen_panel_Battery_Temp, 54, 31);
    NavScreen_panel_Battery_Temp->fn->setBackgroundType(NavScreen_panel_Battery_Temp, LE_WIDGET_BACKGROUND_NONE);
    root2->fn->addChild(root2, (leWidget*)NavScreen_panel_Battery_Temp);

    NavScreen_label_Battery = leLabelWidget_New();
    NavScreen_label_Battery->fn->setPosition(NavScreen_label_Battery, 5, 2);
    NavScreen_label_Battery->fn->setSize(NavScreen_label_Battery, 42, 13);
    NavScreen_label_Battery->fn->setScheme(NavScreen_label_Battery, &text_lightslategray);
    NavScreen_label_Battery->fn->setBackgroundType(NavScreen_label_Battery, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_label_Battery->fn->setVAlignment(NavScreen_label_Battery, LE_VALIGN_TOP);
    NavScreen_label_Battery->fn->setMargins(NavScreen_label_Battery, 0, 0, 0, 0);
    NavScreen_label_Battery->fn->setString(NavScreen_label_Battery, (leString*)&string_figmaStr_Battery_0);
    NavScreen_panel_Battery_Temp->fn->addChild(NavScreen_panel_Battery_Temp, (leWidget*)NavScreen_label_Battery);

    NavScreen_label_BattTemp = leLabelWidget_New();
    NavScreen_label_BattTemp->fn->setPosition(NavScreen_label_BattTemp, 5, 15);
    NavScreen_label_BattTemp->fn->setSize(NavScreen_label_BattTemp, 34, 18);
    NavScreen_label_BattTemp->fn->setScheme(NavScreen_label_BattTemp, &text_white);
    NavScreen_label_BattTemp->fn->setBackgroundType(NavScreen_label_BattTemp, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_label_BattTemp->fn->setVAlignment(NavScreen_label_BattTemp, LE_VALIGN_TOP);
    NavScreen_label_BattTemp->fn->setMargins(NavScreen_label_BattTemp, 0, 0, 0, 0);
    NavScreen_label_BattTemp->fn->setString(NavScreen_label_BattTemp, (leString*)&string_figmaStr_38_C);
    NavScreen_panel_Battery_Temp->fn->addChild(NavScreen_panel_Battery_Temp, (leWidget*)NavScreen_label_BattTemp);

    NavScreen_panel_Motor_Temp = leWidget_New();
    NavScreen_panel_Motor_Temp->fn->setPosition(NavScreen_panel_Motor_Temp, 737, 379);
    NavScreen_panel_Motor_Temp->fn->setSize(NavScreen_panel_Motor_Temp, 46, 31);
    NavScreen_panel_Motor_Temp->fn->setBackgroundType(NavScreen_panel_Motor_Temp, LE_WIDGET_BACKGROUND_NONE);
    root2->fn->addChild(root2, (leWidget*)NavScreen_panel_Motor_Temp);

    NavScreen_label_Motor = leLabelWidget_New();
    NavScreen_label_Motor->fn->setPosition(NavScreen_label_Motor, 10, 1);
    NavScreen_label_Motor->fn->setSize(NavScreen_label_Motor, 30, 13);
    NavScreen_label_Motor->fn->setScheme(NavScreen_label_Motor, &text_lightslategray);
    NavScreen_label_Motor->fn->setBackgroundType(NavScreen_label_Motor, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_label_Motor->fn->setVAlignment(NavScreen_label_Motor, LE_VALIGN_TOP);
    NavScreen_label_Motor->fn->setMargins(NavScreen_label_Motor, 0, 0, 0, 0);
    NavScreen_label_Motor->fn->setString(NavScreen_label_Motor, (leString*)&string_figmaStr_Motor);
    NavScreen_panel_Motor_Temp->fn->addChild(NavScreen_panel_Motor_Temp, (leWidget*)NavScreen_label_Motor);

    NavScreen_label__MotorTempValue = leLabelWidget_New();
    NavScreen_label__MotorTempValue->fn->setPosition(NavScreen_label__MotorTempValue, 3, 14);
    NavScreen_label__MotorTempValue->fn->setSize(NavScreen_label__MotorTempValue, 37, 18);
    NavScreen_label__MotorTempValue->fn->setScheme(NavScreen_label__MotorTempValue, &text_white);
    NavScreen_label__MotorTempValue->fn->setBackgroundType(NavScreen_label__MotorTempValue, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_label__MotorTempValue->fn->setVAlignment(NavScreen_label__MotorTempValue, LE_VALIGN_TOP);
    NavScreen_label__MotorTempValue->fn->setMargins(NavScreen_label__MotorTempValue, 0, 0, 0, 0);
    NavScreen_label__MotorTempValue->fn->setString(NavScreen_label__MotorTempValue, (leString*)&string_figmaStr_62_C);
    NavScreen_panel_Motor_Temp->fn->addChild(NavScreen_panel_Motor_Temp, (leWidget*)NavScreen_label__MotorTempValue);

    NavScreen_StatPanel = leWidget_New();
    NavScreen_StatPanel->fn->setPosition(NavScreen_StatPanel, 443, 309);
    NavScreen_StatPanel->fn->setSize(NavScreen_StatPanel, 229, 115);
    NavScreen_StatPanel->fn->setBackgroundType(NavScreen_StatPanel, LE_WIDGET_BACKGROUND_NONE);
    root2->fn->addChild(root2, (leWidget*)NavScreen_StatPanel);

    NavScreen_label_kph = leLabelWidget_New();
    NavScreen_label_kph->fn->setPosition(NavScreen_label_kph, 157, 8);
    NavScreen_label_kph->fn->setSize(NavScreen_label_kph, 63, 25);
    NavScreen_label_kph->fn->setScheme(NavScreen_label_kph, &text_deepskyblue);
    NavScreen_label_kph->fn->setBackgroundType(NavScreen_label_kph, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_label_kph->fn->setHAlignment(NavScreen_label_kph, LE_HALIGN_RIGHT);
    NavScreen_label_kph->fn->setVAlignment(NavScreen_label_kph, LE_VALIGN_BOTTOM);
    NavScreen_label_kph->fn->setMargins(NavScreen_label_kph, 0, 0, 0, 0);
    NavScreen_label_kph->fn->setString(NavScreen_label_kph, (leString*)&string_figmaStr_KPH);
    NavScreen_StatPanel->fn->addChild(NavScreen_StatPanel, (leWidget*)NavScreen_label_kph);

    NavScreen_lblGauge = leLabelWidget_New();
    NavScreen_lblGauge->fn->setPosition(NavScreen_lblGauge, -14, 36);
    NavScreen_lblGauge->fn->setSize(NavScreen_lblGauge, 237, 76);
    NavScreen_lblGauge->fn->setScheme(NavScreen_lblGauge, &text_white);
    NavScreen_lblGauge->fn->setBackgroundType(NavScreen_lblGauge, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_lblGauge->fn->setHAlignment(NavScreen_lblGauge, LE_HALIGN_RIGHT);
    NavScreen_lblGauge->fn->setVAlignment(NavScreen_lblGauge, LE_VALIGN_TOP);
    NavScreen_lblGauge->fn->setMargins(NavScreen_lblGauge, 0, 0, 0, 0);
    NavScreen_lblGauge->fn->setString(NavScreen_lblGauge, (leString*)&string_strSpeedSmall);
    NavScreen_StatPanel->fn->addChild(NavScreen_StatPanel, (leWidget*)NavScreen_lblGauge);

    NavScreen_lblDistance = leLabelWidget_New();
    NavScreen_lblDistance->fn->setPosition(NavScreen_lblDistance, 367, 56);
    NavScreen_lblDistance->fn->setSize(NavScreen_lblDistance, 240, 31);
    NavScreen_lblDistance->fn->setScheme(NavScreen_lblDistance, &text_white);
    NavScreen_lblDistance->fn->setBackgroundType(NavScreen_lblDistance, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_lblDistance->fn->setMargins(NavScreen_lblDistance, 0, 0, 0, 0);
    NavScreen_lblDistance->fn->setString(NavScreen_lblDistance, (leString*)&string_strDistance);
    root2->fn->addChild(root2, (leWidget*)NavScreen_lblDistance);

    NavScreen_lblStreet = leLabelWidget_New();
    NavScreen_lblStreet->fn->setPosition(NavScreen_lblStreet, 366, 86);
    NavScreen_lblStreet->fn->setSize(NavScreen_lblStreet, 240, 34);
    NavScreen_lblStreet->fn->setScheme(NavScreen_lblStreet, &text_deepskyblue);
    NavScreen_lblStreet->fn->setBackgroundType(NavScreen_lblStreet, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_lblStreet->fn->setMargins(NavScreen_lblStreet, 0, 0, 0, 0);
    NavScreen_lblStreet->fn->setString(NavScreen_lblStreet, (leString*)&string_strStreet);
    root2->fn->addChild(root2, (leWidget*)NavScreen_lblStreet);

    NavScreen_imgDirection = leImageWidget_New();
    NavScreen_imgDirection->fn->setPosition(NavScreen_imgDirection, 293, 58);
    NavScreen_imgDirection->fn->setSize(NavScreen_imgDirection, 60, 60);
    NavScreen_imgDirection->fn->setBackgroundType(NavScreen_imgDirection, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_imgDirection->fn->setBorderType(NavScreen_imgDirection, LE_WIDGET_BORDER_NONE);
    NavScreen_imgDirection->fn->setImage(NavScreen_imgDirection, (leImage*)&StraightIcon);
    root2->fn->addChild(root2, (leWidget*)NavScreen_imgDirection);

    NavScreen_panel_Drive_Modes = leWidget_New();
    NavScreen_panel_Drive_Modes->fn->setPosition(NavScreen_panel_Drive_Modes, 139, 385);
    NavScreen_panel_Drive_Modes->fn->setSize(NavScreen_panel_Drive_Modes, 275, 41);
    NavScreen_panel_Drive_Modes->fn->setBackgroundType(NavScreen_panel_Drive_Modes, LE_WIDGET_BACKGROUND_NONE);
    root2->fn->addChild(root2, (leWidget*)NavScreen_panel_Drive_Modes);

    NavScreen_image_imgEcoOff = leImageWidget_New();
    NavScreen_image_imgEcoOff->fn->setPosition(NavScreen_image_imgEcoOff, 18, 7);
    NavScreen_image_imgEcoOff->fn->setSize(NavScreen_image_imgEcoOff, 46, 24);
    NavScreen_image_imgEcoOff->fn->setBackgroundType(NavScreen_image_imgEcoOff, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_image_imgEcoOff->fn->setBorderType(NavScreen_image_imgEcoOff, LE_WIDGET_BORDER_NONE);
    NavScreen_image_imgEcoOff->fn->setImage(NavScreen_image_imgEcoOff, (leImage*)&figmaImg_imgEcoOff);
    NavScreen_panel_Drive_Modes->fn->addChild(NavScreen_panel_Drive_Modes, (leWidget*)NavScreen_image_imgEcoOff);

    NavScreen_image_imgTourOff = leImageWidget_New();
    NavScreen_image_imgTourOff->fn->setPosition(NavScreen_image_imgTourOff, 72, 7);
    NavScreen_image_imgTourOff->fn->setSize(NavScreen_image_imgTourOff, 53, 24);
    NavScreen_image_imgTourOff->fn->setBackgroundType(NavScreen_image_imgTourOff, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_image_imgTourOff->fn->setBorderType(NavScreen_image_imgTourOff, LE_WIDGET_BORDER_NONE);
    NavScreen_image_imgTourOff->fn->setImage(NavScreen_image_imgTourOff, (leImage*)&figmaImg_imgTourOff);
    NavScreen_panel_Drive_Modes->fn->addChild(NavScreen_panel_Drive_Modes, (leWidget*)NavScreen_image_imgTourOff);

    NavScreen_image_imgSportOff = leImageWidget_New();
    NavScreen_image_imgSportOff->fn->setPosition(NavScreen_image_imgSportOff, 132, 7);
    NavScreen_image_imgSportOff->fn->setSize(NavScreen_image_imgSportOff, 60, 24);
    NavScreen_image_imgSportOff->fn->setBackgroundType(NavScreen_image_imgSportOff, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_image_imgSportOff->fn->setBorderType(NavScreen_image_imgSportOff, LE_WIDGET_BORDER_NONE);
    NavScreen_image_imgSportOff->fn->setImage(NavScreen_image_imgSportOff, (leImage*)&figmaImg_imgSportOff);
    NavScreen_panel_Drive_Modes->fn->addChild(NavScreen_panel_Drive_Modes, (leWidget*)NavScreen_image_imgSportOff);

    NavScreen_image_imgBoostOn = leImageWidget_New();
    NavScreen_image_imgBoostOn->fn->setPosition(NavScreen_image_imgBoostOn, 200, 7);
    NavScreen_image_imgBoostOn->fn->setSize(NavScreen_image_imgBoostOn, 60, 24);
    NavScreen_image_imgBoostOn->fn->setBackgroundType(NavScreen_image_imgBoostOn, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_image_imgBoostOn->fn->setBorderType(NavScreen_image_imgBoostOn, LE_WIDGET_BORDER_NONE);
    NavScreen_image_imgBoostOn->fn->setImage(NavScreen_image_imgBoostOn, (leImage*)&figmaImg_imgBoostOn);
    NavScreen_panel_Drive_Modes->fn->addChild(NavScreen_panel_Drive_Modes, (leWidget*)NavScreen_image_imgBoostOn);

    NavScreen_label_ECO = leLabelWidget_New();
    NavScreen_label_ECO->fn->setPosition(NavScreen_label_ECO, 26, 11);
    NavScreen_label_ECO->fn->setSize(NavScreen_label_ECO, 29, 16);
    NavScreen_label_ECO->fn->setScheme(NavScreen_label_ECO, &text_lightslategray);
    NavScreen_label_ECO->fn->setBackgroundType(NavScreen_label_ECO, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_label_ECO->fn->setHAlignment(NavScreen_label_ECO, LE_HALIGN_CENTER);
    NavScreen_label_ECO->fn->setVAlignment(NavScreen_label_ECO, LE_VALIGN_TOP);
    NavScreen_label_ECO->fn->setMargins(NavScreen_label_ECO, 0, 0, 0, 0);
    NavScreen_label_ECO->fn->setString(NavScreen_label_ECO, (leString*)&string_figmaStr_ECO);
    NavScreen_panel_Drive_Modes->fn->addChild(NavScreen_panel_Drive_Modes, (leWidget*)NavScreen_label_ECO);

    NavScreen_label_TOUR = leLabelWidget_New();
    NavScreen_label_TOUR->fn->setPosition(NavScreen_label_TOUR, 80, 11);
    NavScreen_label_TOUR->fn->setSize(NavScreen_label_TOUR, 35, 16);
    NavScreen_label_TOUR->fn->setScheme(NavScreen_label_TOUR, &text_lightslategray);
    NavScreen_label_TOUR->fn->setBackgroundType(NavScreen_label_TOUR, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_label_TOUR->fn->setHAlignment(NavScreen_label_TOUR, LE_HALIGN_CENTER);
    NavScreen_label_TOUR->fn->setVAlignment(NavScreen_label_TOUR, LE_VALIGN_TOP);
    NavScreen_label_TOUR->fn->setMargins(NavScreen_label_TOUR, 0, 0, 0, 0);
    NavScreen_label_TOUR->fn->setString(NavScreen_label_TOUR, (leString*)&string_figmaStr_TOUR);
    NavScreen_panel_Drive_Modes->fn->addChild(NavScreen_panel_Drive_Modes, (leWidget*)NavScreen_label_TOUR);

    NavScreen_label_SPORT = leLabelWidget_New();
    NavScreen_label_SPORT->fn->setPosition(NavScreen_label_SPORT, 143, 11);
    NavScreen_label_SPORT->fn->setSize(NavScreen_label_SPORT, 36, 16);
    NavScreen_label_SPORT->fn->setScheme(NavScreen_label_SPORT, &text_lightslategray);
    NavScreen_label_SPORT->fn->setBackgroundType(NavScreen_label_SPORT, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_label_SPORT->fn->setHAlignment(NavScreen_label_SPORT, LE_HALIGN_CENTER);
    NavScreen_label_SPORT->fn->setVAlignment(NavScreen_label_SPORT, LE_VALIGN_TOP);
    NavScreen_label_SPORT->fn->setMargins(NavScreen_label_SPORT, 0, 0, 0, 0);
    NavScreen_label_SPORT->fn->setString(NavScreen_label_SPORT, (leString*)&string_figmaStr_SPORT);
    NavScreen_panel_Drive_Modes->fn->addChild(NavScreen_panel_Drive_Modes, (leWidget*)NavScreen_label_SPORT);

    NavScreen_label_BOOST = leLabelWidget_New();
    NavScreen_label_BOOST->fn->setPosition(NavScreen_label_BOOST, 210, 11);
    NavScreen_label_BOOST->fn->setSize(NavScreen_label_BOOST, 42, 16);
    NavScreen_label_BOOST->fn->setScheme(NavScreen_label_BOOST, &text_black);
    NavScreen_label_BOOST->fn->setBackgroundType(NavScreen_label_BOOST, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_label_BOOST->fn->setHAlignment(NavScreen_label_BOOST, LE_HALIGN_CENTER);
    NavScreen_label_BOOST->fn->setMargins(NavScreen_label_BOOST, 0, 0, 0, 0);
    NavScreen_label_BOOST->fn->setString(NavScreen_label_BOOST, (leString*)&string_figmaStr_BOOST);
    NavScreen_panel_Drive_Modes->fn->addChild(NavScreen_panel_Drive_Modes, (leWidget*)NavScreen_label_BOOST);

    NavScreen_imgDirIcon = leImageWidget_New();
    NavScreen_imgDirIcon->fn->setPosition(NavScreen_imgDirIcon, 385, 240);
    NavScreen_imgDirIcon->fn->setSize(NavScreen_imgDirIcon, 60, 60);
    NavScreen_imgDirIcon->fn->setBackgroundType(NavScreen_imgDirIcon, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_imgDirIcon->fn->setBorderType(NavScreen_imgDirIcon, LE_WIDGET_BORDER_NONE);
    NavScreen_imgDirIcon->fn->setImage(NavScreen_imgDirIcon, (leImage*)&DirIcon2);
    root2->fn->addChild(root2, (leWidget*)NavScreen_imgDirIcon);

    NavScreen_PanelRegenDischarge = leWidget_New();
    NavScreen_PanelRegenDischarge->fn->setPosition(NavScreen_PanelRegenDischarge, 29, 64);
    NavScreen_PanelRegenDischarge->fn->setSize(NavScreen_PanelRegenDischarge, 145, 48);
    NavScreen_PanelRegenDischarge->fn->setBackgroundType(NavScreen_PanelRegenDischarge, LE_WIDGET_BACKGROUND_NONE);
    root2->fn->addChild(root2, (leWidget*)NavScreen_PanelRegenDischarge);

    NavScreen_image_imgMeterTrack = leImageWidget_New();
    NavScreen_image_imgMeterTrack->fn->setPosition(NavScreen_image_imgMeterTrack, 14, 19);
    NavScreen_image_imgMeterTrack->fn->setSize(NavScreen_image_imgMeterTrack, 120, 4);
    NavScreen_image_imgMeterTrack->fn->setBackgroundType(NavScreen_image_imgMeterTrack, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_image_imgMeterTrack->fn->setBorderType(NavScreen_image_imgMeterTrack, LE_WIDGET_BORDER_NONE);
    NavScreen_image_imgMeterTrack->fn->setImage(NavScreen_image_imgMeterTrack, (leImage*)&figmaImg_imgMeterTrack);
    NavScreen_PanelRegenDischarge->fn->addChild(NavScreen_PanelRegenDischarge, (leWidget*)NavScreen_image_imgMeterTrack);

    NavScreen_image_RegenBar = leImageWidget_New();
    NavScreen_image_RegenBar->fn->setPosition(NavScreen_image_RegenBar, 14, 19);
    NavScreen_image_RegenBar->fn->setSize(NavScreen_image_RegenBar, 60, 4);
    NavScreen_image_RegenBar->fn->setBackgroundType(NavScreen_image_RegenBar, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_image_RegenBar->fn->setBorderType(NavScreen_image_RegenBar, LE_WIDGET_BORDER_NONE);
    NavScreen_image_RegenBar->fn->setHAlignment(NavScreen_image_RegenBar, LE_HALIGN_LEFT);
    NavScreen_image_RegenBar->fn->setMargins(NavScreen_image_RegenBar, 0, 4, 4, 4);
    NavScreen_image_RegenBar->fn->setImage(NavScreen_image_RegenBar, (leImage*)&imgregendischarge);
    NavScreen_PanelRegenDischarge->fn->addChild(NavScreen_PanelRegenDischarge, (leWidget*)NavScreen_image_RegenBar);

    NavScreen_image_DischargeBar = leImageWidget_New();
    NavScreen_image_DischargeBar->fn->setPosition(NavScreen_image_DischargeBar, 74, 19);
    NavScreen_image_DischargeBar->fn->setSize(NavScreen_image_DischargeBar, 60, 4);
    NavScreen_image_DischargeBar->fn->setBackgroundType(NavScreen_image_DischargeBar, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_image_DischargeBar->fn->setBorderType(NavScreen_image_DischargeBar, LE_WIDGET_BORDER_NONE);
    NavScreen_image_DischargeBar->fn->setHAlignment(NavScreen_image_DischargeBar, LE_HALIGN_RIGHT);
    NavScreen_image_DischargeBar->fn->setMargins(NavScreen_image_DischargeBar, 0, 4, 0, 4);
    NavScreen_image_DischargeBar->fn->setImage(NavScreen_image_DischargeBar, (leImage*)&imgregendischarge);
    NavScreen_PanelRegenDischarge->fn->addChild(NavScreen_PanelRegenDischarge, (leWidget*)NavScreen_image_DischargeBar);

    NavScreen_image_imgEnergyFlow = leImageWidget_New();
    NavScreen_image_imgEnergyFlow->fn->setPosition(NavScreen_image_imgEnergyFlow, 5, 13);
    NavScreen_image_imgEnergyFlow->fn->setSize(NavScreen_image_imgEnergyFlow, 139, 30);
    NavScreen_image_imgEnergyFlow->fn->setBackgroundType(NavScreen_image_imgEnergyFlow, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_image_imgEnergyFlow->fn->setBorderType(NavScreen_image_imgEnergyFlow, LE_WIDGET_BORDER_NONE);
    NavScreen_image_imgEnergyFlow->fn->setImage(NavScreen_image_imgEnergyFlow, (leImage*)&figmaImg_imgEnergyFlow);
    NavScreen_PanelRegenDischarge->fn->addChild(NavScreen_PanelRegenDischarge, (leWidget*)NavScreen_image_imgEnergyFlow);

    NavScreen_label_REGEN = leLabelWidget_New();
    NavScreen_label_REGEN->fn->setPosition(NavScreen_label_REGEN, 14, 29);
    NavScreen_label_REGEN->fn->setSize(NavScreen_label_REGEN, 34, 13);
    NavScreen_label_REGEN->fn->setScheme(NavScreen_label_REGEN, &text_chartreuse);
    NavScreen_label_REGEN->fn->setBackgroundType(NavScreen_label_REGEN, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_label_REGEN->fn->setVAlignment(NavScreen_label_REGEN, LE_VALIGN_TOP);
    NavScreen_label_REGEN->fn->setMargins(NavScreen_label_REGEN, 0, 0, 0, 0);
    NavScreen_label_REGEN->fn->setString(NavScreen_label_REGEN, (leString*)&string_figmaStr_REGEN);
    NavScreen_PanelRegenDischarge->fn->addChild(NavScreen_PanelRegenDischarge, (leWidget*)NavScreen_label_REGEN);

    NavScreen_label_DISCHARGE = leLabelWidget_New();
    NavScreen_label_DISCHARGE->fn->setPosition(NavScreen_label_DISCHARGE, 82, 29);
    NavScreen_label_DISCHARGE->fn->setSize(NavScreen_label_DISCHARGE, 54, 13);
    NavScreen_label_DISCHARGE->fn->setScheme(NavScreen_label_DISCHARGE, &text_darkorange);
    NavScreen_label_DISCHARGE->fn->setBackgroundType(NavScreen_label_DISCHARGE, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_label_DISCHARGE->fn->setVAlignment(NavScreen_label_DISCHARGE, LE_VALIGN_TOP);
    NavScreen_label_DISCHARGE->fn->setMargins(NavScreen_label_DISCHARGE, 0, 0, 0, 0);
    NavScreen_label_DISCHARGE->fn->setString(NavScreen_label_DISCHARGE, (leString*)&string_figmaStr_DISCHARGE);
    NavScreen_PanelRegenDischarge->fn->addChild(NavScreen_PanelRegenDischarge, (leWidget*)NavScreen_label_DISCHARGE);

    NavScreen_RangePanel = leWidget_New();
    NavScreen_RangePanel->fn->setPosition(NavScreen_RangePanel, 638, 56);
    NavScreen_RangePanel->fn->setSize(NavScreen_RangePanel, 128, 60);
    NavScreen_RangePanel->fn->setBackgroundType(NavScreen_RangePanel, LE_WIDGET_BACKGROUND_NONE);
    root2->fn->addChild(root2, (leWidget*)NavScreen_RangePanel);

    NavScreen_label_Est_Range = leLabelWidget_New();
    NavScreen_label_Est_Range->fn->setPosition(NavScreen_label_Est_Range, 29, 10);
    NavScreen_label_Est_Range->fn->setSize(NavScreen_label_Est_Range, 60, 13);
    NavScreen_label_Est_Range->fn->setScheme(NavScreen_label_Est_Range, &text_lightslategray);
    NavScreen_label_Est_Range->fn->setBackgroundType(NavScreen_label_Est_Range, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_label_Est_Range->fn->setVAlignment(NavScreen_label_Est_Range, LE_VALIGN_TOP);
    NavScreen_label_Est_Range->fn->setMargins(NavScreen_label_Est_Range, 0, 0, 0, 0);
    NavScreen_label_Est_Range->fn->setString(NavScreen_label_Est_Range, (leString*)&string_figmaStr_Est__Range);
    NavScreen_RangePanel->fn->addChild(NavScreen_RangePanel, (leWidget*)NavScreen_label_Est_Range);

    NavScreen_label_Range = leLabelWidget_New();
    NavScreen_label_Range->fn->setPosition(NavScreen_label_Range, 9, 22);
    NavScreen_label_Range->fn->setSize(NavScreen_label_Range, 81, 32);
    NavScreen_label_Range->fn->setScheme(NavScreen_label_Range, &text_white);
    NavScreen_label_Range->fn->setBackgroundType(NavScreen_label_Range, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_label_Range->fn->setHAlignment(NavScreen_label_Range, LE_HALIGN_RIGHT);
    NavScreen_label_Range->fn->setMargins(NavScreen_label_Range, 0, 0, 0, 0);
    NavScreen_label_Range->fn->setString(NavScreen_label_Range, (leString*)&string_figmaStr_184);
    NavScreen_RangePanel->fn->addChild(NavScreen_RangePanel, (leWidget*)NavScreen_label_Range);

    NavScreen_label_KM = leLabelWidget_New();
    NavScreen_label_KM->fn->setPosition(NavScreen_label_KM, 93, 33);
    NavScreen_label_KM->fn->setSize(NavScreen_label_KM, 28, 21);
    NavScreen_label_KM->fn->setScheme(NavScreen_label_KM, &text_deepskyblue);
    NavScreen_label_KM->fn->setBackgroundType(NavScreen_label_KM, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_label_KM->fn->setMargins(NavScreen_label_KM, 0, 0, 0, 0);
    NavScreen_label_KM->fn->setString(NavScreen_label_KM, (leString*)&string_figmaStr_KM);
    NavScreen_RangePanel->fn->addChild(NavScreen_RangePanel, (leWidget*)NavScreen_label_KM);

    NavScreen_touchPanel = leWidget_New();
    NavScreen_touchPanel->fn->setPosition(NavScreen_touchPanel, 115, 119);
    NavScreen_touchPanel->fn->setSize(NavScreen_touchPanel, 575, 260);
    NavScreen_touchPanel->fn->setBackgroundType(NavScreen_touchPanel, LE_WIDGET_BACKGROUND_NONE);
    root2->fn->addChild(root2, (leWidget*)NavScreen_touchPanel);

    NavScreen_imgMGS = leImageWidget_New();
    NavScreen_imgMGS->fn->setPosition(NavScreen_imgMGS, 200, 8);
    NavScreen_imgMGS->fn->setSize(NavScreen_imgMGS, 48, 40);
    NavScreen_imgMGS->fn->setBackgroundType(NavScreen_imgMGS, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_imgMGS->fn->setBorderType(NavScreen_imgMGS, LE_WIDGET_BORDER_NONE);
    NavScreen_imgMGS->fn->setHAlignment(NavScreen_imgMGS, LE_HALIGN_LEFT);
    NavScreen_imgMGS->fn->setImage(NavScreen_imgMGS, (leImage*)&Image1);
    root2->fn->addChild(root2, (leWidget*)NavScreen_imgMGS);

    NavScreen_pnlMetrics = leWidget_New();
    NavScreen_pnlMetrics->fn->setPosition(NavScreen_pnlMetrics, 117, 363);
    NavScreen_pnlMetrics->fn->setSize(NavScreen_pnlMetrics, 296, 20);
    NavScreen_pnlMetrics->fn->setBackgroundType(NavScreen_pnlMetrics, LE_WIDGET_BACKGROUND_NONE);
    root2->fn->addChild(root2, (leWidget*)NavScreen_pnlMetrics);

    NavScreen_lblUpdatePct = leLabelWidget_New();
    NavScreen_lblUpdatePct->fn->setPosition(NavScreen_lblUpdatePct, 56, 0);
    NavScreen_lblUpdatePct->fn->setSize(NavScreen_lblUpdatePct, 40, 18);
    NavScreen_lblUpdatePct->fn->setScheme(NavScreen_lblUpdatePct, &text_lightslategray);
    NavScreen_lblUpdatePct->fn->setBackgroundType(NavScreen_lblUpdatePct, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_lblUpdatePct->fn->setMargins(NavScreen_lblUpdatePct, 0, 0, 0, 0);
    NavScreen_lblUpdatePct->fn->setString(NavScreen_lblUpdatePct, (leString*)&string_figmaStr_042_8_mi);
    NavScreen_pnlMetrics->fn->addChild(NavScreen_pnlMetrics, (leWidget*)NavScreen_lblUpdatePct);

    NavScreen_lblDrawPct = leLabelWidget_New();
    NavScreen_lblDrawPct->fn->setPosition(NavScreen_lblDrawPct, 158, 0);
    NavScreen_lblDrawPct->fn->setSize(NavScreen_lblDrawPct, 40, 18);
    NavScreen_lblDrawPct->fn->setScheme(NavScreen_lblDrawPct, &text_lightslategray);
    NavScreen_lblDrawPct->fn->setBackgroundType(NavScreen_lblDrawPct, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_lblDrawPct->fn->setMargins(NavScreen_lblDrawPct, 0, 0, 0, 0);
    NavScreen_lblDrawPct->fn->setString(NavScreen_lblDrawPct, (leString*)&string_figmaStr_042_8_mi);
    NavScreen_pnlMetrics->fn->addChild(NavScreen_pnlMetrics, (leWidget*)NavScreen_lblDrawPct);

    NavScreen_lblFPSValue = leLabelWidget_New();
    NavScreen_lblFPSValue->fn->setPosition(NavScreen_lblFPSValue, 238, -1);
    NavScreen_lblFPSValue->fn->setSize(NavScreen_lblFPSValue, 50, 18);
    NavScreen_lblFPSValue->fn->setScheme(NavScreen_lblFPSValue, &text_lightslategray);
    NavScreen_lblFPSValue->fn->setBackgroundType(NavScreen_lblFPSValue, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_lblFPSValue->fn->setMargins(NavScreen_lblFPSValue, 0, 0, 0, 0);
    NavScreen_lblFPSValue->fn->setString(NavScreen_lblFPSValue, (leString*)&string_figmaStr_042_8_mi);
    NavScreen_pnlMetrics->fn->addChild(NavScreen_pnlMetrics, (leWidget*)NavScreen_lblFPSValue);

    NavScreen_lblUpdate = leLabelWidget_New();
    NavScreen_lblUpdate->fn->setPosition(NavScreen_lblUpdate, 4, 1);
    NavScreen_lblUpdate->fn->setSize(NavScreen_lblUpdate, 44, 18);
    NavScreen_lblUpdate->fn->setScheme(NavScreen_lblUpdate, &text_lightslategray);
    NavScreen_lblUpdate->fn->setBackgroundType(NavScreen_lblUpdate, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_lblUpdate->fn->setHAlignment(NavScreen_lblUpdate, LE_HALIGN_RIGHT);
    NavScreen_lblUpdate->fn->setMargins(NavScreen_lblUpdate, 0, 0, 0, 0);
    NavScreen_lblUpdate->fn->setString(NavScreen_lblUpdate, (leString*)&string_strCPUUpdate);
    NavScreen_pnlMetrics->fn->addChild(NavScreen_pnlMetrics, (leWidget*)NavScreen_lblUpdate);

    NavScreen_lblDraw = leLabelWidget_New();
    NavScreen_lblDraw->fn->setPosition(NavScreen_lblDraw, 106, 0);
    NavScreen_lblDraw->fn->setSize(NavScreen_lblDraw, 44, 18);
    NavScreen_lblDraw->fn->setScheme(NavScreen_lblDraw, &text_lightslategray);
    NavScreen_lblDraw->fn->setBackgroundType(NavScreen_lblDraw, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_lblDraw->fn->setHAlignment(NavScreen_lblDraw, LE_HALIGN_RIGHT);
    NavScreen_lblDraw->fn->setMargins(NavScreen_lblDraw, 0, 0, 0, 0);
    NavScreen_lblDraw->fn->setString(NavScreen_lblDraw, (leString*)&string_strCPUDraw);
    NavScreen_pnlMetrics->fn->addChild(NavScreen_pnlMetrics, (leWidget*)NavScreen_lblDraw);

    NavScreen_lblFPS = leLabelWidget_New();
    NavScreen_lblFPS->fn->setPosition(NavScreen_lblFPS, 204, 0);
    NavScreen_lblFPS->fn->setSize(NavScreen_lblFPS, 26, 18);
    NavScreen_lblFPS->fn->setScheme(NavScreen_lblFPS, &text_lightslategray);
    NavScreen_lblFPS->fn->setBackgroundType(NavScreen_lblFPS, LE_WIDGET_BACKGROUND_NONE);
    NavScreen_lblFPS->fn->setHAlignment(NavScreen_lblFPS, LE_HALIGN_RIGHT);
    NavScreen_lblFPS->fn->setMargins(NavScreen_lblFPS, 0, 0, 0, 0);
    NavScreen_lblFPS->fn->setString(NavScreen_lblFPS, (leString*)&string_strFPS);
    NavScreen_pnlMetrics->fn->addChild(NavScreen_pnlMetrics, (leWidget*)NavScreen_lblFPS);

    leAddRootWidget(root2, 2);
    leSetLayerColorMode(2, LE_COLOR_MODE_RGBA_8888);

    NavScreen_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_NavScreen(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
    root1->fn->setSize(root1, root1->rect.width, root1->rect.height);
    root2->fn->setSize(root2, root2->rect.width, root2->rect.height);

    NavScreen_OnUpdate(); // raise event
}

void screenHide_NavScreen(void)
{
    NavScreen_OnHide(); // raise event


    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    NavScreen_BackgroundPanelBase = NULL;
    NavScreen_drawNav = NULL;

    leRemoveRootWidget(root1, 1);
    leWidget_Delete(root1);
    root1 = NULL;

    leRemoveRootWidget(root2, 2);
    leWidget_Delete(root2);
    root2 = NULL;

    NavScreen_panel_electric_moto_cluster = NULL;
    NavScreen_panel_Status_Bar = NULL;
    NavScreen_image_imgRegenFullBar = NULL;
    NavScreen_imgRegenBar = NULL;
    NavScreen_image_iconBattery = NULL;
    NavScreen_image_iconTemp = NULL;
    NavScreen_panel_Shortcut_Bar = NULL;
    NavScreen_image_imgPowerTrack = NULL;
    NavScreen_image_imgPowerProg = NULL;
    NavScreen_image_imgBatTrack = NULL;
    NavScreen_image_imgBatProg = NULL;
    NavScreen_label_Battery = NULL;
    NavScreen_label_0 = NULL;
    NavScreen_label_BattValue = NULL;
    NavScreen_label_Power = NULL;
    NavScreen_label_PowerValue = NULL;
    NavScreen_label_kW = NULL;
    NavScreen_panel_Battery_Temp = NULL;
    NavScreen_panel_Motor_Temp = NULL;
    NavScreen_StatPanel = NULL;
    NavScreen_lblDistance = NULL;
    NavScreen_lblStreet = NULL;
    NavScreen_imgDirection = NULL;
    NavScreen_panel_Drive_Modes = NULL;
    NavScreen_imgDirIcon = NULL;
    NavScreen_PanelRegenDischarge = NULL;
    NavScreen_RangePanel = NULL;
    NavScreen_touchPanel = NULL;
    NavScreen_imgMGS = NULL;
    NavScreen_pnlMetrics = NULL;
    NavScreen_panel_Status_Left = NULL;
    NavScreen_panel_Status_Center = NULL;
    NavScreen_panel_Status_Right = NULL;
    NavScreen_image_iconLeftOn = NULL;
    NavScreen_odo = NULL;
    NavScreen_label_OdoValue = NULL;
    NavScreen_image_iconHazard = NULL;
    NavScreen_image_iconArrow = NULL;
    NavScreen_image_iconCancel = NULL;
    NavScreen_image_iconPlug = NULL;
    NavScreen_label_TRIP_A = NULL;
    NavScreen_label_TripValue = NULL;
    NavScreen_label__Time = NULL;
    NavScreen_image_iconRightOff = NULL;
    NavScreen_btnPhone = NULL;
    NavScreen_btnCamera = NULL;
    NavScreen_btnHome = NULL;
    NavScreen_btnMusic = NULL;
    NavScreen_btnMap = NULL;
    NavScreen_btnLight = NULL;
    NavScreen_label_Battery = NULL;
    NavScreen_label_BattTemp = NULL;
    NavScreen_label_Motor = NULL;
    NavScreen_label__MotorTempValue = NULL;
    NavScreen_label_kph = NULL;
    NavScreen_lblGauge = NULL;
    NavScreen_image_imgEcoOff = NULL;
    NavScreen_image_imgTourOff = NULL;
    NavScreen_image_imgSportOff = NULL;
    NavScreen_image_imgBoostOn = NULL;
    NavScreen_label_ECO = NULL;
    NavScreen_label_TOUR = NULL;
    NavScreen_label_SPORT = NULL;
    NavScreen_label_BOOST = NULL;
    NavScreen_image_imgMeterTrack = NULL;
    NavScreen_image_RegenBar = NULL;
    NavScreen_image_DischargeBar = NULL;
    NavScreen_image_imgEnergyFlow = NULL;
    NavScreen_label_REGEN = NULL;
    NavScreen_label_DISCHARGE = NULL;
    NavScreen_label_Est_Range = NULL;
    NavScreen_label_Range = NULL;
    NavScreen_label_KM = NULL;
    NavScreen_lblUpdatePct = NULL;
    NavScreen_lblDrawPct = NULL;
    NavScreen_lblFPSValue = NULL;
    NavScreen_lblUpdate = NULL;
    NavScreen_lblDraw = NULL;
    NavScreen_lblFPS = NULL;


    showing = LE_FALSE;
}

void screenDestroy_NavScreen(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_NavScreen(uint32_t lyrIdx)
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


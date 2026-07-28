#ifndef LE_GEN_SCREEN_NAVSCREEN_H
#define LE_GEN_SCREEN_NAVSCREEN_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* NavScreen_BackgroundPanelBase;
extern leDrawSurfaceWidget* NavScreen_drawNav;
extern leWidget* NavScreen_panel_electric_moto_cluster;
extern leWidget* NavScreen_panel_Status_Bar;
extern leImageWidget* NavScreen_image_imgRegenFullBar;
extern leImageWidget* NavScreen_imgRegenBar;
extern leImageWidget* NavScreen_image_iconBattery;
extern leImageWidget* NavScreen_image_iconTemp;
extern leWidget* NavScreen_panel_Shortcut_Bar;
extern leImageWidget* NavScreen_image_imgPowerTrack;
extern leImageWidget* NavScreen_image_imgPowerProg;
extern leImageWidget* NavScreen_image_imgBatTrack;
extern leImageWidget* NavScreen_image_imgBatProg;
extern leLabelWidget* NavScreen_label_Battery;
extern leLabelWidget* NavScreen_label_0;
extern leLabelWidget* NavScreen_label_BattValue;
extern leLabelWidget* NavScreen_label_Power;
extern leLabelWidget* NavScreen_label_PowerValue;
extern leLabelWidget* NavScreen_label_kW;
extern leWidget* NavScreen_panel_Battery_Temp;
extern leWidget* NavScreen_panel_Motor_Temp;
extern leWidget* NavScreen_StatPanel;
extern leLabelWidget* NavScreen_lblDistance;
extern leLabelWidget* NavScreen_lblStreet;
extern leImageWidget* NavScreen_imgDirection;
extern leWidget* NavScreen_panel_Drive_Modes;
extern leImageWidget* NavScreen_imgDirIcon;
extern leWidget* NavScreen_PanelRegenDischarge;
extern leWidget* NavScreen_RangePanel;
extern leWidget* NavScreen_touchPanel;
extern leImageWidget* NavScreen_imgMGS;
extern leWidget* NavScreen_pnlMetrics;
extern leWidget* NavScreen_panel_Status_Left;
extern leWidget* NavScreen_panel_Status_Center;
extern leWidget* NavScreen_panel_Status_Right;
extern leImageWidget* NavScreen_image_iconLeftOn;
extern leLabelWidget* NavScreen_odo;
extern leLabelWidget* NavScreen_label_OdoValue;
extern leImageWidget* NavScreen_image_iconHazard;
extern leImageWidget* NavScreen_image_iconArrow;
extern leImageWidget* NavScreen_image_iconCancel;
extern leImageWidget* NavScreen_image_iconPlug;
extern leLabelWidget* NavScreen_label_TRIP_A;
extern leLabelWidget* NavScreen_label_TripValue;
extern leLabelWidget* NavScreen_label__Time;
extern leImageWidget* NavScreen_image_iconRightOff;
extern leButtonWidget* NavScreen_btnPhone;
extern leButtonWidget* NavScreen_btnCamera;
extern leButtonWidget* NavScreen_btnHome;
extern leButtonWidget* NavScreen_btnMusic;
extern leButtonWidget* NavScreen_btnMap;
extern leButtonWidget* NavScreen_btnLight;
extern leLabelWidget* NavScreen_label_Battery;
extern leLabelWidget* NavScreen_label_BattTemp;
extern leLabelWidget* NavScreen_label_Motor;
extern leLabelWidget* NavScreen_label__MotorTempValue;
extern leLabelWidget* NavScreen_label_kph;
extern leLabelWidget* NavScreen_lblGauge;
extern leImageWidget* NavScreen_image_imgEcoOff;
extern leImageWidget* NavScreen_image_imgTourOff;
extern leImageWidget* NavScreen_image_imgSportOff;
extern leImageWidget* NavScreen_image_imgBoostOn;
extern leLabelWidget* NavScreen_label_ECO;
extern leLabelWidget* NavScreen_label_TOUR;
extern leLabelWidget* NavScreen_label_SPORT;
extern leLabelWidget* NavScreen_label_BOOST;
extern leImageWidget* NavScreen_image_imgMeterTrack;
extern leImageWidget* NavScreen_image_RegenBar;
extern leImageWidget* NavScreen_image_DischargeBar;
extern leImageWidget* NavScreen_image_imgEnergyFlow;
extern leLabelWidget* NavScreen_label_REGEN;
extern leLabelWidget* NavScreen_label_DISCHARGE;
extern leLabelWidget* NavScreen_label_Est_Range;
extern leLabelWidget* NavScreen_label_Range;
extern leLabelWidget* NavScreen_label_KM;
extern leLabelWidget* NavScreen_lblUpdatePct;
extern leLabelWidget* NavScreen_lblDrawPct;
extern leLabelWidget* NavScreen_lblFPSValue;
extern leLabelWidget* NavScreen_lblUpdate;
extern leLabelWidget* NavScreen_lblDraw;
extern leLabelWidget* NavScreen_lblFPS;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
leBool event_NavScreen_drawNav_OnDraw(leDrawSurfaceWidget* sfc, leRect* bounds);
void event_NavScreen_btnPhone_OnPressed(leButtonWidget* btn);
void event_NavScreen_btnCamera_OnPressed(leButtonWidget* btn);
void event_NavScreen_btnHome_OnPressed(leButtonWidget* btn);
void event_NavScreen_btnMusic_OnPressed(leButtonWidget* btn);
void event_NavScreen_btnMap_OnPressed(leButtonWidget* btn);
void event_NavScreen_btnLight_OnPressed(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_NavScreen(void); // called when Legato is initialized
leResult screenShow_NavScreen(void); // called when screen is shown
void screenHide_NavScreen(void); // called when screen is hidden
void screenDestroy_NavScreen(void); // called when Legato is destroyed
void screenUpdate_NavScreen(void); // called when Legato is updating

leWidget* screenGetRoot_NavScreen(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void NavScreen_OnShow(void); // called when this screen is shown
void NavScreen_OnHide(void); // called when this screen is hidden
void NavScreen_OnUpdate(void); // called when this screen is updated

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_NAVSCREEN_H

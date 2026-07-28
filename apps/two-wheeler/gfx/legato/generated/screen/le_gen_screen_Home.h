#ifndef LE_GEN_SCREEN_HOME_H
#define LE_GEN_SCREEN_HOME_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* Home_BackgroundPanelBase;
extern leWidget* Home_panel_electric_moto_cluster;
extern leWidget* Home_panel_Status_Bar;
extern leImageWidget* Home_image_imgRegenFullBar;
extern leImageWidget* Home_imgRegenBar;
extern leWidget* Home_panel_Drive_Modes;
extern leImageWidget* Home_image_iconBattery;
extern leImageWidget* Home_image_iconTemp;
extern leWidget* Home_panel_Shortcut_Bar;
extern leImageWidget* Home_image_imgEnergyFlow;
extern leLabelWidget* Home_label_REGEN;
extern leImageWidget* Home_image_imgMeterTrack;
extern leLabelWidget* Home_label_DISCHARGE;
extern leImageWidget* Home_image_imgPowerTrack;
extern leImageWidget* Home_image_imgPowerProg;
extern leImageWidget* Home_image_imgBatTrack;
extern leImageWidget* Home_image_imgBatProg;
extern leLabelWidget* Home_label_Battery;
extern leLabelWidget* Home_label_0;
extern leLabelWidget* Home_label_BattValue;
extern leLabelWidget* Home_label_Power;
extern leLabelWidget* Home_label_PowerValue;
extern leLabelWidget* Home_label_kW;
extern leLabelWidget* Home_lblGauge;
extern leLabelWidget* Home_label_MPH;
extern leWidget* Home_panel_Battery_Temp;
extern leLabelWidget* Home_label_Est_Range;
extern leLabelWidget* Home_label_Range;
extern leLabelWidget* Home_label_KM;
extern leWidget* Home_panel_Motor_Temp;
extern leImageWidget* Home_image_RegenBar;
extern leImageWidget* Home_image_DischargeBar;
extern leWidget* Home_touchPanel;
extern leImageWidget* Home_imgMGS;
extern leWidget* Home_pnlMetrics;
extern leWidget* Home_panel_Status_Left;
extern leWidget* Home_panel_Status_Center;
extern leWidget* Home_panel_Status_Right;
extern leImageWidget* Home_image_iconLeftOn;
extern leLabelWidget* Home_odo;
extern leLabelWidget* Home_label_OdoValue;
extern leImageWidget* Home_image_iconHazard;
extern leImageWidget* Home_image_iconArrow;
extern leImageWidget* Home_image_iconCancel;
extern leImageWidget* Home_image_iconPlug;
extern leLabelWidget* Home_label_TRIP_A;
extern leLabelWidget* Home_label_TripValue;
extern leLabelWidget* Home_label__Time;
extern leImageWidget* Home_image_iconRightOff;
extern leImageWidget* Home_image_imgEcoOff;
extern leImageWidget* Home_image_imgTourOff;
extern leImageWidget* Home_image_imgSportOff;
extern leImageWidget* Home_image_imgBoostOn;
extern leLabelWidget* Home_label_ECO;
extern leLabelWidget* Home_label_TOUR;
extern leLabelWidget* Home_label_SPORT;
extern leLabelWidget* Home_label_BOOST;
extern leButtonWidget* Home_btnPhone;
extern leButtonWidget* Home_btnCamera;
extern leButtonWidget* Home_btnHome;
extern leButtonWidget* Home_btnMusic;
extern leButtonWidget* Home_btnMap;
extern leButtonWidget* Home_btnLight;
extern leLabelWidget* Home_label_Battery;
extern leLabelWidget* Home_label_BattTemp;
extern leLabelWidget* Home_label_Motor;
extern leLabelWidget* Home_label_MotorTempValue;
extern leLabelWidget* Home_lblUpdatePct;
extern leLabelWidget* Home_lblDrawPct;
extern leLabelWidget* Home_lblFPSValue;
extern leLabelWidget* Home_lblUpdate;
extern leLabelWidget* Home_lblDraw;
extern leLabelWidget* Home_lblFPS;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_Home_btnPhone_OnPressed(leButtonWidget* btn);
void event_Home_btnCamera_OnPressed(leButtonWidget* btn);
void event_Home_btnHome_OnPressed(leButtonWidget* btn);
void event_Home_btnMusic_OnPressed(leButtonWidget* btn);
void event_Home_btnMap_OnPressed(leButtonWidget* btn);
void event_Home_btnLight_OnPressed(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_Home(void); // called when Legato is initialized
leResult screenShow_Home(void); // called when screen is shown
void screenHide_Home(void); // called when screen is hidden
void screenDestroy_Home(void); // called when Legato is destroyed
void screenUpdate_Home(void); // called when Legato is updating

leWidget* screenGetRoot_Home(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void Home_OnShow(void); // called when this screen is shown
void Home_OnHide(void); // called when this screen is hidden
void Home_OnUpdate(void); // called when this screen is updated

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_HOME_H

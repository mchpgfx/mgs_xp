#ifndef LE_GEN_SCREEN_SCREEN_SETTINGS_H
#define LE_GEN_SCREEN_SCREEN_SETTINGS_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* Screen_Settings_Panel_0;
extern leButtonWidget* Screen_Settings_ButtonWidget_Back;
extern leImageWidget* Screen_Settings_ImageWidget_mgsLogo;
extern leLabelWidget* Screen_Settings_LabelWidget_0;
extern leImageWidget* Screen_Settings_ImageWidget_0;
extern leWidget* Screen_Settings_PanelWidget_0;
extern leWidget* Screen_Settings_PanelWidget_4;
extern leWidget* Screen_Settings_PanelWidget_1;
extern leWidget* Screen_Settings_PanelWidget_2;
extern leWidget* Screen_Settings_PanelWidget_3;
extern leLabelWidget* Screen_Settings_LabelWidget_1;
extern leButtonWidget* Screen_Settings_ButtonWidget_ChgThm;
extern leLabelWidget* Screen_Settings_LabelWidget_2;
extern leButtonWidget* Screen_Settings_ButtonWidget_Fah;
extern leButtonWidget* Screen_Settings_ButtonWidget_Cel;
extern leLabelWidget* Screen_Settings_LabelWidget_3;
extern leButtonWidget* Screen_Settings_ButtonWidget_EcoMode;
extern leLabelWidget* Screen_Settings_LabelWidget_4;
extern leButtonWidget* Screen_Settings_ButtonWidget_OtherNet;
extern leWidget* Screen_Settings_PanelWidget_5;
extern leImageWidget* Screen_Settings_ImageWidget_wifinamebkg;
extern leImageWidget* Screen_Settings_ImageWidget_WifiConn;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_Screen_Settings_ButtonWidget_Back_OnReleased(leButtonWidget* btn);
void event_Screen_Settings_ButtonWidget_ChgThm_OnReleased(leButtonWidget* btn);
void event_Screen_Settings_ButtonWidget_Fah_OnReleased(leButtonWidget* btn);
void event_Screen_Settings_ButtonWidget_Cel_OnReleased(leButtonWidget* btn);
void event_Screen_Settings_ButtonWidget_EcoMode_OnReleased(leButtonWidget* btn);
void event_Screen_Settings_ButtonWidget_OtherNet_OnReleased(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_Screen_Settings(void); // called when Legato is initialized
leResult screenShow_Screen_Settings(void); // called when screen is shown
void screenHide_Screen_Settings(void); // called when screen is hidden
void screenDestroy_Screen_Settings(void); // called when Legato is destroyed
void screenUpdate_Screen_Settings(void); // called when Legato is updating

leWidget* screenGetRoot_Screen_Settings(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void Screen_Settings_OnShow(void); // called when this screen is shown
void Screen_Settings_OnHide(void); // called when this screen is hidden
void Screen_Settings_OnUpdate(void); // called when this screen is updated

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_SCREEN_SETTINGS_H

#ifndef LE_GEN_SCREEN_SCREEN_WATER_Q_H
#define LE_GEN_SCREEN_SCREEN_WATER_Q_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* Screen_Water_Q_Panel_0;
extern leButtonWidget* Screen_Water_Q_ButtonWidget_Back;
extern leImageWidget* Screen_Water_Q_ImageWidget_mgsLogo;
extern leLabelWidget* Screen_Water_Q_LabelWidget_0;
extern leImageWidget* Screen_Water_Q_ImageWidget_0;
extern leWidget* Screen_Water_Q_PanelWidget_0;
extern leWidget* Screen_Water_Q_PanelWidget_4;
extern leWidget* Screen_Water_Q_PanelWidget_4_0;
extern leWidget* Screen_Water_Q_PanelWidget_1;
extern leWidget* Screen_Water_Q_PanelWidget_2;
extern leLabelWidget* Screen_Water_Q_LabelWidget_1;
extern leButtonWidget* Screen_Water_Q_ButtonWidget_StartCC;
extern leLabelWidget* Screen_Water_Q_LabelWidget_2;
extern leButtonWidget* Screen_Water_Q_ButtonWidget_ACCOff;
extern leButtonWidget* Screen_Water_Q_ButtonWidget_ACCOn;
extern leWidget* Screen_Water_Q_PanelWidget_3;
extern leLabelWidget* Screen_Water_Q_LabelWidget_3;
extern leWidget* Screen_Water_Q_PanelWidget_5;
extern leLabelWidget* Screen_Water_Q_LabelWidget_4;
extern leLabelWidget* Screen_Water_Q_LabelWidget_5;
extern leLabelWidget* Screen_Water_Q_LabelWidget_6;
extern leLabelWidget* Screen_Water_Q_LabelWidget_7;
extern leLabelWidget* Screen_Water_Q_LabelWidget_8;
extern leLabelWidget* Screen_Water_Q_LabelWidget_9;
extern leLabelWidget* Screen_Water_Q_LabelWidget_3_0;
extern leWidget* Screen_Water_Q_PanelWidget_5_0;
extern leLabelWidget* Screen_Water_Q_LabelWidget_FC;
extern leLabelWidget* Screen_Water_Q_LabelWidget_FC_Date;
extern leLabelWidget* Screen_Water_Q_LabelWidget_WatCh;
extern leLabelWidget* Screen_Water_Q_LabelWidget_WatCh_Date;
extern leButtonWidget* Screen_Water_Q_ButtonWidget_RstFilterClean;
extern leButtonWidget* Screen_Water_Q_ButtonWidget_RstWatChg;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_Screen_Water_Q_ButtonWidget_Back_OnReleased(leButtonWidget* btn);
void event_Screen_Water_Q_ButtonWidget_StartCC_OnReleased(leButtonWidget* btn);
void event_Screen_Water_Q_ButtonWidget_ACCOff_OnReleased(leButtonWidget* btn);
void event_Screen_Water_Q_ButtonWidget_ACCOn_OnReleased(leButtonWidget* btn);
void event_Screen_Water_Q_ButtonWidget_RstFilterClean_OnReleased(leButtonWidget* btn);
void event_Screen_Water_Q_ButtonWidget_RstWatChg_OnReleased(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_Screen_Water_Q(void); // called when Legato is initialized
leResult screenShow_Screen_Water_Q(void); // called when screen is shown
void screenHide_Screen_Water_Q(void); // called when screen is hidden
void screenDestroy_Screen_Water_Q(void); // called when Legato is destroyed
void screenUpdate_Screen_Water_Q(void); // called when Legato is updating

leWidget* screenGetRoot_Screen_Water_Q(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void Screen_Water_Q_OnShow(void); // called when this screen is shown
void Screen_Water_Q_OnHide(void); // called when this screen is hidden
void Screen_Water_Q_OnUpdate(void); // called when this screen is updated

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_SCREEN_WATER_Q_H

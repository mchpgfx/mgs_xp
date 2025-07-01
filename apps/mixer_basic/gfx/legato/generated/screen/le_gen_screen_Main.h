#ifndef LE_GEN_SCREEN_MAIN_H
#define LE_GEN_SCREEN_MAIN_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* Main_PanelWidget_0;
extern leWidget* Main_PanelWidget_0_0;
extern leButtonWidget* Main_btnInputCh1;
extern leButtonWidget* Main_btnInputCh2;
extern leButtonWidget* Main_btnInputCh3;
extern leButtonWidget* Main_btnInputCh4;
extern leButtonWidget* Main_btnRun;
extern leButtonWidget* Main_btnOutputCh1;
extern leButtonWidget* Main_btnOutputCh2;
extern leButtonWidget* Main_btnOutputCh3;
extern leButtonWidget* Main_btnOutputCh4;
extern leProgressBarWidget* Main_pbarAmpMain;
extern leWidget* Main_pnlMainGain;
extern leButtonWidget* Main_btnMainGain;
extern leButtonWidget* Main_btnMainMute;
extern leWidget* Main_pnlColorBarMain;
extern leLabelWidget* Main_lblOutput;
extern leLabelWidget* Main_lblMain;
extern leWidget* Main_pnlChnCtrlCh4;
extern leWidget* Main_pnlChnCtrlCh3;
extern leWidget* Main_pnlChnCtrlCh2;
extern leWidget* Main_pnlChnCtrlCh1;
extern leImageWidget* Main_ImageWidget_1;
extern leButtonWidget* Main_btnReset;
extern leImageWidget* Main_ImageWidget_0_1;
extern leImageWidget* Main_ImageWidget_0_2;
extern leImageWidget* Main_ImageWidget_0_2_0;
extern leImageWidget* Main_ImageWidget_0_2_1;
extern leImageWidget* Main_ImageWidget_0;
extern leImageWidget* Main_ImageWidget_0_0;
extern leImageWidget* Main_ImageWidget_0_0_0;
extern leImageWidget* Main_ImageWidget_0_0_1;
extern leButtonWidget* Main_btnCue_4;
extern leWidget* Main_pnlGain_4;
extern leButtonWidget* Main_btnM_4;
extern leButtonWidget* Main_btnS_4;
extern leProgressBarWidget* Main_pbarAmp_4;
extern leWidget* Main_pnlColorBar_4;
extern leWidget* Main_pnlLR_4;
extern leCircleWidget* Main_circLRKnob_4;
extern leLabelWidget* Main_lblChNum_4;
extern leLabelWidget* Main_lblL_4;
extern leLabelWidget* Main_lbl10_4;
extern leLabelWidget* Main_lblR_4;
extern leLabelWidget* Main_lbl5_4;
extern leLabelWidget* Main_lbl0_4;
extern leLabelWidget* Main_lbln5_4;
extern leLabelWidget* Main_lbln10_4;
extern leLabelWidget* Main_lbln15_4;
extern leLabelWidget* Main_lbln20_4;
extern leLabelWidget* Main_lbln25_4;
extern leLabelWidget* Main_lblChName_4;
extern leButtonWidget* Main_btnGainKnob_4;
extern leButtonWidget* Main_btnCue_3;
extern leWidget* Main_pnlGain_3;
extern leButtonWidget* Main_btnM_3;
extern leButtonWidget* Main_btnS_3;
extern leProgressBarWidget* Main_pbarAmp_3;
extern leWidget* Main_pnlColorBar_3;
extern leWidget* Main_pnlLR_3;
extern leCircleWidget* Main_circLRKnob_3;
extern leLabelWidget* Main_lblChNum_3;
extern leLabelWidget* Main_lblL_3;
extern leLabelWidget* Main_lbl10_3;
extern leLabelWidget* Main_lblR_3;
extern leLabelWidget* Main_lbl5_3;
extern leLabelWidget* Main_lbl0_3;
extern leLabelWidget* Main_lbln5_3;
extern leLabelWidget* Main_lbln10_3;
extern leLabelWidget* Main_lbln15_3;
extern leLabelWidget* Main_lbln20_3;
extern leLabelWidget* Main_lbln25_3;
extern leLabelWidget* Main_lblChName_3;
extern leButtonWidget* Main_btnGainKnob_3;
extern leButtonWidget* Main_btnCue_2;
extern leWidget* Main_pnlGain_2;
extern leButtonWidget* Main_btnM_2;
extern leButtonWidget* Main_btnS_2;
extern leProgressBarWidget* Main_pbarAmp_2;
extern leWidget* Main_pnlColorBar_2;
extern leWidget* Main_pnlLR_2;
extern leCircleWidget* Main_circLRKnob_2;
extern leLabelWidget* Main_lblChNum_2;
extern leLabelWidget* Main_lblL_2;
extern leLabelWidget* Main_lbl10_2;
extern leLabelWidget* Main_lblR_2;
extern leLabelWidget* Main_lbl5_2;
extern leLabelWidget* Main_lbl0_2;
extern leLabelWidget* Main_lbln5_2;
extern leLabelWidget* Main_lbln10_2;
extern leLabelWidget* Main_lbln15_2;
extern leLabelWidget* Main_lbln20_2;
extern leLabelWidget* Main_lbln25_2;
extern leLabelWidget* Main_lblChName_2;
extern leButtonWidget* Main_btnGainKnob_2;
extern leButtonWidget* Main_btnCue;
extern leWidget* Main_pnlGain;
extern leButtonWidget* Main_btnM;
extern leButtonWidget* Main_btnS;
extern leProgressBarWidget* Main_pbarAmp;
extern leWidget* Main_pnlColorBar;
extern leWidget* Main_pnlLR;
extern leCircleWidget* Main_circLRKnob;
extern leLabelWidget* Main_lblChNum;
extern leLabelWidget* Main_lblL;
extern leLabelWidget* Main_lbl10;
extern leLabelWidget* Main_lblR;
extern leLabelWidget* Main_lbl5;
extern leLabelWidget* Main_lbl0;
extern leLabelWidget* Main_lbln5;
extern leLabelWidget* Main_lbln10;
extern leLabelWidget* Main_lbln15;
extern leLabelWidget* Main_lbln20;
extern leLabelWidget* Main_lbln25;
extern leLabelWidget* Main_lblChName;
extern leButtonWidget* Main_btnGainKnob;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_Main_btnInputCh1_OnReleased(leButtonWidget* btn);
void event_Main_btnInputCh2_OnReleased(leButtonWidget* btn);
void event_Main_btnInputCh3_OnReleased(leButtonWidget* btn);
void event_Main_btnInputCh4_OnReleased(leButtonWidget* btn);
void event_Main_btnRun_OnReleased(leButtonWidget* btn);
void event_Main_btnOutputCh1_OnReleased(leButtonWidget* btn);
void event_Main_btnOutputCh2_OnReleased(leButtonWidget* btn);
void event_Main_btnOutputCh3_OnReleased(leButtonWidget* btn);
void event_Main_btnOutputCh4_OnReleased(leButtonWidget* btn);
void event_Main_btnMainMute_OnReleased(leButtonWidget* btn);
void event_Main_btnReset_OnReleased(leButtonWidget* btn);
void event_Main_btnCue_4_OnReleased(leButtonWidget* btn);
void event_Main_btnM_4_OnReleased(leButtonWidget* btn);
void event_Main_btnS_4_OnReleased(leButtonWidget* btn);
void event_Main_btnCue_3_OnReleased(leButtonWidget* btn);
void event_Main_btnM_3_OnReleased(leButtonWidget* btn);
void event_Main_btnS_3_OnReleased(leButtonWidget* btn);
void event_Main_btnCue_2_OnReleased(leButtonWidget* btn);
void event_Main_btnM_2_OnReleased(leButtonWidget* btn);
void event_Main_btnS_2_OnReleased(leButtonWidget* btn);
void event_Main_btnCue_OnReleased(leButtonWidget* btn);
void event_Main_btnM_OnReleased(leButtonWidget* btn);
void event_Main_btnS_OnReleased(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_Main(void); // called when Legato is initialized
leResult screenShow_Main(void); // called when screen is shown
void screenHide_Main(void); // called when screen is hidden
void screenDestroy_Main(void); // called when Legato is destroyed
void screenUpdate_Main(void); // called when Legato is updating

leWidget* screenGetRoot_Main(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void Main_OnShow(void); // called when this screen is shown
void Main_OnHide(void); // called when this screen is hidden
void Main_OnUpdate(void); // called when this screen is updated

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_MAIN_H

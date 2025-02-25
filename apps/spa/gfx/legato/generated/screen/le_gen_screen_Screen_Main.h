#ifndef LE_GEN_SCREEN_SCREEN_MAIN_H
#define LE_GEN_SCREEN_SCREEN_MAIN_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* Screen_Main_BackgroundPanel;
extern leButtonWidget* Screen_Main_ButtonWidget_Settings;
extern leButtonWidget* Screen_Main_ButtonWidget_WaterQ;
extern leLabelWidget* Screen_Main_LabelWidget_SelectReg;
extern leLabelWidget* Screen_Main_LabelWidget_ControlDisp;
extern leImageWidget* Screen_Main_ImageWidget_Regions;
extern leButtonWidget* Screen_Main_ButtonWidget_Reg2;
extern leButtonWidget* Screen_Main_ButtonWidget_Reg1;
extern leButtonWidget* Screen_Main_ButtonWidget_Reg3;
extern leButtonWidget* Screen_Main_ButtonWidget_Reg4;
extern leWidget* Screen_Main_EditPanelWidget;
extern leWidget* Screen_Main_PanelWidget_0;
extern leWidget* Screen_Main_PanelWidget_1;
extern leImageWidget* Screen_Main_ImageWidget_mgsLogo;
extern leWidget* Screen_Main_PanelWidget_WaterTemp;
extern leWidget* Screen_Main_PanelWidget_SelColors;
extern leWidget* Screen_Main_PanelWidget_JetCtrl;
extern leWidget* Screen_Main_PanelWidget_MP;
extern leButtonWidget* Screen_Main_ButtonWidget_MP;
extern leLabelWidget* Screen_Main_LabelWidget_WaterTemp;
extern leButtonWidget* Screen_Main_ButtonWidget_IncTemp;
extern leButtonWidget* Screen_Main_ButtonWidget_DecTemp;
extern leLabelWidget* Screen_Main_LabelWidget_Deg;
extern leLabelWidget* Screen_Main_LabelWidget_SelectedReg;
extern leLabelWidget* Screen_Main_LabelWidget_Brightness;
extern leButtonWidget* Screen_Main_ButtonWidget_Red;
extern leButtonWidget* Screen_Main_ButtonWidget_Orange;
extern leButtonWidget* Screen_Main_ButtonWidget_Yellow;
extern leButtonWidget* Screen_Main_ButtonWidget_Green;
extern leButtonWidget* Screen_Main_ButtonWidget_Cyan;
extern leButtonWidget* Screen_Main_ButtonWidget_Purple;
extern leButtonWidget* Screen_Main_ButtonWidget_Pink;
extern leButtonWidget* Screen_Main_ButtonWidget_Radial;
extern leWidget* Screen_Main_PanelWidget_BrgGen;
extern leWidget* Screen_Main_PanelWidget_BrgLight;
extern leWidget* Screen_Main_PanelWidget_BrgDark;
extern leButtonWidget* Screen_Main_ButtonWidget_Brg;
extern leButtonWidget* Screen_Main_ButtonWidget_JetDec;
extern leButtonWidget* Screen_Main_ButtonWidget_JetInc;
extern leImageWidget* Screen_Main_ImageWidget_bubbles;
extern leLabelWidget* Screen_Main_LabelWidget_BubbleLevel;
extern leWidget* Screen_Main_PanelWidget_Bkg;
extern leImageWidget* Screen_Main_ImageWidget_SongCover;
extern leLabelWidget* Screen_Main_LabelWidget_SongTitle;
extern leLabelWidget* Screen_Main_LabelWidget_ArtistName;
extern leWidget* Screen_Main_PanelWidget_4;
extern leButtonWidget* Screen_Main_ButtonWidget_Prev;
extern leButtonWidget* Screen_Main_ButtonWidget_PlayPause;
extern leButtonWidget* Screen_Main_ButtonWidget_Next;
extern leImageWidget* Screen_Main_ImageWidget_Volume;
extern leWidget* Screen_Main_PanelWidget_Vol;
extern leWidget* Screen_Main_PanelWidget_VolLight;
extern leWidget* Screen_Main_PanelWidget_VolDark;
extern leImageWidget* Screen_Main_MicrochipLogo;
extern leImageWidget* Screen_Main_MGSLogo;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_Screen_Main_ButtonWidget_Settings_OnReleased(leButtonWidget* btn);
void event_Screen_Main_ButtonWidget_WaterQ_OnReleased(leButtonWidget* btn);
void event_Screen_Main_ButtonWidget_Reg2_OnReleased(leButtonWidget* btn);
void event_Screen_Main_ButtonWidget_Reg1_OnReleased(leButtonWidget* btn);
void event_Screen_Main_ButtonWidget_Reg3_OnReleased(leButtonWidget* btn);
void event_Screen_Main_ButtonWidget_Reg4_OnReleased(leButtonWidget* btn);
void event_Screen_Main_ButtonWidget_MP_OnReleased(leButtonWidget* btn);
void event_Screen_Main_ButtonWidget_IncTemp_OnPressed(leButtonWidget* btn);
void event_Screen_Main_ButtonWidget_IncTemp_OnReleased(leButtonWidget* btn);
void event_Screen_Main_ButtonWidget_DecTemp_OnPressed(leButtonWidget* btn);
void event_Screen_Main_ButtonWidget_DecTemp_OnReleased(leButtonWidget* btn);
void event_Screen_Main_ButtonWidget_Red_OnPressed(leButtonWidget* btn);
void event_Screen_Main_ButtonWidget_Orange_OnPressed(leButtonWidget* btn);
void event_Screen_Main_ButtonWidget_Yellow_OnPressed(leButtonWidget* btn);
void event_Screen_Main_ButtonWidget_Green_OnPressed(leButtonWidget* btn);
void event_Screen_Main_ButtonWidget_Cyan_OnPressed(leButtonWidget* btn);
void event_Screen_Main_ButtonWidget_Purple_OnPressed(leButtonWidget* btn);
void event_Screen_Main_ButtonWidget_Pink_OnPressed(leButtonWidget* btn);
void event_Screen_Main_ButtonWidget_Radial_OnPressed(leButtonWidget* btn);
void event_Screen_Main_ButtonWidget_JetDec_OnPressed(leButtonWidget* btn);
void event_Screen_Main_ButtonWidget_JetDec_OnReleased(leButtonWidget* btn);
void event_Screen_Main_ButtonWidget_JetInc_OnPressed(leButtonWidget* btn);
void event_Screen_Main_ButtonWidget_JetInc_OnReleased(leButtonWidget* btn);
void event_Screen_Main_ButtonWidget_Prev_OnReleased(leButtonWidget* btn);
void event_Screen_Main_ButtonWidget_PlayPause_OnPressed(leButtonWidget* btn);
void event_Screen_Main_ButtonWidget_PlayPause_OnReleased(leButtonWidget* btn);
void event_Screen_Main_ButtonWidget_Next_OnReleased(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_Screen_Main(void); // called when Legato is initialized
leResult screenShow_Screen_Main(void); // called when screen is shown
void screenHide_Screen_Main(void); // called when screen is hidden
void screenDestroy_Screen_Main(void); // called when Legato is destroyed
void screenUpdate_Screen_Main(void); // called when Legato is updating

leWidget* screenGetRoot_Screen_Main(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void Screen_Main_OnShow(void); // called when this screen is shown
void Screen_Main_OnHide(void); // called when this screen is hidden
void Screen_Main_OnUpdate(void); // called when this screen is updated

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_SCREEN_MAIN_H

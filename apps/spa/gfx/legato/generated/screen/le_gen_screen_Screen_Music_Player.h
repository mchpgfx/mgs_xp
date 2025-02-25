#ifndef LE_GEN_SCREEN_SCREEN_MUSIC_PLAYER_H
#define LE_GEN_SCREEN_SCREEN_MUSIC_PLAYER_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* Screen_Music_Player_Panel_0;
extern leImageWidget* Screen_Music_Player_ImageWidget_mgsLogo;
extern leLabelWidget* Screen_Music_Player_LabelWidget_0;
extern leImageWidget* Screen_Music_Player_ImageWidget_0;
extern leWidget* Screen_Music_Player_PanelWidget_0;
extern leWidget* Screen_Music_Player_PanelWidget_4;
extern leButtonWidget* Screen_Music_Player_ButtonWidget_Back;
extern leWidget* Screen_Music_Player_PanelWidget_2;
extern leWidget* Screen_Music_Player_PanelWidget_3;
extern leLabelWidget* Screen_Music_Player_LabelWidget_2;
extern leWidget* Screen_Music_Player_PanelWidget_5_0;
extern leImageWidget* Screen_Music_Player_ImageWidget_selBT;
extern leImageWidget* Screen_Music_Player_ImageWidget_2_0;
extern leLabelWidget* Screen_Music_Player_LabelWidget_3;
extern leButtonWidget* Screen_Music_Player_ButtonWidget_SearchBT;
extern leWidget* Screen_Music_Player_PanelWidget_BT1;
extern leWidget* Screen_Music_Player_PanelWidget_BT2;
extern leWidget* Screen_Music_Player_PanelWidget_BT3;
extern leButtonWidget* Screen_Music_Player_ButtonWidget_BT1;
extern leButtonWidget* Screen_Music_Player_ButtonWidget_BT2;
extern leButtonWidget* Screen_Music_Player_ButtonWidget_BT3;
extern leImageWidget* Screen_Music_Player_ImageWidget_SongPIc;
extern leLabelWidget* Screen_Music_Player_LabelWidget_ST;
extern leLabelWidget* Screen_Music_Player_LabelWidget_AN;
extern leWidget* Screen_Music_Player_PanelWidget_MP;
extern leImageWidget* Screen_Music_Player_ImageWidget_Volume;
extern leButtonWidget* Screen_Music_Player_ButtonWidget_Prev;
extern leButtonWidget* Screen_Music_Player_ButtonWidget_PlayPause;
extern leButtonWidget* Screen_Music_Player_ButtonWidget_Next;
extern leWidget* Screen_Music_Player_PanelWidget_Vol;
extern leWidget* Screen_Music_Player_PanelWidget_VolLight;
extern leWidget* Screen_Music_Player_PanelWidget_VolDark;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_Screen_Music_Player_ButtonWidget_Back_OnReleased(leButtonWidget* btn);
void event_Screen_Music_Player_ButtonWidget_SearchBT_OnPressed(leButtonWidget* btn);
void event_Screen_Music_Player_ButtonWidget_SearchBT_OnReleased(leButtonWidget* btn);
void event_Screen_Music_Player_ButtonWidget_Prev_OnReleased(leButtonWidget* btn);
void event_Screen_Music_Player_ButtonWidget_PlayPause_OnPressed(leButtonWidget* btn);
void event_Screen_Music_Player_ButtonWidget_PlayPause_OnReleased(leButtonWidget* btn);
void event_Screen_Music_Player_ButtonWidget_Next_OnReleased(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_Screen_Music_Player(void); // called when Legato is initialized
leResult screenShow_Screen_Music_Player(void); // called when screen is shown
void screenHide_Screen_Music_Player(void); // called when screen is hidden
void screenDestroy_Screen_Music_Player(void); // called when Legato is destroyed
void screenUpdate_Screen_Music_Player(void); // called when Legato is updating

leWidget* screenGetRoot_Screen_Music_Player(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void Screen_Music_Player_OnShow(void); // called when this screen is shown
void Screen_Music_Player_OnHide(void); // called when this screen is hidden
void Screen_Music_Player_OnUpdate(void); // called when this screen is updated

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_SCREEN_MUSIC_PLAYER_H

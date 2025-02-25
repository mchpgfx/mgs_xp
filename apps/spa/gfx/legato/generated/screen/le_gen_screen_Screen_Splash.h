#ifndef LE_GEN_SCREEN_SCREEN_SPLASH_H
#define LE_GEN_SCREEN_SCREEN_SPLASH_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* Screen_Splash_Panel_0;
extern leWidget* Screen_Splash_MidLine;
extern leWidget* Screen_Splash_PanelWidget_0;
extern leWidget* Screen_Splash_PanelWidget_1;
extern leImageWidget* Screen_Splash_MicrochipLogo;
extern leImageWidget* Screen_Splash_MGSLogo;

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_Screen_Splash(void); // called when Legato is initialized
leResult screenShow_Screen_Splash(void); // called when screen is shown
void screenHide_Screen_Splash(void); // called when screen is hidden
void screenDestroy_Screen_Splash(void); // called when Legato is destroyed
void screenUpdate_Screen_Splash(void); // called when Legato is updating

leWidget* screenGetRoot_Screen_Splash(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void Screen_Splash_OnShow(void); // called when this screen is shown
void Screen_Splash_OnHide(void); // called when this screen is hidden
void Screen_Splash_OnUpdate(void); // called when this screen is updated

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_SCREEN_SPLASH_H

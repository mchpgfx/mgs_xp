#ifndef LEGATO_INIT_SCHEME_H
#define LEGATO_INIT_SCHEME_H

#include "gfx/legato/legato.h"

extern const leScheme WhiteScheme;
extern const leScheme BkgScheme;
extern const leScheme EditPanel;
extern const leScheme FontScheme;
extern const leScheme Scheme_Light;
extern const leScheme SliderLightScheme;
extern const leScheme SliderDarkScheme;
extern const leScheme EditPanel_Dark;
extern const leScheme Scheme_Dark;
extern const leScheme BkgScheme_Dark;
extern const leScheme SliderLightScheme_Dark;
extern const leScheme SliderDarkScheme_Dark;

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

void legato_initialize_schemes(void);

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LEGATO_INIT_SCHEME_H

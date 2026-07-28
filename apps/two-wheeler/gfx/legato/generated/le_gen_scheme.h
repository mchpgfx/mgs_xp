#ifndef LEGATO_INIT_SCHEME_H
#define LEGATO_INIT_SCHEME_H

#include "gfx/legato/legato.h"

extern const leScheme WhiteScheme;
extern const leScheme GaugeScheme;
extern const leScheme GrayScheme;
extern const leScheme GreenScheme;
extern const leScheme ClearScheme;
extern const leScheme panel_black;
extern const leScheme text_darkslategray;
extern const leScheme text_lightslategray;
extern const leScheme text_white;
extern const leScheme text_deepskyblue;
extern const leScheme text_chartreuse;
extern const leScheme text_darkorange;
extern const leScheme text_black;
extern const leScheme panel_white;

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

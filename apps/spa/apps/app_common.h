/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef _APP_COMMON_H
#define _APP_COMMON_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************
#define APP_LE_SCHEME(widget, scheme) widget->fn->setScheme(widget, setScheme)
#define APP_LE_SETVISIBLE(widget, visible) widget->fn->setVisible(widget, visible)
#define APP_LE_GETVISIBLE(widget) widget->fn->getVisible(widget)
#define APP_LE_GETX(widget) widget->fn->getX(widget)
#define APP_LE_GETY(widget) widget->fn->getY(widget)
#define APP_LE_SETX(widget, xpos) widget->fn->setX(widget, xpos)
#define APP_LE_SETY(widget, ypos) widget->fn->setY(widget, ypos)
#define APP_LE_GETWIDTH(widget) widget->fn->getWidth(widget)
#define APP_LE_GETHEIGHT(widget) widget->fn->getHeight(widget)
#define APP_LE_SETWIDTH(widget, width) widget->fn->setWidth(widget, width)
#define APP_LE_SETHEIGHT(widget, height) widget->fn->setHeight(widget, height)
#define APP_LE_SETEVENTFILTER(widget, filter) widget->fn->installEventFilter(widget, filter)
#define APP_LE_SHOWIMAGE_IDX(imageSequenceWidget, idx) imageSequenceWidget->fn->showImage(imageSequenceWidget, idx)
#define APP_LE_SHOWIMAGE_NEXT(imageSequenceWidget) imageSequenceWidget->fn->showNextImage(imageSequenceWidget)
#define APP_LE_SETLABELSTRING(labelWidget, string) labelWidget->fn->setString(labelWidget, (leString*)&string);
#define APP_LE_INVALIDATE(widget) widget->fn->invalidate(widget)
#define APP_LE_SETSCHEME(widget, scheme) widget->fn->setScheme(widget, scheme)
#define APP_LE_SETLABELDYNSTRING(labelWidget, lStr, cStr) {lStr.fn->setFromCStr(&lStr, cStr); \
                                                           labelWidget->fn->setString(labelWidget, (leString*)&lStr); }
#define APP_LE_SETPRESSEDIMAGE(widget, image) widget->fn->setPressedImage(widget, (leImage*)&image)
#define APP_LE_SETRELEASEDIMAGE(widget, image) widget->fn->setReleasedImage(widget, (leImage*)&image)
    
#define APP_LE_SETPRESSED(button, pressed) button->fn->setPressed(button, pressed)

#define DEFAULT_BTN_CORNER_RADIUS 10
#define DEFAULT_PANEL_CORNER_RADIUS 16
#define DEFAULT_BAR_RADIUS 2
#define NUM_OF_REGIONS 5
#define DEFAULT_WATER_TEMP 10
#define DEFAULT_JET_SPEED 7
#define MAX_CSTR_STR_SIZE 15

#define BRIGHTNESS_PANEL_OFFSET 566
#define BRIGHTNESS_PANEL_EXTRA_OFFSET 64
#define MAX_BRIGHTNESS_PANEL_WIDTH 302
#define BRIGHTNESS_BAR_EXTRA_OFFSET 8
#define BRIGHTNESS_X_TO_PERCENT(x)  (((float)x / MAX_BRIGHTNESS_PANEL_WIDTH) * 100)
#define BRIGHTNESS_PERCENT_TO_X(x)  ((x * MAX_BRIGHTNESS_PANEL_WIDTH)/100)
    
#define VOL_MUSIC_PANEL_X_OFFSET 620
#define VOL_MUSIC_PANEL_OFFSET 10
#define VOL_MUSIC_PANEL_EXTRA_OFFSET 12
#define MAX_MUSIC_VOL_PANEL_WIDTH 220
#define VOL_MAIN_PANEL_X_OFFSET (316 + 56 + 205)
#define VOL_MAIN_BAR_PANEL_EXTRA_OFFSET 10
#define MAX_MAIN_VOL_PANEL_WIDTH 120
#define VOLUME_MAIN_TO_MUSIC_X(x) (((float)x / MAX_MAIN_VOL_PANEL_WIDTH) * MAX_MUSIC_VOL_PANEL_WIDTH)
#define VOLUME_MUSIC_TO_MAIN_X(x) (((float)x / MAX_MUSIC_VOL_PANEL_WIDTH) * MAX_MAIN_VOL_PANEL_WIDTH)

#define VOLUME_MAIN_X_TO_PERCENT(x) (((float)x / MAX_MAIN_VOL_PANEL_WIDTH) * 100)
#define VOLUME_MUSIC_X_TO_PERCENT(x) (((float)x / MAX_MUSIC_VOL_PANEL_WIDTH) * 100)

#define VOLUME_PERCENT_TO_MAIN_X(x)  ((x * MAX_MAIN_VOL_PANEL_WIDTH)/100)
#define VOLUME_PERCENT_TO_MUSIC_X(x)  ((x * MAX_MUSIC_VOL_PANEL_WIDTH)/100)

typedef enum
{
    ALL_REGIONS = 0,
    REGION_1,
    REGION_2,
    REGION_3,
    REGION_4
}regions;

typedef enum
{
    RED = 0,
    ORANGE,
    YELLOW,
    GREEN,
    CYAN,
    PURPLE,
    PINK,
    RADIAL,
    ERROR_COLOR
}colors;

struct brightnessValues
{
    uint32_t brghtCoord;
    uint32_t brghtPercent;
};
struct musicVol
{
    uint32_t volCoordMainScreen;
    uint32_t volCoordMusicScreen;
    uint32_t volPercent;
};
struct userSettingsStruct
{
    bool tempFahrSetting;
    bool ecoActSetting;
    bool autoCleanCycle;
    bool musicPlaying;
    bool lightTheme;
    struct brightnessValues ledsBrightness;
    struct musicVol musicVolume;
};

// *****************************************************************************
// *****************************************************************************
// Section: Helper Functions
// *****************************************************************************
// *****************************************************************************
void set_direct_boot(bool enable);
bool get_direct_boot(void);
uint8_t get_selected_region(void);
void set_selected_region(uint8_t reg);
colors get_region_color(void);
void set_region_color(colors clr);
uint8_t get_region_temp(void);
void set_region_temp(uint8_t temp);
uint8_t get_region_jet(void);
void set_region_jet(uint8_t jet);
uint32_t get_light_brightness_coord(void);
uint32_t get_light_brightness_percent(void);
void set_light_brightness(uint32_t brightness);
uint32_t get_music_volume_coord_mains(void);
uint32_t get_music_volume_coord_musics(void);
uint32_t get_music_volume_percent(void);
void set_music_volume_from_mains(int32_t volume);
void set_music_volume_from_musics(int32_t volume);
uint32_t get_music_volume_percent(void);

bool get_music_playing(void);
void set_music_playing(bool play);
bool get_light_theme(void);
void set_light_theme(bool theme);

bool get_fahr_temp_setting(void);
void set_fahr_temp_setting(bool tempFahr);
bool get_eco_setting(void);
void set_eco_setting(bool eco);
bool get_auto_clean_setting(void);
void set_auto_clean_setting(bool autoClean);
//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _APP_COMMON_H */

/*******************************************************************************
 End of File
 */


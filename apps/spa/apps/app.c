/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/
#include "app.h"

APP_DATA appData;
uint8_t selectedRegion = ALL_REGIONS;
uint8_t regColor[NUM_OF_REGIONS] = {RED, RED, RED, RED, RED};
uint8_t regTemp[NUM_OF_REGIONS] = {DEFAULT_WATER_TEMP, DEFAULT_WATER_TEMP, DEFAULT_WATER_TEMP, DEFAULT_WATER_TEMP, DEFAULT_WATER_TEMP};
uint8_t regJet[NUM_OF_REGIONS] = {DEFAULT_JET_SPEED, DEFAULT_JET_SPEED, DEFAULT_JET_SPEED, DEFAULT_JET_SPEED, DEFAULT_JET_SPEED};
struct userSettingsStruct userSettings;
bool appDirectUIBoot = false;

void set_direct_boot(bool enabled)
{
    appDirectUIBoot = enabled;
}

bool get_direct_boot(void)
{
    return appDirectUIBoot;
}

uint8_t get_selected_region()
{
    return selectedRegion;
}
void set_selected_region(uint8_t reg)
{
    selectedRegion = reg;
}

colors get_region_color()
{
    return regColor[selectedRegion];
}
void set_region_color(colors clr)
{
    // if all regions are selected, update individual array positions also
    if (selectedRegion == ALL_REGIONS)
    {
        regColor[REGION_1] = regColor[REGION_2] = regColor[REGION_3] = regColor[REGION_4] = clr;
    }
    regColor[selectedRegion] = clr;
}

uint8_t get_region_temp()
{
    return regTemp[selectedRegion];
}
void set_region_temp(uint8_t temp)
{
    // if all regions are selected, update individual array positions also
    if (selectedRegion == ALL_REGIONS)
    {
        regTemp[REGION_1] = regTemp[REGION_2] = regTemp[REGION_3] = regTemp[REGION_4] = temp;
    }
    regTemp[selectedRegion] = temp;
}

uint8_t get_region_jet()
{
    return regJet[selectedRegion];
}
void set_region_jet(uint8_t temp)
{
    // if all regions are selected, update individual array positions also
    if (selectedRegion == ALL_REGIONS)
    {
        regJet[REGION_1] = regJet[REGION_2] = regJet[REGION_3] = regJet[REGION_4] = temp;
    }
    regJet[selectedRegion] = temp;
}

void init_regions()
{
    set_selected_region(ALL_REGIONS);
    set_region_color(RADIAL);
    set_region_temp(DEFAULT_WATER_TEMP);
    set_region_jet(DEFAULT_JET_SPEED);
}

bool get_fahr_temp_setting()
{
    return userSettings.tempFahrSetting;
}
void set_fahr_temp_setting(bool tempFahr)
{
    userSettings.tempFahrSetting = tempFahr;
}
bool get_eco_setting()
{
    return userSettings.ecoActSetting;
}
void set_eco_setting(bool eco)
{
    userSettings.ecoActSetting = eco;
}
bool get_auto_clean_setting()
{
    return userSettings.autoCleanCycle;
}
void set_auto_clean_setting(bool autoClean)
{
    userSettings.autoCleanCycle = autoClean;
}

bool get_music_playing()
{
    return userSettings.musicPlaying;
}
void set_music_playing(bool play)
{
    userSettings.musicPlaying = play;
}
bool get_light_theme()
{
    return userSettings.lightTheme;
}
void set_light_theme(bool theme)
{
    userSettings.lightTheme = theme;
}

uint32_t get_light_brightness_coord()
{
    return userSettings.ledsBrightness.brghtCoord;
}
uint32_t get_light_brightness_percent()
{
    return userSettings.ledsBrightness.brghtPercent;
}
void set_light_brightness(uint32_t brightness)
{
    userSettings.ledsBrightness.brghtCoord = brightness;
    userSettings.ledsBrightness.brghtPercent = BRIGHTNESS_X_TO_PERCENT(brightness);
}
uint32_t get_music_volume_coord_mains()
{
    return userSettings.musicVolume.volCoordMainScreen;
}
uint32_t get_music_volume_coord_musics()
{
    return userSettings.musicVolume.volCoordMusicScreen;
}
void set_music_volume_from_mains(int32_t volume)
{
    userSettings.musicVolume.volCoordMainScreen = volume;
    userSettings.musicVolume.volCoordMusicScreen = VOLUME_MAIN_TO_MUSIC_X(volume);
    userSettings.musicVolume.volPercent = VOLUME_MAIN_X_TO_PERCENT(volume);
}
void set_music_volume_from_musics(int32_t volume)
{
    userSettings.musicVolume.volCoordMainScreen = VOLUME_MUSIC_TO_MAIN_X(volume);
    userSettings.musicVolume.volCoordMusicScreen = volume;
    userSettings.musicVolume.volPercent = VOLUME_MUSIC_X_TO_PERCENT(volume);
}
uint32_t get_music_volume_percent()
{
    return userSettings.musicVolume.volPercent;
}

void init_user_settings()
{
    userSettings.lightTheme = true;
    userSettings.tempFahrSetting = true;
    userSettings.ecoActSetting = false;
    userSettings.autoCleanCycle = false;
    userSettings.ledsBrightness.brghtPercent = 50;
    userSettings.ledsBrightness.brghtCoord = MAX_BRIGHTNESS_PANEL_WIDTH / 2;
    userSettings.musicPlaying = false;
    userSettings.musicVolume.volPercent = 50;
    userSettings.musicVolume.volCoordMainScreen = VOLUME_PERCENT_TO_MAIN_X(50);
    userSettings.musicVolume.volCoordMusicScreen = VOLUME_PERCENT_TO_MUSIC_X(50);
}
// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    appData.state = APP_STATE_INIT;
    init_regions();
    init_user_settings();
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */
void APP_Tasks ( void )
{
    switch ( appData.state )
    {
        case APP_STATE_INIT:
        {
            bool appInitialized = true;
            if (appInitialized)
            {
                appData.state = APP_STATE_SERVICE_TASKS;
            }
            break;
        }
        case APP_STATE_SERVICE_TASKS:
        {
            break;
        }
        default:
        {
            break;
        }
    }
}


/*******************************************************************************
 End of File
 */

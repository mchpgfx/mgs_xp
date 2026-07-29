/*******************************************************************************
  Application for Screen - Home

  Company:
    Microchip Technology Inc.

  File Name:
    app_screen_home.c

  Summary:
    Home screen application logic for the electric motorcycle cluster demo.

  Description:
    This module implements the Home screen functionality including:

    - Gauge Animation: Speedometer with animated needle sweep on startup,
      followed by a driving simulation that cycles through accelerate,
      cruise, and decelerate phases.

    - Power/Battery Display: Real-time power consumption (kW) and battery
      level indicators with animated progress bars. Battery drains during
      driving and triggers a charging state when depleted.

    - Battery Icon Flashing: When battery is depleted, the battery icon
      flashes at 500ms intervals until fully recharged.

    - Double-Tap Animation Cycling: Double-tapping the touch panel area
      cycles through available background animations (orb, wave, etc.).

    - Shortcut Button Bar: Six shortcut buttons (Camera, Music, Map, Home,
      Phone, Light) with visual selection feedback. The Map button navigates
      to the NavScreen.

    - Camera Preview: The Camera button toggles a live USB camera preview.
      Frames are captured as uncompressed YUYV and pushed straight to a display
      overlay plane by app_camera.c, bypassing Legato entirely, so the preview
      costs the UI render loop almost nothing. See app_camera.h for the module
      layering.

    - Needle Rendering: Custom draw surface callback renders the speedometer
      needle using vector graphics at the current gauge angle.
 *******************************************************************************/

#include "gfx/legato/generated/le_gen_init.h"
#include "app_gauge.h"
#include "app_anim.h"
#include "app_metrics.h"
#include "app_sys_timer.h"
#include "app_camera.h"

#include <stdio.h>
/*******************************************************************************
 * Configuration Constants
 ******************************************************************************/
#define BATTERY_FLASH_INTERVAL_MS 500   // Battery icon flash rate when depleted
#define DOUBLE_TAP_THRESHOLD_MS 300     // Max time between taps for double-tap

/* Camera preview placement on the 800x480 cluster. The overlay plane scales the
   camera frame to this rectangle in hardware, so these values are free to
   change without affecting CPU cost. */
#define CAMERA_PREVIEW_X      160
#define CAMERA_PREVIEW_Y      60
#define CAMERA_PREVIEW_WIDTH  480
#define CAMERA_PREVIEW_HEIGHT 360

/*******************************************************************************
 * Module Variables
 ******************************************************************************/
static ButtonAnimState_t homeButtonState;   // Shortcut button animation state
static uint32_t lastTapTime = 0;            // Timestamp for double-tap detection

static SYS_TIME_HANDLE timer = SYS_TIME_HANDLE_INVALID;
volatile unsigned int tickCountMS = 0;

/*******************************************************************************
 * Home_GetButtonByIndex
 * Maps button index enum to the corresponding widget pointer.
 ******************************************************************************/
static leButtonWidget* Home_GetButtonByIndex(ButtonIndex_t idx)
{
    switch (idx)
    {
        case BTN_IDX_CAMERA: return Home_btnCamera;
        case BTN_IDX_MUSIC:  return Home_btnMusic;
        case BTN_IDX_MAP:    return Home_btnMap;
        case BTN_IDX_HOME:   return Home_btnHome;
        case BTN_IDX_PHONE:  return Home_btnPhone;
        case BTN_IDX_LIGHT:  return Home_btnLight;
        default: return NULL;
    }
    
}
void event_Home_ButtonWidgetQuickStart_OnReleased(leButtonWidget* btn)
{
    (void)btn;
}

static void APP_UI_Timer_Callback ( uintptr_t context)
{
    tickCountMS++;
}

/*******************************************************************************
 * Home_CycleAnimation
 * Cycles through available background animations (orb, wave, etc.).
 * Called on double-tap or Home button press.
 ******************************************************************************/

/*******************************************************************************
 * Home_TouchPanelEventFilter
 * Event filter for the touch panel widget. Detects double-tap gestures
 * and triggers animation cycling when detected.
 ******************************************************************************/
static leBool Home_TouchPanelEventFilter(leWidget* target, leWidgetEvent* evt, void* data)
{
    (void)data;

    if (evt->id == LE_EVENT_TOUCH_DOWN)
    {
        uint32_t elapsedMs = tickCountMS - lastTapTime;

        if (elapsedMs <= DOUBLE_TAP_THRESHOLD_MS && lastTapTime != 0)
        {
            lastTapTime = 0;
        }
        else
        {
            lastTapTime = tickCountMS;
        }

        leWidgetEvent_Accept(evt, target);
        return LE_TRUE;
    }

    return LE_FALSE;
}

/*******************************************************************************
 * Screen Lifecycle Functions
 ******************************************************************************/

/*******************************************************************************
 * Home_OnShow
 * Called when screen becomes visible. Initializes gauge system, button
 * animations, and registers touch panel event filter for double-tap detection.
 ******************************************************************************/
void Home_OnShow(void)
{
    Gauge_Init((leFont*)&Unbounded110, (leFont*)&Unbounded28, (leFont*)&Unbounded32, (leFont*)&GeistMono14);
    PowerBattery_Init(Home_imgRegenBar, Home_image_RegenBar, Home_image_DischargeBar);
    Buttons_Init(&homeButtonState, Home_GetButtonByIndex);
    Metrics_Init();

    leWidgetEventFilter touchFilter = { Home_TouchPanelEventFilter, NULL };
    Home_touchPanel->fn->installEventFilter(Home_touchPanel, touchFilter);

    if (timer == SYS_TIME_HANDLE_INVALID)
    {
        timer = SYS_TIME_CallbackRegisterMS(APP_UI_Timer_Callback,
                                            1,
                                            1,
                                            SYS_TIME_PERIODIC);
    }
}

/*******************************************************************************
 * Home_OnHide
 * Called when screen is hidden. Resets gauge state machine for next show.
 ******************************************************************************/
void Home_OnHide(void)
{
    /* Release the camera and its overlay plane so the preview does not stay
       composited over whichever screen comes next. */
    Camera_Stop();

    Gauge_Reset();
}

extern void APP_Tasks ( void );

/*******************************************************************************
 * Home_OnUpdate
 * Called every frame. Updates gauge animation, power/battery indicators,
 * button states, and handles battery icon flashing when depleted.
 ******************************************************************************/
void Home_OnUpdate(void)
{
    uint32_t currentTime = tickCountMS;

    Buttons_Update(&homeButtonState, BUTTON_UPDATE_INTERVAL_MS);
    if (Gauge_Update(Home_lblGauge, NULL, GAUGE_UPDATE_INTERVAL_MS))
    {
        PowerBattery_Update(Home_label_PowerValue, Home_image_imgPowerProg,
                            Home_label_BattValue, Home_image_imgBatProg,
                            Home_label_Range,
                            Home_label_OdoValue, Home_label_TripValue,
                            Home_imgRegenBar,
                            Home_image_RegenBar, Home_image_DischargeBar);
    }

    // Flash battery icon while depleted and charging
    static uint32_t lastBatteryFlashTime = 0;
    static bool batteryIconVisible = true;

    if (Gauge_IsBatteryDepleted())
    {
        uint32_t flashElapsed = currentTime - lastBatteryFlashTime;
        if (flashElapsed >= BATTERY_FLASH_INTERVAL_MS)
        {
            lastBatteryFlashTime = currentTime;
            batteryIconVisible = !batteryIconVisible;
            Home_image_iconBattery->fn->setVisible(Home_image_iconBattery, batteryIconVisible ? LE_TRUE : LE_FALSE);
        }
    }
    else if (!batteryIconVisible)
    {
        batteryIconVisible = true;
        Home_image_iconBattery->fn->setVisible(Home_image_iconBattery, LE_TRUE);
    }

    /* Pump the camera preview. Returns immediately when idle or when no frame
       has arrived, so this is safe to call every rendered frame. */
    Camera_Tasks();

    Metrics_Update(Home_lblUpdatePct, Home_lblDrawPct, Home_lblFPSValue);
}

/*******************************************************************************
 * Draw Surface Callbacks
 ******************************************************************************/

/*******************************************************************************
 * event_Home_drwNeedle_OnDraw
 * Renders the speedometer needle on the draw surface at the current angle.
 ******************************************************************************/
leBool event_Home_drwNeedle_OnDraw(leDrawSurfaceWidget* sfc, leRect* bounds)
{
    Gauge_DrawNeedle(sfc, 80, 140, GAUGE_NEEDLE_THICKNESS, GAUGE_NEEDLE_COLOR);
    return LE_TRUE;
}

/*******************************************************************************
 * Button Event Handlers
 * Each handler updates button visual state and performs the associated action.
 ******************************************************************************/

// Music button - visual feedback only
void event_Home_btnMusic_OnPressed(leButtonWidget* btn)
{
    Buttons_Select(&homeButtonState, BTN_IDX_MUSIC);
}

// Home button - cycles through background animations
void event_Home_btnHome_OnPressed(leButtonWidget* btn)
{
    Buttons_Select(&homeButtonState, BTN_IDX_HOME);
}

// Map button - navigates to NavScreen
void event_Home_btnMap_OnPressed(leButtonWidget* btn)
{
    Buttons_Select(&homeButtonState, BTN_IDX_MAP);
    legato_showScreen(screenID_NavScreen);
}

/*******************************************************************************
 * Camera button - toggles the live USB camera preview.
 * Bring-up is asynchronous: Camera_Start() only arms the state machine, and
 * Camera_Tasks() in Home_OnUpdate does the work, so pressing the button never
 * stalls the UI even when no camera is attached.
 ******************************************************************************/
void event_Home_btnCamera_OnPressed(leButtonWidget* btn)
{
    Buttons_Select(&homeButtonState, BTN_IDX_CAMERA);

    if (Camera_GetState() != CAMERA_STATE_IDLE)
    {
        Camera_Stop();
        return;
    }

    cameraConfig cfg;

    Camera_ConfigDefault(&cfg);
    cfg.destX      = CAMERA_PREVIEW_X;
    cfg.destY      = CAMERA_PREVIEW_Y;
    cfg.destWidth  = CAMERA_PREVIEW_WIDTH;
    cfg.destHeight = CAMERA_PREVIEW_HEIGHT;

    Camera_Start(&cfg);
}

// Phone button - visual feedback only
void event_Home_btnPhone_OnPressed(leButtonWidget* btn)
{
    Buttons_Select(&homeButtonState, BTN_IDX_PHONE);
}

// Light button - visual feedback only
void event_Home_btnLight_OnPressed(leButtonWidget* btn)
{
    Buttons_Select(&homeButtonState, BTN_IDX_LIGHT);
}




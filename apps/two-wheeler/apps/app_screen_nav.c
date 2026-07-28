/*******************************************************************************
  Application for Screen - NavScreen

  Company:
    Microchip Technology Inc.

  File Name:
    app_screen_nav.c

  Summary:
    Navigation screen application logic for the electric motorcycle cluster demo.

  Description:
    This module implements the Navigation screen functionality including:

    - Polyline Map Display: Animated route visualization with turn-by-turn
      directions. Map updates are paused when battery is depleted.

    - Touch Pan/Zoom: Double-tap cycles through zoom levels (75%, 100%, 200%).
      Touch-drag pans the map view. Pan snaps back to center on release.

    - Gauge Animation: Speedometer display with smaller font for nav view.
      Same driving simulation as Home screen.

    - Power/Battery Display: Real-time power consumption and battery level
      with animated progress bars.

    - Battery Icon Flashing: When battery is depleted, the battery icon
      flashes at 500ms intervals until fully recharged.

    - Shortcut Button Bar: Six shortcut buttons with visual feedback.
      The Home button navigates back to the Home screen.

    - Needle Rendering: Custom draw surface callback renders the speedometer
      needle using vector graphics.
 *******************************************************************************/
#include "app_gauge.h"
#include "app_anim.h"
#include "app_metrics.h"

#include "gfx/legato/generated/le_gen_init.h"


/*******************************************************************************
 * Configuration Constants
 ******************************************************************************/
#define NAV_UPDATE_INTERVAL_MS  30      // Map and animation update rate
#define BATTERY_FLASH_INTERVAL_MS 500   // Battery icon flash rate when depleted
#define DOUBLE_TAP_THRESHOLD_MS 300     // Max time between taps for double-tap
#define ZOOM_STEP_PCT 5                 // Zoom animation increment per frame
#define PAN_RETURN_SPEED 0.15f          // Pan snap-back easing factor (0-1)

/*******************************************************************************
 * Module Variables
 ******************************************************************************/
static int32_t polyPct = 100;           // Current map zoom percentage
static int32_t polyPctTarget = 100;     // Target zoom percentage for animation
static int32_t panOffsetX = 0;          // Current horizontal pan offset
static int32_t panOffsetY = 0;          // Current vertical pan offset
static bool panActive = false;          // True while touch is held down
static uint32_t tickCount = 0;          // Frame counter for map animation
static uint32_t lastTapTime = 0;        // Timestamp for double-tap detection
static ButtonAnimState_t navButtonState; // Shortcut button animation state

extern volatile unsigned int tickCountMS;

/*******************************************************************************
 * Nav_GetButtonByIndex
 * Maps button index enum to the corresponding widget pointer.
 ******************************************************************************/
static leButtonWidget* Nav_GetButtonByIndex(ButtonIndex_t idx)
{
    switch (idx)
    {
        case BTN_IDX_CAMERA: return NavScreen_btnCamera;
        case BTN_IDX_MUSIC:  return NavScreen_btnMusic;
        case BTN_IDX_MAP:    return NavScreen_btnMap;
        case BTN_IDX_HOME:   return NavScreen_btnHome;
        case BTN_IDX_PHONE:  return NavScreen_btnPhone;
        case BTN_IDX_LIGHT:  return NavScreen_btnLight;
        default: return NULL;
    }
}

/*******************************************************************************
 * External Navigation Polyline Functions
 ******************************************************************************/
extern void NavPoly_OnShow(void);
void NavPoly_OnUpdate(leDrawSurfaceWidget* NavScreen_surfPath, uint32_t appTickCounter, uint32_t pct,
                      leLabelWidget * distance, leLabelWidget * street, leImageWidget * dirIcon,
                      int32_t xoffset, int32_t yoffset);

/*******************************************************************************
 * NavScreen_CycleZoom
 * Cycles through map zoom levels: 75% -> 100% -> 200% -> 75%
 * Called on double-tap gesture.
 ******************************************************************************/
static void NavScreen_CycleZoom(void)
{
    if (polyPctTarget == 75)
        polyPctTarget = 100;
    else if (polyPctTarget == 100)
        polyPctTarget = 200;
    else
        polyPctTarget = 75;
}

/*******************************************************************************
 * NavScreen_TouchPanelEventFilter
 * Event filter for the touch panel widget. Handles:
 * - TOUCH_DOWN: Detects double-tap for zoom cycling, starts pan tracking
 * - TOUCH_MOVE: Updates pan offset based on drag delta
 * - TOUCH_UP: Ends pan tracking, triggers snap-back animation
 ******************************************************************************/
static leBool NavScreen_TouchPanelEventFilter(leWidget* target, leWidgetEvent* evt, void* data)
{
    (void)data;

    // Double-tap detection and pan start
    if (evt->id == LE_EVENT_TOUCH_DOWN)
    {
        uint32_t elapsedMs = tickCountMS - lastTapTime;

        if (elapsedMs <= DOUBLE_TAP_THRESHOLD_MS && lastTapTime != 0)
        {
            NavScreen_CycleZoom();
            lastTapTime = 0;
        }
        else
        {
            lastTapTime = tickCountMS;
        }

        panActive = true;
        leWidgetEvent_Accept(evt, target);
        return LE_TRUE;
    }

    // Pan tracking - accumulate drag delta
    if (evt->id == LE_EVENT_TOUCH_MOVE)
    {
        leWidgetEvent_TouchMove* moveEvt = (leWidgetEvent_TouchMove*)evt;
        panOffsetX += (moveEvt->x - moveEvt->prevX);
        panOffsetY += (moveEvt->y - moveEvt->prevY);

        leWidgetEvent_Accept(evt, target);
        return LE_TRUE;
    }

    // Pan end - snap-back handled in OnUpdate
    if (evt->id == LE_EVENT_TOUCH_UP)
    {
        panActive = false;
        leWidgetEvent_Accept(evt, target);
        return LE_TRUE;
    }

    return LE_FALSE;
}

/*******************************************************************************
 * Screen Lifecycle Functions
 ******************************************************************************/

/*******************************************************************************
 * NavScreen_OnShow
 * Called when screen becomes visible. Initializes gauge system, button
 * animations, touch panel event filter, and navigation polyline display.
 * Disables HEO layer to allow polyline rendering on base layer.
 ******************************************************************************/
void NavScreen_OnShow(void)
{
    Gauge_Init((leFont*)&Unbounded80, (leFont*)&Unbounded28, (leFont*)&Unbounded32, (leFont*)&GeistMono14);
    PowerBattery_Init(NavScreen_imgRegenBar, NavScreen_image_RegenBar, NavScreen_image_DischargeBar);
    Buttons_Init(&navButtonState, Nav_GetButtonByIndex);
    Metrics_Init();

    leWidgetEventFilter touchFilter = { NavScreen_TouchPanelEventFilter, NULL };
    NavScreen_touchPanel->fn->installEventFilter(NavScreen_touchPanel, touchFilter);


    NavPoly_OnShow();
}

/*******************************************************************************
 * NavScreen_OnHide
 * Called when screen is hidden. Re-enables HEO layer for other screens.
 ******************************************************************************/
void NavScreen_OnHide(void)
{

}

/*******************************************************************************
 * NavScreen_OnUpdate
 * Called every frame. Updates:
 * - Zoom animation toward target percentage
 * - Pan snap-back when touch released
 * - Navigation polyline (paused when battery depleted)
 * - Gauge and power/battery indicators
 * - Battery icon flashing when depleted
 ******************************************************************************/
void NavScreen_OnUpdate(void)
{
    static uint32_t lastNavUpdateTime = 0;

    uint32_t currentTime = tickCountMS;
    uint32_t elapsedMs = currentTime - lastNavUpdateTime;

    if (elapsedMs <= NAV_UPDATE_INTERVAL_MS)
    return;

    {

        lastNavUpdateTime = currentTime;

        // Animate zoom percentage toward target
        if (polyPct < polyPctTarget)
        {
            polyPct += ZOOM_STEP_PCT;
            if (polyPct > polyPctTarget)
                polyPct = polyPctTarget;
        }
        else if (polyPct > polyPctTarget)
        {
            polyPct -= ZOOM_STEP_PCT;
            if (polyPct < polyPctTarget)
                polyPct = polyPctTarget;
        }

        // Snap pan offset back to 0,0 when not actively panning
        if (!panActive)
        {
            panOffsetX = (int32_t)(panOffsetX * PAN_RETURN_SPEED);
            panOffsetY = (int32_t)(panOffsetY * PAN_RETURN_SPEED);
        }

        if (!Gauge_IsBatteryDepleted())
        {
            tickCount++;

            NavPoly_OnUpdate(NavScreen_drawNav, tickCount, polyPct,
                                    NavScreen_lblDistance,
                                    NavScreen_lblStreet,
                                    NavScreen_imgDirection,
                                    panOffsetX, panOffsetY);

            NavScreen_drawNav->fn->invalidate(NavScreen_drawNav);
        }
    }

    Buttons_Update(&navButtonState, BUTTON_UPDATE_INTERVAL_MS);

    if (Gauge_Update(NavScreen_lblGauge, NULL, GAUGE_UPDATE_INTERVAL_MS))
    {
        PowerBattery_Update(NavScreen_label_PowerValue, NavScreen_image_imgPowerProg,
                            NavScreen_label_BattValue, NavScreen_image_imgBatProg,
                            NavScreen_label_Range,
                            NavScreen_label_OdoValue, NavScreen_label_TripValue,
                            NavScreen_imgRegenBar,
                            NavScreen_image_RegenBar, NavScreen_image_DischargeBar);
    }

    // Flash battery icon while depleted and charging
    static uint32_t lastBatteryFlashTime = 0;
    static bool batteryIconVisible = true;

    if (Gauge_IsBatteryDepleted())
    {
        uint32_t flashElapsed = tickCountMS - lastBatteryFlashTime;
        if (flashElapsed >= BATTERY_FLASH_INTERVAL_MS)
        {
            lastBatteryFlashTime = tickCountMS;
            batteryIconVisible = !batteryIconVisible;
            NavScreen_image_iconBattery->fn->setVisible(NavScreen_image_iconBattery, batteryIconVisible ? LE_TRUE : LE_FALSE);
        }
    }
    else if (!batteryIconVisible)
    {
        batteryIconVisible = true;
        NavScreen_image_iconBattery->fn->setVisible(NavScreen_image_iconBattery, LE_TRUE);
    }

    Metrics_Update(NavScreen_lblUpdatePct, NavScreen_lblDrawPct, NavScreen_lblFPSValue);
}

/*******************************************************************************
 * Draw Surface Callbacks
 ******************************************************************************/

/*******************************************************************************
 * event_NavScreen_drawNav_OnDraw
 * Delegates to the navigation polyline draw handler.
 ******************************************************************************/
leBool event_NavScreen_drawNav_OnDraw(leDrawSurfaceWidget* sfc, leRect* bounds)
{
    return event_NavScreen_surfPath_OnDraw(sfc, bounds);
}

/*******************************************************************************
 * event_NavScreen_drwNeedle_OnDraw
 * Renders the speedometer needle on the draw surface at the current angle.
 ******************************************************************************/
leBool event_NavScreen_drwNeedle_OnDraw(leDrawSurfaceWidget* sfc, leRect* bounds)
{
    Gauge_DrawNeedle(sfc, 80, 140, GAUGE_NEEDLE_THICKNESS, GAUGE_NEEDLE_COLOR);
    return LE_TRUE;
}

/*******************************************************************************
 * Button Event Handlers
 * Each handler updates button visual state and performs the associated action.
 ******************************************************************************/

// Map button - visual feedback only (already on nav screen)
void event_NavScreen_btnMap_OnPressed(leButtonWidget* btn)
{
    Buttons_Select(&navButtonState, BTN_IDX_MAP);
}

// Music button - visual feedback only
void event_NavScreen_btnMusic_OnPressed(leButtonWidget* btn)
{
    Buttons_Select(&navButtonState, BTN_IDX_MUSIC);
}

// Home button - navigates to Home screen
void event_NavScreen_btnHome_OnPressed(leButtonWidget* btn)
{
    Buttons_Select(&navButtonState, BTN_IDX_HOME);
    legato_showScreen(screenID_Home);
}

// Camera button - visual feedback only
void event_NavScreen_btnCamera_OnPressed(leButtonWidget* btn)
{
    Buttons_Select(&navButtonState, BTN_IDX_CAMERA);
}

// Phone button - visual feedback only
void event_NavScreen_btnPhone_OnPressed(leButtonWidget* btn)
{
    Buttons_Select(&navButtonState, BTN_IDX_PHONE);
}

// Light button - visual feedback only
void event_NavScreen_btnLight_OnPressed(leButtonWidget* btn)
{
    Buttons_Select(&navButtonState, BTN_IDX_LIGHT);
}
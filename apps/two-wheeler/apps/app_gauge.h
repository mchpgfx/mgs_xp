/*******************************************************************************
  Gauge and Electric Motorcycle Animation Functions

  Company:
    Microchip Technology Inc.

  File Name:
    app_gauge.h

  Summary:
    Header file for electric motorcycle cluster animation system.

  Description:
    This module provides animation functions for an electric motorcycle instrument
    cluster display. It simulates realistic motorcycle behavior including:
    - Speedometer gauge with needle animation
    - Power consumption bar (kW output)
    - Battery level indicator with charge/discharge simulation
    - Estimated range calculation
    - Odometer and trip counter
    - Regenerative braking visualization

    All visual elements use easing curves for smooth transitions.
 *******************************************************************************/

#ifndef APP_GAUGE_H
#define APP_GAUGE_H

#include "gfx/legato/legato.h"
#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * Gauge Configuration
 ******************************************************************************/
#define GAUGE_MIN_VALUE           0       // Minimum speed value (km/h)
#define GAUGE_MAX_VALUE           220     // Maximum speed value (km/h)
#define GAUGE_MIN_ANGLE           225     // Needle angle at min speed (degrees)
#define GAUGE_MAX_ANGLE           (-45)   // Needle angle at max speed (degrees)
#define GAUGE_CHAR_BUFFER_SIZE    8       // Buffer size for gauge string
#define GAUGE_UPDATE_INTERVAL_MS  30      // Update interval in milliseconds

#define GAUGE_NEEDLE_COLOR        0xFFFFFFFF  // White needle color (ARGB)
#define GAUGE_NEEDLE_THICKNESS    4           // Needle line thickness in pixels

/*******************************************************************************
 * Power and Battery Bar Configuration
 ******************************************************************************/
#define POWER_BAR_MAX_HEIGHT      220     // Maximum height of power bar (pixels)
#define POWER_BAR_ORIG_Y          141     // Y position when bar is at minimum
#define BATTERY_BAR_MAX_HEIGHT    220     // Maximum height of battery bar (pixels)
#define BATTERY_BAR_ORIG_Y        142     // Y position when bar is at minimum
#define MAX_POWER_KW              50      // Maximum power output (kW)

/*******************************************************************************
 * Animation State Enumerations
 ******************************************************************************/

/**
 * @brief Gauge animation state machine states
 *
 * GAUGE_STATE_INIT    - Initial state, prepares for startup animation
 * GAUGE_STATE_REVUP   - Startup sweep: needle moves from 0 to max
 * GAUGE_STATE_REVDOWN - Startup sweep: needle returns from max to 0
 * GAUGE_STATE_ANIM    - Normal operation with driving simulation
 */
typedef enum
{
    GAUGE_STATE_INIT,
    GAUGE_STATE_REVUP,
    GAUGE_STATE_REVDOWN,
    GAUGE_STATE_ANIM
} GaugeState_t;

/**
 * @brief Driving animation phase during GAUGE_STATE_ANIM
 *
 * ANIM_PHASE_ACCELERATE - Speed increasing toward target
 * ANIM_PHASE_CRUISE     - Maintaining speed with minor variations
 * ANIM_PHASE_DECELERATE - Speed decreasing, regenerative braking active
 */
typedef enum
{
    ANIM_PHASE_ACCELERATE,
    ANIM_PHASE_CRUISE,
    ANIM_PHASE_DECELERATE
} AnimPhase_t;

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/

/**
 * @brief Initialize the gauge animation system
 *
 * Sets up string buffers with appropriate fonts and initializes all animation
 * state variables to their default values. Must be called before any other
 * gauge functions.
 *
 * @param gaugeFont        Font for the main speedometer display
 * @param powerBatteryFont Font for power (kW) and battery (%) labels
 * @param rangeFont        Font for estimated range display
 * @param odoTripFont      Font for odometer and trip counter
 */
void Gauge_Init(leFont* gaugeFont, leFont* powerBatteryFont, leFont* rangeFont, leFont* odoTripFont);

/**
 * @brief Reset gauge to initial state
 *
 * Resets the state machine to GAUGE_STATE_INIT, triggering the startup
 * needle sweep animation on next update.
 */
void Gauge_Reset(void);

/**
 * @brief Get current gauge speed value
 *
 * @return Current speed value (0 to GAUGE_MAX_VALUE)
 */
int32_t Gauge_GetValue(void);

/**
 * @brief Check if battery is depleted
 *
 * @return true if battery is depleted and charging, false otherwise
 */
bool Gauge_IsBatteryDepleted(void);

/**
 * @brief Update gauge animation state
 *
 * Main animation tick function. Advances the gauge state machine and updates
 * the speedometer display. Should be called from the screen's OnUpdate handler.
 *
 * Animation sequence:
 * 1. INIT -> REVUP: Needle sweeps from 0 to max
 * 2. REVUP -> REVDOWN: Needle sweeps from max back to 0
 * 3. REVDOWN -> ANIM: Normal driving simulation begins
 * 4. ANIM: Cycles through accelerate -> cruise -> decelerate phases
 *
 * @param label      Speedometer label widget to update
 * @param needle     Draw surface for needle (invalidated on change), can be NULL
 * @param intervalMs Minimum time between updates in milliseconds
 * @return true if an update occurred, false if interval not elapsed
 */
bool Gauge_Update(leLabelWidget* label, leDrawSurfaceWidget* needle, uint32_t intervalMs);

/**
 * @brief Draw the gauge needle on a draw surface
 *
 * Renders the speedometer needle at the current gauge value angle. Should be
 * called from the draw surface's OnDraw callback.
 *
 * @param sfc         Draw surface widget to render on
 * @param innerRadius Distance from center to needle start (pixels)
 * @param outerRadius Distance from center to needle end (pixels)
 * @param thickness   Line thickness in pixels
 * @param color       Needle color in ARGB format
 */
void Gauge_DrawNeedle(leDrawSurfaceWidget* sfc, uint32_t innerRadius, uint32_t outerRadius,
                      uint32_t thickness, uint32_t color);

/**
 * @brief Initialize power/battery animation positions
 *
 * Records the initial positions of animated widgets from their screen layout.
 * Must be called during screen OnShow before PowerBattery_Update.
 *
 * @param regenBar       Image widget for vertical regen indicator
 * @param regenMeter     Image widget for horizontal regen meter
 * @param dischargeMeter Image widget for horizontal discharge meter
 */
void PowerBattery_Init(leImageWidget* regenBar,
                       leImageWidget* regenMeter, leImageWidget* dischargeMeter);

/**
 * @brief Update all power and battery related animations
 *
 * Updates multiple dashboard elements with smooth easing animations:
 * - Power bar: Height based on current power output (kW)
 * - Battery bar: Height based on battery level (0-100%)
 * - Battery simulation: Drains during acceleration/cruise, charges during decel
 * - Range estimate: Calculated from battery level
 * - Odometer/Trip: Incremented based on speed
 * - Regen bar: Vertical position indicates regeneration level
 * - Regen/Discharge meters: Horizontal bars showing energy flow direction
 *
 * Battery behavior:
 * - Drains randomly during acceleration and cruise phases
 * - Charges during deceleration (regenerative braking)
 * - When depleted (0%), forces deceleration until stopped
 * - When stopped at 0%, charges faster until 100%
 * - Resumes driving automatically when fully charged
 *
 * All bar/meter animations use ease-out curves (1/5 of remaining distance per tick).
 *
 * @param powerLabel     Label showing power in kW
 * @param powerBar       Image widget for power level bar
 * @param batteryLabel   Label showing battery percentage
 * @param batteryBar     Image widget for battery level bar
 * @param rangeLabel     Label showing estimated range in km
 * @param odoLabel       Label showing total odometer (with "km" suffix)
 * @param tripLabel      Label showing trip distance (with "km" suffix)
 * @param regenBar       Image widget for vertical regen indicator
 * @param regenMeter     Image widget for horizontal regen meter (extends left)
 * @param dischargeMeter Image widget for horizontal discharge meter (extends right)
 */
void PowerBattery_Update(leLabelWidget* powerLabel, leImageWidget* powerBar,
                         leLabelWidget* batteryLabel, leImageWidget* batteryBar,
                         leLabelWidget* rangeLabel,
                         leLabelWidget* odoLabel, leLabelWidget* tripLabel,
                         leImageWidget* regenBar,
                         leImageWidget* regenMeter, leImageWidget* dischargeMeter);

#endif /* APP_GAUGE_H */

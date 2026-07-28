/*******************************************************************************
  Gauge and Electric Motorcycle Animation Functions

  Company:
    Microchip Technology Inc.

  File Name:
    app_gauge.c

  Summary:
    Implementation of electric motorcycle cluster animation system.

  Description:
    This module implements realistic electric motorcycle dashboard animations
    including speedometer, battery management, regenerative braking visualization,
    and distance tracking. All animations use easing curves for smooth transitions.
 *******************************************************************************/

#include <stdio.h>
#include "gfx/legato/generated/le_gen_init.h"
#include "app_gauge.h"
#include "vector_render.h"

/*******************************************************************************
 * String Buffers for Label Updates
 * Each animated label needs its own fixed string and character buffers.
 ******************************************************************************/

// Speedometer display
static leFixedString gaugeStr;
static leChar gaugeCharBuffer[GAUGE_CHAR_BUFFER_SIZE];
static char gaugeCStrBuffer[GAUGE_CHAR_BUFFER_SIZE];

// Power output display (kW)
static leFixedString powerStr;
static leChar powerCharBuffer[GAUGE_CHAR_BUFFER_SIZE];
static char powerCStrBuffer[GAUGE_CHAR_BUFFER_SIZE];

// Battery percentage display
static leFixedString batteryStr;
static leChar batteryCharBuffer[GAUGE_CHAR_BUFFER_SIZE];
static char batteryCStrBuffer[GAUGE_CHAR_BUFFER_SIZE];

// Estimated range display
static leFixedString rangeStr;
static leChar rangeCharBuffer[GAUGE_CHAR_BUFFER_SIZE];
static char rangeCStrBuffer[GAUGE_CHAR_BUFFER_SIZE];

// Odometer and trip counter (larger buffer for "000000 km" format)
#define ODO_TRIP_BUFFER_SIZE 16
static leFixedString odoStr;
static leChar odoCharBuffer[ODO_TRIP_BUFFER_SIZE];
static char odoCStrBuffer[ODO_TRIP_BUFFER_SIZE];

static leFixedString tripStr;
static leChar tripCharBuffer[ODO_TRIP_BUFFER_SIZE];
static char tripCStrBuffer[ODO_TRIP_BUFFER_SIZE];

/*******************************************************************************
 * Animation State Variables
 ******************************************************************************/

// Battery and distance simulation
static int32_t batteryLevel = 100;          // Current battery level (0-100%)
static int32_t estimatedRange = 184;        // Calculated range in km
static int32_t odometerValue = 1240;        // Total distance in meters (displays as km)
static int32_t tripValue = 0;               // Trip distance in meters

// Easing animation current positions (smoothly approach targets)
static int32_t regenBarY = 270;             // Vertical regen indicator Y position
static int32_t regenMeterWidth = 0;         // Horizontal regen meter width
static int32_t dischargeMeterWidth = 0;     // Horizontal discharge meter width
static int32_t powerBarHeight = 0;          // Power bar current height
static int32_t batteryBarHeight = BATTERY_BAR_MAX_HEIGHT;  // Battery bar current height
static bool batteryDepleted = false;        // True when battery hit 0, until fully recharged

/*******************************************************************************
 * Regen/Discharge Meter Configuration
 * These meters show energy flow direction at the center of the dashboard.
 ******************************************************************************/
#define REGEN_METER_MAX_WIDTH     60    // Maximum width when fully regenerating
#define DISCHARGE_METER_MAX_WIDTH 60    // Maximum width when fully discharging
#define REGEN_BAR_TRAVEL          200   // Vertical travel distance for regen bar

// Initial positions recorded during PowerBattery_Init
static int32_t regenBarInitY = 270;         // Vertical regen bar initial Y
static int32_t regenMeterInitX = 388;       // Horizontal regen meter initial X (right edge)
static int32_t regenMeterInitY = 323;       // Horizontal regen meter initial Y
static int32_t dischargeMeterInitX = 388;   // Horizontal discharge meter initial X (left edge)
static int32_t dischargeMeterInitY = 323;   // Horizontal discharge meter initial Y

/*******************************************************************************
 * Gauge State Machine Variables
 ******************************************************************************/
static uint32_t lastGaugeUpdateTime = 0;    // Timestamp of last update
static int32_t gaugeValue = 0;              // Current speed value (0-220)
static int32_t gaugeTargetSpeed = 0;        // Target speed for acceleration phase
static int32_t cruiseCounter = 0;           // Ticks remaining in cruise phase
static GaugeState_t gaugeState = GAUGE_STATE_INIT;
static AnimPhase_t animPhase = ANIM_PHASE_ACCELERATE;

extern volatile unsigned int tickCountMS;

/*******************************************************************************
 * Gauge_Init
 * Initialize all string buffers and reset animation state.
 ******************************************************************************/
void Gauge_Init(leFont* gaugeFont, leFont* powerBatteryFont, leFont* rangeFont, leFont* odoTripFont)
{
    // Initialize speedometer string
    leFixedString_Constructor(&gaugeStr, gaugeCharBuffer, GAUGE_CHAR_BUFFER_SIZE);
    gaugeStr.fn->setFont(&gaugeStr, gaugeFont);

    // Initialize power display string
    leFixedString_Constructor(&powerStr, powerCharBuffer, GAUGE_CHAR_BUFFER_SIZE);
    powerStr.fn->setFont(&powerStr, powerBatteryFont);

    // Initialize battery display string
    leFixedString_Constructor(&batteryStr, batteryCharBuffer, GAUGE_CHAR_BUFFER_SIZE);
    batteryStr.fn->setFont(&batteryStr, powerBatteryFont);

    // Initialize range display string
    leFixedString_Constructor(&rangeStr, rangeCharBuffer, GAUGE_CHAR_BUFFER_SIZE);
    rangeStr.fn->setFont(&rangeStr, rangeFont);

    // Initialize odometer string
    leFixedString_Constructor(&odoStr, odoCharBuffer, ODO_TRIP_BUFFER_SIZE);
    odoStr.fn->setFont(&odoStr, odoTripFont);

    // Initialize trip counter string
    leFixedString_Constructor(&tripStr, tripCharBuffer, ODO_TRIP_BUFFER_SIZE);
    tripStr.fn->setFont(&tripStr, odoTripFont);

    // Reset all simulation values to defaults
    gaugeValue = 0;
    batteryLevel = 100;
    estimatedRange = 184;
    odometerValue = 1240;
    tripValue = 0;
    gaugeState = GAUGE_STATE_INIT;
    lastGaugeUpdateTime = tickCountMS;
}

/*******************************************************************************
 * PowerBattery_Init
 * Record initial positions of animated widgets for position-relative animations.
 ******************************************************************************/
void PowerBattery_Init(leImageWidget* regenBar,
                       leImageWidget* regenMeter, leImageWidget* dischargeMeter)
{
    if (regenBar != NULL)
    {
        regenBarInitY = regenBar->widget.rect.y;
        regenBarY = regenBarInitY;
    }

    if (regenMeter != NULL)
    {
        regenMeterInitX = regenMeter->widget.rect.x + regenMeter->widget.rect.width;
        regenMeterInitY = regenMeter->widget.rect.y;
        regenMeterWidth = 0;
    }

    if (dischargeMeter != NULL)
    {
        dischargeMeterInitX = dischargeMeter->widget.rect.x;
        dischargeMeterInitY = dischargeMeter->widget.rect.y;
        dischargeMeterWidth = 0;
    }
}

/*******************************************************************************
 * Gauge_Reset
 * Return to initial state to replay startup animation.
 ******************************************************************************/
void Gauge_Reset(void)
{
    gaugeState = GAUGE_STATE_INIT;
}

/*******************************************************************************
 * Gauge_GetValue
 * Accessor for current speed value.
 ******************************************************************************/
int32_t Gauge_GetValue(void)
{
    return gaugeValue;
}

/*******************************************************************************
 * Gauge_IsBatteryDepleted
 * Check if battery is in depleted state (charging while stopped).
 ******************************************************************************/
bool Gauge_IsBatteryDepleted(void)
{
    return batteryDepleted;
}

/*******************************************************************************
 * Gauge_UpdateLabel (static)
 * Update the speedometer label with current gauge value.
 ******************************************************************************/
static void Gauge_UpdateLabel(leLabelWidget* label)
{
    sprintf(gaugeCStrBuffer, "%ld", (long)gaugeValue);
    gaugeStr.fn->setFromCStr(&gaugeStr, gaugeCStrBuffer);
    label->fn->setString(label, (leString*)&gaugeStr);
}

/*******************************************************************************
 * Gauge_Update
 * Main animation tick - advances state machine and updates display.
 ******************************************************************************/
bool Gauge_Update(leLabelWidget* label, leDrawSurfaceWidget* needle, uint32_t intervalMs)
{
    uint32_t currentTime = tickCountMS;

    uint32_t elapsedMs = currentTime - lastGaugeUpdateTime;

    // Rate limiting - only update at specified interval
    if (elapsedMs < intervalMs)
    {
        return false;
    }

    lastGaugeUpdateTime = currentTime;

    // State machine for gauge animation
    switch (gaugeState)
    {
        case GAUGE_STATE_INIT:
            // Prepare for startup sweep
            gaugeValue = 0;
            gaugeState = GAUGE_STATE_REVUP;
            break;

        case GAUGE_STATE_REVUP:
            // Startup animation: sweep needle from 0 to max
            gaugeValue += 8;
            if (gaugeValue >= GAUGE_MAX_VALUE)
            {
                gaugeValue = GAUGE_MAX_VALUE;
                gaugeState = GAUGE_STATE_REVDOWN;
            }
            break;

        case GAUGE_STATE_REVDOWN:
            // Startup animation: sweep needle from max back to 0
            gaugeValue -= 8;
            if (gaugeValue <= GAUGE_MIN_VALUE)
            {
                gaugeValue = GAUGE_MIN_VALUE;
                animPhase = ANIM_PHASE_ACCELERATE;
                gaugeTargetSpeed = 80 + (rand() % 60);  // Random target 80-140
                gaugeState = GAUGE_STATE_ANIM;
            }
            break;

        case GAUGE_STATE_ANIM:
            // Normal driving simulation with three phases
            switch (animPhase)
            {
                case ANIM_PHASE_ACCELERATE:
                    // Gradually increase speed toward target
                    if (gaugeValue < gaugeTargetSpeed)
                        gaugeValue += 1;
                    if (gaugeValue >= gaugeTargetSpeed)
                    {
                        gaugeValue = gaugeTargetSpeed;
                        animPhase = ANIM_PHASE_CRUISE;
                        cruiseCounter = 150 + (rand() % 150);  // Cruise for 150-300 ticks
                    }
                    break;

                case ANIM_PHASE_CRUISE:
                    // Maintain speed with minor random variations
                    cruiseCounter--;
                    if (cruiseCounter % 15 == 0)
                    {
                        int32_t drift = -1 + (rand() % 3);  // -1, 0, or +1
                        gaugeValue += drift;
                        // Clamp to +/- 3 of target
                        if (gaugeValue < gaugeTargetSpeed - 3)
                            gaugeValue = gaugeTargetSpeed - 3;
                        if (gaugeValue > gaugeTargetSpeed + 3)
                            gaugeValue = gaugeTargetSpeed + 3;
                    }
                    if (cruiseCounter <= 0)
                        animPhase = ANIM_PHASE_DECELERATE;
                    break;

                case ANIM_PHASE_DECELERATE:
                    // Gradually decrease speed (regenerative braking)
                    // Stay in decelerate phase when stopped - PowerBattery_Update
                    // controls when to resume based on battery level
                    if (gaugeValue > 0)
                        gaugeValue -= 1;
                    break;
            }
            break;
    }

    // Update speedometer display
    Gauge_UpdateLabel(label);

    // Invalidate needle draw surface to trigger redraw
    if (needle != NULL)
    {
        needle->widget.fn->invalidate((leWidget*)needle);
    }

    return true;
}

/*******************************************************************************
 * Gauge_DrawNeedle
 * Render the speedometer needle at current angle.
 ******************************************************************************/
void Gauge_DrawNeedle(leDrawSurfaceWidget* sfc, uint32_t innerRadius, uint32_t outerRadius,
                      uint32_t thickness, uint32_t color)
{
    // Calculate needle angle from gauge value using linear interpolation
    int32_t angle = GAUGE_MIN_ANGLE +
        (gaugeValue - GAUGE_MIN_VALUE) * (GAUGE_MAX_ANGLE - GAUGE_MIN_ANGLE) /
        (GAUGE_MAX_VALUE - GAUGE_MIN_VALUE);

    leVector2 startVec, endVec;
    lePoint centerPt;
    int32_t surfaceWidth = sfc->widget.rect.width;
    int32_t surfaceHeight = sfc->widget.rect.height;

    // Calculate center point in screen coordinates
    centerPt.x = surfaceWidth / 2;
    centerPt.y = surfaceHeight / 2;
    leUtils_PointToScreenSpace((leWidget*)sfc, &centerPt);

    // Convert angle to radians and calculate trig values
    leReal_i16 angleRad = LE_REAL_I16_MULTIPLY(leReal_i16_FromInt(angle), LE_REAL_I16_RADIANS);
    leReal_i16 cosVal = leReal_i16_Cos(angleRad);
    leReal_i16 sinVal = leReal_i16_Sin(angleRad);

    // Calculate needle start and end points
    int32_t startX = centerPt.x + leReal_i16_ToInt(LE_REAL_I16_MULTIPLY(leReal_i16_FromInt(innerRadius), cosVal));
    int32_t startY = centerPt.y - leReal_i16_ToInt(LE_REAL_I16_MULTIPLY(leReal_i16_FromInt(innerRadius), sinVal));
    int32_t endX = centerPt.x + leReal_i16_ToInt(LE_REAL_I16_MULTIPLY(leReal_i16_FromInt(outerRadius), cosVal));
    int32_t endY = centerPt.y - leReal_i16_ToInt(LE_REAL_I16_MULTIPLY(leReal_i16_FromInt(outerRadius), sinVal));

    // Convert to fixed-point vectors for rendering
    startVec.x = leReal_i16_FromInt(startX);
    startVec.y = leReal_i16_FromInt(startY);
    endVec.x = leReal_i16_FromInt(endX);
    endVec.y = leReal_i16_FromInt(endY);

    // Draw the needle line
    leDraw_VectorBasicLine(&startVec, &endVec, color, 255, thickness);
}

/*******************************************************************************
 * PowerBattery_Update
 * Update all power, battery, and energy flow visualizations.
 ******************************************************************************/
void PowerBattery_Update(leLabelWidget* powerLabel, leImageWidget* powerBar,
                         leLabelWidget* batteryLabel, leImageWidget* batteryBar,
                         leLabelWidget* rangeLabel,
                         leLabelWidget* odoLabel, leLabelWidget* tripLabel,
                         leImageWidget* regenBar,
                         leImageWidget* regenMeter, leImageWidget* dischargeMeter)
{
    /***************************************************************************
     * Power Bar Animation
     * Height proportional to current power output (0 to MAX_POWER_KW).
     * Bar grows upward from fixed bottom position.
     **************************************************************************/
    int32_t powerKw = (gaugeValue * MAX_POWER_KW) / GAUGE_MAX_VALUE;
    int32_t targetPowerHeight = (powerKw * POWER_BAR_MAX_HEIGHT) / MAX_POWER_KW;

    // Ease toward target (1/5 of remaining distance per tick)
    if (powerBarHeight != targetPowerHeight)
    {
        int32_t diff = targetPowerHeight - powerBarHeight;
        int32_t step = diff / 5;
        if (step == 0)
            step = (diff > 0) ? 1 : -1;
        powerBarHeight += step;
    }

    if (powerBar != NULL)
    {
        int32_t powerY = POWER_BAR_ORIG_Y + (POWER_BAR_MAX_HEIGHT - powerBarHeight);
        powerBar->fn->setPosition(powerBar, 34, powerY);
        powerBar->fn->setSize(powerBar, 70, powerBarHeight > 0 ? powerBarHeight : 1);
    }

    // Update power label (kW value)
    if (powerLabel != NULL)
    {
        sprintf(powerCStrBuffer, "%ld", (long)powerKw);
        powerStr.fn->setFromCStr(&powerStr, powerCStrBuffer);
        powerLabel->fn->setString(powerLabel, (leString*)&powerStr);
    }

    /***************************************************************************
     * Battery Simulation
     * - Drains during acceleration and cruise (3% chance per tick)
     * - No regen charging during normal deceleration (simplify behavior)
     * - When battery hits 0: stop and charge until 100% before resuming
     **************************************************************************/
    if (batteryLevel <= 0)
    {
        // Battery depleted - enter charging mode
        batteryLevel = 0;
        batteryDepleted = true;
        animPhase = ANIM_PHASE_DECELERATE;
    }

    if (batteryDepleted && gaugeValue == 0)
    {
        // Charging while parked (battery was depleted) - 5x speed
        if (rand() % 100 < 50)
            batteryLevel++;

        if (batteryLevel >= 100)
        {
            // Fully charged - resume driving
            batteryLevel = 100;
            batteryDepleted = false;
            animPhase = ANIM_PHASE_ACCELERATE;
            gaugeTargetSpeed = 80 + (rand() % 60);
        }
    }
    else if (!batteryDepleted && gaugeValue == 0 && animPhase == ANIM_PHASE_DECELERATE)
    {
        // Normal stop (battery not depleted) - resume driving
        animPhase = ANIM_PHASE_ACCELERATE;
        gaugeTargetSpeed = 80 + (rand() % 60);
    }
    else if (gaugeState == GAUGE_STATE_ANIM && animPhase != ANIM_PHASE_DECELERATE && batteryLevel > 0)
    {
        // Drain during acceleration/cruise
        if (rand() % 100 < 3)
            batteryLevel--;
    }

    /***************************************************************************
     * Battery Bar Animation
     * Height proportional to battery level (0-100%).
     * Bar grows upward from fixed bottom position.
     **************************************************************************/
    int32_t targetBatteryHeight = (batteryLevel * BATTERY_BAR_MAX_HEIGHT) / 100;

    // Ease toward target
    if (batteryBarHeight != targetBatteryHeight)
    {
        int32_t diff = targetBatteryHeight - batteryBarHeight;
        int32_t step = diff / 5;
        if (step == 0)
            step = (diff > 0) ? 1 : -1;
        batteryBarHeight += step;
    }

    if (batteryBar != NULL)
    {
        int32_t batteryY = BATTERY_BAR_ORIG_Y + (BATTERY_BAR_MAX_HEIGHT - batteryBarHeight);
        batteryBar->fn->setPosition(batteryBar, 697, batteryY);
        batteryBar->fn->setSize(batteryBar, 70, batteryBarHeight > 0 ? batteryBarHeight : 1);
    }

    // Update battery percentage label
    if (batteryLabel != NULL)
    {
        sprintf(batteryCStrBuffer, "%ld", (long)batteryLevel);
        batteryStr.fn->setFromCStr(&batteryStr, batteryCStrBuffer);
        batteryLabel->fn->setString(batteryLabel, (leString*)&batteryStr);
    }

    /***************************************************************************
     * Estimated Range
     * Linear calculation: range = battery% * max_range / 100
     * Max range is 184 km at 100% battery.
     **************************************************************************/
    estimatedRange = (batteryLevel * 184) / 100;

    if (rangeLabel != NULL)
    {
        sprintf(rangeCStrBuffer, "%ld", (long)estimatedRange);
        rangeStr.fn->setFromCStr(&rangeStr, rangeCStrBuffer);
        rangeLabel->fn->setString(rangeLabel, (leString*)&rangeStr);
    }

    /***************************************************************************
     * Odometer and Trip Counter
     * Incremented based on current speed (faster = more distance).
     * Values stored in meters, displayed in km.
     **************************************************************************/
    if (gaugeValue > 0)
    {
        tripValue += gaugeValue;
        odometerValue += gaugeValue;
    }

    if (odoLabel != NULL)
    {
        sprintf(odoCStrBuffer, "%06ld km", (long)(odometerValue / 1000));
        odoStr.fn->setFromCStr(&odoStr, odoCStrBuffer);
        odoLabel->fn->setString(odoLabel, (leString*)&odoStr);
    }

    if (tripLabel != NULL)
    {
        sprintf(tripCStrBuffer, "%ld.%ld km", (long)(tripValue / 1000), (long)((tripValue % 1000) / 100));
        tripStr.fn->setFromCStr(&tripStr, tripCStrBuffer);
        tripLabel->fn->setString(tripLabel, (leString*)&tripStr);
    }

    /***************************************************************************
     * Vertical Regen Bar Animation
     * Y position indicates regeneration level during deceleration.
     * Moves from initial Y (no regen) upward by REGEN_BAR_TRAVEL (max regen).
     **************************************************************************/
    if (regenBar != NULL)
    {
        int32_t targetRegenY;
        if (animPhase == ANIM_PHASE_DECELERATE && gaugeValue > 0)
        {
            // Higher speed during decel = more regen energy captured
            int32_t regenLevel = (GAUGE_MAX_VALUE - gaugeValue) * 100 / GAUGE_MAX_VALUE;
            targetRegenY = regenBarInitY - (regenLevel * REGEN_BAR_TRAVEL) / 100;
        }
        else
        {
            targetRegenY = regenBarInitY;  // Default position (no regen)
        }

        // Ease toward target
        if (regenBarY != targetRegenY)
        {
            int32_t diff = targetRegenY - regenBarY;
            int32_t step = diff / 5;
            if (step == 0)
                step = (diff > 0) ? 1 : -1;
            regenBarY += step;
        }

        regenBar->fn->setY(regenBar, regenBarY);
    }

    /***************************************************************************
     * Horizontal Regen/Discharge Meters
     * These bars meet in the middle and extend in opposite directions:
     * - Regen meter extends LEFT from center when decelerating
     * - Discharge meter extends RIGHT from center when accelerating/cruising
     **************************************************************************/
    int32_t targetRegenMeterWidth = 0;
    int32_t targetDischargeMeterWidth = 0;

    if (animPhase == ANIM_PHASE_DECELERATE && gaugeValue > 0)
    {
        // Regenerating - show regen meter
        targetRegenMeterWidth = (gaugeValue * REGEN_METER_MAX_WIDTH) / GAUGE_MAX_VALUE;
    }
    else if (animPhase != ANIM_PHASE_DECELERATE && gaugeValue > 0)
    {
        // Consuming power - show discharge meter
        targetDischargeMeterWidth = (gaugeValue * DISCHARGE_METER_MAX_WIDTH) / GAUGE_MAX_VALUE;
    }

    // Ease regen meter width
    if (regenMeterWidth != targetRegenMeterWidth)
    {
        int32_t diff = targetRegenMeterWidth - regenMeterWidth;
        int32_t step = diff / 5;
        if (step == 0)
            step = (diff > 0) ? 1 : -1;
        regenMeterWidth += step;
    }

    // Ease discharge meter width
    if (dischargeMeterWidth != targetDischargeMeterWidth)
    {
        int32_t diff = targetDischargeMeterWidth - dischargeMeterWidth;
        int32_t step = diff / 5;
        if (step == 0)
            step = (diff > 0) ? 1 : -1;
        dischargeMeterWidth += step;
    }

    // Update regen meter (extends left from fixed right edge)
    if (regenMeter != NULL)
    {
        int32_t width = regenMeterWidth > 0 ? regenMeterWidth : 1;
        int32_t x = regenMeterInitX - width;
        regenMeter->fn->setPosition(regenMeter, x, regenMeterInitY);
        regenMeter->fn->setSize(regenMeter, width, 4);
    }

    // Update discharge meter (extends right from fixed left edge)
    if (dischargeMeter != NULL)
    {
        int32_t width = dischargeMeterWidth > 0 ? dischargeMeterWidth : 1;
        dischargeMeter->fn->setPosition(dischargeMeter, dischargeMeterInitX, dischargeMeterInitY);
        dischargeMeter->fn->setSize(dischargeMeter, width, 4);
    }
}

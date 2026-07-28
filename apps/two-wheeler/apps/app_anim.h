/*******************************************************************************
  Animation Helper Functions

  Company:
    Microchip Technology Inc.

  File Name:
    app_anim.h

  Summary:
    Shared animation logic for Home and NavScreen.
 *******************************************************************************/

#ifndef APP_ANIM_H
#define APP_ANIM_H

#include "gfx/legato/legato.h"
#include <stdbool.h>
#include <stdint.h>

#define BUTTONS_ORIG_POS_Y          10
#define BUTTONS_SELECT_POS_Y        0
#define BUTTON_EASE_FACTOR          5
#define BUTTON_MIN_STEP             1
#define BUTTON_UPDATE_INTERVAL_MS   30

typedef enum
{
    BTN_IDX_CAMERA,
    BTN_IDX_MUSIC,
    BTN_IDX_MAP,
    BTN_IDX_HOME,
    BTN_IDX_PHONE,
    BTN_IDX_LIGHT,
    BTN_IDX_COUNT,
    BTN_IDX_NONE = -1
} ButtonIndex_t;

typedef struct
{
    int32_t posY[BTN_IDX_COUNT];
    int32_t targetY[BTN_IDX_COUNT];
    ButtonIndex_t selected;
    uint32_t lastUpdateTime;
    leButtonWidget* (*getButton)(ButtonIndex_t idx);
} ButtonAnimState_t;

void Buttons_Init(ButtonAnimState_t* state, leButtonWidget* (*getButtonFunc)(ButtonIndex_t));
void Buttons_Select(ButtonAnimState_t* state, ButtonIndex_t idx);
bool Buttons_Update(ButtonAnimState_t* state, uint32_t intervalMs);

#endif /* APP_ANIM_H */

/*******************************************************************************
  Animation Helper Functions

  Company:
    Microchip Technology Inc.

  File Name:
    app_anim.c

  Summary:
    Shared animation logic for Home and NavScreen.
 *******************************************************************************/

#include "app_anim.h"

extern volatile unsigned int tickCountMS;

void Buttons_Init(ButtonAnimState_t* state, leButtonWidget* (*getButtonFunc)(ButtonIndex_t))
{
    state->getButton = getButtonFunc;
    state->selected = BTN_IDX_NONE;
    state->lastUpdateTime = tickCountMS;

    for (int i = 0; i < BTN_IDX_COUNT; i++)
    {
        state->posY[i] = BUTTONS_ORIG_POS_Y;
        state->targetY[i] = BUTTONS_ORIG_POS_Y;
    }
}

void Buttons_Select(ButtonAnimState_t* state, ButtonIndex_t idx)
{
    for (int i = 0; i < BTN_IDX_COUNT; i++)
    {
        state->targetY[i] = (i == idx) ? BUTTONS_SELECT_POS_Y : BUTTONS_ORIG_POS_Y;
    }
    state->selected = idx;
}

bool Buttons_Update(ButtonAnimState_t* state, uint32_t intervalMs)
{
    uint32_t currentTime = tickCountMS;
    uint32_t elapsedMs = currentTime - state->lastUpdateTime;

    if (elapsedMs < intervalMs)
        return false;

    state->lastUpdateTime = currentTime;

    for (int i = 0; i < BTN_IDX_COUNT; i++)
    {
        if (state->posY[i] != state->targetY[i])
        {
            leButtonWidget* btn = state->getButton((ButtonIndex_t)i);
            if (btn != NULL)
            {
                int32_t diff = state->targetY[i] - state->posY[i];
                int32_t step = diff / BUTTON_EASE_FACTOR;

                if (step == 0)
                    step = (diff > 0) ? BUTTON_MIN_STEP : -BUTTON_MIN_STEP;

                state->posY[i] += step;

                if ((diff > 0 && state->posY[i] > state->targetY[i]) ||
                    (diff < 0 && state->posY[i] < state->targetY[i]))
                    state->posY[i] = state->targetY[i];

                btn->fn->setY(btn, state->posY[i]);
            }
        }
    }

    return true;
}

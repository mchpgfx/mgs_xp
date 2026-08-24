// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C)  Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

#include <stdlib.h>
#include "gfx/legato/generated/le_gen_init.h"

#define DRAWSURFACE_X_OFFSET     20
#define DRAWSURFACE_Y_OFFSET     40
#define DRAWSURFACE_X_SIZE       760
#define DRAWSURFACE_Y_SIZE       400
#define DRAWSURFACE_ARRAY_X_SIZE 760
#define DRAWSURFACE_ARRAY_Y_SIZE 400
#define DEFAULT_POINT_SIZE       4
#define COLOR_RED                0xFF0000FF
#define COLOR_ORANGE             0xFFA500FF
#define COLOR_YELLOW             0xFFFF00FF
#define COLOR_GREEN              0x00FF00FF
#define COLOR_BLUE               0x0000FFFF
#define COLOR_INDIGO             0x4B0082FF
#define COLOR_VIOLET             0xEE82EEFF

typedef enum
{
    SCRN_DRAW_RECT,
    SCRN_DRAW_RAND,
    SCRN_DRAW_ERASE
} SCRN_DRAW_CMD;

static SCRN_DRAW_CMD drawCmd = SCRN_DRAW_ERASE;
static uint32_t drawsurface[DRAWSURFACE_ARRAY_X_SIZE][DRAWSURFACE_ARRAY_Y_SIZE];
static uint32_t pointSize = DEFAULT_POINT_SIZE;
static leColor clr = COLOR_RED;
static leRect damagedRect;

static leBool DrawSurface_filterEvent(leWidget* target, leWidgetEvent* evt, void* data);
static leWidgetEventFilter DrawSurface_eventFilter =
{
    DrawSurface_filterEvent,
    NULL
};

static leBool DrawSurface_filterEvent(leWidget* target, leWidgetEvent* evt, void* data)
{
    leBool retval = LE_FALSE;
    int32_t x, y;

    (void)data;

    switch (evt->id)
    {
        case LE_EVENT_TOUCH_DOWN:
        {
            x = ((leWidgetEvent_TouchDown *)evt)->x;
            y = ((leWidgetEvent_TouchDown *)evt)->y;

            if ((x < DRAWSURFACE_X_OFFSET) || (x > DRAWSURFACE_X_OFFSET + DRAWSURFACE_X_SIZE)
             || (y < DRAWSURFACE_Y_OFFSET) || (y > DRAWSURFACE_Y_OFFSET + DRAWSURFACE_Y_SIZE))
            {
                break;
            }

            damagedRect.x = x - pointSize / 2;
            damagedRect.y = y - pointSize / 2;
            damagedRect.width = pointSize;
            damagedRect.height = pointSize;

            if (damagedRect.x < DRAWSURFACE_X_OFFSET)
            {
                damagedRect.width = pointSize - (DRAWSURFACE_X_OFFSET - damagedRect.x);
                damagedRect.x = DRAWSURFACE_X_OFFSET;
            }
            if (damagedRect.x > DRAWSURFACE_X_SIZE + DRAWSURFACE_X_OFFSET - pointSize)
            {
                damagedRect.width = DRAWSURFACE_X_SIZE + DRAWSURFACE_X_OFFSET - damagedRect.x;
            }
            if (damagedRect.y < DRAWSURFACE_Y_OFFSET)
            {
                damagedRect.height = pointSize - (DRAWSURFACE_Y_OFFSET - damagedRect.y);
                damagedRect.y = DRAWSURFACE_Y_OFFSET;
            }
            if (damagedRect.y > DRAWSURFACE_Y_SIZE + DRAWSURFACE_Y_OFFSET - pointSize)
            {
                damagedRect.height = DRAWSURFACE_Y_SIZE + DRAWSURFACE_Y_OFFSET - damagedRect.y;
            }

            drawCmd = SCRN_DRAW_RECT;
            Screen0_DrawSurfaceWidget_0->fn->_damageArea(Screen0_DrawSurfaceWidget_0, &damagedRect);

            evt->accepted = LE_TRUE;
            evt->owner = target;

            retval = LE_TRUE;

            break;
        }
        case LE_EVENT_TOUCH_MOVE:
        {
            x = ((leWidgetEvent_TouchMove *)evt)->x;
            y = ((leWidgetEvent_TouchMove *)evt)->y;

            if ((x < DRAWSURFACE_X_OFFSET) || (x > DRAWSURFACE_X_OFFSET + DRAWSURFACE_X_SIZE)
             || (y < DRAWSURFACE_Y_OFFSET) || (y > DRAWSURFACE_Y_OFFSET + DRAWSURFACE_Y_SIZE))
            {
                break;
            }

            damagedRect.x = x - pointSize / 2;
            damagedRect.y = y - pointSize / 2;
            damagedRect.width = pointSize;
            damagedRect.height = pointSize;

            if (damagedRect.x < DRAWSURFACE_X_OFFSET)
            {
                damagedRect.width = pointSize - (DRAWSURFACE_X_OFFSET - damagedRect.x);
                damagedRect.x = DRAWSURFACE_X_OFFSET;
            }
            if (damagedRect.x > DRAWSURFACE_X_SIZE + DRAWSURFACE_X_OFFSET - pointSize)
            {
                damagedRect.width = DRAWSURFACE_X_SIZE + DRAWSURFACE_X_OFFSET - damagedRect.x;
            }
            if (damagedRect.y < DRAWSURFACE_Y_OFFSET)
            {
                damagedRect.height = pointSize - (DRAWSURFACE_Y_OFFSET - damagedRect.y);
                damagedRect.y = DRAWSURFACE_Y_OFFSET;
            }
            if (damagedRect.y > DRAWSURFACE_Y_SIZE + DRAWSURFACE_Y_OFFSET - pointSize)
            {
                damagedRect.height = DRAWSURFACE_Y_SIZE + DRAWSURFACE_Y_OFFSET - damagedRect.y;
            }

            drawCmd = SCRN_DRAW_RECT;
            Screen0_DrawSurfaceWidget_0->fn->_damageArea(Screen0_DrawSurfaceWidget_0, &damagedRect);

            evt->accepted = LE_TRUE;
            retval = LE_TRUE;

            break;
        }
        default:
            break;
    }

    return retval;
}

void event_Screen0_ButtonWidget_Random_OnReleased(leButtonWidget* btn)
{
    int i, j;

    (void)btn;

    for (i = 0; i < DRAWSURFACE_ARRAY_X_SIZE; i++)
        for (j = 0; j < DRAWSURFACE_ARRAY_Y_SIZE; j++)
            drawsurface[i][j] = (rand() * rand()) | 0x000000FF;

    drawCmd = SCRN_DRAW_RAND;
    Screen0_DrawSurfaceWidget_0->fn->invalidate(Screen0_DrawSurfaceWidget_0);
}

void event_Screen0_ButtonWidget_Erase_OnReleased(leButtonWidget* btn)
{
    (void)btn;

    drawCmd = SCRN_DRAW_ERASE;
    Screen0_DrawSurfaceWidget_0->fn->invalidate(Screen0_DrawSurfaceWidget_0);
}

leBool event_Screen0_DrawSurfaceWidget_0_OnDraw(leDrawSurfaceWidget* sfc, leRect* bounds)
{
    leBool retval = LE_TRUE;

    (void)sfc;
    (void)bounds;

    switch (drawCmd)
    {
        case SCRN_DRAW_RECT:
        {
            leRenderer_FillArea(damagedRect.x,
                                damagedRect.y,
                                pointSize, pointSize,
                                clr,
                                255);
            break;
        }
        case SCRN_DRAW_RAND:
        {
            for (int i = 0; i < DRAWSURFACE_ARRAY_X_SIZE; i++)
                for (int j = 0; j < DRAWSURFACE_ARRAY_Y_SIZE; j++)
                    leRenderer_PutPixel_Safe(i + DRAWSURFACE_X_OFFSET,
                                             j + DRAWSURFACE_Y_OFFSET,
                                             (leColor)drawsurface[i][j]);
            break;
        }
        case SCRN_DRAW_ERASE:
            break;
        default:
            break;
    }

    return retval;
}

void Screen0_OnShow(void)
{
    Screen0_DrawSurfaceWidget_0->fn->installEventFilter(Screen0_DrawSurfaceWidget_0, DrawSurface_eventFilter);
}

void Screen0_OnHide(void)
{
    Screen0_DrawSurfaceWidget_0->fn->removeEventFilter(Screen0_DrawSurfaceWidget_0, DrawSurface_eventFilter);
}

void Screen0_OnUpdate(void)
{
}

void event_Screen0_ButtonWidget_Red_OnReleased(leButtonWidget* btn)
{
    (void)btn;
    clr = COLOR_RED;
}

void event_Screen0_ButtonWidget_Orange_OnReleased(leButtonWidget* btn)
{
    (void)btn;
    clr = COLOR_ORANGE;
}

void event_Screen0_ButtonWidget_Yellow_OnReleased(leButtonWidget* btn)
{
    (void)btn;
    clr = COLOR_YELLOW;
}

void event_Screen0_ButtonWidget_Green_OnReleased(leButtonWidget* btn)
{
    (void)btn;
    clr = COLOR_GREEN;
}

void event_Screen0_ButtonWidget_Blue_OnReleased(leButtonWidget* btn)
{
    (void)btn;
    clr = COLOR_BLUE;
}

void event_Screen0_ButtonWidget_Indigo_OnReleased(leButtonWidget* btn)
{
    (void)btn;
    clr = COLOR_INDIGO;
}

void event_Screen0_ButtonWidget_Violet_OnReleased(leButtonWidget* btn)
{
    (void)btn;
    clr = COLOR_VIOLET;
}

void event_Screen0_SliderWidget_0_OnValueChanged(leSliderWidget* scr)
{
    pointSize = scr->fn->getValue(scr) * DEFAULT_POINT_SIZE;
}

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

#include "gfx/legato/generated/le_gen_init.h"
#include <stdlib.h>
#include <stdbool.h>

#define NUMBER_OF_LOGOS_CELLS   6
#define MARGINS_RADIUS_VALUE    15

static leImageWidget* LogoImage[NUMBER_OF_LOGOS_CELLS];
static leButtonWidget* LogoKeypadButton[NUMBER_OF_LOGOS_CELLS];

static void setImageWidgetArray(void)
{
    LogoImage[0] = Logo_Screen_ImageWidget_Logo_1;
    LogoImage[1] = Logo_Screen_ImageWidget_Logo_2;
    LogoImage[2] = Logo_Screen_ImageWidget_Logo_3;
    LogoImage[3] = Logo_Screen_ImageWidget_Logo_4;
    LogoImage[4] = Logo_Screen_ImageWidget_Logo_5;
    LogoImage[5] = Logo_Screen_ImageWidget_Logo_6;
}

static void setKeypadButtons(void)
{
    LogoKeypadButton[0] = Logo_Screen_KeyPadWidget->fn->getCellButton(Logo_Screen_KeyPadWidget, 0, 0);
    LogoKeypadButton[1] = Logo_Screen_KeyPadWidget->fn->getCellButton(Logo_Screen_KeyPadWidget, 0, 1);
    LogoKeypadButton[2] = Logo_Screen_KeyPadWidget->fn->getCellButton(Logo_Screen_KeyPadWidget, 1, 0);
    LogoKeypadButton[3] = Logo_Screen_KeyPadWidget->fn->getCellButton(Logo_Screen_KeyPadWidget, 1, 1);
    LogoKeypadButton[4] = Logo_Screen_KeyPadWidget->fn->getCellButton(Logo_Screen_KeyPadWidget, 2, 0);
    LogoKeypadButton[5] = Logo_Screen_KeyPadWidget->fn->getCellButton(Logo_Screen_KeyPadWidget, 2, 1);
}

static void setLogosOff(void)
{
    int i;
    for (i = 0; i < NUMBER_OF_LOGOS_CELLS; i++)
    {
        LogoImage[i]->fn->setVisible(LogoImage[i], LE_FALSE);
    }
}

static void setLogosOn(void)
{
    int i;
    for (i = 0; i < NUMBER_OF_LOGOS_CELLS; i++)
    {
        LogoImage[i]->fn->setVisible(LogoImage[i], LE_TRUE);
    }
}

static void randLogoPosition(leButtonWidget* cell)
{
    uint8_t randPosition[NUMBER_OF_LOGOS_CELLS - 1];
    uint8_t pressedCellNr = 0;
    int i, j, k;

    setLogosOff();

    for (i = 0; i < NUMBER_OF_LOGOS_CELLS; i++)
    {
        if (cell == LogoKeypadButton[i])
        {
            pressedCellNr = i + 1;
            break;
        }
    }

    if (pressedCellNr == NUMBER_OF_LOGOS_CELLS)
    {
        setLogosOn();
    }
    else
    {
        for (j = 0; j < pressedCellNr; j++)
        {
            bool randOk = false;
            while (randOk == false)
            {
                randPosition[j] = rand() % NUMBER_OF_LOGOS_CELLS;
                randOk = true;
                for (k = 0; k < j; k++)
                {
                    if (randPosition[j] == randPosition[k])
                    {
                        randOk = false;
                    }
                }
            }
        }

        for (j = 0; j < pressedCellNr; j++)
        {
            LogoImage[randPosition[j]]->fn->setVisible(LogoImage[randPosition[j]], LE_TRUE);
        }
    }
}

static void setWidgetsMargins(void)
{
    Logo_Screen_KeyPadWidget->fn->setCornerRadius(Logo_Screen_KeyPadWidget, MARGINS_RADIUS_VALUE);
    Logo_Screen_LabelWidget_KeyPress->fn->setCornerRadius(Logo_Screen_LabelWidget_KeyPress, MARGINS_RADIUS_VALUE);
    Logo_Screen_TextFieldWidget->fn->setCornerRadius(Logo_Screen_TextFieldWidget, MARGINS_RADIUS_VALUE);
    Logo_Screen_ButtonWidget_TicTacToe->fn->setCornerRadius(Logo_Screen_ButtonWidget_TicTacToe, MARGINS_RADIUS_VALUE);
}

void Logo_Screen_OnShow(void)
{
    setWidgetsMargins();
    setImageWidgetArray();
    setKeypadButtons();
    setLogosOff();
}

void Logo_Screen_OnHide(void)
{
}

void event_Logo_Screen_KeyPadWidget_OnKeyClick(leKeyPadWidget* wgt, leButtonWidget* cell, uint32_t row, uint32_t col)
{
    (void)wgt;
    (void)row;
    (void)col;
    randLogoPosition(cell);
}

void event_Logo_Screen_ButtonWidget_TicTacToe_OnPressed(leButtonWidget* btn)
{
    (void)btn;
    legato_showScreen(screenID_Game_Screen);
}

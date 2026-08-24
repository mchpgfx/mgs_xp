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
#include <stdbool.h>

#define X_STRING            1
#define O_STRING            2
#define NO_WINNER           3
#define NUMBER_OF_CELLS     9
#define DUMMY_VALUE         9
#define CLEAR               0
#define SIZE                3
#define RADIUS_VAL          15

static int pressedKeys[NUMBER_OF_CELLS];
static uint8_t arrayIndex = CLEAR;
static uint8_t PlayerState = X_STRING;
static uint8_t gameBoard[SIZE][SIZE];
static leButtonWidget* GameKeypadButton[NUMBER_OF_CELLS];

static void setGameKeypadButtons(void)
{
    GameKeypadButton[0] = Game_Screen_KeyPadWidget->fn->getCellButton(Game_Screen_KeyPadWidget, 0, 0);
    GameKeypadButton[1] = Game_Screen_KeyPadWidget->fn->getCellButton(Game_Screen_KeyPadWidget, 0, 1);
    GameKeypadButton[2] = Game_Screen_KeyPadWidget->fn->getCellButton(Game_Screen_KeyPadWidget, 0, 2);
    GameKeypadButton[3] = Game_Screen_KeyPadWidget->fn->getCellButton(Game_Screen_KeyPadWidget, 1, 0);
    GameKeypadButton[4] = Game_Screen_KeyPadWidget->fn->getCellButton(Game_Screen_KeyPadWidget, 1, 1);
    GameKeypadButton[5] = Game_Screen_KeyPadWidget->fn->getCellButton(Game_Screen_KeyPadWidget, 1, 2);
    GameKeypadButton[6] = Game_Screen_KeyPadWidget->fn->getCellButton(Game_Screen_KeyPadWidget, 2, 0);
    GameKeypadButton[7] = Game_Screen_KeyPadWidget->fn->getCellButton(Game_Screen_KeyPadWidget, 2, 1);
    GameKeypadButton[8] = Game_Screen_KeyPadWidget->fn->getCellButton(Game_Screen_KeyPadWidget, 2, 2);
}

static void displayEndMessage(uint8_t player)
{
    Game_Screen_LabelWidget_Winner->fn->setEnabled(Game_Screen_LabelWidget_Winner, LE_TRUE);
    Game_Screen_LabelWidget_Winner->fn->setVisible(Game_Screen_LabelWidget_Winner, LE_TRUE);
    Game_Screen_KeyPadWidget->fn->setEnabled(Game_Screen_KeyPadWidget, LE_FALSE);

    if (player == X_STRING)
    {
        Game_Screen_LabelWidget_Winner->fn->setString(Game_Screen_LabelWidget_Winner, (leString*)&string_WinX);
    }
    else if (player == O_STRING)
    {
        Game_Screen_LabelWidget_Winner->fn->setString(Game_Screen_LabelWidget_Winner, (leString*)&string_WinO);
    }
    else if (player == NO_WINNER)
    {
        Game_Screen_LabelWidget_Winner->fn->setString(Game_Screen_LabelWidget_Winner, (leString*)&string_Lose);
    }
}

static void setPositionsMatrix(uint8_t player, uint32_t row, uint32_t col)
{
    gameBoard[row][col] = player;
}

static void checkWinningPositions(void)
{
    int i;

    for (i = 0; i < SIZE; i++)
    {
        if (gameBoard[i][0] == gameBoard[i][1] && gameBoard[i][0] == gameBoard[i][2] && gameBoard[i][0] != 0)
        {
            displayEndMessage(gameBoard[i][0]);
            return;
        }
    }

    for (i = 0; i < SIZE; i++)
    {
        if (gameBoard[0][i] == gameBoard[1][i] && gameBoard[0][i] == gameBoard[2][i] && gameBoard[0][i] != 0)
        {
            displayEndMessage(gameBoard[0][i]);
            return;
        }
    }

    if (gameBoard[0][0] == gameBoard[1][1] && gameBoard[0][0] == gameBoard[2][2] && gameBoard[0][0] != 0)
    {
        displayEndMessage(gameBoard[0][0]);
    }
    else if (gameBoard[0][2] == gameBoard[1][1] && gameBoard[0][2] == gameBoard[2][0] && gameBoard[0][2] != 0)
    {
        displayEndMessage(gameBoard[0][2]);
    }
    else if (arrayIndex == NUMBER_OF_CELLS)
    {
        displayEndMessage(NO_WINNER);
    }
}

static void TicTacToeGame(leButtonWidget* cell, uint32_t row, uint32_t col)
{
    bool cellAlreadyPressedFlag = false;
    uint8_t oldPlayerState = CLEAR;
    int i, j;

    for (i = 0; i < NUMBER_OF_CELLS; i++)
    {
        if (cell == GameKeypadButton[i])
        {
            for (j = 0; j < NUMBER_OF_CELLS; j++)
            {
                if (pressedKeys[j] == i)
                {
                    cellAlreadyPressedFlag = true;
                }
            }

            if (cellAlreadyPressedFlag == false)
            {
                pressedKeys[arrayIndex] = i;
                arrayIndex++;

                if (PlayerState == O_STRING)
                {
                    Game_Screen_LabelWidget_Player->fn->setString(Game_Screen_LabelWidget_Player, (leString*)&string_XGame);
                    cell->fn->setString(cell, (leString*)&string_OVariable);
                    oldPlayerState = O_STRING;
                    PlayerState = X_STRING;
                }
                else
                {
                    Game_Screen_LabelWidget_Player->fn->setString(Game_Screen_LabelWidget_Player, (leString*)&string_OGame);
                    cell->fn->setString(cell, (leString*)&string_XVariable);
                    oldPlayerState = X_STRING;
                    PlayerState = O_STRING;
                }

                setPositionsMatrix(oldPlayerState, row, col);
                checkWinningPositions();
            }
        }
    }
}

static void Game_SetWidgetMargins(void)
{
    Game_Screen_ButtonWidget_Game_Rst->fn->setCornerRadius(Game_Screen_ButtonWidget_Game_Rst, RADIUS_VAL);
    Game_Screen_ButtonWidget_Logo->fn->setCornerRadius(Game_Screen_ButtonWidget_Logo, RADIUS_VAL);
    Game_Screen_LabelWidget_Player->fn->setCornerRadius(Game_Screen_LabelWidget_Player, RADIUS_VAL);
    Game_Screen_LabelWidget_Winner->fn->setCornerRadius(Game_Screen_LabelWidget_Winner, RADIUS_VAL);
}

static void Game_VariablesInitialize(void)
{
    int i, j;

    arrayIndex = CLEAR;
    PlayerState = X_STRING;

    for (i = 0; i < NUMBER_OF_CELLS; i++)
    {
        pressedKeys[i] = DUMMY_VALUE;
    }

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            gameBoard[i][j] = CLEAR;
        }
    }

    Game_Screen_KeyPadWidget->fn->setEnabled(Game_Screen_KeyPadWidget, LE_TRUE);
    setGameKeypadButtons();

    for (i = 0; i < NUMBER_OF_CELLS; i++)
    {
        GameKeypadButton[i]->fn->setString(GameKeypadButton[i], (leString*)&string_Clear);
    }

    Game_Screen_LabelWidget_Player->fn->setString(Game_Screen_LabelWidget_Player, (leString*)&string_XGame);
}

void Game_Screen_OnShow(void)
{
    Game_SetWidgetMargins();
    Game_VariablesInitialize();
    setGameKeypadButtons();
}

void Game_Screen_OnHide(void)
{
}

void event_Game_Screen_KeyPadWidget_OnKeyClick(leKeyPadWidget* wgt, leButtonWidget* cell, uint32_t row, uint32_t col)
{
    (void)wgt;
    TicTacToeGame(cell, row, col);
}

void event_Game_Screen_ButtonWidget_Logo_OnPressed(leButtonWidget* btn)
{
    (void)btn;
    legato_showScreen(screenID_Logo_Screen);
}

void event_Game_Screen_ButtonWidget_Game_Rst_OnPressed(leButtonWidget* btn)
{
    (void)btn;
    Game_Screen_LabelWidget_Winner->fn->setVisible(Game_Screen_LabelWidget_Winner, LE_FALSE);
    Game_VariablesInitialize();
}

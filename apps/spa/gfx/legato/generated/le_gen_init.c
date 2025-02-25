#include "gfx/legato/generated/le_gen_init.h"

static int32_t currentScreen;
static int32_t changingToScreen;

void legato_initializeScreenState(void)
{
    leSetStringTable(&stringTable);

    initializeStrings();

    screenInit_Screen_Splash();
    screenInit_Screen_Main();
    screenInit_Screen_Music_Player();
    screenInit_Screen_Settings();
    screenInit_Screen_Water_Q();

    currentScreen = -1;
    changingToScreen = -1;

    legato_showScreen(screenID_Screen_Splash);
}

uint32_t legato_getCurrentScreen(void)
{
    return currentScreen;
}

static void legato_hideCurrentScreen(void)
{
    switch(currentScreen)
    {
        case screenID_Screen_Splash:
        {
            screenHide_Screen_Splash();
            currentScreen = 0;
            break;
        }
        case screenID_Screen_Main:
        {
            screenHide_Screen_Main();
            currentScreen = 0;
            break;
        }
        case screenID_Screen_Music_Player:
        {
            screenHide_Screen_Music_Player();
            currentScreen = 0;
            break;
        }
        case screenID_Screen_Settings:
        {
            screenHide_Screen_Settings();
            currentScreen = 0;
            break;
        }
        case screenID_Screen_Water_Q:
        {
            screenHide_Screen_Water_Q();
            currentScreen = 0;
            break;
        }
    }
}

void legato_showScreen(uint32_t id)
{
    if(changingToScreen >= 0)
        return;

    changingToScreen = id;
}

void legato_updateScreenState(void)
{
    if(leIsDrawing() == LE_TRUE)
        return;

    if(changingToScreen >= 0)
    {
        legato_hideCurrentScreen();

        switch(changingToScreen)
        {
            case screenID_Screen_Splash:
            {
                screenShow_Screen_Splash();
                break;
            }
            case screenID_Screen_Main:
            {
                screenShow_Screen_Main();
                break;
            }
            case screenID_Screen_Music_Player:
            {
                screenShow_Screen_Music_Player();
                break;
            }
            case screenID_Screen_Settings:
            {
                screenShow_Screen_Settings();
                break;
            }
            case screenID_Screen_Water_Q:
            {
                screenShow_Screen_Water_Q();
                break;
            }
        }

        currentScreen = changingToScreen;
        changingToScreen = -1;
    }

    switch(currentScreen)
    {
        case screenID_Screen_Splash:
        {
            screenUpdate_Screen_Splash();
            break;
        }
        case screenID_Screen_Main:
        {
            screenUpdate_Screen_Main();
            break;
        }
        case screenID_Screen_Music_Player:
        {
            screenUpdate_Screen_Music_Player();
            break;
        }
        case screenID_Screen_Settings:
        {
            screenUpdate_Screen_Settings();
            break;
        }
        case screenID_Screen_Water_Q:
        {
            screenUpdate_Screen_Water_Q();
            break;
        }
    }
}

leBool legato_isChangingScreens(void)
{
    return changingToScreen != -1;
}


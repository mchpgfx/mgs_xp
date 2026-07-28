#include "gfx/legato/generated/le_gen_init.h"

static int32_t currentScreen;
static int32_t changingToScreen;

void legato_initializeScreenState(void)
{
    leSetStringTable(&stringTable);

    initializeStrings();

    screenInit_Home();
    screenInit_NavScreen();

    currentScreen = -1;
    changingToScreen = -1;

    legato_showScreen(screenID_Home);
}

uint32_t legato_getCurrentScreen(void)
{
    return currentScreen;
}

static void legato_hideCurrentScreen(void)
{
    switch(currentScreen)
    {
        case screenID_Home:
        {
            screenHide_Home();
            currentScreen = 0;
            break;
        }
        case screenID_NavScreen:
        {
            screenHide_NavScreen();
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

        leEvent_ClearList();

        switch(changingToScreen)
        {
            case screenID_Home:
            {
                screenShow_Home();
                break;
            }
            case screenID_NavScreen:
            {
                screenShow_NavScreen();
                break;
            }
        }

        currentScreen = changingToScreen;
        changingToScreen = -1;
    }

    switch(currentScreen)
    {
        case screenID_Home:
        {
            screenUpdate_Home();
            break;
        }
        case screenID_NavScreen:
        {
            screenUpdate_NavScreen();
            break;
        }
    }
}

leBool legato_isChangingScreens(void)
{
    return changingToScreen != -1;
}


#include "gfx/legato/generated/screen/le_gen_screen_Screen_Splash.h"

// screen member widget declarations
static leWidget* root0;

leWidget* Screen_Splash_Panel_0;
leWidget* Screen_Splash_MidLine;
leWidget* Screen_Splash_PanelWidget_0;
leWidget* Screen_Splash_PanelWidget_1;
leImageWidget* Screen_Splash_MicrochipLogo;
leImageWidget* Screen_Splash_MGSLogo;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_Screen_Splash(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_Screen_Splash(void)
{
    if(showing == LE_TRUE)
        return LE_FAILURE;

    // layer 0
    root0 = leWidget_New();
    root0->fn->setSize(root0, LE_DEFAULT_SCREEN_WIDTH, LE_DEFAULT_SCREEN_HEIGHT);
    root0->fn->setBackgroundType(root0, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->setMargins(root0, 0, 0, 0, 0);
    root0->flags |= LE_WIDGET_IGNOREEVENTS;
    root0->flags |= LE_WIDGET_IGNOREPICK;

    Screen_Splash_Panel_0 = leWidget_New();
    Screen_Splash_Panel_0->fn->setPosition(Screen_Splash_Panel_0, 0, 0);
    Screen_Splash_Panel_0->fn->setSize(Screen_Splash_Panel_0, 1024, 600);
    Screen_Splash_Panel_0->fn->setScheme(Screen_Splash_Panel_0, &BkgScheme);
    root0->fn->addChild(root0, (leWidget*)Screen_Splash_Panel_0);

    Screen_Splash_MidLine = leWidget_New();
    Screen_Splash_MidLine->fn->setPosition(Screen_Splash_MidLine, 316, 439);
    Screen_Splash_MidLine->fn->setSize(Screen_Splash_MidLine, 2, 160);
    root0->fn->addChild(root0, (leWidget*)Screen_Splash_MidLine);

    Screen_Splash_PanelWidget_0 = leWidget_New();
    Screen_Splash_PanelWidget_0->fn->setPosition(Screen_Splash_PanelWidget_0, 0, 494);
    Screen_Splash_PanelWidget_0->fn->setSize(Screen_Splash_PanelWidget_0, 316, 75);
    Screen_Splash_PanelWidget_0->fn->setBackgroundType(Screen_Splash_PanelWidget_0, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->addChild(root0, (leWidget*)Screen_Splash_PanelWidget_0);

    Screen_Splash_MicrochipLogo = leImageWidget_New();
    Screen_Splash_MicrochipLogo->fn->setPosition(Screen_Splash_MicrochipLogo, 52, 16);
    Screen_Splash_MicrochipLogo->fn->setSize(Screen_Splash_MicrochipLogo, 220, 40);
    Screen_Splash_MicrochipLogo->fn->setBackgroundType(Screen_Splash_MicrochipLogo, LE_WIDGET_BACKGROUND_NONE);
    Screen_Splash_MicrochipLogo->fn->setBorderType(Screen_Splash_MicrochipLogo, LE_WIDGET_BORDER_NONE);
    Screen_Splash_MicrochipLogo->fn->setImage(Screen_Splash_MicrochipLogo, (leImage*)&mchp_logo);
    Screen_Splash_PanelWidget_0->fn->addChild(Screen_Splash_PanelWidget_0, (leWidget*)Screen_Splash_MicrochipLogo);

    Screen_Splash_PanelWidget_1 = leWidget_New();
    Screen_Splash_PanelWidget_1->fn->setPosition(Screen_Splash_PanelWidget_1, 320, 470);
    Screen_Splash_PanelWidget_1->fn->setSize(Screen_Splash_PanelWidget_1, 320, 120);
    Screen_Splash_PanelWidget_1->fn->setBackgroundType(Screen_Splash_PanelWidget_1, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->addChild(root0, (leWidget*)Screen_Splash_PanelWidget_1);

    Screen_Splash_MGSLogo = leImageWidget_New();
    Screen_Splash_MGSLogo->fn->setPosition(Screen_Splash_MGSLogo, 46, 27);
    Screen_Splash_MGSLogo->fn->setSize(Screen_Splash_MGSLogo, 225, 69);
    Screen_Splash_MGSLogo->fn->setBackgroundType(Screen_Splash_MGSLogo, LE_WIDGET_BACKGROUND_NONE);
    Screen_Splash_MGSLogo->fn->setBorderType(Screen_Splash_MGSLogo, LE_WIDGET_BORDER_NONE);
    Screen_Splash_MGSLogo->fn->setImage(Screen_Splash_MGSLogo, (leImage*)&mgs_mega_logo);
    Screen_Splash_PanelWidget_1->fn->addChild(Screen_Splash_PanelWidget_1, (leWidget*)Screen_Splash_MGSLogo);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    Screen_Splash_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_Screen_Splash(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);

    Screen_Splash_OnUpdate(); // raise event
}

void screenHide_Screen_Splash(void)
{
    Screen_Splash_OnHide(); // raise event


    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    Screen_Splash_Panel_0 = NULL;
    Screen_Splash_MidLine = NULL;
    Screen_Splash_PanelWidget_0 = NULL;
    Screen_Splash_PanelWidget_1 = NULL;
    Screen_Splash_MicrochipLogo = NULL;
    Screen_Splash_MGSLogo = NULL;


    showing = LE_FALSE;
}

void screenDestroy_Screen_Splash(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_Screen_Splash(uint32_t lyrIdx)
{
    if(lyrIdx >= LE_LAYER_COUNT)
        return NULL;

    switch(lyrIdx)
    {
        case 0:
        {
            return root0;
        }
        default:
        {
            return NULL;
        }
    }
}


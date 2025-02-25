/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_scrn_main.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/
#include "gfx/legato/generated/le_gen_init.h"
#include "app_common.h"
#include "app_sys_timer.h"

#define APP_WTR_TMP_FXD_STR_SZ 3
#define APP_JET_CTRL_FXD_STR_SZ 1
#define NUM_OF_COLOR_BTNS 8

#define CLOCK_TICK_TIMER_PERIOD_MS 5
#define ANIM_PERIOD_MS 15
#define MGS_LOGO_SHOWX 704
#define MCHP_LOGO_SHOWX 1024
#define LOGO_STEP_SIZE 20
#define MAIN_DURATION_MS 10
#define ANIM_PERIOD_TICKS (ANIM_PERIOD_MS/CLOCK_TICK_TIMER_PERIOD_MS)

typedef enum
{
    APP_MAIN_INIT,
    APP_MAIN_WAIT_FOR_GUI,
    APP_MAIN_ANIM_SCREEN,
    APP_MAIN_DONE,
    APP_MAIN_ITER_SHOW,
    APP_MAIN_WAIT_FOR_USER,
    APP_MAIN_EXIT,
} APP_MAIN_STATES;

static APP_MAIN_STATES appMainState;
static volatile unsigned int tickCount = 0;
static volatile unsigned int animTickCount = 0;
uint32_t animTickCountLastMain = 0;
static SYS_TIME_HANDLE timer = SYS_TIME_HANDLE_INVALID;
static leFixedString appWtrStr;
static leChar appWtrStrBuff[APP_WTR_TMP_FXD_STR_SZ] = {0};
static leFixedString appJetCtrl;
static leChar appJetCtrlBuff[APP_JET_CTRL_FXD_STR_SZ] = {0};
static leDynamicString * appRegionLabelStr;
static char cStrBuff[MAX_CSTR_STR_SIZE];
colors regionColor;
uint8_t selReg, waterTemp, jetCtrl;
bool clrBtnUpdProgr = false;
static uint8_t lastSelReg = 255;
static uint8_t lastWaterTemp = 255;
static uint8_t lastJetCtrl = 255;
static colors lastRegionColor = ERROR_COLOR;
leButtonWidget* colorsBtnArray[NUM_OF_COLOR_BTNS];
bool colorsBtnStatus[NUM_OF_COLOR_BTNS] = {false};    
static char cStrBuff[MAX_CSTR_STR_SIZE];
static bool curLightTheme = true;

static leBool BrightPanel_filterEvent(leWidget* target, leWidgetEvent* evt, void* data);
static leWidgetEventFilter BrightPanel_eventFilter =
{
    BrightPanel_filterEvent,
    NULL
};
static leBool VolumePanelMain_filterEvent(leWidget* target, leWidgetEvent* evt, void* data);
static leWidgetEventFilter VolumePanelMain_eventFilter =
{
    VolumePanelMain_filterEvent,
    NULL
};

static void update_theme();

static void APP_UI_Timer_Callback ( uintptr_t context)
{
    tickCount++;

    if (tickCount % ANIM_PERIOD_TICKS)
        animTickCount++;
}

void init_clr_btn_array()
{
    colorsBtnArray[0] = Screen_Main_ButtonWidget_Red;
    colorsBtnArray[1] = Screen_Main_ButtonWidget_Orange;
    colorsBtnArray[2] = Screen_Main_ButtonWidget_Yellow;
    colorsBtnArray[3] = Screen_Main_ButtonWidget_Green;
    colorsBtnArray[4] = Screen_Main_ButtonWidget_Cyan;
    colorsBtnArray[5] = Screen_Main_ButtonWidget_Purple;
    colorsBtnArray[6] = Screen_Main_ButtonWidget_Pink;
    colorsBtnArray[7] = Screen_Main_ButtonWidget_Radial;    
}

void update_sel_reg(regions reg)
{
    if (get_selected_region() != reg)
    {
        set_selected_region(reg);
    }
    else
    {
        set_selected_region(ALL_REGIONS);
    }
}

static void update_screen_reg_img_lbl()
{
    selReg = get_selected_region();
    // Update spa region image and label
    if (lastSelReg != selReg)
    {
        lastSelReg = selReg;
        switch (selReg)
        {
            case ALL_REGIONS:
                if (get_light_theme())
                {
                    Screen_Main_ImageWidget_Regions->fn->setImage(Screen_Main_ImageWidget_Regions, (leImage*)&all_reg);
                }
                else
                {
                    Screen_Main_ImageWidget_Regions->fn->setImage(Screen_Main_ImageWidget_Regions, (leImage*)&all_reg_dark);
                }
                break;
            case REGION_1:
                if (get_light_theme())
                {
                    Screen_Main_ImageWidget_Regions->fn->setImage(Screen_Main_ImageWidget_Regions, (leImage*)&reg_1);
                }
                else
                {
                    Screen_Main_ImageWidget_Regions->fn->setImage(Screen_Main_ImageWidget_Regions, (leImage*)&reg_1_dark);
                }
                break;
            case REGION_2:
                if (get_light_theme())
                {
                    Screen_Main_ImageWidget_Regions->fn->setImage(Screen_Main_ImageWidget_Regions, (leImage*)&reg_2);
                }
                else
                {
                    Screen_Main_ImageWidget_Regions->fn->setImage(Screen_Main_ImageWidget_Regions, (leImage*)&reg_2_dark);
                }
                break;
            case REGION_3:
                if (get_light_theme())
                {
                    Screen_Main_ImageWidget_Regions->fn->setImage(Screen_Main_ImageWidget_Regions, (leImage*)&reg_3);
                }
                else
                {
                    Screen_Main_ImageWidget_Regions->fn->setImage(Screen_Main_ImageWidget_Regions, (leImage*)&reg_3_dark);
                }
                break;
            case REGION_4:
                if (get_light_theme())
                {
                    Screen_Main_ImageWidget_Regions->fn->setImage(Screen_Main_ImageWidget_Regions, (leImage*)&reg_4);
                }
                else
                {
                    Screen_Main_ImageWidget_Regions->fn->setImage(Screen_Main_ImageWidget_Regions, (leImage*)&reg_4_dark);
                }
                break;
            default:
                break;            
        }
        if (selReg == ALL_REGIONS)
        {
            snprintf(cStrBuff, MAX_CSTR_STR_SIZE, "All Regions");
        }
        else
        {
            snprintf(cStrBuff, MAX_CSTR_STR_SIZE, "Region %u", selReg);
        }

        appRegionLabelStr->fn->setFromCStr(appRegionLabelStr, cStrBuff);
        Screen_Main_LabelWidget_SelectedReg->fn->setString(Screen_Main_LabelWidget_SelectedReg, (leString *) appRegionLabelStr);
    }
}

void update_screen_reg_color()
{
    regionColor = get_region_color();
    // Update selected color
    if (lastRegionColor != regionColor)
    {
        if (colorsBtnStatus[regionColor] != true)
        {
            if (lastRegionColor != ERROR_COLOR)
            {
                colorsBtnStatus[lastRegionColor] = false;
                colorsBtnArray[lastRegionColor]->fn->setPressed(colorsBtnArray[lastRegionColor], LE_FALSE);
                colorsBtnArray[lastRegionColor]->fn->setEnabled(colorsBtnArray[lastRegionColor], LE_TRUE);
            }
            if (colorsBtnArray[regionColor]->fn->getPressed(colorsBtnArray[regionColor]) != LE_TRUE)
            {
                // We arrive here if the screen was changed
                clrBtnUpdProgr = true;
                colorsBtnArray[regionColor]->fn->setPressed(colorsBtnArray[regionColor], LE_TRUE);    
            }
            colorsBtnStatus[regionColor] = true;
            colorsBtnArray[regionColor]->fn->setEnabled(colorsBtnArray[regionColor], LE_FALSE);
        }
        lastRegionColor = regionColor;
    }
}

static void update_screen_reg_temp()
{
    waterTemp = get_region_temp();
    // Update Water Temperature label
    if (lastWaterTemp != waterTemp)
    {
        snprintf(cStrBuff, MAX_CSTR_STR_SIZE, "%u%c", waterTemp, 176 /* degree symbol */);
        
        lastWaterTemp = waterTemp;
        
        appWtrStr.fn->setFromCStr(&appWtrStr, cStrBuff);
        Screen_Main_LabelWidget_Deg->fn->setString(Screen_Main_LabelWidget_Deg, (leString *) &appWtrStr);
    } 
}

static void update_screen_reg_jet()
{
    jetCtrl = get_region_jet();
    // Update Jet Control intensity
    if (lastJetCtrl != jetCtrl)
    {
        lastJetCtrl = jetCtrl;
        snprintf(cStrBuff, MAX_CSTR_STR_SIZE, "%u", jetCtrl);
        appJetCtrl.fn->setFromCStr(&appJetCtrl, cStrBuff); //Set string data from C-string
        Screen_Main_LabelWidget_BubbleLevel->fn->setString(Screen_Main_LabelWidget_BubbleLevel, (leString *) &appJetCtrl);
    }
}

void Screen_Main_OnShow(void)
{
    curLightTheme = true;
    update_theme();
    
    Screen_Main_ButtonWidget_Settings->fn->setCornerRadius(Screen_Main_ButtonWidget_Settings, DEFAULT_BTN_CORNER_RADIUS);
    Screen_Main_ButtonWidget_WaterQ->fn->setCornerRadius(Screen_Main_ButtonWidget_WaterQ, DEFAULT_BTN_CORNER_RADIUS);
    Screen_Main_ButtonWidget_DecTemp->fn->setCornerRadius(Screen_Main_ButtonWidget_DecTemp, DEFAULT_BTN_CORNER_RADIUS);
    Screen_Main_ButtonWidget_IncTemp->fn->setCornerRadius(Screen_Main_ButtonWidget_IncTemp, DEFAULT_BTN_CORNER_RADIUS);
    Screen_Main_ButtonWidget_JetDec->fn->setCornerRadius(Screen_Main_ButtonWidget_JetDec, DEFAULT_BTN_CORNER_RADIUS);
    Screen_Main_ButtonWidget_JetInc->fn->setCornerRadius(Screen_Main_ButtonWidget_JetInc, DEFAULT_BTN_CORNER_RADIUS);

    Screen_Main_EditPanelWidget->fn->setCornerRadius(Screen_Main_EditPanelWidget, DEFAULT_PANEL_CORNER_RADIUS);
    Screen_Main_PanelWidget_Bkg->fn->setCornerRadius(Screen_Main_PanelWidget_Bkg, DEFAULT_PANEL_CORNER_RADIUS);

    Screen_Main_PanelWidget_BrgLight->fn->setCornerRadius(Screen_Main_PanelWidget_BrgLight, DEFAULT_BAR_RADIUS);
    Screen_Main_PanelWidget_BrgDark->fn->setCornerRadius(Screen_Main_PanelWidget_BrgDark, DEFAULT_BAR_RADIUS);
    Screen_Main_PanelWidget_BrgGen->fn->installEventFilter(Screen_Main_PanelWidget_BrgGen, BrightPanel_eventFilter);

    Screen_Main_PanelWidget_VolLight->fn->setCornerRadius(Screen_Main_PanelWidget_VolLight, DEFAULT_BAR_RADIUS);
    Screen_Main_PanelWidget_VolDark->fn->setCornerRadius(Screen_Main_PanelWidget_VolDark, DEFAULT_BAR_RADIUS);
    Screen_Main_PanelWidget_Vol->fn->installEventFilter(Screen_Main_PanelWidget_Vol, VolumePanelMain_eventFilter);

    leFixedString_Constructor(&appWtrStr, appWtrStrBuff, APP_WTR_TMP_FXD_STR_SZ);
    appWtrStr.fn->setFont(&appWtrStr, (leFont*) &InterBold96);
    leFixedString_Constructor(&appJetCtrl, appJetCtrlBuff, APP_JET_CTRL_FXD_STR_SZ);
    appJetCtrl.fn->setFont(&appJetCtrl, (leFont*) &InterBold40);

    appRegionLabelStr = leDynamicString_New();
    appRegionLabelStr->fn->setFont(appRegionLabelStr, (leFont*) &InterBold32);

    if (get_music_playing())
    {
        Screen_Main_ButtonWidget_PlayPause->fn->setPressed(Screen_Main_ButtonWidget_PlayPause, LE_TRUE);
    }
    
    uint32_t lightBarPos = get_light_brightness_coord();
    Screen_Main_ButtonWidget_Brg->fn->setX(Screen_Main_ButtonWidget_Brg, lightBarPos);
    Screen_Main_PanelWidget_BrgDark->fn->setWidth(Screen_Main_PanelWidget_BrgDark, lightBarPos);

    int volBarPos = get_music_volume_coord_mains();
    if (volBarPos < 5)
    {
        APP_LE_SETVISIBLE(Screen_Main_PanelWidget_BrgDark, LE_FALSE);
    }
    else
    {
        Screen_Main_PanelWidget_VolDark->fn->setWidth(Screen_Main_PanelWidget_VolDark, volBarPos);
    }
    init_clr_btn_array();
    
    // Update widgets values
    update_screen_reg_img_lbl();
    update_screen_reg_color();
    update_screen_reg_temp();
    update_screen_reg_jet();

    SYS_TIME_TimerStart(timer);

    if (get_direct_boot() == true)
    {
        APP_LE_SETVISIBLE(Screen_Main_MGSLogo, LE_FALSE);
        APP_LE_SETVISIBLE(Screen_Main_MicrochipLogo, LE_FALSE);
        appMainState = APP_MAIN_WAIT_FOR_USER;
        SYS_TIME_DelayMS(MAIN_DURATION_MS, &timer);
    }
    else
    {
        //Set some widgets to not visible and show them after a short while for effect 
        APP_LE_SETVISIBLE(Screen_Main_LabelWidget_SelectedReg, LE_FALSE);
        APP_LE_SETVISIBLE(Screen_Main_PanelWidget_WaterTemp, LE_FALSE);
        APP_LE_SETVISIBLE(Screen_Main_PanelWidget_SelColors, LE_FALSE);
        APP_LE_SETVISIBLE(Screen_Main_PanelWidget_JetCtrl, LE_FALSE);
        APP_LE_SETVISIBLE(Screen_Main_PanelWidget_MP, LE_FALSE);
        timer = SYS_TIME_CallbackRegisterMS(APP_UI_Timer_Callback,
                                        1,
                                        CLOCK_TICK_TIMER_PERIOD_MS,
                                        SYS_TIME_PERIODIC);
        appMainState = APP_MAIN_INIT;
    }
}

void Screen_Main_OnUpdate(void)
{    
    switch(appMainState)
    {
        case APP_MAIN_INIT:
        {
            appMainState = APP_MAIN_WAIT_FOR_GUI;
            
            break;
        }
        case APP_MAIN_WAIT_FOR_GUI:
        {
            if (leIsDrawing() == LE_FALSE)
            {
                appMainState = APP_MAIN_ANIM_SCREEN;
            }
            break;
        }
        case APP_MAIN_ANIM_SCREEN:
        {
            if (animTickCount != animTickCountLastMain)
            {
                int32_t xmgs = APP_LE_GETX(Screen_Main_MGSLogo);
                int32_t xmchp = APP_LE_GETX(Screen_Main_MicrochipLogo);

                if (xmgs <= MGS_LOGO_SHOWX - LOGO_STEP_SIZE)
                {
                    APP_LE_SETX(Screen_Main_MGSLogo, xmgs + LOGO_STEP_SIZE);
                }
                else
                {
                    APP_LE_SETX(Screen_Main_MGSLogo, MGS_LOGO_SHOWX);
                }
                
                if (xmchp <= MCHP_LOGO_SHOWX - LOGO_STEP_SIZE)
                {
                    APP_LE_SETX(Screen_Main_MicrochipLogo, xmchp + LOGO_STEP_SIZE);
                }
                else
                {
                    APP_LE_SETX(Screen_Main_MicrochipLogo, MCHP_LOGO_SHOWX);
                }

                if (xmgs == MGS_LOGO_SHOWX && xmchp == MCHP_LOGO_SHOWX)
                {
                    appMainState = APP_MAIN_DONE;
                    SYS_TIME_DelayMS(MAIN_DURATION_MS, &timer);
                }
                animTickCountLastMain = animTickCount;
            }
            
            break;
        }
        case APP_MAIN_DONE:
        {
            set_direct_boot(true);
            appMainState = APP_MAIN_ITER_SHOW;
            
            break;
        }
        case APP_MAIN_ITER_SHOW:
        {
            if (SYS_TIME_DelayIsComplete(timer) == true)
            {
                bool done = false;
                
                if (APP_LE_GETVISIBLE(Screen_Main_LabelWidget_SelectedReg) == LE_FALSE)
                {
                    APP_LE_SETVISIBLE(Screen_Main_LabelWidget_SelectedReg, LE_TRUE);
                }
                else if (APP_LE_GETVISIBLE(Screen_Main_PanelWidget_WaterTemp) == LE_FALSE)
                {
                    APP_LE_SETVISIBLE(Screen_Main_PanelWidget_WaterTemp, LE_TRUE);
                }
                else if (APP_LE_GETVISIBLE(Screen_Main_PanelWidget_SelColors) == LE_FALSE)
                {
                    APP_LE_SETVISIBLE(Screen_Main_PanelWidget_SelColors, LE_TRUE);
                }
                else if (APP_LE_GETVISIBLE(Screen_Main_PanelWidget_JetCtrl) == LE_FALSE)
                {
                    APP_LE_SETVISIBLE(Screen_Main_PanelWidget_JetCtrl, LE_TRUE);
                }
                else if (APP_LE_GETVISIBLE(Screen_Main_PanelWidget_MP) == LE_FALSE)
                {
                    APP_LE_SETVISIBLE(Screen_Main_PanelWidget_MP, LE_TRUE);
                    done = true;
                }

                if (done == true)
                {
                    SYS_TIME_TimerStop(timer); 
                    SYS_TIME_TimerDestroy(timer); 
                    appMainState = APP_MAIN_WAIT_FOR_USER;
                }
                else
                {
                    SYS_TIME_DelayMS(MAIN_DURATION_MS, &timer);
                }
            }
            break;
        }
        case APP_MAIN_WAIT_FOR_USER:
        {
            update_screen_reg_img_lbl();
            update_screen_reg_color();
            update_screen_reg_temp();
            update_screen_reg_jet();
            break;
        }
        default:
        {
            break;
        }
    }
}

void Screen_Main_OnHide(void)
{
    Screen_Main_PanelWidget_BrgGen->fn->removeEventFilter(Screen_Main_PanelWidget_BrgGen, BrightPanel_eventFilter);
    Screen_Main_PanelWidget_Vol->fn->removeEventFilter(Screen_Main_PanelWidget_Vol, VolumePanelMain_eventFilter);

    /* Free dynamic string allocations */
    leString_Delete((leString *) appRegionLabelStr);
    lastSelReg = 255;
    lastWaterTemp = 255;
    lastJetCtrl = 255;
    lastRegionColor = ERROR_COLOR;
    for (int i = 0; i < NUM_OF_COLOR_BTNS; i++)
    {
        colorsBtnStatus[i] = false;
    }
}

void event_Screen_Main_ButtonWidget_Settings_OnReleased(leButtonWidget* btn)
{
    legato_showScreen(screenID_Screen_Settings);
}
void event_Screen_Main_ButtonWidget_WaterQ_OnReleased(leButtonWidget* btn)
{
    legato_showScreen(screenID_Screen_Water_Q);
}
void event_Screen_Main_ButtonWidget_MP_OnReleased(leButtonWidget* btn)
{
    legato_showScreen(screenID_Screen_Music_Player);
}

void event_Screen_Main_ButtonWidget_Prev_OnReleased(leButtonWidget* btn)
{
}
void event_Screen_Main_ButtonWidget_Next_OnReleased(leButtonWidget* btn)
{
}
void event_Screen_Main_ButtonWidget_PlayPause_OnPressed(leButtonWidget* btn)
{
    set_music_playing(true);
}
void event_Screen_Main_ButtonWidget_PlayPause_OnReleased(leButtonWidget* btn)
{
    set_music_playing(false);
}

void event_Screen_Main_ButtonWidget_DecTemp_OnPressed(leButtonWidget* btn)
{
    Screen_Main_ButtonWidget_DecTemp->fn->setBorderType(Screen_Main_ButtonWidget_DecTemp, LE_WIDGET_BORDER_LINE);
}
void event_Screen_Main_ButtonWidget_DecTemp_OnReleased(leButtonWidget* btn)
{
    Screen_Main_ButtonWidget_DecTemp->fn->setBorderType(Screen_Main_ButtonWidget_DecTemp, LE_WIDGET_BORDER_NONE);
    if (waterTemp > 1)
    {
        waterTemp--;
    }
    set_region_temp(waterTemp);    
}
void event_Screen_Main_ButtonWidget_IncTemp_OnPressed(leButtonWidget* btn)
{
    Screen_Main_ButtonWidget_IncTemp->fn->setBorderType(Screen_Main_ButtonWidget_IncTemp, LE_WIDGET_BORDER_LINE);
}
void event_Screen_Main_ButtonWidget_IncTemp_OnReleased(leButtonWidget* btn)
{
    Screen_Main_ButtonWidget_IncTemp->fn->setBorderType(Screen_Main_ButtonWidget_IncTemp, LE_WIDGET_BORDER_NONE);
    if (waterTemp < 99)
    {
        waterTemp++;
    }
    set_region_temp(waterTemp);
}

void event_Screen_Main_ButtonWidget_JetDec_OnPressed(leButtonWidget* btn)
{
    Screen_Main_ButtonWidget_JetDec->fn->setBorderType(Screen_Main_ButtonWidget_JetDec, LE_WIDGET_BORDER_LINE);
}
void event_Screen_Main_ButtonWidget_JetDec_OnReleased(leButtonWidget* btn)
{
    Screen_Main_ButtonWidget_JetDec->fn->setBorderType(Screen_Main_ButtonWidget_JetDec, LE_WIDGET_BORDER_NONE);
    if (jetCtrl > 0)
    {
        jetCtrl--;
    }
    set_region_jet(jetCtrl);
}
void event_Screen_Main_ButtonWidget_JetInc_OnPressed(leButtonWidget* btn)
{
    Screen_Main_ButtonWidget_JetInc->fn->setBorderType(Screen_Main_ButtonWidget_JetInc, LE_WIDGET_BORDER_LINE);
}
void event_Screen_Main_ButtonWidget_JetInc_OnReleased(leButtonWidget* btn)
{
    Screen_Main_ButtonWidget_JetInc->fn->setBorderType(Screen_Main_ButtonWidget_JetInc, LE_WIDGET_BORDER_NONE);
    if (jetCtrl < 9)
    {
        jetCtrl++;
    }
    set_region_jet(jetCtrl);
}

static void update_btn_color(colors clr)
{
    if (clrBtnUpdProgr == false)
    {
        set_region_color(clr);
    }
    else
    {
        clrBtnUpdProgr = false;
    }
}
void event_Screen_Main_ButtonWidget_Red_OnPressed(leButtonWidget* btn)
{
    update_btn_color(RED);
}
void event_Screen_Main_ButtonWidget_Orange_OnPressed(leButtonWidget* btn)
{
    update_btn_color(ORANGE);
}
void event_Screen_Main_ButtonWidget_Yellow_OnPressed(leButtonWidget* btn)
{
    update_btn_color(YELLOW);
}
void event_Screen_Main_ButtonWidget_Green_OnPressed(leButtonWidget* btn)
{
    update_btn_color(GREEN);
}
void event_Screen_Main_ButtonWidget_Cyan_OnPressed(leButtonWidget* btn)
{
    update_btn_color(CYAN);
}
void event_Screen_Main_ButtonWidget_Purple_OnPressed(leButtonWidget* btn)
{
    update_btn_color(PURPLE);
}
void event_Screen_Main_ButtonWidget_Pink_OnPressed(leButtonWidget* btn)
{
    update_btn_color(PINK);
}
void event_Screen_Main_ButtonWidget_Radial_OnPressed(leButtonWidget* btn)
{
    update_btn_color(RADIAL);
}

void event_Screen_Main_ButtonWidget_Reg1_OnReleased(leButtonWidget* btn)
{
    update_sel_reg(REGION_1);
}
void event_Screen_Main_ButtonWidget_Reg2_OnReleased(leButtonWidget* btn)
{
    update_sel_reg(REGION_2);
}
void event_Screen_Main_ButtonWidget_Reg3_OnReleased(leButtonWidget* btn)
{
    update_sel_reg(REGION_3);
}
void event_Screen_Main_ButtonWidget_Reg4_OnReleased(leButtonWidget* btn)
{
    update_sel_reg(REGION_4);
}

static leBool BrightPanel_filterEvent(leWidget* target, leWidgetEvent* evt, void* data)
{
    leBool retval = LE_FALSE;

    int32_t x;
    
    switch(evt->id)
    {
        case LE_EVENT_TOUCH_DOWN:
        {
            // Need to take into account parent widget position and brightness bar offset
            x = ((leWidgetEvent_TouchDown *) evt)->x - BRIGHTNESS_PANEL_OFFSET - BRIGHTNESS_BAR_EXTRA_OFFSET;
            // need to compare the X coordinate with the panel X coordinate and the brightness bar maximum width
            if (x >= Screen_Main_PanelWidget_BrgGen->fn->getX(Screen_Main_PanelWidget_BrgGen) &&
                x <= Screen_Main_PanelWidget_BrgGen->fn->getX(Screen_Main_PanelWidget_BrgGen) + Screen_Main_PanelWidget_BrgGen->fn->getWidth(Screen_Main_PanelWidget_BrgLight))
            {
                // Need to extract panel offset
                x = x - Screen_Main_PanelWidget_BrgGen->fn->getX(Screen_Main_PanelWidget_BrgGen);
                Screen_Main_ButtonWidget_Brg->fn->setX(Screen_Main_ButtonWidget_Brg, x);
                
                if(x < 5)  //Workaround to fix issue with width 4 or smaller that will end up in error handler
                {
                    APP_LE_SETVISIBLE(Screen_Main_PanelWidget_BrgDark, LE_FALSE);
                }
                else
                {
                    if (APP_LE_GETVISIBLE(Screen_Main_PanelWidget_BrgDark) == LE_FALSE)
                    {
                        APP_LE_SETVISIBLE(Screen_Main_PanelWidget_BrgDark, LE_TRUE);
                    }
                    Screen_Main_PanelWidget_BrgDark->fn->setWidth(Screen_Main_PanelWidget_BrgDark, x);
                }
                set_light_brightness(x);
            }
            
            evt->accepted = LE_TRUE;
            evt->owner = target;
            retval = LE_TRUE;
            break;
        }   
        case LE_EVENT_TOUCH_MOVE:            
        {
            // Need to take into account parent widget position and brightness bar offset
            x = ((leWidgetEvent_TouchMove *) evt)->x - BRIGHTNESS_PANEL_OFFSET - BRIGHTNESS_BAR_EXTRA_OFFSET;
            // need to compare the X coordinate with the panel X coordinate and the brightness bar maximum width            
            if (x >= Screen_Main_PanelWidget_BrgGen->fn->getX(Screen_Main_PanelWidget_BrgGen) &&
                x <= Screen_Main_PanelWidget_BrgGen->fn->getX(Screen_Main_PanelWidget_BrgGen) + Screen_Main_PanelWidget_BrgGen->fn->getWidth(Screen_Main_PanelWidget_BrgLight))
            {
                // Need to extract panel offset
                x = x - Screen_Main_PanelWidget_BrgGen->fn->getX(Screen_Main_PanelWidget_BrgGen);
                Screen_Main_ButtonWidget_Brg->fn->setX(Screen_Main_ButtonWidget_Brg, x);
                
                if(x < 5)  //Workaround to fix issue with width 4 or smaller that will end up in error handler
                {
                    APP_LE_SETVISIBLE(Screen_Main_PanelWidget_BrgDark, LE_FALSE);
                }
                else
                {
                    if (APP_LE_GETVISIBLE(Screen_Main_PanelWidget_BrgDark) == LE_FALSE)
                    {
                        APP_LE_SETVISIBLE(Screen_Main_PanelWidget_BrgDark, LE_TRUE);
                    }
                    Screen_Main_PanelWidget_BrgDark->fn->setWidth(Screen_Main_PanelWidget_BrgDark, x);
                }
                set_light_brightness(x);
            }
            
            evt->accepted = LE_TRUE;
            retval = LE_TRUE;
            break;
        }
        default:
            break;
    }
    
   return retval;
}

static leBool VolumePanelMain_filterEvent(leWidget* target, leWidgetEvent* evt, void* data)
{    
    leBool retval = LE_FALSE;

    int32_t x;
    
    switch(evt->id)
    {
        case LE_EVENT_TOUCH_DOWN:
        {
            // Need to take into account parent widget position and volume bar offset
            // getX will return the widget position in it's parent widget, not relative to screen size
            x = ((leWidgetEvent_TouchDown *) evt)->x - VOL_MAIN_PANEL_X_OFFSET - VOL_MAIN_BAR_PANEL_EXTRA_OFFSET;
            // need to compare the X coordinate with the panel X coordinate and the volume bar maximum width
            if (x >= Screen_Main_PanelWidget_Vol->fn->getX(Screen_Main_PanelWidget_Vol) &&
                x <= Screen_Main_PanelWidget_Vol->fn->getX(Screen_Main_PanelWidget_Vol) + Screen_Main_PanelWidget_VolLight->fn->getWidth(Screen_Main_PanelWidget_VolLight))
            {
                x = x - Screen_Main_PanelWidget_Vol->fn->getX(Screen_Main_PanelWidget_Vol);
                
                if(x < 5)  //Workaround to fix issue with width 4 or smaller that will end up in error handler
                {
                    APP_LE_SETVISIBLE(Screen_Main_PanelWidget_VolDark, LE_FALSE);
                }
                else
                {
                    if (APP_LE_GETVISIBLE(Screen_Main_PanelWidget_VolDark) == LE_FALSE)
                    {
                        APP_LE_SETVISIBLE(Screen_Main_PanelWidget_VolDark, LE_TRUE);
                    }
                    Screen_Main_PanelWidget_VolDark->fn->setWidth(Screen_Main_PanelWidget_VolDark, (uint32_t)x);
                }
                set_music_volume_from_mains(x);
            }
            
            evt->accepted = LE_TRUE;
            evt->owner = target;
            
            retval = LE_TRUE;
            
            break;
        }
        case LE_EVENT_TOUCH_MOVE:
        {
            x = ((leWidgetEvent_TouchMove *) evt)->x - VOL_MAIN_PANEL_X_OFFSET;
            if (x >= Screen_Main_PanelWidget_Vol->fn->getX(Screen_Main_PanelWidget_Vol) &&
                x <= Screen_Main_PanelWidget_Vol->fn->getX(Screen_Main_PanelWidget_Vol) + Screen_Main_PanelWidget_VolLight->fn->getWidth(Screen_Main_PanelWidget_VolLight))
            {
                x = x - Screen_Main_PanelWidget_Vol->fn->getX(Screen_Main_PanelWidget_Vol);
                
                if(x < 5)  //Workaround to fix issue with width 4 or smaller that will end up in error handler
                {
                    APP_LE_SETVISIBLE(Screen_Main_PanelWidget_VolDark, LE_FALSE);
                }
                else
                {
                    if (APP_LE_GETVISIBLE(Screen_Main_PanelWidget_VolDark) == LE_FALSE)
                    {
                        APP_LE_SETVISIBLE(Screen_Main_PanelWidget_VolDark, LE_TRUE);
                    }
                    Screen_Main_PanelWidget_VolDark->fn->setWidth(Screen_Main_PanelWidget_VolDark, (uint32_t)x);
                }
                set_music_volume_from_mains(x);
            }
            
            evt->accepted = LE_TRUE;
            
            retval = LE_TRUE;
           
            break;
        }
        default:
            break;
    }
    
   return retval;
}

static void update_theme()
{
    if (get_light_theme() != curLightTheme)
    {
        curLightTheme = get_light_theme();
        if (curLightTheme)
        {
            //set to light theme
            Screen_Main_BackgroundPanel->fn->setScheme(Screen_Main_BackgroundPanel, &BkgScheme);
            Screen_Main_ButtonWidget_Settings->fn->setScheme(Screen_Main_ButtonWidget_Settings, &Scheme_Light);
            Screen_Main_ButtonWidget_WaterQ->fn->setScheme(Screen_Main_ButtonWidget_WaterQ, &Scheme_Light);
            Screen_Main_LabelWidget_SelectReg->fn->setScheme(Screen_Main_LabelWidget_SelectReg, &Scheme_Light);
            Screen_Main_LabelWidget_ControlDisp->fn->setScheme(Screen_Main_LabelWidget_ControlDisp, &Scheme_Light);
            Screen_Main_EditPanelWidget->fn->setScheme(Screen_Main_EditPanelWidget, &EditPanel);
            Screen_Main_LabelWidget_SelectedReg->fn->setScheme(Screen_Main_LabelWidget_SelectedReg, &Scheme_Light);
            Screen_Main_ButtonWidget_DecTemp->fn->setScheme(Screen_Main_ButtonWidget_DecTemp, &Scheme_Light);
            Screen_Main_ButtonWidget_IncTemp->fn->setScheme(Screen_Main_ButtonWidget_IncTemp, &Scheme_Light);
            Screen_Main_LabelWidget_WaterTemp->fn->setScheme(Screen_Main_LabelWidget_WaterTemp, &Scheme_Light);
            Screen_Main_LabelWidget_Deg->fn->setScheme(Screen_Main_LabelWidget_Deg, &Scheme_Light);
            Screen_Main_PanelWidget_BrgLight->fn->setScheme(Screen_Main_PanelWidget_BrgLight, &SliderLightScheme);
            Screen_Main_PanelWidget_BrgDark->fn->setScheme(Screen_Main_PanelWidget_BrgDark, &SliderDarkScheme);
            Screen_Main_ButtonWidget_JetDec->fn->setScheme(Screen_Main_ButtonWidget_JetDec, &Scheme_Light);
            Screen_Main_ButtonWidget_JetInc->fn->setScheme(Screen_Main_ButtonWidget_JetInc, &Scheme_Light);
            Screen_Main_LabelWidget_BubbleLevel->fn->setScheme(Screen_Main_LabelWidget_BubbleLevel, &Scheme_Light);
            Screen_Main_PanelWidget_Bkg->fn->setScheme(Screen_Main_PanelWidget_Bkg, &Scheme_Light);
            Screen_Main_LabelWidget_SongTitle->fn->setScheme(Screen_Main_LabelWidget_SongTitle, &Scheme_Light);
            Screen_Main_LabelWidget_ArtistName->fn->setScheme(Screen_Main_LabelWidget_ArtistName, &Scheme_Light);
            Screen_Main_PanelWidget_VolLight->fn->setScheme(Screen_Main_PanelWidget_VolLight, &SliderLightScheme);
            Screen_Main_PanelWidget_VolDark->fn->setScheme(Screen_Main_PanelWidget_VolDark, &SliderDarkScheme);

            Screen_Main_ButtonWidget_Settings->fn->setPressedImage(Screen_Main_ButtonWidget_Settings, (leImage*)&settings);
            Screen_Main_ButtonWidget_Settings->fn->setReleasedImage(Screen_Main_ButtonWidget_Settings, (leImage*)&settings);
            Screen_Main_ButtonWidget_WaterQ->fn->setPressedImage(Screen_Main_ButtonWidget_WaterQ, (leImage*)&water_drop);
            Screen_Main_ButtonWidget_WaterQ->fn->setReleasedImage(Screen_Main_ButtonWidget_WaterQ, (leImage*)&water_drop);

            Screen_Main_ButtonWidget_DecTemp->fn->setPressedImage(Screen_Main_ButtonWidget_DecTemp, (leImage*)&chevron_left15x24);
            Screen_Main_ButtonWidget_DecTemp->fn->setReleasedImage(Screen_Main_ButtonWidget_DecTemp, (leImage*)&chevron_left15x24);
            Screen_Main_ButtonWidget_IncTemp->fn->setPressedImage(Screen_Main_ButtonWidget_IncTemp, (leImage*)&chevron_right15x24);
            Screen_Main_ButtonWidget_IncTemp->fn->setReleasedImage(Screen_Main_ButtonWidget_IncTemp, (leImage*)&chevron_right15x24);

            Screen_Main_ButtonWidget_Brg->fn->setPressedImage(Screen_Main_ButtonWidget_Brg, (leImage*)&brg_btn);
            Screen_Main_ButtonWidget_Brg->fn->setReleasedImage(Screen_Main_ButtonWidget_Brg, (leImage*)&brg_btn);

            Screen_Main_ButtonWidget_JetDec->fn->setPressedImage(Screen_Main_ButtonWidget_JetDec, (leImage*)&chevron_left11x16);
            Screen_Main_ButtonWidget_JetDec->fn->setReleasedImage(Screen_Main_ButtonWidget_JetDec, (leImage*)&chevron_left11x16);
            Screen_Main_ButtonWidget_JetInc->fn->setPressedImage(Screen_Main_ButtonWidget_JetInc, (leImage*)&chevron_right11x16);
            Screen_Main_ButtonWidget_JetInc->fn->setReleasedImage(Screen_Main_ButtonWidget_JetInc, (leImage*)&chevron_right11x16);

            Screen_Main_ImageWidget_bubbles->fn->setImage(Screen_Main_ImageWidget_bubbles, (leImage*)&bubble_chart_40x40);

            Screen_Main_ButtonWidget_Prev->fn->setPressedImage(Screen_Main_ButtonWidget_Prev, (leImage*)&skip_previous);
            Screen_Main_ButtonWidget_Prev->fn->setReleasedImage(Screen_Main_ButtonWidget_Prev, (leImage*)&skip_previous);
            Screen_Main_ButtonWidget_PlayPause->fn->setPressedImage(Screen_Main_ButtonWidget_PlayPause, (leImage*)&play_circle);
            Screen_Main_ButtonWidget_PlayPause->fn->setReleasedImage(Screen_Main_ButtonWidget_PlayPause, (leImage*)&pause_circle);
            Screen_Main_ButtonWidget_Next->fn->setPressedImage(Screen_Main_ButtonWidget_Next, (leImage*)&skip_next);
            Screen_Main_ButtonWidget_Next->fn->setReleasedImage(Screen_Main_ButtonWidget_Next, (leImage*)&skip_next);

            Screen_Main_ImageWidget_Volume->fn->setImage(Screen_Main_ImageWidget_Volume, (leImage*)&volume_16x16);
        }
        else
        {
            //set to dark theme
            Screen_Main_BackgroundPanel->fn->setScheme(Screen_Main_BackgroundPanel, &BkgScheme_Dark);
            Screen_Main_ButtonWidget_Settings->fn->setScheme(Screen_Main_ButtonWidget_Settings, &Scheme_Dark);
            Screen_Main_ButtonWidget_WaterQ->fn->setScheme(Screen_Main_ButtonWidget_WaterQ, &Scheme_Dark);
            Screen_Main_LabelWidget_SelectReg->fn->setScheme(Screen_Main_LabelWidget_SelectReg, &Scheme_Dark);
            Screen_Main_LabelWidget_ControlDisp->fn->setScheme(Screen_Main_LabelWidget_ControlDisp, &Scheme_Dark);
            Screen_Main_EditPanelWidget->fn->setScheme(Screen_Main_EditPanelWidget, &EditPanel_Dark);
            Screen_Main_LabelWidget_SelectedReg->fn->setScheme(Screen_Main_LabelWidget_SelectedReg, &Scheme_Dark);
            Screen_Main_ButtonWidget_DecTemp->fn->setScheme(Screen_Main_ButtonWidget_DecTemp, &Scheme_Dark);
            Screen_Main_ButtonWidget_IncTemp->fn->setScheme(Screen_Main_ButtonWidget_IncTemp, &Scheme_Dark);
            Screen_Main_LabelWidget_WaterTemp->fn->setScheme(Screen_Main_LabelWidget_WaterTemp, &Scheme_Dark);
            Screen_Main_LabelWidget_Deg->fn->setScheme(Screen_Main_LabelWidget_Deg, &Scheme_Dark);
            Screen_Main_PanelWidget_BrgLight->fn->setScheme(Screen_Main_PanelWidget_BrgLight, &SliderLightScheme_Dark);
            Screen_Main_PanelWidget_BrgDark->fn->setScheme(Screen_Main_PanelWidget_BrgDark, &SliderDarkScheme_Dark);
            Screen_Main_ButtonWidget_JetDec->fn->setScheme(Screen_Main_ButtonWidget_JetDec, &Scheme_Dark);
            Screen_Main_ButtonWidget_JetInc->fn->setScheme(Screen_Main_ButtonWidget_JetInc, &Scheme_Dark);
            Screen_Main_LabelWidget_BubbleLevel->fn->setScheme(Screen_Main_LabelWidget_BubbleLevel, &Scheme_Dark);
            Screen_Main_PanelWidget_Bkg->fn->setScheme(Screen_Main_PanelWidget_Bkg, &Scheme_Dark);
            Screen_Main_LabelWidget_SongTitle->fn->setScheme(Screen_Main_LabelWidget_SongTitle, &Scheme_Dark);
            Screen_Main_LabelWidget_ArtistName->fn->setScheme(Screen_Main_LabelWidget_ArtistName, &Scheme_Dark);
            Screen_Main_PanelWidget_VolLight->fn->setScheme(Screen_Main_PanelWidget_VolLight, &SliderLightScheme_Dark);
            Screen_Main_PanelWidget_VolDark->fn->setScheme(Screen_Main_PanelWidget_VolDark, &SliderDarkScheme_Dark);


            Screen_Main_ButtonWidget_Brg->fn->setPressedImage(Screen_Main_ButtonWidget_Brg, (leImage*)&brg_btn_dark);
            Screen_Main_ButtonWidget_Brg->fn->setReleasedImage(Screen_Main_ButtonWidget_Brg, (leImage*)&brg_btn_dark);
            
            Screen_Main_ButtonWidget_Settings->fn->setPressedImage(Screen_Main_ButtonWidget_Settings, (leImage*)&settings_dark);
            Screen_Main_ButtonWidget_Settings->fn->setReleasedImage(Screen_Main_ButtonWidget_Settings, (leImage*)&settings_dark);
            Screen_Main_ButtonWidget_WaterQ->fn->setPressedImage(Screen_Main_ButtonWidget_WaterQ, (leImage*)&water_drop_dark);
            Screen_Main_ButtonWidget_WaterQ->fn->setReleasedImage(Screen_Main_ButtonWidget_WaterQ, (leImage*)&water_drop_dark);

            Screen_Main_ButtonWidget_DecTemp->fn->setPressedImage(Screen_Main_ButtonWidget_DecTemp, (leImage*)&chevron_left15x24_dark);
            Screen_Main_ButtonWidget_DecTemp->fn->setReleasedImage(Screen_Main_ButtonWidget_DecTemp, (leImage*)&chevron_left15x24_dark);
            Screen_Main_ButtonWidget_IncTemp->fn->setPressedImage(Screen_Main_ButtonWidget_IncTemp, (leImage*)&chevron_right15x24_dark);
            Screen_Main_ButtonWidget_IncTemp->fn->setReleasedImage(Screen_Main_ButtonWidget_IncTemp, (leImage*)&chevron_right15x24_dark);

            Screen_Main_ButtonWidget_Brg->fn->setPressedImage(Screen_Main_ButtonWidget_Brg, (leImage*)&brg_btn_dark);
            Screen_Main_ButtonWidget_Brg->fn->setReleasedImage(Screen_Main_ButtonWidget_Brg, (leImage*)&brg_btn_dark);

            Screen_Main_ButtonWidget_JetDec->fn->setPressedImage(Screen_Main_ButtonWidget_JetDec, (leImage*)&chevron_left11x16_dark);
            Screen_Main_ButtonWidget_JetDec->fn->setReleasedImage(Screen_Main_ButtonWidget_JetDec, (leImage*)&chevron_left11x16_dark);
            Screen_Main_ButtonWidget_JetInc->fn->setPressedImage(Screen_Main_ButtonWidget_JetInc, (leImage*)&chevron_right11x16_dark);
            Screen_Main_ButtonWidget_JetInc->fn->setReleasedImage(Screen_Main_ButtonWidget_JetInc, (leImage*)&chevron_right11x16_dark);

            Screen_Main_ImageWidget_bubbles->fn->setImage(Screen_Main_ImageWidget_bubbles, (leImage*)&bubble_chart_40x40_dark);

            Screen_Main_ButtonWidget_Prev->fn->setPressedImage(Screen_Main_ButtonWidget_Prev, (leImage*)&skip_previous_dark);
            Screen_Main_ButtonWidget_Prev->fn->setReleasedImage(Screen_Main_ButtonWidget_Prev, (leImage*)&skip_previous_dark);
            Screen_Main_ButtonWidget_PlayPause->fn->setPressedImage(Screen_Main_ButtonWidget_PlayPause, (leImage*)&play_circle_dark);
            Screen_Main_ButtonWidget_PlayPause->fn->setReleasedImage(Screen_Main_ButtonWidget_PlayPause, (leImage*)&pause_circle_dark);
            Screen_Main_ButtonWidget_Next->fn->setPressedImage(Screen_Main_ButtonWidget_Next, (leImage*)&skip_next_dark);
            Screen_Main_ButtonWidget_Next->fn->setReleasedImage(Screen_Main_ButtonWidget_Next, (leImage*)&skip_next_dark);

            Screen_Main_ImageWidget_Volume->fn->setImage(Screen_Main_ImageWidget_Volume, (leImage*)&volume_16x16_dark);
        }        
    }
}

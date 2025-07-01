/*******************************************************************************
  Application Header

  File Name:
    app_ScreenMain.h

  Summary:
    Application screen and widget callback code

  Description:
    Application screen and widget callback code
 *******************************************************************************/

//DOM-IGNORE-BEGIN
/*****************************************************************************
 Copyright (C) 2024 Microchip Technology Inc. and its subsidiaries.

Microchip Technology Inc. and its subsidiaries.

Subject to your compliance with these terms, you may use Microchip software 
and any derivatives exclusively with Microchip products. It is your 
responsibility to comply with third party license terms applicable to your 
use of third party software (including open source software) that may 
accompany Microchip software.

THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR 
PURPOSE.

IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE 
FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN 
ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, 
THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*****************************************************************************/
//DOM-IGNORE-END

typedef enum
{
    APP_SCRN_INIT,
    APP_SCRN_IDLE,
    APP_SCRN_RUN,
    APP_SCRN_STOP,
} APP_SCRN_STATE_t;

typedef enum
{
    APP_SCRN_EVT_INPUT_ENABLE,
    APP_SCRN_EVT_INPUT_VOLUME,
    APP_SCRN_EVT_INPUT_MUTE,
    APP_SCRN_EVT_INPUT_SOLO,
    APP_SCRN_EVT_INPUT_CUE,

    APP_SCRN_EVT_OUTPUT_ENABLE,

    APP_SCRN_EVT_MAIN_VOLUME,
    APP_SCRN_EVT_MAIN_MUTE,
    
    APP_SCRN_EVT_RUN,

    APP_SCRN_EVT_RESET,
    
    /* number of events */
    APP_SCRN_EVT_MAX, 

    /* limit to 32 events, due to 32-bit event flag used */
    APP_SCRN_EVT_LIMIT = 31,
} APP_SCRN_EVENT_TYPE_t;

typedef struct
{
    unsigned char idx;
    unsigned char value;
} APP_SCRN_EVENT_PARM_t;

typedef struct
{
    uint32_t eventFlag;
    APP_SCRN_EVENT_PARM_t eventParm[APP_SCRN_EVT_MAX];
} APP_SCRN_EVENTS_t;
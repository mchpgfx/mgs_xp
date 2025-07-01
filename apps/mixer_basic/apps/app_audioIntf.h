/*******************************************************************************
  Application Source

  File Name:
    app_audioIntf.h

  Summary:
    Application audio interface 

  Description:
    Application audio interface 
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

#include <stdio.h>

#define APP_AUDIO_INTF_SUCCESS 0
#define APP_AUDIO_INTF_FAILED -1

#define VOLUME_DEFAULT_PCT 50

typedef enum
{
    APP_AUDIO_DISABLE,
    APP_AUDIO_ENABLE,
} APP_AUDIO_ENABLE_t;

typedef enum
{
    APP_AUDIO_IDX1,
    APP_AUDIO_IDX2,
    APP_AUDIO_IDX3,
    APP_AUDIO_IDX4,
    APP_AUDIO_IDX_MAX,
} APP_AUDIO_IDX_t;

int App_AudioIntf_InputEnable(APP_AUDIO_IDX_t input, APP_AUDIO_ENABLE_t en);
int App_AudioIntf_InputMute(APP_AUDIO_IDX_t input, APP_AUDIO_ENABLE_t en);
int App_AudioIntf_InputCue(APP_AUDIO_IDX_t input, APP_AUDIO_ENABLE_t en);
int App_AudioIntf_InputSolo(APP_AUDIO_IDX_t input, APP_AUDIO_ENABLE_t en);
int App_AudioIntf_InputSetVol(APP_AUDIO_IDX_t input, unsigned int vol);

int App_AudioIntf_OutputEnable(APP_AUDIO_IDX_t output, APP_AUDIO_ENABLE_t en);

int App_AudioIntf_MainSetVol(unsigned int vol);
int App_AudioIntf_MixerRun(void);
int App_AudioIntf_MixerStop(void);
int App_AudioIntf_MainMute(APP_AUDIO_ENABLE_t en);

void App_AudioIntf_Reset(void);

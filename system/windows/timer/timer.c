/*******************************************************************************
* Copyright (C) 2025 Microchip Technology Inc. and its subsidiaries.
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

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "timer.h"

#define MAX_TIMER_COUNT 100

struct timer
{
    SDL_TimerID sdl_timer_id;
    uint32_t interval;
    TIMER_TYPE type;
    void* data;
    timer_handler callback;
    struct timer *next;
};

static struct timer *timer_head = NULL;
static int timer_initialized = 0;

static Uint32 sdl_timer_callback(Uint32 interval, void *param)
{
    struct timer *t = (struct timer *)param;

    if (t && t->callback)
    {
        t->callback((uintptr_t)t, t->data);
    }

    if (t && t->type == TIMER_SINGLE_SHOT)
    {
        return 0;
    }

    return interval;
}

int32_t timer_init(void)
{
    if (timer_initialized)
    {
        return 1;
    }

    timer_initialized = 1;
    printf("In %s : Done\n", __FUNCTION__);

    return 1;
}

uintptr_t start_timer(unsigned int interval, timer_handler handler, TIMER_TYPE type, void *data)
{
    struct timer* tnode = NULL;

    tnode = (struct timer *)malloc(sizeof(struct timer));
    if (tnode == NULL)
    {
        return 0;
    }

    tnode->interval = interval;
    tnode->data = data;
    tnode->type = type;
    tnode->callback = handler;

    tnode->sdl_timer_id = SDL_AddTimer(interval, sdl_timer_callback, tnode);

    if (tnode->sdl_timer_id == 0)
    {
        printf("SDL_AddTimer failed: %s\n", SDL_GetError());
        free(tnode);
        return 0;
    }

    tnode->next = timer_head;
    timer_head = tnode;

    printf("In %s : Done\n", __FUNCTION__);

    return (uintptr_t)tnode;
}

void stop_timer(uintptr_t timer)
{
    struct timer *tmp = NULL;
    struct timer *tnode = (struct timer *)timer;

    if (tnode == NULL)
    {
        return;
    }

    SDL_RemoveTimer(tnode->sdl_timer_id);

    if (tnode == timer_head)
    {
        timer_head = timer_head->next;
        free(tnode);
    }
    else
    {
        tmp = timer_head;

        while (tmp && tmp->next != tnode)
        {
            tmp = tmp->next;
        }

        if (tmp)
        {
            tmp->next = tmp->next->next;
            free(tnode);
        }
    }
}

void timer_deinit(void)
{
    while (timer_head)
    {
        stop_timer((uintptr_t)timer_head);
    }

    timer_initialized = 0;
}

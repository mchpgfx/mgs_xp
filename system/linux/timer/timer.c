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

#include <poll.h>
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/timerfd.h>
#include <unistd.h>

#include "timer.h"

#define MAX_TIMER_COUNT 100

struct timer
{
    int32_t fd;
    uint32_t interval;
    TIMER_TYPE type;
    void* data;
    timer_handler callback;
    struct timer *next;
};

static void *timer_thread(void *data);
static pthread_t p_timer;
static struct timer *timer_head = NULL;

int32_t timer_init()
{
    if(pthread_create(&p_timer, NULL, timer_thread, NULL))
    {
        return -1;
    }

    return 1;
}

uintptr_t start_timer(unsigned int interval, timer_handler handler, TIMER_TYPE type, void *data)
{
    struct timer* tnode = NULL;
    struct itimerspec its;

    tnode = (struct timer *)malloc(sizeof(struct timer));
    if(tnode == NULL)
		return 0;

    tnode->interval = interval;
    tnode->data = data;
    tnode->type = type;
    tnode->callback = handler;

    tnode->fd = timerfd_create(CLOCK_REALTIME, 0);

    if (tnode->fd == -1)
    {
        free(tnode);
        return 0;
    }

    its.it_value.tv_sec = interval / 1000;
    its.it_value.tv_nsec = (interval % 1000)* 1000000;

    if (type == TIMER_PERIODIC)
    {
      its.it_interval.tv_sec= interval / 1000;
      its.it_interval.tv_nsec = (interval %1000) * 1000000;
    }
    else
    {
      its.it_interval.tv_sec= 0;
      its.it_interval.tv_nsec = 0;
    }

    timerfd_settime(tnode->fd, 0, &its, NULL);

    /*Inserting the timer node into the list*/
    tnode->next = timer_head;
    timer_head = tnode;

	printf("In %s : Done\n",__FUNCTION__);

    return (uintptr_t)tnode;
}

void stop_timer(uintptr_t timer)
{
    struct timer *tmp = NULL;
    struct timer *tnode = (struct timer *)timer;

    if(tnode == NULL)
		return;

    if(tnode == timer_head)
    {
        timer_head = timer_head->next;
    }
	else
	{
		tmp = timer_head;
      
		while(tmp && tmp->next != tnode)
			tmp = tmp->next;

      	if(tmp)
      	{
          tmp->next = tmp->next->next;
          close(tnode->fd);
          free(tnode);
      	}
    }
}

void timer_deinit()
{
    while(timer_head)
		stop_timer((size_t)timer_head);

    pthread_cancel(p_timer);
    pthread_join(p_timer, NULL);
}

struct timer* get_timer(int fd)
{
    struct timer *tmp = timer_head;

    while(tmp)
    {
        if(tmp->fd == fd)
			return tmp;

        tmp = tmp->next;
    }
    return NULL;
}

void *timer_thread(void * data)
{
    struct timer *tmp = NULL;
    struct pollfd ufds[MAX_TIMER_COUNT] = {{0}};
    int count = 0;
    int rfd = 0, i, s;
    uint64_t exp;

    while(1)
    {
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        pthread_testcancel();
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

        count = 0;
        tmp = timer_head;

        memset(ufds, 0, sizeof(struct pollfd)*MAX_TIMER_COUNT);
        while(tmp)
        {
            ufds[count].fd = tmp->fd;
            ufds[count].events = POLLIN;
            count++;

            tmp = tmp->next;
        }

        rfd = poll(ufds, count, 100);

        if(rfd <= 0)
			continue;

        for(i = 0; i < count; i++)
        {
            if(ufds[i].revents & POLLIN)
            {
                s = read(ufds[i].fd, &exp, sizeof(uint64_t));

                if(s != sizeof(uint64_t))
					continue;

                tmp = get_timer(ufds[i].fd);
                if(tmp && tmp->callback)
				{
					tmp->callback((uintptr_t)tmp, tmp->data);
					// printf("In %s Done callback\n",__FUNCTION__);
				}
            }
        }
    }

    return NULL;
}

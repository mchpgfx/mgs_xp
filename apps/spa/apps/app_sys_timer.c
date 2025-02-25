#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#include "app_sys_timer.h"

SYS_TIME_CALLBACK callbackFn;

static volatile bool timeUp = 0;
static uint32_t periodMS;

void timer_callback(uintptr_t timer, void * data) 
{
       if (callbackFn != NULL)
       {
              callbackFn((uintptr_t) data);

              timeUp = 1;
       }
}

SYS_TIME_HANDLE SYS_TIME_CallbackRegisterMS(SYS_TIME_CALLBACK callback, 
                                            uint32_t unused,
                                            uint32_t period_ms,
                                            uint32_t unused2)
{
       periodMS = period_ms;
       callbackFn = callback;

       return start_timer(period_ms, timer_callback, TIMER_PERIODIC, NULL);
}

SYS_TIME_HANDLE SYS_TIME_TimerStart(SYS_TIME_HANDLE timer)
{
       if (timer != NULL)
       {
              stop_timer(timer);
       }

       return start_timer(periodMS, timer_callback, TIMER_PERIODIC, NULL);
}

void SYS_TIME_DelayMS(uint32_t period_ms, SYS_TIME_HANDLE * timer)
{
       usleep(period_ms * 1000);

}

bool SYS_TIME_DelayIsComplete(SYS_TIME_HANDLE timer)
{
       return true;
}

void SYS_TIME_TimerStop ( SYS_TIME_HANDLE timer )
{
       stop_timer(timer);
}

void SYS_TIME_TimerDestroy ( SYS_TIME_HANDLE timer )
{
       stop_timer(timer);
}


#ifndef _APP_SYS_TIMER_H    /* Guard against multiple inclusion */
#define _APP_SYS_TIMER_H


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>
#include "linux/timer/timer.h"

#define SYS_TIME_HANDLE         uintptr_t
#define SYS_TIME_PERIODIC       1
#define SYS_TIME_HANDLE_INVALID NULL
#define SYS_TIME_RESULT         int32_t

typedef void (*SYS_TIME_CALLBACK)( uintptr_t context) ;

SYS_TIME_HANDLE SYS_TIME_CallbackRegisterMS(SYS_TIME_CALLBACK callback, 
                                            uint32_t unused,
                                            uint32_t period_ms,
                                            uint32_t unused2);

SYS_TIME_HANDLE SYS_TIME_TimerStart(SYS_TIME_HANDLE timer);  
void SYS_TIME_TimerStop ( SYS_TIME_HANDLE timer );
void SYS_TIME_DelayMS(uint32_t period_ms, SYS_TIME_HANDLE * timer);
void SYS_TIME_TimerDestroy ( SYS_TIME_HANDLE timer );
bool SYS_TIME_DelayIsComplete(SYS_TIME_HANDLE timer);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _APP_SYS_TIMER_H */

#include <stddef.h>

#ifdef _WIN32
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#endif

#include "system_init.h"

int main ( void )
{
#ifdef _WIN32
    SDL_SetMainReady();
#endif

    /* Initialize all modules */
    SYS_Initialize(NULL);

    while (1) {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks();
    }

    /* Execution should not come here during normal operation */

    return 0;
}

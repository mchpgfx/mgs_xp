
#include <stddef.h>

#include "system_init.h"

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize(NULL);

    while (1) {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks();
    }

    /* Execution should not come here during normal operation */

    return 0;
}

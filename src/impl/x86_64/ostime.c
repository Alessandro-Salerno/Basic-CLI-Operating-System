#include "ostime.h"
#include "ostypes.h"


void time_wait(uint32_t time) {
    while (TRUE) {
        asm volatile ("nop");
        if (time-- <= 0)
            break;
    }
}

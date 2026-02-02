#pragma once
#include <stdint.h>

#ifdef HW
    #include <avr/io.h>
    #include <avr/interrupt.h>
    #include <util/delay.h>
#endif


#ifdef SIM
    #include "sim/sim_io.h"
    static inline void _delay_ms(uint16_t time_ms) {
        /*debug_delay_ms(time_ms);*/
    }
#endif

#if !(defined HW) && !(defined SIM)
#error BUILD MACRO IS NOT DEFINED FOR EITHER HARDWARE (HW) OR SIMULATION (SIM)
#endif


#if defined HW && defined SIM
#error MACRO IS DEFINED FOR BOTH HARDWARE (HW) AND SIMULATION (SIM)
#endif
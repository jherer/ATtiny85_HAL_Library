#include <platform/delay.h>


#ifdef HW
#include <util/delay.h>

void delay_msec(uint16_t time_msec) {
    for (uint32_t i = 0; i < time_msec; i++) {
        _delay_ms(1);
    }
}

void delay_usec(uint32_t time_usec) {
    for (uint32_t i = 0; i < time_usec; i++) {
        _delay_us(1);
    }
}
#endif


#ifdef SIM

void delay_msec(uint16_t time_msec) {
}

void delay_usec(uint32_t time_usec) {
}

#endif
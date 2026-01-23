#include "hal_status.h"
#include "platform.h"

uint8_t hal_status_get_sreg(void) {
    return SREG;
}

void hal_status_set_sreg(uint8_t new_sreg) {
    SREG = new_sreg;
}

void hal_status_interrupts_enable(void) {
    sei();
}

void hal_status_interrupts_disable(void) {
    cli();
}
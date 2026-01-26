#include "hal_status.h"

void interrupts_enable(void) {
    hal_status_interrupts_enable();
}

void interrupts_disable(void) {
    hal_status_interrupts_disable();
}

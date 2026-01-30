#include "drivers/interrupt_driver.h"
#include "hal_status.h"
#include "sim/debug.h"

void interrupt_enable(void) {
    debug_println("enable interrupts", DEBUG_LAYER_DRIVERS);
    hal_status_interrupt_enable();
}

void interrupt_disable(void) {
    debug_println("disable interrupts", DEBUG_LAYER_DRIVERS);
    hal_status_interrupt_disable();
}
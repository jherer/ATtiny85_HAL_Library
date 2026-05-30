#include <drivers/interrupt_driver.h>
#include <hal/hal_status.h>
#include <platform/debug.h>

void interrupt_enable(void) {
    DEBUG_PRINTLN("Interrupt enable", DEBUG_LAYER_DRIVERS);
    hal_status_interrupt_enable();
}

void interrupt_disable(void) {
    DEBUG_PRINTLN("Interrupt disable", DEBUG_LAYER_DRIVERS);
    hal_status_interrupt_disable();
}
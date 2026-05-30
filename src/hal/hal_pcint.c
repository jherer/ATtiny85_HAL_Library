#include <hal/hal_pcint.h>

#include "bitwise.h"

void hal_pcint_enable_interrupts() {
    bitwise_write_bit(&GIMSK, PCIE, 1);
}

void hal_pcint_disable_interrupts() {
    bitwise_write_bit(&GIMSK, PCIE, 0);
}

void hal_pcint_enable_pin(uint8_t pin_num) {
    bitwise_write_bit(&PCMSK, pin_num, 1);
}

void hal_pcint_disable_pin(uint8_t pin_num) {
    bitwise_write_bit(&PCMSK, pin_num, 0);
}

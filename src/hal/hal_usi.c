#include "hal_usi.h"
#include <avr/io.h>
#include "bitwise.h"


void hal_usi_set_wire_mode(uint8_t wm_bits) {
    bitwise_write_bit(&USICR, USIWM0, wm_bits & (1 << 0));
    bitwise_write_bit(&USICR, USIWM1, wm_bits & (1 << 1));
}

void hal_usi_set_clock_source(uint8_t cs_bits) {
    bitwise_write_bit(&USICR, USICS0, cs_bits & (1 << 0));
    bitwise_write_bit(&USICR, USICS1, cs_bits & (1 << 1));
}

void hal_usi_enable_interrupt_ovf(bool enable) {
    bitwise_write_bit(&USICR, USIOIE, enable);
}

bool hal_usi_read_overflow_flag(void) {
    return bitwise_read_bit(USICR, USIOIF);
}

void hal_usi_clear_overflow_flag(void) {
    bitwise_write_bit(&USISR, USIOIF, 1);
}

void hal_usi_write_data(uint8_t data) {
    USIDR = data;
}

uint8_t hal_usi_read_data(void) {
    return USIDR;
}

void hal_usi_soft_strobe_clock() {
    bitwise_write_bit(&USICR, USITC, 1); // Toggle clock
    bitwise_write_bit(&USICR, USICLK, 1); // Shift data
}
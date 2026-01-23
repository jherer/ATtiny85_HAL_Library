#include "hal_timer0.h"
#include <avr/io.h>
#include "bitwise.h"


// CONFIG

void hal_timer0_config(uint8_t tccr0a_bits, uint8_t tccr0b_bits) {
    TCCR0A = tccr0a_bits;
    TCCR0B = tccr0b_bits;
}

// COUNTER 

uint8_t hal_timer0_get_count(void) {
    return TCNT0;
}

void hal_timer0_set_count(uint8_t count) {
    TCNT0 = count;
}


// COMPARE REGISTER

void hal_timer0_set_output_compare_register_A(uint8_t ocr0a_value) {
    OCR0A = ocr0a_value;
}

void hal_timer0_set_output_compare_register_B(uint8_t ocr0b_value) {
    OCR0B = ocr0b_value;
}


// INTERRUPTS

void hal_timer0_enable_interrupt_compA(bool enable) {
    bitwise_write_bit(&TIMSK, OCIE0A, enable);
}

void hal_timer0_enable_interrupt_compB(bool enable) {
    bitwise_write_bit(&TIMSK, OCIE0B, enable);
}

void hal_timer0_enable_interrupt_ovf(bool enable) {
    bitwise_write_bit(&TIMSK, TOIE0, enable);
}

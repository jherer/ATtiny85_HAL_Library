#include "hal_adc.h"
#include <avr/io.h>
#include "bitwise.h"

void hal_adc_enable(bool aden_bit) {
    bitwise_write_bit(&ADCSRA, ADEN, aden_bit);
}

void hal_adc_set_input_channel(uint8_t mux_bits) {
    bitwise_write_bit(&ADMUX, MUX0, mux_bits & (1 << 0));
    bitwise_write_bit(&ADMUX, MUX1, mux_bits & (1 << 1));
    bitwise_write_bit(&ADMUX, MUX2, mux_bits & (1 << 2));
    bitwise_write_bit(&ADMUX, MUX3, mux_bits & (1 << 3));
}

void hal_adc_set_reference(uint8_t refs_bits) {
    bitwise_write_bit(&ADMUX, REFS0, refs_bits & (1 << 0));
    bitwise_write_bit(&ADMUX, REFS1, refs_bits & (1 << 1));
    bitwise_write_bit(&ADMUX, REFS2, refs_bits & (1 << 2));
}

void hal_adc_set_prescaler(uint8_t adps_bits) {
    bitwise_write_bit(&ADCSRA, ADPS0, adps_bits & (1 << 0));
    bitwise_write_bit(&ADCSRA, ADPS1, adps_bits & (1 << 1));
    bitwise_write_bit(&ADCSRA, ADPS1, adps_bits & (1 << 2));
}

void hal_adc_start_conversion(void) {
    bitwise_write_bit(&ADCSRA, ADSC, 1);
}

uint8_t hal_adc_read(void) {
    return ADCH;
}
#include <hal/hal_adc.h>
#include <platform/io.h>
#include "bitwise.h"

static uint8_t _get_admux_byte(bool adlar_bit, adc_channel_t channel) {
    switch (channel) {
    case ADC_CHANNEL_0: return (adlar_bit << ADLAR);
    case ADC_CHANNEL_1: return (adlar_bit << ADLAR) | (1 << MUX0);
    case ADC_CHANNEL_2: return (adlar_bit << ADLAR) | (1 << MUX1);
    case ADC_CHANNEL_3: return (adlar_bit << ADLAR) | ((1 << MUX1) | (1 << MUX0));
    default: return (adlar_bit << ADLAR);
    }
}

static uint8_t _get_adcsra_byte(bool aden_bit, bool adie_bit, adc_prescaler_t prescaler) {
    uint8_t adcsra_byte = (aden_bit << ADEN) | (adie_bit << ADIE);
    switch (prescaler) {
    case ADC_PRESCALER_2: return adcsra_byte | (1 << ADPS0);
    case ADC_PRESCALER_4: return adcsra_byte | (1 << ADPS1);
    case ADC_PRESCALER_8: return adcsra_byte | (1 << ADPS1) | (1 << ADPS0);
    case ADC_PRESCALER_16: return adcsra_byte | (1 << ADPS2);
    case ADC_PRESCALER_32: return adcsra_byte | (1 << ADPS2) | (1 << ADPS0);
    case ADC_PRESCALER_64: return adcsra_byte | (1 << ADPS2) | (1 << ADPS1);
    case ADC_PRESCALER_128: return adcsra_byte | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    default: return adcsra_byte;
    }
}

void hal_adc_set_control_status_register(bool enable_adc_bit, bool enable_interrupt_bit, adc_prescaler_t prescaler) {
    ADCSRA = _get_adcsra_byte(enable_adc_bit, enable_interrupt_bit, prescaler);
}

void hal_adc_set_mux(adc_channel_t channel) {
    ADMUX = _get_admux_byte(true, channel);
}

void hal_adc_start_conversion(void) {
    bitwise_write_bit(&ADCSRA, ADSC, 1);
}

uint8_t hal_adc_read(void) {
    return ADCH;
}
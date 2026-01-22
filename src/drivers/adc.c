#include "drivers/adc.h"
#include <util/delay.h>

#define ADC_READ_DELAY_US 1
static bool initialized = false;

error_t adc_init(void) {
    hal_adc_enable(true);
    hal_adc_set_reference(0b00);
    hal_adc_set_prescaler(0b010);
    initialized = true;
    return ERROR_OK;
}

error_t adc_read(adc_channel_t channel, uint8_t *value_ptr) {
    if (!initialized) {
        return ERROR_ADC_UNINITIALIZED;
    }
    uint8_t mux_bits = 0b00;
    switch (channel) {
    case ADC_CHANNEL_0:
        hal_adc_set_input_channel(0b0000);
        break;
    case ADC_CHANNEL_1:
        hal_adc_set_input_channel(0b0001);
        break;
    case ADC_CHANNEL_2:
        hal_adc_set_input_channel(0b0010);
        break;
    case ADC_CHANNEL_3:
        hal_adc_set_input_channel(0b0011);
        break;
    default:
        return ERROR_ADC_CHANNEL_UNSUPPORTED;
    }
    hal_adc_start_conversion();
    _delay_us(ADC_READ_DELAY_US);
    *value_ptr = hal_adc_read();
    return ERROR_OK;
}
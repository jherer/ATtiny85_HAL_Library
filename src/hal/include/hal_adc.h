#ifndef HAL_ADC_H
#define HAL_ADC_H
#include <stdint.h>
#include <stdbool.h>

void hal_adc_enable(bool aden_bit);
void hal_adc_set_input_channel(uint8_t mux_bits);
void hal_adc_set_reference(uint8_t refs_bits);
void hal_adc_set_prescaler(uint8_t adps_bits);
void hal_adc_start_conversion(void);
uint8_t hal_adc_read(void);

#endif
#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <hal/adc_enums.h>

void hal_adc_enable(bool enabled);
void hal_adc_set_mux(adc_channel_t channel);
void hal_adc_set_prescaler(adc_prescaler_t prescaler);
void hal_adc_start_conversion(void);
uint8_t hal_adc_read(void);
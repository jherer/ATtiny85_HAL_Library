#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <hal/adc_enums.h>

void hal_adc_set_control_status_register(bool enable_adc_bit, bool enable_interrupt_bit, adc_prescaler_t prescaler);
void hal_adc_set_mux(adc_channel_t channel);
void hal_adc_start_conversion(void);
uint8_t hal_adc_read(void);
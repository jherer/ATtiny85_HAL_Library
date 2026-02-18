#pragma once
#include <hal/adc_enums.h>
#include <stdint.h>
#include <stdbool.h>
#include <core/error_code.h>

#define ERROR_ADC_UNINIT        (ERROR_MODULE_ADC | 0x01)
#define ERROR_ADC_BAD_PRESCALER (ERROR_MODULE_ADC | 0x02)
#define ERROR_ADC_BAD_CHANNEL   (ERROR_MODULE_ADC | 0x03)

error_code_t adc_init(adc_prescaler_t prescaler);
error_code_t adc_set_prescaler(adc_prescaler_t prescaler);
error_code_t adc_set_channel(adc_channel_t channel);
uint8_t adc_read(void);
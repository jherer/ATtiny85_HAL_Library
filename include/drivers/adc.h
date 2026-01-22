#ifndef ADC_H
#define ADC_H
#include "hal_adc.h"
#include "error.h"

typedef enum {
    ADC_CHANNEL_0,
    ADC_CHANNEL_1,
    ADC_CHANNEL_2,
    ADC_CHANNEL_3,
    NUM_ADC_CHANNELS,
} adc_channel_t;

error_t adc_init(void);
error_t adc_read(adc_channel_t channel, uint8_t *value_ptr);

#endif
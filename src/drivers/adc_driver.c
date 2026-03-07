#include <drivers/adc_driver.h>
#include <platform/delay.h>
#include <hal/hal_adc.h>
#include <hal/hal_status.h>

static inline bool _adc_is_prescaler_valid(adc_prescaler_t prescaler) {
    return (unsigned)prescaler < ADC_NUM_PRESCALERS;
}

static inline bool _adc_is_channel_valid(adc_channel_t channel) {
    return (unsigned)channel < ADC_NUM_CHANNELS;
}

typedef struct {
    bool initialized;
    volatile uint8_t latest_reading;
} adc_state_t;

static adc_state_t state = {0};

error_code_t adc_init(adc_prescaler_t prescaler) {
    hal_adc_set_control_status_register(true, true, prescaler);
    state.initialized = true;
    return ERROR_OK;
}

error_code_t adc_set_prescaler(adc_prescaler_t prescaler) {
    if (!state.initialized) {
        return ERROR_ADC_UNINIT;
    }
    if (!_adc_is_prescaler_valid(prescaler)) {
        return ERROR_ADC_BAD_PRESCALER;
    }
    hal_adc_set_control_status_register(true, true, prescaler);
    return ERROR_OK;
}

error_code_t adc_set_channel(adc_channel_t channel) {
    if (!state.initialized) {
        return ERROR_ADC_UNINIT;
    }
    if (!_adc_is_channel_valid(channel)) {
        return ERROR_ADC_BAD_CHANNEL;
    }
    hal_adc_set_mux(channel);
    return ERROR_OK;
}

error_code_t adc_start_conversion(void) {
    if (!state.initialized) {
        return ERROR_ADC_UNINIT;
    }
    hal_adc_start_conversion();
    return ERROR_OK;
}

uint8_t adc_read_latest(void) {
    return state.latest_reading;
}

void adc_fire_conversion_interrupt(void) {
    state.latest_reading = hal_adc_read();
}
#include <drivers/pcint_driver.h>
#include <hal/hal_pcint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <platform/debug.h>

typedef struct {
    bool initialized;
    pcint_callback_t callback;
} pcint_state_t;

static pcint_state_t state = {0};


error_code_t pcint_init() {
    DEBUG_PRINTLN("PCINT init", DEBUG_LAYER_DRIVERS);
    hal_pcint_disable_pin(0);
    hal_pcint_disable_pin(1);
    hal_pcint_disable_pin(2);
    hal_pcint_disable_pin(3);
    hal_pcint_disable_pin(4);
    hal_pcint_enable_interrupts();
    state.callback = NULL;
    state.initialized = true;
    return ERROR_OK;
}

error_code_t pcint_cleanup() {
    DEBUG_PRINTLN("PCINT cleanup", DEBUG_LAYER_DRIVERS);
    hal_pcint_disable_interrupts();
    hal_pcint_disable_pin(0);
    hal_pcint_disable_pin(1);
    hal_pcint_disable_pin(2);
    hal_pcint_disable_pin(3);
    hal_pcint_disable_pin(4);
    state.initialized = false;
    return ERROR_OK;
}

error_code_t pcint_enable_interrupts() {
    DEBUG_PRINTLN("PCINT enable interrupt", DEBUG_LAYER_DRIVERS);
    if (!state.initialized) {
        return ERROR_PCINT_UNINIT;
    }
    hal_pcint_enable_interrupts();
    return ERROR_OK;
}

error_code_t pcint_disable_interrupts() {
    DEBUG_PRINTLN("PCINT disable interrupt", DEBUG_LAYER_DRIVERS);
    if (!state.initialized) {
        return ERROR_PCINT_UNINIT;
    }
    hal_pcint_disable_interrupts();
    return ERROR_OK;
}


error_code_t pcint_enable_pin(gpio_id_t gpio_id) {
    DEBUG_PRINTLN_HEX("PCINT enable pin", gpio_id, DEBUG_LAYER_DRIVERS);
    if (!state.initialized) {
        return ERROR_PCINT_UNINIT;
    }
    switch (gpio_id) {
        case GPIO_B0:
            hal_pcint_enable_pin(0);
        break;
        case GPIO_B1:
            hal_pcint_enable_pin(1);
        break;
        case GPIO_B2:
            hal_pcint_enable_pin(2);
        break;
        case GPIO_B3:
            hal_pcint_enable_pin(3);
        break;
        case GPIO_B4:
            hal_pcint_enable_pin(4);
        break;
        default:
            return ERROR_PCINT_BAD_PIN;
    }
    return ERROR_OK;
}

error_code_t pcint_disable_pin(gpio_id_t gpio_id) {
    DEBUG_PRINTLN_HEX("PCINT disable pin", gpio_id, DEBUG_LAYER_DRIVERS);
    if (!state.initialized) {
        return ERROR_PCINT_UNINIT;
    }
    switch (gpio_id) {
        case GPIO_B0:
            hal_pcint_disable_pin(0);
        break;
        case GPIO_B1:
            hal_pcint_disable_pin(1);
        break;
        case GPIO_B2:
            hal_pcint_disable_pin(2);
        break;
        case GPIO_B3:
            hal_pcint_disable_pin(3);
        break;
        case GPIO_B4:
            hal_pcint_disable_pin(4);
        break;
        default:
            return ERROR_PCINT_BAD_PIN;
    }
    return ERROR_OK;
}


error_code_t pcint_set_callback(pcint_callback_t callback) {
    DEBUG_PRINTLN("PCINT set callback", DEBUG_LAYER_DRIVERS);
    if (!state.initialized) {
        return ERROR_PCINT_UNINIT;
    }
    state.callback = callback;
    return ERROR_OK;
}

void pcint_fire_isr() {
    DEBUG_PRINTLN("PCINT isr fire", DEBUG_LAYER_DRIVERS);
    if (state.callback != NULL) {
        state.callback();
    }
}

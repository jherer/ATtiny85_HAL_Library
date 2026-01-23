#include "drivers/timer0.h"
#include "drivers/timer_common.h"
#include "hal_timer0.h"
#include <avr/io.h>
#include <stdlib.h>
#include "drivers/error.h"


typedef struct {
    bool initialized;
    timer0_mode_t mode;
    timer0_clock_t clock;
    timer_callback_t compa_callback;
    timer_callback_t compb_callback;
    timer_callback_t ovf_callback;
} timer0_state_t;

static timer0_state_t state;


static uint8_t _build_tccr0a_reg(uint8_t wgm0_bits, uint8_t com0a_bits, uint8_t com0b_bits) {
    return wgm0_bits | (com0a_bits << COM0A0) | (com0b_bits << COM0B0);
}

static uint8_t _build_tccr0b_reg(uint8_t wgm0_bits, uint8_t cs0_bits) {
    uint8_t wgm02 = 0;
    if ((wgm0_bits & (1 << 2)) != 0) {
        wgm02 = 1;
    }
    return cs0_bits | (wgm02 << WGM02);
}

error_t timer0_config(timer0_mode_t mode, timer0_clock_t clock) {
    uint8_t wgm0_bits = 0;
    uint8_t cs0_bits = 0;
    uint8_t com0a_bits = 0;
    uint8_t com0b_bits = 0;
    
    switch (mode) {
    case TIMER0_MODE_NORMAL:
        break;
    case TIMER0_MODE_CTC:
        wgm0_bits = 0b010;
        break;
    case TIMER0_MODE_PWM_FIXED_A:
        wgm0_bits = 0b011;
        com0a_bits = 0b10;
        break;
    case TIMER0_MODE_PWM_FIXED_B:
        wgm0_bits = 0b011;
        com0b_bits = 0b10;
        break;
    case TIMER0_MODE_PWM_FIXED_AB:
        wgm0_bits = 0b011;
        com0a_bits = 0b10;
        com0b_bits = 0b10;
        break;
    case TIMER0_MODE_PWM_VARIABLE_A:
        wgm0_bits = 0b111;
        com0a_bits = 0b10;
        break;
    case TIMER0_MODE_PWM_VARIABLE_B:
        wgm0_bits = 0b111;
        com0b_bits = 0b10;
        break;
    case TIMER0_MODE_PWM_VARIABLE_AB:
        wgm0_bits = 0b111;
        com0a_bits = 0b10;
        com0b_bits = 0b10;
        break;
    default:
        return ERROR_TIMER_MODE_UNSUPPORTED;
    }

    switch (clock) {
    case TIMER0_CLOCK_OFF:
        cs0_bits = 0;
        break;
    case TIMER0_CLOCK_1:
        cs0_bits = 0b001;
        break;
    case TIMER0_CLOCK_8:
        cs0_bits = 0b010;
        break;
    case TIMER0_CLOCK_64:
        cs0_bits = 0b011;
        break;
    case TIMER0_CLOCK_256:
        cs0_bits = 0b100;
        break;
    case TIMER0_CLOCK_1024:
        cs0_bits = 0b101;
        break;
    default:
        return ERROR_TIMER_CLOCK_UNSUPPORTED;
    }

    uint8_t tccr0a_bits = _build_tccr0a_reg(wgm0_bits, com0a_bits, com0b_bits);
    uint8_t tccr0b_bits = _build_tccr0b_reg(wgm0_bits, cs0_bits);
    hal_timer0_config(tccr0a_bits, tccr0b_bits);
    return ERROR_OK;
}

error_t timer0_set_callback(timer_event_t event, timer_callback_t callback) {
    switch (event) {
    case TIMER_EVENT_COMPA:
        state.compa_callback = callback;
        break;
    case TIMER_EVENT_COMPB:
        state.compb_callback = callback;
        break;
    case TIMER_EVENT_OVERFLOW:
        state.ovf_callback = callback;
        break;
    default:
        return ERROR_TIMER_EVENT_UNSUPPORTED;
    }
    return ERROR_OK;
}


error_t timer0_enable_interrupt(timer_event_t event, bool enable) {
  switch (event) {
    case TIMER_EVENT_COMPA:
        hal_timer0_enable_interrupt_compa(enable);
        break;
    case TIMER_EVENT_COMPB:
        hal_timer0_enable_interrupt_compb(enable);
        break;
    case TIMER_EVENT_OVERFLOW:
        if (state.mode == TIMER0_MODE_CTC) {
            return ERROR_TIMER_MODE_OVF_INVALID;
        }
        hal_timer0_enable_interrupt_ovf(true);
        break;
    default:
        break;
    }  
}


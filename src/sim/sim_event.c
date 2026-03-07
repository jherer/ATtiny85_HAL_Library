
#include <sim/sim_event.h>
#include <platform/debug.h>
#include <sim/sim_io.h>
#include <hal/gpio_ids.h>
#include <drivers/adc_driver.h>

void sim_event_set_gpio_input(gpio_id_t gpio_id, bool state) {
    DEBUG_PRINTLN_HEX("Sim event gpio", (uint16_t)gpio_id, DEBUG_LAYER_SIM);
    if (state) {
        switch (gpio_id) {
        case GPIO_B0:
            sim_io_state.PINB_SIM |= (1 << 0);
            break;
        case GPIO_B1:
            sim_io_state.PINB_SIM |= (1 << 1);
            break;
        case GPIO_B2:
            sim_io_state.PINB_SIM |= (1 << 2);
            break;
        case GPIO_B3:
            sim_io_state.PINB_SIM |= (1 << 3);
            break;
        case GPIO_B4:
            sim_io_state.PINB_SIM |= (1 << 4);
            break;
        default:
            break;
        }
        DEBUG_PRINTLN("\tInput high", DEBUG_LAYER_SIM);
    } else {
        switch (gpio_id) {
        case GPIO_B0:
            sim_io_state.PINB_SIM &= ~(1 << 0);
            break;
        case GPIO_B1:
            sim_io_state.PINB_SIM &= ~(1 << 1);
            break;
        case GPIO_B2:
            sim_io_state.PINB_SIM &= ~(1 << 2);
            break;
        case GPIO_B3:
            sim_io_state.PINB_SIM &= ~(1 << 3);
            break;
        case GPIO_B4:
            sim_io_state.PINB_SIM &= ~(1 << 4);
            break;
        default:
            break;
        }
        DEBUG_PRINTLN("\tInput low", DEBUG_LAYER_SIM);
    }
}

void sim_event_set_adc_input(adc_channel_t adc_channel, uint8_t value) {
    /*switch (adc_channel) {
    case ADC_CHANNEL_0:
        ADCH = 
        break;
    case ADC_CHANNEL_1:
        ADCH = 
        break;
    case ADC_CHANNEL_2:
        ADCH = 
        break;
    case ADC_CHANNEL_3:
        ADCH = 
        break;
    
    default:
        break;
    }*/
}

void sim_event_timer0_increment(uint8_t count) {

}

void sim_event_timer1_increment(uint8_t count) {

}
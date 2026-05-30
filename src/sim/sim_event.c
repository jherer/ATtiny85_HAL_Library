

#include <drivers/adc_driver.h>
#include <drivers/pcint_driver.h>
#include <drivers/spi_peripheral_driver.h>
#include <hal/gpio_ids.h>
#include <platform/debug.h>
#include <sim/sim_event.h>
#include <sim/sim_io.h>

void sim_event_set_gpio_input(gpio_id_t gpio_id, bool state) {
    DEBUG_PRINTLN("GPIO input", DEBUG_LAYER_SIM);
    DEBUG_PRINTLN_HEX("    pin", (uint16_t)gpio_id, DEBUG_LAYER_SIM);
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
        DEBUG_PRINTLN("    state: high", DEBUG_LAYER_SIM);
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
        DEBUG_PRINTLN("    state: low", DEBUG_LAYER_SIM);
    }
}

void sim_event_set_adc_input(adc_channel_t adc_channel, uint8_t value) {
    DEBUG_PRINTLN("ADC set input: NOT IMPL", DEBUG_LAYER_SIM);
    DEBUG_PRINTLN_HEX("    channel", (uint16_t)adc_channel, DEBUG_LAYER_SIM);
    DEBUG_PRINTLN_HEX("    value", (uint16_t)value, DEBUG_LAYER_SIM);
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
    DEBUG_PRINTLN_HEX("T0 increment: NOT IMPL", (uint16_t)count, DEBUG_LAYER_SIM);
}

void sim_event_timer1_increment(uint8_t count) {
    DEBUG_PRINTLN_HEX("T1 increment: NOT IMPL", (uint16_t)count, DEBUG_LAYER_SIM);
}

void sim_event_pcint_isr() {
    DEBUG_PRINTLN("PCINT ISR", DEBUG_LAYER_SIM);
    pcint_fire_isr();
}

void sim_event_spi_peripheral_isr(uint8_t rx) {
    DEBUG_PRINTLN("SPI periph ISR", DEBUG_LAYER_SIM);
    DEBUG_PRINTLN_HEX("    rx", rx, DEBUG_LAYER_SIM);
    sim_io_state.USIBR_SIM = rx;
    sim_io_state.USIDR_SIM = rx;
    spi_peripheral_fire_isr();
}
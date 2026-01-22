#include "drivers/error.h"
#include <util/delay.h>
#include "hal_gpio.h"

static gpio_id_t error_led_id = GPIO_ID_B4;

void error_led_init(gpio_id_t gpio_id) {
    error_led_id = gpio_id;
}


static void _error_gpio_init() {
    hal_gpio_write_ddr(error_led_id, 1);
    hal_gpio_write_port(error_led_id, 0);
}


void error_blink_once(uint8_t num_blinks) {
    _error_gpio_init();
    uint8_t count = num_blinks;
    for (int i = 0; i < count; i++) {
        hal_gpio_write_port(error_led_id, 1);
        _delay_ms(160);
        hal_gpio_write_port(error_led_id, 0);
        _delay_ms(160);
    }
}


void error_blink_forever(uint8_t num_blinks) {
    _error_gpio_init();
    uint8_t count = num_blinks;
    while (1) {
        for (int i = 0; i < count; i++) {
            hal_gpio_write_port(error_led_id, 1);
            _delay_ms(160);
            hal_gpio_write_port(error_led_id, 0);
            _delay_ms(160);
        }
        for (int i = 0; i < 100; i++) {
            _delay_ms(10);
        }
    }
}
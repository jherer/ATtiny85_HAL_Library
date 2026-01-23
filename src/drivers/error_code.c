#include "drivers/error_code.h"
#include "hal_gpio.h"
#include "hal_delay.h"

static GPIO_t error_led_id = GPIO_B4;

void error_led_init(GPIO_t gpio_id) {
    error_led_id = gpio_id;
}


#define LONG_MS 1150
#define SHORT_MS 500
#define SPACE_MS 150

static void _blink_setup(void) {
    hal_gpio_write_ddr(error_led_id, 1);
    hal_gpio_write_port(error_led_id, 0);
}

static uint8_t _get_module_count(uint8_t code) {
    return (code & 0x10) >> 4; // Get top nibble
}

static uint8_t _get_submodule_count(uint8_t code) {
    return (code & 0x01); // Get bottom nibble
}

static void _blink_subroutine(uint16_t count1, uint16_t count2) {
    for (int i = 0; i < count1; i++) {
        hal_gpio_write_port(error_led_id, 1);
        hal_delay_smart_ms(SPACE_MS);
        hal_gpio_write_port(error_led_id, 0);
        hal_delay_smart_ms(SPACE_MS);
    }
    hal_delay_smart_ms(SHORT_MS);

    for (int i = 0; i < count2; i++) {
        hal_gpio_write_port(error_led_id, 1);
        hal_delay_smart_ms(SPACE_MS);
        hal_gpio_write_port(error_led_id, 0);
        hal_delay_smart_ms(SPACE_MS);
    }
    hal_delay_smart_ms(LONG_MS);
}


void error_code_blink_forever(error_code_t code) {
    _blink_setup();
    uint8_t module_count = _get_module_count(code); // Which module has error
    uint8_t submodule_count = _get_submodule_count(code); // Which error within module
    while (1) {
        _blink_subroutine(module_count, submodule_count);
    }

}

void error_code_blink_once(error_code_t code) {
    _blink_setup();
    uint8_t module_count = _get_module_count(code); // Which module has error
    uint8_t submodule_count = _get_submodule_count(code); // Which error within module
    _blink_subroutine(module_count, submodule_count);
}
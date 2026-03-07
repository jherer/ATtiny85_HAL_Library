
#include <platform/debug.h>
#include <sim/sim_event.h>
#include <hal/gpio_ids.h>
#include <stdbool.h>

void process_start(char response);
void process_gpio_pin(char response);
void process_gpio_state(char response, gpio_id_t gpio_id);


void dialogue_run(void) {
    DEBUG_PRINT("ACTION: ", DEBUG_LAYER_SIM);
    process_start(DEBUG_QUERY_CHAR("STEP(ENTER)    DUMP(0)    GPIO(1)    ADC(2)    T0(3)    T1(4)", DEBUG_LAYER_SIM));
}

void process_start(char response) {
    switch (response) {
    case '0':
        DEBUG_PRINTLN("DUMP", DEBUG_LAYER_SIM);
        DEBUG_PRINTLN("NOT IMPLEMENTED", DEBUG_LAYER_SIM);
        break;
    case '1':
        process_gpio_pin(DEBUG_QUERY_CHAR("\tPB0(0)    PB1(1)    PB2(2)    PB3(3)    PB4(4)", DEBUG_LAYER_SIM));
        break;
    case '2':
        DEBUG_PRINTLN("ADC", DEBUG_LAYER_SIM);
        DEBUG_PRINTLN("NOT IMPLEMENTED", DEBUG_LAYER_SIM);
        break;
    case '3':
        DEBUG_PRINTLN("T0", DEBUG_LAYER_SIM);
        DEBUG_PRINTLN("NOT IMPLEMENTED", DEBUG_LAYER_SIM);
        break;
    case '4':
        DEBUG_PRINTLN("T1", DEBUG_LAYER_SIM);
        DEBUG_PRINTLN("NOT IMPLEMENTED", DEBUG_LAYER_SIM);
        break;
    default:
        return;
    }
}

void process_gpio_pin(char response) {
    gpio_id_t gpio_id;
    switch (response) {
    case '0':
        gpio_id = GPIO_B0;
        break;
    case '1':
        gpio_id = GPIO_B1;
        break;
    case '2':
        gpio_id = GPIO_B2;
        break;
    case '3':
        gpio_id = GPIO_B3;
        break;
    case '4':
        gpio_id = GPIO_B4;
        break;
    default:
        DEBUG_PRINT("INVALID RESPONSE", DEBUG_LAYER_SIM);
        return;
    }
    process_gpio_state(DEBUG_QUERY_CHAR("LOW(0)    HIGH(1)", DEBUG_LAYER_SIM), gpio_id);
}

void process_gpio_state(char response, gpio_id_t gpio_id) {
    switch (response) {
    case '0':
        sim_event_set_gpio_input(gpio_id, false);
        break;
    case '1':
        sim_event_set_gpio_input(gpio_id, true);
        break;
    }
}
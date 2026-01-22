#include "app/app.h"
#include "drivers/interrupts.h"
#include "services/button.h"

/* Add state variables in this struct */
typedef struct {
    gpio_t led0;
    gpio_t led1;
} app_state_t;

static app_state_t state = {0}; // Always zero initialize state by default

void toggle0() {
    gpio_toggle(&state.led0);
}


void press1() {
    gpio_write(&state.led1, 1);
}



void release1() {
    gpio_write(&state.led1, 0);
}


error_t app_init(void) {
    /* Configure drivers, services, and initial state here */
    VALIDATE_ERROR(gpio_create(&state.led0, GPIO_ID_B2, GPIO_MODE_OUTPUT));
    VALIDATE_ERROR(gpio_create(&state.led1, GPIO_ID_B3, GPIO_MODE_OUTPUT));
    VALIDATE_ERROR(button_service_init());
    
    VALIDATE_ERROR(button_create(0, GPIO_ID_B0, true));
    VALIDATE_ERROR(button_set_callback(0, BUTTON_EVENT_PRESS, toggle0));
    VALIDATE_ERROR(button_set_callback(0, BUTTON_EVENT_RELEASE, toggle0));

    VALIDATE_ERROR(button_create(1, GPIO_ID_B1, false));
    VALIDATE_ERROR(button_set_callback(1, BUTTON_EVENT_PRESS, press1));
    VALIDATE_ERROR(button_set_callback(1, BUTTON_EVENT_RELEASE, release1));
    interrupts_enable();
    return ERROR_OK;
}

error_t app_run(void) {

    /* Run the main loop of the program here */

    return ERROR_OK;
}
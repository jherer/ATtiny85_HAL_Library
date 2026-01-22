#include "app/app.h"
#include "drivers/interrupts.h"
#include "drivers/gpio.h"
#include "drivers/pwm.h"
#include "services/button.h"

/* Add state variables in this struct */
typedef struct {
    uint8_t btn_state;
    bool last_timer_on;
} app_state_t;

static app_state_t state = {0}; // Always zero initialize state by default

error_t app_init(void) {
    /* Configure drivers, services, and initial state here */
    VALIDATE_ERROR(button_service_init());
    VALIDATE_ERROR(button_create(0, GPIO_ID_B0, true));
    VALIDATE_ERROR(button_create(1, GPIO_ID_B1, true));
    VALIDATE_ERROR(button_create(2, GPIO_ID_B2, true));
    VALIDATE_ERROR(timer_init(TIMER_ID_0, TIMER_MODE_CTC));
    
    interrupts_enable();
    return ERROR_OK;
}

void set_freq(uint8_t freq) {
    uint8_t top = (F_CPU / (256 * freq)) - 1;
    timer_set_top(TIMER_ID_0, top);
}

uint16_t get_freq_from_buttons(uint8_t btn_state) {
    switch (btn_state) {
    case 0: return 0;
    case 1: return 880;
    case 2: return 988;
    case 3: return 1109;
    case 4: return 1175;
    case 5: return 1319;
    case 6: return 1480;
    case 7: return 1760;
    default: return 0;
    }
}

error_t app_run(void) {
    /* Run the main loop of the program here */
    state.btn_state = (btn_read(0) << 2) | (btn_read(1) << 1) | (btn_read(0) << 0);
    uint16_t freq = get_freq_from_buttons(state.btn_state);

    bool timer_on = true;
    if (freq == 0) {
        timer_on = false;
    }

    if (!state.last_timer_on && timer_on) {
        VALIDATE_ERROR(timer_start(TIMER_ID_0, TIMER_CLOCK_1024));
    }
    if (!timer_on) {
        VALIDATE_ERROR(timer_stop(TIMER_ID_0));
    }


    state.last_timer_on = timer_on;
    return ERROR_OK;
}
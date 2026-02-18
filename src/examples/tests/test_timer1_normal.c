#include <app/app.h>
#include <drivers/timer1_driver.h>
#include <drivers/gpio_driver.h>
#include <platform/debug.h>

typedef struct {
    gpio_t led0;
    gpio_t btn0;
    uint8_t clock_stage;
    bool last_btn;
    bool s;
} app_state_t;

static app_state_t state = {0};

void callback0(void) {
    gpio_toggle(&state.led0);
}

static timer1_clock_t get_clock(uint8_t stage) {
    switch (stage) {
    case 0: return TIMER1_CLOCK_OFF;
    case 1: return TIMER1_CLOCK_1;
    case 2: return TIMER1_CLOCK_2;
    case 3: return TIMER1_CLOCK_4;
    case 4: return TIMER1_CLOCK_8;
    case 5: return TIMER1_CLOCK_16;
    case 6: return TIMER1_CLOCK_32;
    case 7: return TIMER1_CLOCK_64;
    case 8: return TIMER1_CLOCK_128;
    case 9:
        return TIMER1_CLOCK_256;
    case 10:
        return TIMER1_CLOCK_512;
    case 11:
        return TIMER1_CLOCK_1024;
    case 12:
        return TIMER1_CLOCK_2048;
    case 13:
        return TIMER1_CLOCK_4096;
    case 14:
        return TIMER1_CLOCK_8192;
    case 15:
        return TIMER1_CLOCK_16384;
    default:
        return TIMER1_CLOCK_INVALID;
    }
}



error_code_t app_init(void) {
    DEBUG_PRINTLN("Timer1 normal test", DEBUG_LAYER_APP);
    ASSERT_OK(gpio_create(&state.led0, GPIO_B0, GPIO_MODE_OUTPUT));
    ASSERT_OK(gpio_create(&state.btn0, GPIO_B1, GPIO_MODE_INPUT_PULLUP));
    ASSERT_OK(timer1_init(TIMER1_MODE_NORMAL));
    ASSERT_OK(timer1_set_callback(TIMER1_EVENT_OVERFLOW, callback0));
    ASSERT_OK(timer1_enable_callback(TIMER1_EVENT_OVERFLOW, true));

    interrupt_enable();
    return ERROR_OK;
}

error_code_t app_run(void) {
    bool curr_btn = gpio_read(&state.btn0);
    if (state.last_btn && !curr_btn) {
        //return 0x65;
        timer0_clock_t clock = get_clock(state.clock_stage);
        ASSERT_OK(timer0_start_clock(clock));
        if (clock == TIMER1_CLOCK_OFF) {
            gpio_write(&state.led0, 0);
        }

        state.clock_stage++;
        if (state.clock_stage >= TIMER0_NUM_CLOCKS) {
            state.clock_stage = 0;
        }
    }
    state.last_btn = curr_btn;

    return ERROR_OK;
}
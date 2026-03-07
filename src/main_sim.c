// #define F_CPU 16000000UL

#include <app/app.h>
#include <drivers/gpio_driver.h>
#include <drivers/timer0_driver.h>
#include <drivers/timer1_driver.h>
#include <sim/sim_timer0.h>
#include <platform/io.h>
#include <platform/debug.h>
#include <sim/sim_dialogue.h>

void process_input(char c);

void _print_columns() {
    DEBUG_PRINTLN("SIM\t\t\tAPP\t\t\tSERVICES\t\tDRIVERS\t\t\tHAL", DEBUG_LAYER_SIM);
    DEBUG_PRINTLN("---\t\t\t---\t\t\t--------\t\t-------\t\t\t---", DEBUG_LAYER_SIM);
}

int main(void) {
    uint64_t microseconds = 0;
    _debug_init();
    DEBUG_PRINTLN_TITLE("ATtiny85 Simulator", 55, DEBUG_LAYER_SIM);
    DEBUG_PAUSE("Press ENTER to init", DEBUG_LAYER_SIM);
    DEBUG_PRINTLN_TITLE("INIT", 45, DEBUG_LAYER_SIM);
    _print_columns();

    error_code_t init_err = app_init();
    if (init_err == ERROR_OK) {
        DEBUG_PRINTLN("Init success!", DEBUG_LAYER_SIM);
    } else {
        DEBUG_PRINTLN_HEX("INIT ERROR", init_err, DEBUG_LAYER_SIM);
    }

    DEBUG_PAUSE("Press ENTER to run", DEBUG_LAYER_SIM);
    DEBUG_PRINTLN_TITLE("RUN", 45, DEBUG_LAYER_SIM);
    uint32_t i = 0;
    while (1) {
        DEBUG_PRINTLN_DEC("Step", i++, DEBUG_LAYER_SIM);
        _print_columns();
        error_code_t run_err = app_run();

        if (run_err != ERROR_OK) {
            DEBUG_PRINTLN_HEX("RUN ERROR", run_err, DEBUG_LAYER_SIM);
        }
        
        dialogue_run();
        DEBUG_PRINTLN("", DEBUG_LAYER_SIM);
        DEBUG_PRINTLN("\n---------------\n", DEBUG_LAYER_SIM);
    }

    return 0;
}
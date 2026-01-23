//#define F_CPU 16000000UL

#include "app/app.h"
#include "drivers/error_code.h"
#include "drivers/gpio.h"
#include "sim/debug.h"

int main() {
    {
        debug_print("\n--------------- ATtiny85 SIMULATOR ---------------\n");
        debug_init();
        debug_pause("Press enter to init");
        debug_print("\n----- INIT -----\n");
        error_code_t init_err = app_init();

        if (init_err == ERROR_OK) {
            debug_print("Init success!");
        } else {
            debug_print_hex("INIT ERROR:", init_err);
        }
    }
    debug_delay_ms(500);

    debug_print("\n----- RUN -----\n");
    debug_pause("Press enter to step");
    uint32_t i = 0;
    while (1) {
        debug_print_dec("Step", i++);
        error_code_t run_err = app_run();
        
        if (run_err != ERROR_OK) {
            debug_print_hex("RUN ERROR:", run_err);
        }
        debug_pause(".");
        debug_print("");
    }

    return 0;
}
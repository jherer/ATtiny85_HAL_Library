#include "app/app.h"
#include "drivers/error_code.h"
#include "drivers/gpio.h"
#include "sim/debug.h"

#define DO_ERROR_BLINK

int main() {
    error_code_t init_err = app_init();

    #ifdef DO_ERROR_BLINK
        if (init_err != ERROR_OK) {
            error_code_blink_forever(init_err);
        }
    #endif

    while (1) {
        error_code_t run_err = app_run();
        
        #ifdef DO_ERROR_BLINK
            if (run_err != ERROR_OK) {
                error_code_blink_forever(run_err);
            }
        #endif
    }
    return 0;
}
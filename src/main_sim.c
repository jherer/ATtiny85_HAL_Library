//#define F_CPU 16000000UL

#include "app/app.h"
#include "drivers/gpio_driver.h"
#include "drivers/timer0_driver.h"
#include "drivers/timer1_driver.h"
#include "platform/debug.h"

static void _print_columns(void) {
    DEBUG_PRINTLN("APP\t\t\tSERVICES\t\tDRIVERS\t\t\tHAL", DEBUG_LAYER_MAIN);
    DEBUG_PRINTLN(  "---\t\t\t--------\t\t-------\t\t\t---", DEBUG_LAYER_MAIN);
}

int main(void) {
    {   
        debug_init();
        DEBUG_PRINTLN_TITLE("ATtiny85 Simulator", 55, DEBUG_LAYER_MAIN);
        debug_pause("Press ENTER to init", DEBUG_LAYER_MAIN);
        DEBUG_PRINTLN_TITLE("INIT", 45, DEBUG_LAYER_MAIN);
        _print_columns();

        error_code_t init_err = app_init();

        if (init_err == ERROR_OK) {
            DEBUG_PRINTLN("Init success!", DEBUG_LAYER_MAIN);
        } else {
            DEBUG_PRINTLN_HEX("INIT ERROR", init_err, DEBUG_LAYER_MAIN);
        }
    }
    debug_delay_ms(500);

    DEBUG_PRINTLN_TITLE("RUN", 45, DEBUG_LAYER_MAIN);
    debug_pause("Press ENTER to step", DEBUG_LAYER_MAIN);
    uint32_t i = 0;
    while (1) {
        DEBUG_PRINTLN_DEC("Step", i++, DEBUG_LAYER_MAIN);
        _print_columns();
        error_code_t run_err = app_run();
        
        if (run_err != ERROR_OK) {
            DEBUG_PRINTLN_HEX("RUN ERROR", run_err, DEBUG_LAYER_MAIN);
        }

        char timer_char = DEBUG_QUERY_CHAR("Next step (ENTER)    T0 ISR (0)    T1 ISR (1)", DEBUG_LAYER_MAIN);
        bool use_t0 = timer_char == '0';
        bool use_t1 = timer_char == '1';

        while (use_t0 || use_t1) {
            char isr_char = DEBUG_QUERY_CHAR("COMPA (a)    COMPB (b)    OVF (o)", DEBUG_LAYER_MAIN);
            bool isr_compa = isr_char == 'a';
            bool isr_compb = isr_char == 'b';
            bool isr_ovf = isr_char == 'o';

            if (use_t0) {
                if (isr_compa) {
                    DEBUG_PRINTLN("Timer0 ISR COMPA Fired", DEBUG_LAYER_MAIN);
                    timer0_fire_isr_compa(); break;
                } else if (isr_compb) {
                    DEBUG_PRINTLN("Timer0 ISR COMPB Fired", DEBUG_LAYER_MAIN);
                    timer0_fire_isr_compb(); break;
                } else if (isr_ovf) {
                    DEBUG_PRINTLN("Timer0 ISR OVF Fired", DEBUG_LAYER_MAIN);
                    timer0_fire_isr_ovf(); break;
                } else {
                    DEBUG_PRINTLN("Invalid entry", DEBUG_LAYER_MAIN); break;
                }
            } else if (use_t1) {
                if (isr_compa) {
                    DEBUG_PRINTLN("Timer1 ISR COMPA Fired", DEBUG_LAYER_MAIN);
                    timer1_fire_isr_compa(); break;
                } else if (isr_compb) {
                    DEBUG_PRINTLN("Timer1 ISR COMPB Fired", DEBUG_LAYER_MAIN);
                    timer1_fire_isr_compb(); break;
                } else if (isr_ovf) {
                    DEBUG_PRINTLN("Timer1 ISR OVF Fired", DEBUG_LAYER_MAIN);
                    timer1_fire_isr_ovf(); break;
                } else {
                    DEBUG_PRINTLN("Invalid entry", DEBUG_LAYER_MAIN); break;
                }
            }
        }
        DEBUG_PRINTLN("\n---------------\n", DEBUG_LAYER_MAIN);
    }

    return 0;
}
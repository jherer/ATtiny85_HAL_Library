
#include <platform/debug.h>
#include <sim/sim_event.h>
#include <hal/gpio_ids.h>
#include <stdbool.h>

bool process_start(sim_io_state_t *sim_io, char response);
bool process_gpio_pin(char response);
bool process_gpio_state(char response, gpio_id_t gpio_id);
void dump(sim_io_state_t *sim);

void dialogue_run(sim_io_state_t *sim_io) {
    bool repeat = true;
    while (repeat) {
        DEBUG_PRINTLN("", DEBUG_LAYER_SIM);
        DEBUG_PRINT("ACTION: ", DEBUG_LAYER_SIM);
        repeat = process_start(sim_io, DEBUG_QUERY_CHAR("STEP(ENTER)    DUMP(0)    GPIO(1)    ADC(2)    T0(3)    T1(4)", DEBUG_LAYER_SIM));
    }
}


bool process_start(sim_io_state_t *sim_io, char response) {
    switch (response) {
    case '0':
        //DEBUG_PRINTLN("DUMP", DEBUG_LAYER_SIM);
        //DEBUG_PRINTLN("NOT IMPLEMENTED", DEBUG_LAYER_SIM);
        dump(sim_io);
        return true;
    case '1':
        return process_gpio_pin(DEBUG_QUERY_CHAR("\tPB0(0)    PB1(1)    PB2(2)    PB3(3)    PB4(4)", DEBUG_LAYER_SIM));
        break;
    case '2':
        DEBUG_PRINTLN("ADC", DEBUG_LAYER_SIM);
        DEBUG_PRINTLN("NOT IMPLEMENTED", DEBUG_LAYER_SIM);
        return true;
    case '3':
        DEBUG_PRINTLN("T0", DEBUG_LAYER_SIM);
        DEBUG_PRINTLN("NOT IMPLEMENTED", DEBUG_LAYER_SIM);
        return true;
    case '4':
        DEBUG_PRINTLN("T1", DEBUG_LAYER_SIM);
        DEBUG_PRINTLN("NOT IMPLEMENTED", DEBUG_LAYER_SIM);
        return true;
    default:
        return false;
    }
}

bool process_gpio_pin(char response) {
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
        return true;
    }
    process_gpio_state(DEBUG_QUERY_CHAR("LOW(0)    HIGH(1)", DEBUG_LAYER_SIM), gpio_id);
    return true;
}

bool process_gpio_state(char response, gpio_id_t gpio_id) {
    switch (response) {
    case '0':
        sim_event_set_gpio_input(gpio_id, false);
        break;
    case '1':
        sim_event_set_gpio_input(gpio_id, true);
        break;
    }
    return true;
}


void dump(sim_io_state_t *sim_io) {
    DEBUG_PRINTLN("REGISTER DUMP", DEBUG_LAYER_SIM);
    
    DEBUG_PRINTLN("--GPIO--", DEBUG_LAYER_SIM);
    DEBUG_PRINTLN_BIN("    DDRB", sim_io->DDRB_SIM, DEBUG_LAYER_SIM);
    DEBUG_PRINTLN_BIN("    PORTB", sim_io->PORTB_SIM, DEBUG_LAYER_SIM);
    DEBUG_PRINTLN_BIN("    PINB", sim_io->PINB_SIM, DEBUG_LAYER_SIM);
    DEBUG_PRINTLN("--T0--", DEBUG_LAYER_SIM);
    DEBUG_PRINTLN_BIN("    TCCR0A", sim_io->TCCR0A_SIM, DEBUG_LAYER_SIM);
    DEBUG_PRINTLN_BIN("    TCCR0B", sim_io->TCCR0B_SIM, DEBUG_LAYER_SIM);
    DEBUG_PRINTLN_DEC("    TCNT0", sim_io->TCNT0_SIM, DEBUG_LAYER_SIM);
    DEBUG_PRINTLN_DEC("    OCR0A", sim_io->OCR0A_SIM, DEBUG_LAYER_SIM);
    DEBUG_PRINTLN_DEC("    OCR0B", sim_io->OCR0B_SIM, DEBUG_LAYER_SIM);
    DEBUG_PRINTLN("--T1--", DEBUG_LAYER_SIM);
    DEBUG_PRINTLN_BIN("    TCCR1", sim_io->TCCR1_SIM, DEBUG_LAYER_SIM);
    DEBUG_PRINTLN_BIN("    GTCCR", sim_io->GTCCR_SIM, DEBUG_LAYER_SIM);
    DEBUG_PRINTLN_BIN("    PLLCSR", sim_io->PLLCSR_SIM, DEBUG_LAYER_SIM);
    DEBUG_PRINTLN_DEC("    TCNT1", sim_io->TCNT1_SIM, DEBUG_LAYER_SIM);
    DEBUG_PRINTLN_DEC("    OCR1A", sim_io->OCR1A_SIM, DEBUG_LAYER_SIM);
    DEBUG_PRINTLN_DEC("    OCR1B", sim_io->OCR1B_SIM, DEBUG_LAYER_SIM);
    DEBUG_PRINTLN_DEC("    OCR1C", sim_io->OCR1C_SIM, DEBUG_LAYER_SIM);
    DEBUG_PRINTLN("--INTERRUPT--", DEBUG_LAYER_SIM);
    DEBUG_PRINTLN_BIN("    TIMSK", sim_io->TIMSK_SIM, DEBUG_LAYER_SIM);
    DEBUG_PRINTLN_BIN("    SREG", sim_io->SREG_SIM, DEBUG_LAYER_SIM);
    DEBUG_PRINTLN("--ADC--", DEBUG_LAYER_SIM);
    DEBUG_PRINTLN_BIN("    ADMUX", sim_io->ADMUX_SIM, DEBUG_LAYER_SIM);
    DEBUG_PRINTLN_BIN("    ADCSRA", sim_io->ADCSRA_SIM, DEBUG_LAYER_SIM);
    DEBUG_PRINTLN_BIN("    ADCH", sim_io->ADCH_SIM, DEBUG_LAYER_SIM);

}
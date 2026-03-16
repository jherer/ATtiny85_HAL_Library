#ifdef HW
#include <avr/io.h>
#include <avr/interrupt.h>
#include <drivers/pcint_driver.h>
ISR(PCINT0_vect) {
    pcint_fire_isr();
}
#endif
#ifdef HW
#include <avr/io.h>
#include <avr/interrupt.h>
#include <drivers/adc_driver.h>

ISR(ADC_vect) {
    adc_fire_conversion_interrupt();
}

#endif

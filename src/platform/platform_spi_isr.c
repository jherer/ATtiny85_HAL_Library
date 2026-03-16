#ifdef HW
#include <avr/io.h>
#include <avr/interrupt.h>
#include <drivers/spi_peripheral_driver.h>
ISR(USI_OVF_vect) {
    spi_peripheral_fire_isr();
}
#endif
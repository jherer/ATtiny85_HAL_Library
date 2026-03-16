#include <platform/io.h>
#include <hal/gpio_ids.h>

void hal_pcint_enable_interrupts();
void hal_pcint_disable_interrupts();
void hal_pcint_enable_pin(uint8_t pin_num);
void hal_pcint_disable_pin(uint8_t pin_num);
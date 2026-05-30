#include <hal/gpio_ids.h>
#include <core/error_code.h>
typedef void (*pcint_callback_t)(void);

#define ERROR_PCINT_UNINIT (ERROR_MODULE_PCINT | 0x1)
#define ERROR_PCINT_BAD_PIN (ERROR_MODULE_PCINT | 0x2)

error_code_t pcint_init();
error_code_t pcint_cleanup();
error_code_t pcint_enable_interrupts();
error_code_t pcint_disable_interrupts();
error_code_t pcint_enable_pin(gpio_id_t gpio_id);
error_code_t pcint_disable_pin(gpio_id_t gpio_id);
error_code_t pcint_set_callback(pcint_callback_t callback);
void pcint_fire_isr(void);
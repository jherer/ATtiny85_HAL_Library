#pragma once
#include <stdint.h>

uint8_t hal_status_get_sreg(void);
void hal_status_set_sreg(uint8_t new_sreg);
void hal_status_interrupt_enable(void);
void hal_status_interrupt_disable(void);
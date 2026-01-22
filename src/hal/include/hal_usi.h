#ifndef HAL_USI_H
#define HAL_USI_H
#include <stdint.h>
#include <stdbool.h>

void hal_usi_set_wire_mode(uint8_t wm_bits);
void hal_usi_set_clock_source(uint8_t cs_bits);
void hal_usi_enable_interrupt_ovf(bool enable);
bool hal_usi_read_overflow_flag(void);
void hal_usi_clear_overflow_flag(void);
void hal_usi_write_data(uint8_t data);
uint8_t hal_usi_read_data(void);
void hal_usi_soft_strobe_clock(void);
#endif
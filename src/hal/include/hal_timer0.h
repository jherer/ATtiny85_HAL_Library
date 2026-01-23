/**
 * @file hal_timer0.h
 * @brief Header for Timer0 Hardware Abstraction Layer (HAL)
 * 
 * This module provides a direct interface to Timer0 configuration bits
 * 
 * @author Joshua Herer
 * @date January 17, 2026
 * @version 1.0
 */

#ifndef HAL_TIMER0_H
#define HAL_TIMER0_H
#include <stdint.h>
#include <stdbool.h>

// CONFIG
void hal_timer0_config(uint8_t tccr0a_bits, uint8_t tccr0b_bits);

// COUNTER
uint8_t hal_timer0_get_count(void);
void hal_timer0_set_count(uint8_t count);

// COMPARE REGISTER
void hal_timer0_set_output_compare_reg_a(uint8_t ocr0a_value);
void hal_timer0_set_output_compare_reg_b(uint8_t ocr0b_value);

// INTERRUPTS
void hal_timer0_enable_interrupt_compa(bool enable);
void hal_timer0_enable_interrupt_compb(bool enable);
void hal_timer0_enable_interrupt_ovf(bool enable);
#endif
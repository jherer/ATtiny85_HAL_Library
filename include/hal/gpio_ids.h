/**
 * @file gpio_ids.h
 * @brief Header for GPIO IDs
 * 
 * This module provides constants that each encode a particular GPIO pin.
 * Only the pins valid for the specified microcontroller are defined.
 * 
 * @author Joshua Herer
 * @date January 17, 2026
 * @version 1.0
 */

#pragma once
#include <stdint.h>

/*
    Each GPIO pin is encoded as a single 8-bit string to save space.
    - High nibble is port letter (A=0, B=1, etc)
    - Low nibble is pin number (0, 1, 2, etc)
    ATtiny85 only has PORTB, but additional ports are provided as a starting point for other microcontrollers
*/
typedef uint8_t GPIO_t;


#define GPIO_B0 0x10
#define GPIO_B1 0x11
#define GPIO_B2 0x12
#define GPIO_B3 0x13
#define GPIO_B4 0x14
//#define GPIO_B5 0x15
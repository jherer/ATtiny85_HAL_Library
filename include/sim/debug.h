#pragma once
#include <stdint.h>
#define DEBUG_PRINT_DELAY_MS 100
#define DEBUG_YIELD_LOOP_DELAY_MS 100

void debug_init(void);
void debug_print(char *message);
void debug_print_bin(char *message, uint8_t bin);
void debug_print_dec(char *message, uint8_t dec);
void debug_print_hex(char *message, uint8_t hex);
void debug_delay_ms(uint32_t ms);
void debug_yield_loop(void);
void debug_pause(char* message);
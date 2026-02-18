#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    HAL_USI_MODE_NONE = 0,
    HAL_USI_MODE_3_WIRE,
    HAL_USI_MODE_2_WIRE,
    HAL_USI_NUM_MODES,
} hal_usi_mode;

typedef enum {
    HAL_USI_CLOCK_NONE = 0,
    HAL_USI_CLOCK_SOFT_STROBE,
    HAL_USI_CLOCK_EXT_RISE_BOTH_EDGE,
    HAL_USI_CLOCK_EXT_FALL_BOTH_EDGE,
    HAL_USI_NUM_CLOCKS,
} hal_usi_clock;

void hal_usi_set_control_register(hal_usi_mode mode, hal_usi_clock clock);
uint8_t hal_usi_read_data(void);
void hal_usi_write_data(uint8_t data);
bool hal_usi_check_overflow(void);
void hal_usi_clear_overflow(void);

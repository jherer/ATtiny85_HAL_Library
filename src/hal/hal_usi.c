#include <hal/hal_usi.h>
#include <platform/io.h>
#include <stdbool.h>
#include "bitwise.h"
#include "masks.h"


uint8_t _build_usicr(uint8_t usiwm_bits, uint8_t usics_bits, bool usiclk_bit, bool usitc_bit) {
    return ((usiwm_bits << USIWM0) & MASK_USIWM) |
        ((usics_bits << USICS0) & MASK_USICS) |
        ((usiclk_bit << USICLK) & MASK_USICLK) |
        ((usitc_bit << USITC) & MASK_USITC);
}

uint8_t _get_usiwm_bits(hal_usi_mode mode) {
    switch (mode) {
    case HAL_USI_MODE_NONE: return 0b00;
    case HAL_USI_MODE_3_WIRE: return 0b01;
    case HAL_USI_MODE_2_WIRE: return 0b10;
    default: return 0b00;
    }
}

uint8_t _get_usics_bits(hal_usi_clock clock) {
    switch (clock) {
    case HAL_USI_CLOCK_SOFT_STROBE: return 0b00;
    case HAL_USI_CLOCK_EXT_RISE_BOTH_EDGE: return 0b10;
    case HAL_USI_CLOCK_EXT_FALL_BOTH_EDGE: return 0b11;
    default: return 0b00;
    }
}

bool _get_usiclk_bit(hal_usi_clock clock) {
    switch (clock) {
    case HAL_USI_CLOCK_SOFT_STROBE: return 1;
    case HAL_USI_CLOCK_EXT_RISE_BOTH_EDGE: return 0;
    case HAL_USI_CLOCK_EXT_FALL_BOTH_EDGE: return 0;
    default: return 0;
    }
}

bool _get_usitc_bit(hal_usi_clock clock) {
    switch (clock) {
    case HAL_USI_CLOCK_SOFT_STROBE: return 1;
    case HAL_USI_CLOCK_EXT_RISE_BOTH_EDGE: return 0;
    case HAL_USI_CLOCK_EXT_FALL_BOTH_EDGE: return 0;
    default: return 0;
    }
}

void hal_usi_set_control_register(hal_usi_mode mode, hal_usi_clock clock) {
    uint8_t usiwm_bits = _get_usiwm_bits(mode);
    uint8_t usics_bits = _get_usics_bits(clock);
    bool usiclk_bit = _get_usiclk_bit(clock);
    bool usitc_bit = _get_usitc_bit(clock);
    USICR = _build_usicr(usiwm_bits, usics_bits, usiclk_bit, usitc_bit);
}

void hal_usi_write_data(uint8_t data) {
    USIDR = data;
}

uint8_t hal_usi_read_data(void) {
    return USIBR;
}

bool hal_usi_check_overflow(void) {
    return bitwise_read_bit(USISR, USIOIF);
}

void hal_usi_clear_overflow(void) {
    bitwise_write_bit(&USISR, USIOIF, 1);
}
#include <drivers/spi_peripheral_driver.h>
#include <drivers/gpio_driver.h>
#include <stdlib.h>

#define DEFAULT_TX 0x59
#define DEFAULT_RX 0x35

typedef struct {
    volatile bool initialized;
    spi_sample_edge_t sample_edge;
    volatile spi_process_callback_t callback;
} spi_peripheral_state;

static error_code_t _set_usi_control_reg(spi_sample_edge_t sample_edge, bool enable_interrupt) {
    hal_usi_clock_t usi_clock = HAL_USI_CLOCK_NONE;
    switch (sample_edge) {
    case SPI_SAMPLE_EDGE_RISING:
        usi_clock = HAL_USI_CLOCK_EXT_RISE_BOTH_EDGE;
        break;
    case SPI_SAMPLE_EDGE_FALLING:
        usi_clock = HAL_USI_CLOCK_EXT_FALL_BOTH_EDGE;
        break;
    default:
        return ERROR_SPI_PERIPHERAL_BAD_EDGE;
    }
    hal_usi_set_control_register(HAL_USI_MODE_3_WIRE,
                                usi_clock,
                                enable_interrupt);
    return ERROR_OK;
}


static spi_peripheral_state state = {0};

error_code_t spi_peripheral_init(spi_sample_edge_t sample_edge) {
    state.sample_edge = sample_edge;

    error_code_t err =_set_usi_control_reg(state.sample_edge, false);
    if (err != ERROR_OK) return err;
    hal_usi_write_data(DEFAULT_TX);
    hal_usi_clear_overflow();
    state.initialized = true;
    return ERROR_OK;
}

error_code_t spi_peripheral_enable_interrupt(void) {
    if (!state.initialized) {
        return ERROR_SPI_PERIPHERAL_UNINIT;
    }
    return _set_usi_control_reg(state.sample_edge, true);
}

error_code_t spi_peripheral_disable_interrupt(void) {
    if (!state.initialized) {
        return ERROR_SPI_PERIPHERAL_UNINIT;
    }
    return _set_usi_control_reg(state.sample_edge, false);
}

error_code_t spi_peripheral_set_process_callback(spi_process_callback_t callback) {
    if (!state.initialized) {
        return ERROR_SPI_PERIPHERAL_UNINIT;
    }
    state.callback = callback;
    return ERROR_OK;
}

error_code_t spi_peripheral_clear(void) {
    if (!state.initialized) {
        return ERROR_SPI_PERIPHERAL_UNINIT;
    }
    hal_usi_clear_overflow();
    return ERROR_OK;
}

void spi_peripheral_fire_isr(void) {
    if (state.initialized) {
        uint8_t rx = hal_usi_read_data();
        uint8_t tx = DEFAULT_TX;
        if (state.callback != NULL) {
            tx = state.callback(rx);
        }
        hal_usi_write_data(tx);
        hal_usi_clear_overflow();
    }
}

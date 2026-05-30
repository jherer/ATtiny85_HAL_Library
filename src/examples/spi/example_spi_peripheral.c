
/**
 * @file app.c
 * @brief SPI peripheral implementation using USI peripheral
 *
 * Wiring (ATtiny85):
 *   PB0 - MOSI (DI)
 *   PB1 - MISO (DO)
 *   PB2 - USCK (SCK)
 *   PB3 - CS (active low, polled)
 *
 * SPI Mode 1 (CPOL=0, CPHA=1): sample on falling edge.
 * Counter clocked on both edges so it naturally overflows at 8 cycles.
 *
 * @author Joshua Herer
 * @date January 18, 2026
 */

#include <app/app.h>
#include <platform/debug.h>
#include <drivers/gpio_driver.h>
#include <drivers/spi_peripheral_driver.h>
#include <drivers/pcint_driver.h>

/* Response is always (received byte + 1). This is pre-loaded into USIDR
 * while CS is high so the master clocks out valid data from the first bit. */
#define SLAVE_IDLE_BYTE  0xca

typedef struct {
    gpio_t miso;
    gpio_t mosi;
    gpio_t clk;
    gpio_t cs;
    gpio_t debug;
    volatile bool spi_isr_enabled;
    volatile bool last_cs;
} app_state_t;

static app_state_t state = {.last_cs = true};


uint8_t process_spi(uint8_t rx) {
    //gpio_toggle(&state.debug);
    return rx + 1;
    gpio_toggle(&state.debug);
}

void cs_callback() {
    // Clear counter on falling edge of CS
    bool cs = gpio_read(&state.cs);
    if (!cs && state.last_cs) {
        // Falling edge
        if (!state.spi_isr_enabled) {
            spi_peripheral_enable_interrupt();
            state.spi_isr_enabled = true;
        }
        spi_peripheral_clear();
    }
    if (cs && !state.last_cs) {
        // Rising edge
        //spi_peripheral_disable_interrupt();
        spi_peripheral_clear();
    }
    state.last_cs = cs;
}

/* -------------------------------------------------------------------------
 * app_init
 * ------------------------------------------------------------------------- */
error_code_t app_init(void) {
    DEBUG_PRINTLN("SPI peripheral init", DEBUG_LAYER_APP);
    ASSERT_OK(gpio_create(&state.mosi, GPIO_B0, GPIO_MODE_INPUT));
    ASSERT_OK(gpio_create(&state.miso, GPIO_B1, GPIO_MODE_OUTPUT));
    ASSERT_OK(gpio_create(&state.clk,  GPIO_B2, GPIO_MODE_INPUT));
    ASSERT_OK(gpio_create(&state.cs, GPIO_B3, GPIO_MODE_INPUT));
    ASSERT_OK(gpio_create(&state.debug, GPIO_B4, GPIO_MODE_OUTPUT));
    ASSERT_OK(spi_peripheral_init(SPI_SAMPLE_EDGE_FALLING));
    ASSERT_OK(spi_peripheral_set_process_callback(process_spi));

    ASSERT_OK(pcint_init());
    ASSERT_OK(pcint_set_callback(cs_callback));
    ASSERT_OK(pcint_enable_pin(GPIO_B3));
    ASSERT_OK(pcint_enable());
    //ASSERT_OK(spi_peripheral_enable_interrupt());
    
    ASSERT_OK(gpio_write(&state.debug, 1));
    interrupt_enable();
    return ERROR_OK;
}


/* -------------------------------------------------------------------------
 * app_run  (called repeatedly from main loop)
 * ------------------------------------------------------------------------- */
error_code_t app_run(void) {
    //spi_peripheral_set_next_transmission(spi_peripheral_get_last_received() + 1);
    return ERROR_OK;
}
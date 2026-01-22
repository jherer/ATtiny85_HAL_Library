#include "drivers/spi.h"
#include <stdlib.h>
#include <avr/interrupt.h>
#include "hal_usi.h"
#include "drivers/gpio.h"

#define GPIO_ID_MOSI GPIO_ID_B0
#define GPIO_ID_MISO GPIO_ID_B1
#define GPIO_ID_SCK GPIO_ID_B2
#define GPIO_ID_CS GPIO_ID_B4 // Chip-select can be any pin


typedef struct {
    bool initialized;
    spi_clock_t clock;
    gpio_t mosi_pin;
    gpio_t miso_pin;
    gpio_t sck_pin;
    gpio_t cs_pin;

    uint8_t data_in;
    uint8_t data_out;
} spi_t;

static spi_t spi;

error_t spi_init(spi_clock_t clock) {
    switch (clock) {
    case SPI_CLOCK_SOFT_STROBE:
        gpio_create(&spi.mosi_pin, GPIO_ID_MOSI, GPIO_MODE_OUTPUT);
        gpio_create(&spi.miso_pin, GPIO_ID_MISO, GPIO_MODE_INPUT);
        gpio_create(&spi.sck_pin, GPIO_ID_SCK, GPIO_MODE_OUTPUT);
        gpio_create(&spi.cs_pin, GPIO_ID_CS, GPIO_MODE_OUTPUT);
        VALIDATE_ERROR(gpio_write(&spi.cs_pin, 1));
        hal_usi_set_clock_source(0b001);
        hal_usi_enable_interrupt_ovf(false);
        break;
    case SPI_CLOCK_EXTERNAL:
        gpio_create(&spi.mosi_pin, GPIO_ID_MOSI, GPIO_MODE_INPUT);
        gpio_create(&spi.miso_pin, GPIO_ID_MISO, GPIO_MODE_OUTPUT);
        gpio_create(&spi.sck_pin, GPIO_ID_SCK, GPIO_MODE_INPUT);
        gpio_create(&spi.cs_pin, GPIO_ID_CS, GPIO_MODE_INPUT_PULLUP);
        hal_usi_set_clock_source(0b110);
        hal_usi_enable_interrupt_ovf(true);
        break;
    case SPI_CLOCK_NONE:
    case NUM_SPI_CLOCKS:
        return ERROR_SPI_CLOCK_UNSUPPORTED;
    }
    spi.clock = clock;
    spi.initialized = true;
    return ERROR_OK;
}

error_t spi_peripheral_write(uint8_t data) {
    if (!spi.initialized) {
        return ERROR_SPI_UNINITIALIZED;
    }
    if (spi.clock == SPI_CLOCK_SOFT_STROBE) {
        return ERROR_SPI_CLOCK_WRONG_ROLE;
    }
    spi.data_out = data;
    return ERROR_OK;
}

uint8_t spi_peripheral_read() {
    if (!spi.initialized) {
        return 0;
    }
    if (spi.clock == SPI_CLOCK_SOFT_STROBE) {
        return 0;
    }
    return spi.data_in;
}

error_t spi_transfer(uint8_t tx, uint8_t *rx) {
    if (!spi.initialized) {
        return ERROR_SPI_UNINITIALIZED;
    }
    if (spi.clock == SPI_CLOCK_SOFT_STROBE) {
        return ERROR_SPI_CLOCK_WRONG_ROLE;
    }

    switch (spi.clock) {
    case SPI_CLOCK_SOFT_STROBE:
        VALIDATE_ERROR(gpio_write(&spi.cs_pin, 0));
        hal_usi_write_data(tx);
        hal_usi_clear_overflow_flag();
        while (!hal_usi_read_overflow_flag()) {
            hal_usi_soft_strobe_clock();
        }
        if (rx != NULL) {
            *rx = hal_usi_read_data();
        }
        VALIDATE_ERROR(gpio_write(&spi.cs_pin, 1));
        break;
    default:
        return ERROR_SPI_CLOCK_UNSUPPORTED;
    }
    return ERROR_OK;
}


ISR(USI_OVF_vect) {
    if (gpio_read(&spi.cs_pin) == 0) {
        hal_usi_write_data(spi.data_out);
        spi.data_in = hal_usi_read_data();
    }
}

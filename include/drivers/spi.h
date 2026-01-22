#ifndef SPI_H
#define SPI_H
#include <stdint.h>
#include "drivers/error.h"

typedef enum {
    SPI_CLOCK_NONE = 0,
    SPI_CLOCK_SOFT_STROBE,
    SPI_CLOCK_EXTERNAL,

    NUM_SPI_CLOCKS, //  Number of SPI clock sources
} spi_clock_t;

error_t spi_init(spi_clock_t clock);
error_t spi_transfer(uint8_t tx, uint8_t *rx);
error_t spi_write(uint8_t data);
uint8_t spi_read();
#endif
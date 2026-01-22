#include "app/app.h"
#include "drivers/interrupts.h"
#include "drivers/gpio.h"
#include "drivers/spi.h"

/* Add state variables in this struct */
typedef struct {
    uint8_t a;
} app_state_t;

static app_state_t state = {0}; // Always zero initialize state by default

error_t app_init(void) {
    /* Configure drivers, services, and initial state here */
    
    VALIDATE_ERROR(spi_init(SPI_CLOCK_SOFT_STROBE));

    interrupts_enable();
    return ERROR_OK;
}

error_t app_run(void) {
    /* Run the main loop of the program here */
    uint8_t rx = 0;
    spi_transfer(0b11010111, &rx);
    return ERROR_OK;
}
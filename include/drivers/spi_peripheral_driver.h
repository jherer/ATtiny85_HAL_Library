#include <hal/hal_usi.h>
#include <hal/gpio_ids.h>
#include <core/error_code.h>

#define ERROR_SPI_PERIPHERAL_UNINIT    (ERROR_MODULE_SPI_PERIPHERAL | 0x01)
#define ERROR_SPI_PERIPHERAL_BAD_EDGE  (ERROR_MODULE_SPI_PERIPHERAL | 0x02)

typedef uint8_t (*spi_process_callback_t)(uint8_t rx);

typedef enum {
    SPI_SAMPLE_EDGE_RISING = 0,
    SPI_SAMPLE_EDGE_FALLING = 1,
} spi_sample_edge_t;

error_code_t spi_peripheral_init(spi_sample_edge_t sample_edge);
error_code_t spi_peripheral_enable_interrupt(void);
error_code_t spi_peripheral_disable_interrupt(void);
error_code_t spi_peripheral_set_process_callback(spi_process_callback_t callback);
error_code_t spi_peripheral_set_next_transmission(uint8_t tx);
uint8_t spi_peripheral_get_last_received(void);
error_code_t spi_peripheral_clear(void);
void spi_peripheral_fire_isr(void);
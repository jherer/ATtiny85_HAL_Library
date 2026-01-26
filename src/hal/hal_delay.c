#include "hal_delay.h"
#include "platform.h"

void hal_delay_smart_ms(uint16_t ms) {
    #ifdef HAL_SIM
        _delay_ms(ms);
    #endif

    #ifndef HAL_SIM
        for (int i = 0; i < ms; i++) {
            _delay_ms(1);
        }
    #endif
}

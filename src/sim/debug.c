#include "sim/debug.h"

#ifdef HAL_SIM
    #include <stdio.h>
    #include <unistd.h>
#endif


void debug_init(void) {
    #ifdef HAL_SIM
        setbuf(stdout, NULL);
    #endif
}

void debug_delay_ms(uint32_t time_ms) {
    #ifdef HAL_SIM
        usleep(((uint64_t)time_ms) * 1000);
    #endif
}

void debug_print(char* message) {
    #ifdef HAL_SIM
        printf(message);
        printf("\n");
        debug_delay_ms(DEBUG_PRINT_DELAY_MS);
    #endif
}

void debug_print_bin(char* message, uint8_t bin) {
    #ifdef HAL_SIM
        printf(message);
        printf(" ");
        for (int i = 7; i >= 0; i--) {
            if (bin & (1 << i)) {
                printf("1");
            } else {
                printf("0");
            }
            if (i == 4) {
                printf(" ");
            }
        }
        printf("\n");
        debug_delay_ms(DEBUG_PRINT_DELAY_MS);
    #endif
}

void debug_print_dec(char* message, uint8_t dec) {
    #ifdef HAL_SIM
        printf(message);
        printf(" %d\n", dec);
        debug_delay_ms(DEBUG_PRINT_DELAY_MS);
    #endif
}

void debug_print_hex(char* message, uint8_t hex) {
    #ifdef HAL_SIM
        printf(message);
        printf(" x%02X\n", hex);
        debug_delay_ms(DEBUG_PRINT_DELAY_MS);
    #endif
}

void debug_yield_loop(void) {
    #ifdef HAL_SIM
        debug_delay_ms(DEBUG_YIELD_LOOP_DELAY_MS);
    #endif
}

void debug_pause(char* message) {
    #ifdef HAL_SIM
        printf(message);
        // Read and discard all characters until the newline character is found.
        while (getchar() != '\n');
    #endif
}

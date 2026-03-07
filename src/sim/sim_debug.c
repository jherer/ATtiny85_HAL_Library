#include <sim/sim_debug.h>
#include <stdbool.h>

#include <stdio.h>
#include <unistd.h>

#ifdef _WIN32
    #include <conio.h>
#endif

// Private helpers

static bool _keys_in_buffer(void) {
    #ifdef _WIN32
        return _kbhit();
    #endif
return false;
}

static void _clear_key_buffer(void) {
    #ifdef _WIN32
        _getch();
    #endif
}


static bool _check_layer_enabled(debug_layer_t layer) {
    switch (layer) {
    case DEBUG_LAYER_HAL:
        #ifdef ENABLE_DEBUG_LAYER_HAL
            return true;
        #endif
        break;
    case DEBUG_LAYER_DRIVERS:
        #ifdef ENABLE_DEBUG_LAYER_DRIVERS
            return true;
        #endif
        break;
    case DEBUG_LAYER_SERVICES:
        #ifdef ENABLE_DEBUG_LAYER_SERVICES
            return true;
        #endif
        break;
    case DEBUG_LAYER_APP:
        #ifdef ENABLE_DEBUG_LAYER_APP
            return true;
        #endif
        break;
    case DEBUG_LAYER_SIM:
        #ifdef ENABLE_DEBUG_LAYER_SIM
            return true;
        #endif
        break;
    case DEBUG_LAYER_SIM_ISR:
        #ifdef ENABLE_DEBUG_LAYER_SIM_ISR
            return true;
        #endif
        break;
    default:
        break;
    }
    return false;
}


static void _layer_indent(debug_layer_t layer) {
    switch (layer) {
    case DEBUG_LAYER_HAL:
        printf("\t\t\t\t\t\t\t\t\t\t\t\t");
        break;
    case DEBUG_LAYER_DRIVERS:
        printf("\t\t\t\t\t\t\t\t\t");
        break;
    case DEBUG_LAYER_SERVICES:
        printf("\t\t\t\t\t\t");
        break;
    case DEBUG_LAYER_APP:
        printf("\t\t\t");
    case DEBUG_LAYER_SIM:
    case DEBUG_LAYER_SIM_ISR:
    default:
        break;
    }
}


// PUBLIC API

void _debug_init(void) {
    setbuf(stdout, NULL);
}

void _debug_delay_ms(uint32_t time_ms) {
    #ifdef DEBUG_DELAY_ENABLED
        usleep(((uint64_t)time_ms) * 1000);
    #endif
}

void _debug_print(char* message, debug_layer_t layer, bool newline) {
    if (_check_layer_enabled(layer)) {
        _layer_indent(layer);
        printf(message);
        if (newline) {
            printf("\n");
        }
        _debug_delay_ms(DEBUG_PRINT_DELAY_MS);
    }
}

void _debug_print_bin(char* message, uint8_t bin, debug_layer_t layer, bool newline) {
    if (_check_layer_enabled(layer)) {
        _layer_indent(layer);
        printf(message);
        printf(": ");
        for (int i = 7; i >= 0; i--) {
            if (bin & (1 << i)) {
                printf("1");
            } else {
                printf("0");
            }
            if (i == 4) {
                printf("_");
            }
        }
        if (newline) {
            printf("\n");
        }
        _debug_delay_ms(DEBUG_PRINT_DELAY_MS);
    }
}

void _debug_print_dec(char* message, uint32_t dec, debug_layer_t layer, bool newline) {
    if (_check_layer_enabled(layer)) {
        _layer_indent(layer);
        printf(message);
        printf(": %d", dec);
        if (newline) {
            printf("\n");
        }
        _debug_delay_ms(DEBUG_PRINT_DELAY_MS);
    }
}

void _debug_print_hex(char* message, uint8_t hex, debug_layer_t layer, bool newline) {
    if (_check_layer_enabled(layer)) {
        _layer_indent(layer);
        printf(message);
        printf(": x%02X", hex);
        if (newline) {
            printf("\n");
        }
        _debug_delay_ms(DEBUG_PRINT_DELAY_MS);
    }
}

void _debug_print_title(char* message, uint8_t width, debug_layer_t layer, bool newline) {
    if (_check_layer_enabled(layer)) {
        printf("\n\n[");
        //printf(left);
        for (int i = 0; i < width; i++) {
            printf("=");
        }
        printf(" ");
        printf(message);
        printf(" ");
        
        for (int i = 0; i < width; i++) {
            printf("=");
        }
        printf("]");
        if (newline) {
            printf("\n");
        }
        _debug_delay_ms(DEBUG_PRINT_DELAY_MS);
    }
}

void _debug_pause(char* message, debug_layer_t layer) {
    if (_check_layer_enabled(layer)) {
        _layer_indent(layer);
        printf(message);
        // Read and discard all characters until the newline character is found.
        char c;
        while (1) {
            c = getchar();
            if (c == '\n' || c == '\r') {
                break;
            }
        }
        while (_keys_in_buffer()) {
            _clear_key_buffer();
        }
    }
}

char _debug_query_char(char* message, debug_layer_t layer) {
    if (_check_layer_enabled(layer)) {
        _layer_indent(layer);
        printf(message);
        printf(": ");
        // Read and discard all characters until the newline character is found.
        char c;
        c = getchar();
        while (_keys_in_buffer()) {
            _clear_key_buffer();
        }
        if (c != '\n' && c != '\r') {
            getchar();
        }
        return c;
    }
    return 0;
}


uint32_t _debug_query_int(char* message, debug_layer_t layer) {
    if (_check_layer_enabled(layer)) {
        _layer_indent(layer);
        printf(message);
        printf(": ");
        int num;
        scanf(" %d", &num);
        while (_keys_in_buffer()) {
            _clear_key_buffer();
        }
        getchar();
        return num;
    }
    return -1;
}

void debug_yield_loop(void) {
    _debug_delay_ms(DEBUG_YIELD_LOOP_DELAY_MS);
}
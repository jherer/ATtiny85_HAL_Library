#include <core/debug_layer.h>

#ifdef HW
    #define DEBUG_PRINT(msg, layer) do {} while (0)
    #define DEBUG_PRINT_DEC(msg, dec, layer) do {} while (0)
    #define DEBUG_PRINT_BIN(msg, bin, layer) do {} while (0)
    #define DEBUG_PRINT_HEX(msg, hex, layer) do {} while (0)

    #define DEBUG_PRINTLN(msg, layer) do {} while (0)
    #define DEBUG_PRINTLN_DEC(msg, dec, layer) do {} while (0)
    #define DEBUG_PRINTLN_BIN(msg, bin, layer) do {} while (0)
    #define DEBUG_PRINTLN_HEX(msg, hex, layer) do {} while (0)
    #define DEBUG_PRINTLN_TITLE(msg, width, layer) do {} while (0)

    #define DEBUG_DELAY_MS(time) do {} while (0)
    #define DEBUG_YIELD_LOOP() do {} while (0)
    #define DEBUG_PAUSE(msg, layer) do {} while (0)
    #define DEBUG_QUERY_CHAR(msg, layer) do {} while (0)
    #define DEBUG_QUERY_INT(msg, layer) do {} while (0)
#endif


#ifdef SIM
    #include <sim/sim_debug.h>
    #define DEBUG_PRINT(msg, layer) do {_debug_print(msg, layer, false);} while (0)
    #define DEBUG_PRINT_DEC(msg, dec, layer) do {_debug_print_dec(msg, dec, layer, false);} while (0)
    #define DEBUG_PRINT_BIN(msg, bin, layer) do {_debug_print_bin(msg, bin, layer, false);} while (0)
    #define DEBUG_PRINT_HEX(msg, hex, layer) do {_debug_print_hex(msg, hex, layer, false);} while (0)

    #define DEBUG_PRINTLN(msg, layer) do {_debug_print(msg, layer, true);} while (0)
    #define DEBUG_PRINTLN_DEC(msg, dec, layer) do {_debug_print_dec(msg, dec, layer, true);} while (0)
    #define DEBUG_PRINTLN_BIN(msg, bin, layer) do {_debug_print_bin(msg, bin, layer, true);} while (0)
    #define DEBUG_PRINTLN_HEX(msg, hex, layer) do {_debug_print_hex(msg, hex, layer, true);} while (0)
    #define DEBUG_PRINTLN_TITLE(msg, width, layer) do {_debug_print_title(msg, width, layer, true);} while (0)
    
    #define DEBUG_DELAY_MS(time_ms) do {_debug_delay_ms(time_ms);} while (0)
    #define DEBUG_YIELD_LOOP() do {} while (0)
    #define DEBUG_PAUSE(msg, layer) do {_debug_pause(msg, layer);} while (0)
    #define DEBUG_QUERY_CHAR(msg, layer) _debug_query_char(msg, layer)
    #define DEBUG_QUERY_INT(msg, layer) _debug_query_int(msg, layer)

#endif
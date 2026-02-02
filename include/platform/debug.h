#include "sim/sim_debug.h"

#ifdef HW
    #define DEBUG_PRINT(...) do {} while (0)
    #define DEBUG_PRINTLN(...) do {} while (0)
    #define DEBUG_PRINTLN_DEC(...) do {} while (0)
    #define DEBUG_PRINTLN_BIN(...) do {} while (0)
    #define DEBUG_PRINTLN_HEX(...) do {} while (0)
    #define DEBUG_PRINTLN_TITLE(...) do {} while (0)
    #define DEBUG_QUERY_CHAR(...) do {} while (0)
#endif


#ifdef SIM
    #define DEBUG_PRINT(...) do {debug_print(__VA_ARGS__);} while (0)
    #define DEBUG_PRINTLN(...) do {debug_println(__VA_ARGS__);} while (0)
    #define DEBUG_PRINTLN_DEC(...) do {debug_println_dec(__VA_ARGS__);} while (0)
    #define DEBUG_PRINTLN_BIN(...) do {debug_println_bin(__VA_ARGS__);} while (0)
    #define DEBUG_PRINTLN_HEX(...) do {debug_println_hex(__VA_ARGS__);} while (0)
    #define DEBUG_PRINTLN_TITLE(...) do {debug_println_title(__VA_ARGS__);} while (0)
    #define DEBUG_QUERY_CHAR(...) (debug_query_char(__VA_ARGS__))

#endif
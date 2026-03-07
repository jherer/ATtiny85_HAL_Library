/**
 * @file app.c
 * @brief Template for app source files
 *
 * This module provides the boilerplate code to implement the functions specified in the app.h header
 *
 * @author Joshua Herer
 * @date January 18, 2026
 * @version 1.0
 */

#include <app/app.h>
#include <platform/debug.h>

typedef struct {
    uint8_t a;
} app_state_t;

static app_state_t state = {0};

error_code_t app_init(void) {
    DEBUG_PRINTLN("App template", DEBUG_LAYER_APP);
    // Configure drivers and services here


    // ASSERT_OK(gpio_write(&state.led1, 1)); // Causes init error (write input)
    interrupt_enable();
    return ERROR_OK;
}

error_code_t app_run(void) {
    // Run the main loop of the program here

    return ERROR_OK;
}
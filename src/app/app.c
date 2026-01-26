/**
 * @file app.c
 * @brief Template for app source files
 * 
 * This module provides the boilerplate code to implement the functions specified in the app.h header
 * 
 * @author Joshua Herer
 * @date January 19, 2026
 * @version 1.0
 */


#include "app/app.h"
#include "drivers/interrupts.h"
#include "drivers/gpio.h"
#include "sim/debug.h"

/* Add state variables in this struct */
typedef struct {
<<<<<<< HEAD

} app_state_t;

static app_state_t state = {0}; // Always zero initialize state by default

error_t app_init(void) {
    /* Configure drivers, services, and initial state here */
    
=======
    uint8_t a;
} app_state_t;

static app_state_t state = {0};

error_code_t app_init(void) {
    /* Configure drivers and services here */
>>>>>>> a1f2091 (Added a simulator for testing errors and register config. Cannot do interrupts or simulate gpio inputs as of yet. Also, revert some untested modules.)

    interrupts_enable();
    return ERROR_OK;
}

<<<<<<< HEAD
error_t app_run(void) {
    /* Run the main loop of the program here */

=======
error_code_t app_run(void) {
    /* Run the main loop of the program here */
>>>>>>> a1f2091 (Added a simulator for testing errors and register config. Cannot do interrupts or simulate gpio inputs as of yet. Also, revert some untested modules.)
    
    return ERROR_OK;
}
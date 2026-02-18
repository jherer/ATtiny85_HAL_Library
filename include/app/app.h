/**
 * @file app.h
 * @brief Header for the app layer
 *
 * This module provides an interface for main.c to access the user-defined application
 * The makefile determines which application to compile.
 *
 * @author Joshua Herer
 * @date January 17, 2026
 * @version 1.0
 */

#pragma once
#include <core/error_code.h>
#include <app/assert.h>
#include <drivers/interrupt_driver.h>

error_code_t app_init(void);
error_code_t app_run(void);
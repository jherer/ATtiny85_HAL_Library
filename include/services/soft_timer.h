#ifndef SOFT_TIMER_H
#define SOFT_TIMER_H
#include "drivers/timer.h"
#include "drivers/error.h"

typedef uint8_t soft_timer_id_t;

error_t soft_timer_service_init(void);
error_t soft_timer_set_callback(soft_timer_id_t st_id, uint16_t period_ms, timer_callback_t cb);
bool soft_timer_check_overflow(soft_timer_id_t st_id);
uint32_t soft_timer_service_get_millis(void);
#endif
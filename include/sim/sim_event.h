#pragma once
#include <hal/gpio_ids.h>
#include <drivers/adc_driver.h>

void sim_event_set_gpio_input(gpio_id_t gpio_id, bool state);
void sim_event_set_adc_input(adc_channel_t adc_channel, uint8_t value);
void sim_event_timer0_increment(uint8_t count);
void sim_event_timer1_increment(uint8_t count);
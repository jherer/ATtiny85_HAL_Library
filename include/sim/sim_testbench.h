/*
    A "testbench" is a way to test the app by simulating certain events, such as GPIO and ADC inputs.
    Some events such as ISRs have to be manually invoked by the testbench for simplicity
*/

#pragma once
#include <stdint.h>
void sim_testbench_init(void);
void sim_testbench_run(uint32_t loop_num);
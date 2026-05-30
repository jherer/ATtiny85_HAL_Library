#include <platform/debug.h>
#include <sim/sim_event.h>
#include <sim/sim_testbench.h>

void sim_testbench_init(void) {
    DEBUG_PRINTLN("Default testbench started", DEBUG_LAYER_SIM);
}

void sim_testbench_run(uint32_t loop_num) {
    DEBUG_PRINTLN_DEC("Default testbench running, loop", loop_num, DEBUG_LAYER_SIM);
}
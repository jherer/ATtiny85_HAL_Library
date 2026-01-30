#include "sim_io.h"

sim_io_t sim_io = {0};

void sei(void) {
    sim_io.SREG_SIM |= (1 << 7);
}

void cli(void) {
    sim_io.SREG_SIM &= ~(1 << 7);
}
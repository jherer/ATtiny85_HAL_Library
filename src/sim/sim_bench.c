#include <sim/sim_bench.h>
#include <sim/sim_event.h>

void sim_bench_run(uint32_t loop_num) {
    
    sim_event_set_gpio_input(GPIO_B0, loop_num % 2 == 0);
    /*switch (loop_num) {
    case 0:
        break;
    
    default:
        break;
    }*/
}
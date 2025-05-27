#include "pico/stdlib.h"
#include "hardware_abstraction.h"

static bool led_state = false;

// Application level timer callback function
bool app_toggle_led(struct repeating_timer *t) {
    led_state = !led_state;
    gpio_put(15, led_state);
    return true;
}

int main() {
    stdio_init_all();

    // Hardware abstraction layer initialization
    hal_init();

    // Start timer with application callback
    hal_timer_start(app_toggle_led);

    while (1) {
        tight_loop_contents();
    }
}

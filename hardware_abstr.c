#include "hardware_abstraction.h"

static timer_cb_t app_timer_callback = NULL;
static struct repeating_timer timer;

// This is the callback that SDK timer calls internally
// It will call the application callback indirectly
bool hal_timer_callback(struct repeating_timer *t) {
    if (app_timer_callback) {
        return app_timer_callback(t);
    }
    return true;
}

void hal_init(void) {
    // Initialize GPIO for LED, for example GPIO15
    gpio_init(15);
    gpio_set_dir(15, GPIO_OUT);
}

void hal_timer_start(timer_cb_t app_callback) {
    app_timer_callback = app_callback;
    add_repeating_timer_ms(1000, hal_timer_callback, NULL, &timer);
}

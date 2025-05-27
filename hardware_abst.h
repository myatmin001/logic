#ifndef HARDWARE_ABSTRACTION_H
#define HARDWARE_ABSTRACTION_H

#include "pico/stdlib.h"

// Timer callback type
typedef bool (*timer_cb_t)(struct repeating_timer *t);

// Hardware initialization
void hal_init(void);

// Start repeating timer with application callback
void hal_timer_start(timer_cb_t app_callback);

#endif // HARDWARE_ABSTRACTION_H

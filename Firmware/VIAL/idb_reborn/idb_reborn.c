#include "idb_reborn.h"

void keyboard_pre_init_kb(void) {
    setPinOutput(C6);
    setPinOutput(C7);
}

inline void caps_led_on(void) {
    writePinLow(C6);
}

inline void fn_led_on(void) {
    writePinLow(C7);
}

inline void caps_led_off(void) {
    writePinHigh(C6);
}

inline void fn_led_off(void) {
    writePinHigh(C7);
}

// Capslock LED indicator

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        if (led_state.caps_lock) {
            caps_led_on();
        } else {
            caps_led_off();
        }
    }
    return res;
}

// Layer LED indicator - drive LED when not on base layer

__attribute__((weak)) layer_state_t layer_state_set_user(layer_state_t state) {
    if (get_highest_layer(state) == 0) {
        fn_led_off();
    } else {
        fn_led_on();
    }
    return state;
}


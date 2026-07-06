#include QMK_KEYBOARD_H
#include "keymap_japanese.h"
#include "gpio.h"
#include "host.h"

/*
 * ThinkPad X20x JP keyboard matrix
 * 8 rows (SENSE) x 16 cols (DRV)
 *
 * Layer 0 — main JP
 * Layer 1 — NumPad (toggle via NUM_TOG, follows NumLock state)
 * Layer 2 — Fn (momentary, GP28 active HIGH)
 *
 * GP4  = Power (active LOW, INPUT_PULLUP) — wakes host from suspend
 * GP28 = Fn    (active HIGH, INPUT no pullup)
 * GP29 = TrackPoint RESET (active LOW, OUTPUT)
 * GP10 = TP DATA
 * GP11 = TP CLK
 * GP9  = LED CapsLock
 */

// ---------------------------------------------------------------------------
// Custom keycodes
// ---------------------------------------------------------------------------

static bool suspend_waiting_release = true;
static bool trackpoint_enabled = true;


enum custom_keycodes {
    NUM_TOG = SAFE_RANGE,  // toggle NumLock + layer 1
    CK_SCRSVR,             // XF86ScreenSaver  consumer 0xA0
    CK_BATT,               // XF86Battery      consumer 0xF4
    CK_RFKILL,             // XF86RFKill       consumer 0xF6
    CK_DISP,               // XF86Display      consumer 0xEB
    CK_LNCH1,              // XF86Launch1      consumer 0x9C
    CK_TPDTOG,             // Touchpad Toggle  consumer 0xD4
//    CK_MICMT,              // Mic Mute Toggle  consumer 0xF8
};

// ---------------------------------------------------------------------------
// Keymaps
// ---------------------------------------------------------------------------
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // Layer 0 — main JP
    [0] = {
    //       0           1           2           3           4           5           6           7           8           9           10          11          12          13          14          15
    /* 0 */ {KC_LALT,    KC_NO,      KC_UP,      KC_NO,      KC_NO,      KC_ESC,     KC_NO,      KC_NO,      KC_NO,      KC_F4,      KC_QUOT,    KC_G,       JP_HENK,    KC_F5,      KC_F6,      KC_H    },
    /* 1 */ {KC_NO,      KC_LCTL,    KC_HOME,    KC_NO,      KC_PGUP,    JP_ZKHK,    KC_INS,     KC_F1,      KC_DEL,     KC_F2,      KC_MINS,    KC_5,       KC_F8,      KC_F9,      JP_CIRC,    KC_6    },
    /* 2 */ {KC_NO,      KC_NO,      KC_NO,      KC_LSFT,    KC_NO,      KC_TAB,     KC_NO,      KC_CAPS,    KC_VOLD,    KC_F3,      JP_AT,      KC_T,       KC_F7,      KC_BSPC,    JP_LBRC,    KC_Y    },
    /* 3 */ {KC_SCRL,    KC_NO,      KC_NO,      KC_NO,      KC_LGUI,    KC_Q,       KC_NO,      KC_W,       KC_VOLU,    KC_E,       KC_P,       KC_R,       KC_O,       JP_YEN,     KC_I,       KC_U    },
    /* 4 */ {KC_RALT,    KC_NO,      KC_LEFT,    KC_NO,      KC_WFWD,    JP_MHEN,    KC_RGHT,    KC_NO,      KC_DOWN,    KC_NO,      KC_SLSH,    KC_B,       JP_KANA,    KC_SPC,     JP_BSLS,    KC_N    },
    /* 5 */ {KC_NO,      KC_RCTL,    KC_PAUS,    KC_RSFT,    KC_WBAK,    KC_Z,       KC_NO,      KC_X,       KC_NO,      KC_C,       JP_RBRC,    KC_V,       KC_DOT,     KC_ENT,     KC_COMM,    KC_M    },
    /* 6 */ {KC_PSCR,    KC_NO,      KC_END,     KC_NO,      KC_PGDN,    KC_1,       KC_F12,     KC_2,       KC_F11,     KC_3,       KC_0,       KC_4,       KC_9,       KC_F10,     KC_8,       KC_7    },
    /* 7 */ {KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_APP,     KC_A,       KC_NO,      KC_S,       KC_MUTE,    KC_D,       KC_SCLN,    KC_F,       KC_L,       KC_NO,      KC_K,       KC_J    },
    },

    // Layer 1 — NumPad (toggle, follows NumLock state)
    [1] = {
    //       0           1           2           3           4           5           6           7           8           9           10          11          12          13          14          15
    /* 0 */ {KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS },
    /* 1 */ {KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS },
    /* 2 */ {KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_PENT,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS },
    /* 3 */ {NUM_TOG,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_PAST,    KC_TRNS,    KC_P6,      KC_TRNS,    KC_P5,      KC_P4   },
    /* 4 */ {KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_PPLS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS },
    /* 5 */ {KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_PDOT,    KC_TRNS,    KC_TRNS,    KC_P0   },
    /* 6 */ {KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_PSLS,    KC_TRNS,    KC_P9,      KC_TRNS,    KC_P8,      KC_P7   },
    /* 7 */ {KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_PMNS,    KC_TRNS,    KC_P3,      KC_TRNS,    KC_P2,      KC_P1   },
    },

    // Layer 2 — Fn
    [2] = {
    //       0           1           2           3           4           5           6           7           8           9           10          11          12          13          14          15
    /* 0 */ {KC_NO,      KC_NO,      KC_MSTP,    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      CK_LNCH1,   KC_SLEP,    KC_NO,      KC_NO,      KC_NO,      CK_RFKILL,  KC_NO,      KC_NO   },
    /* 1 */ {KC_NO,      KC_NO,      KC_BRIU,    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      CK_SCRSVR,  KC_NO,      KC_F17,     CK_TPDTOG,  KC_EJCT,    KC_NO,      KC_F18  },
    /* 2 */ {KC_NO,      KC_NO,      KC_NO,      KC_TRNS,    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      CK_BATT,    KC_NO,      KC_NO,      CK_DISP,    KC_NO,      KC_NO,      KC_NO   },
    /* 3 */ {NUM_TOG,    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO   },
    /* 4 */ {KC_NO,      KC_NO,      KC_MPRV,    KC_NO,      KC_NO,      KC_NO,      KC_MNXT,    KC_NO,      KC_MPLY,    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_WSCH,    KC_NO,      KC_NO   },
    /* 5 */ {KC_NO,      KC_NO,      KC_BRK,     KC_TRNS,    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO   },
    /* 6 */ {KC_SYRQ,    KC_NO,      KC_BRID,    KC_NO,      KC_NO,      KC_F13,     KC_NO,      KC_F14,     KC_NO,      KC_F15,     KC_NO,      KC_F16,     KC_NO,      KC_NO,      KC_NO,      KC_NO   },
    /* 7 */ {KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_F20,     KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO   },
    },
};

// ---------------------------------------------------------------------------
// Initializtion
// ---------------------------------------------------------------------------
void keyboard_pre_init_user(void) {
    gpio_set_pin_output(GP29);
    gpio_write_pin_low(GP29);
    gpio_set_pin_input_high(GP28);
    gpio_set_pin_input_high(GP4);
}

void keyboard_post_init_user(void) {
    debug_enable = true;
    debug_mouse  = false;
}

// ---------------------------------------------------------------------------
// Fn → housekeeping
// ---------------------------------------------------------------------------
void housekeeping_task_user(void) {
    // Fn
    bool fn = !gpio_read_pin(GP28);             // active LOW (INPUT_PULLUP)
    if (fn) {
        if (!layer_state_is(2)) layer_on(2);
    } else {
        if (layer_state_is(2)) layer_off(2);
    }

    // Power button — длинное нажатие >1сек = KC_PWR, короткое = ничего
    static uint32_t power_timer = 0;
    static bool power_held = false;
    static bool power_fired = false;

    bool power = !gpio_read_pin(GP4);           // active LOW (INPUT_PULLUP

    if (power && !power_held) {
        power_held = true;
        power_fired = false;
        power_timer = timer_read32();
    } else if (power && power_held && !power_fired) {
        if (timer_elapsed32(power_timer) > 500) {
            // Длинное нажатие — отправляем KC_PWR
            tap_code(KC_PWR);                    //KC_PWR
            power_fired = true;
        }
    } else if (!power && power_held) {
        power_held = false;
        // Короткое нажатие — ничего (или можно добавить действие)
    }
}

// ---------------------------------------------------------------------------
// NumLock → layer 1 sync
// ---------------------------------------------------------------------------
bool led_update_user(led_t led_state) {
    if (led_state.num_lock) {
        layer_on(1);
    } else {
        layer_off(1);
    }
    return true;
}

// ---------------------------------------------------------------------------
// Suspend / wakeup
// ---------------------------------------------------------------------------
bool suspend_wakeup_condition_user(void) {
    bool fn_pressed    = !gpio_read_pin(GP28);
    bool power_pressed = !gpio_read_pin(GP4);

    if (suspend_waiting_release) {
        if (!fn_pressed && !power_pressed) {
            suspend_waiting_release = false;
        }
        return false;
    }

    return fn_pressed || power_pressed;
}

void suspend_wakeup_init_user(void) {
    suspend_waiting_release = true;
    wait_ms(300);
}

void suspend_power_down_user(void) {
    wait_ms(10);
}

// ---------------------------------------------------------------------------
// TrackPoint toggle
// ---------------------------------------------------------------------------
void ps2_mouse_moved_user(report_mouse_t *mouse_report) {
    if (!trackpoint_enabled) {
        mouse_report->x = 0;
        mouse_report->y = 0;
        mouse_report->v = 0;
        mouse_report->h = 0;
    }
}
// ---------------------------------------------------------------------------
// process_record_user — custom_keycodes + debug
// ---------------------------------------------------------------------------
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case NUM_TOG:
            if (record->event.pressed) tap_code(KC_NUM);
            return false;
        case CK_SCRSVR:
            if (record->event.pressed) host_consumer_send(0xA0);
            else host_consumer_send(0);
            return false;

        case CK_BATT:
            if (record->event.pressed) host_consumer_send(0xF4);
            else host_consumer_send(0);
            return false;

        case CK_RFKILL:
            if (record->event.pressed) host_consumer_send(0xF7);
            else host_consumer_send(0);
            return false;

        case CK_DISP:
            if (record->event.pressed) host_consumer_send(0xEB);
            else host_consumer_send(0);
            return false;

        case CK_LNCH1:
            if (record->event.pressed) host_consumer_send(0x9C);
            else host_consumer_send(0);
            return false;

//        case CK_TPDTOG:               //Toggle touchpad
//            if (record->event.pressed) host_consumer_send(0xD4);
//            else host_consumer_send(0);
//            return false;

        case CK_TPDTOG:                 //Toggle TrackPoint
            if (record->event.pressed) {
                trackpoint_enabled = !trackpoint_enabled;
//                host_consumer_send(0xD4);
//            } else {
//                host_consumer_send(0);
            }
            return false;


        default:
            if (record->event.pressed) {
                uprintf("KEY: row=%u col=%u kc=0x%04X\n",
                        record->event.key.row,
                        record->event.key.col,
                        keycode);
            }
            return true;
    }
}

#include "keymap_common.h"
#include "led.h"
#include "keyboard.h"
#include "action_layer.h"

/* Holding shift and pressing Scroll Lock/Number Lock enables/disables the integrated number pad.
 * Pressing Scroll Lock/Number Lock without shift while the number pad is enabled switches between the numbers
 * and cursor keys by turning Number Lock on or off through the host OS.
 */

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap 0: Default Layer
     * ,-------------------------------------------------------------------------------------.
     * |Esc|     | F1| F2| F3| F4| F5| F6| F7| F8| F9| F10| F11| F12|   PSCR|  SCRL|  PAUS|  |
     * |-------------------------------------------------------------------------------------|
     * |-------------------------------------------------------------------------------------|
     * |`  |  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =| * Bspc|     INS|  HOME|  PGUP|
     * |-------------------------------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|     DEL|   END|  PGDN|
     * |-------------------------------------------------------------------------------------|
     * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|* Return|
     * |-------------------------------------------------------------------------------------|
     * |Shift * |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /| *   Shift|        |   UP |         |
     * |-------------------------------------------------------------------------------------|
     * |Ctrl|    |Alt |            Space          |Alt |    |Ctrl  |    LEFT| DOWN | RIGHT|  |
     * `-------------------------------------------------------------------------------------'
     */    
    KEYMAP( \
        ESC,        F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,   F9,   F10,   F11,   F12,         PSCR,  FN0,  PAUS, \
        GRV,  1,    2,   3,   4,   5,   6,   7,   8,   9,    0,    MINS,  EQL,   BSLS, BSPC,  INS,   HOME, PGUP, \
        TAB,  Q,    W,   E,   R,   T,   Y,   U,   I,   O,    P,    LBRC,  RBRC,  BSLS,        DEL,   END,  PGDN, \
        CAPS, A,    S,   D,   F,   G,   H,   J,   K,   L,    SCLN, QUOT,  BSLS,  ENT, \
        LSFT, NUBS, Z,   X,   C,   V,   B,   N,   M,   COMM, DOT,  SLSH,  NO,    RSFT,               UP, \
        LCTL,       LALT,                    SPC,                  RALT,         RCTL,        LEFT,  DOWN, RIGHT),
        
    KEYMAP( \
        TRNS,       TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS,        TRNS,  FN1,  TRNS, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,P7,  P8,  P9,   TRNS, PMNS,  PPLS,  TRNS, TRNS,  TRNS,  TRNS, TRNS, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,P4,  P5,  P6,   TRNS, TRNS,  TRNS,  TRNS,        TRNS,  TRNS, TRNS, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,P1,  P2,  P3,   PAST, TRNS,  TRNS,  PENT, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,P0,  PCMM, PDOT, PSLS,  TRNS,  TRNS,               TRNS, \
        TRNS,       TRNS,                    TRNS,                 TRNS,         TRNS,        TRNS,  TRNS, TRNS)
         
};

/*
* user defined action function
*/
enum function_id {
    SHIFT_NUM, // Shift + SCRL -> Num Pad Layer On
    SHIFT_NUM1, // Shift + Num -> Num Pad Layer Off
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    if (record->event.pressed) dprint("P"); else dprint("R");
    if (record->tap.interrupted) dprint("i");

#   define MODS_SHIFT_MASK   (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
    static uint8_t shift_mod;

    switch (id) {
        // Shift + Scroll Lock -> Num Pad Layer On
        case SHIFT_NUM:
            shift_mod = get_mods()&MODS_SHIFT_MASK;
            if (record->event.pressed) {
                if (shift_mod) {
		    layer_invert(1); // toggle number pad layer
                } else {
                    del_mods(shift_mod); // remove shift
                    add_key(KC_SLCK);
                    send_keyboard_report(); // send Scroll Lock
                    add_mods(shift_mod); // return shift but not sent
                }
            } else {
                if (shift_mod) {
                    
                } else {
                    del_key(KC_SLCK);
                    send_keyboard_report();
                }
            }
            break;
	// Shift + Num Lock -> Num Pad Layer Off
        case SHIFT_NUM1:
            shift_mod = get_mods()&MODS_SHIFT_MASK;
            if (record->event.pressed) {
                if (shift_mod) {
		    layer_invert(1); // toggle number pad layer
                } else {
                    del_mods(shift_mod); // remove shift
                    add_key(KC_NLCK);
                    send_keyboard_report(); // send Num Lock
                    add_mods(shift_mod); // return shift but not sent
                }
            } else {
                if (shift_mod) {

                } else {
                    del_key(KC_NLCK);
                    send_keyboard_report();
                }
            }
            break;
    }

};

const uint16_t PROGMEM fn_actions[] = {
   [0] = ACTION_FUNCTION(SHIFT_NUM),	// number pad layer on
   [1] = ACTION_FUNCTION(SHIFT_NUM1),	// number pad layer off
};
#include "keymap_common.h"
#include "led.h"
#include "keyboard.h"
#include "action_layer.h"

/*
 * LED CONFIG:
 * caps/num/scl:4/3/2
 */
const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap 0: Default Layer
     * ,-------------------------------------------------------------------------------------.
     * |Esc|     | F1| F2| F3| F4| F5| F6| F7| F8| F9| F10| F11| F12|   PSCR|  SCRL|  PAUS|  |
     * |-------------------------------------------------------------------------------------|
     * |-------------------------------------------------------------------------------------|
     * |`  |  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  Bspc |	 INS|  HOME|  PGUP|
     * |-------------------------------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|   \ |	 DEL|   END|  PGDN|
     * |-------------------------------------------------------------------------------------|
     * |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |
     * |-------------------------------------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |	    |   UP |         |
     * |-------------------------------------------------------------------------------------|
     * |Caps |    |Alt |            Space          |Alt |    |Ctrl  |	LEFT| DOWN | RIGHT|  |
     * `-------------------------------------------------------------------------------------'
     */    
    KEYMAP( \
        ESC,        F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,   F9,   F10,   F11,   F12,         PSCR,  FN0,  PAUS, \
        GRV,  1,    2,   3,   4,   5,   6,   7,   8,   9,    0,    MINS,  EQL,   BSLS, BSPC,  INS,   HOME, PGUP, \
        TAB,  Q,    W,   E,   R,   T,   Y,   U,   I,   O,    P,    LBRC,  RBRC,  BSLS,        DEL,   END,  PGDN, \
        LCTL, A,    S,   D,   F,   G,   H,   J,   K,   L,    SCLN, QUOT,  BSLS,  ENT, \
        LSFT, NUBS, Z,   X,   C,   V,   B,   N,   M,   COMM, DOT,  SLSH,  RSFT,  RSFT,               UP, \
        FN1,       LALT,                    SPC,                  RALT,         RCTL,        LEFT,  DOWN, RIGHT),
    /* Keymap 1: Number Pad */    
    KEYMAP( \
        TRNS,       TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS,        TRNS,  TRNS, TRNS, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,P7,  P8,  P9,   TRNS, PMNS,  PPLS,  TRNS, TRNS,  TRNS,  TRNS, TRNS, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,P4,  P5,  P6,   TRNS, TRNS,  TRNS,  TRNS,        TRNS,  TRNS, TRNS, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,P1,  P2,  P3,   PAST, TRNS,  TRNS,  PENT, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,P0,  PCMM, PDOT, PSLS,  TRNS,  TRNS,               TRNS, \
        TRNS,       TRNS,                    TRNS,                 TRNS,         TRNS,        TRNS,  TRNS, TRNS),
    /* Keymap 2: Mouse and Media */
    KEYMAP( \
        PWR,        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS,        MYCM,  CALC, WHOM, \
        FN2,  TRNS, BTN3,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, PMNS,  TRNS,  TRNS, TRNS,  TRNS,  TRNS, TRNS, \
        TRNS, BTN2, MS_U,BTN1,WH_U,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS,        TRNS,  TRNS, TRNS, \
        TRNS, MS_L, MS_D,MS_R,WH_D,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS, \
        TRNS, TRNS, ACL0,ACL1,ACL2,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS,               TRNS, \
        TRNS,       LGUI,                    TRNS,                 TRNS,         TRNS,        VOLD,  TRNS, VOLU),         
};

/*
* user defined action function
*/
enum function_id {
    SHIFT_NUM, // Shift + SCRL -> Num Lock
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    if (record->event.pressed) dprint("P"); else dprint("R");
    if (record->tap.interrupted) dprint("i");

#   define MODS_SHIFT_MASK   (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
    static uint8_t shift_mod;

    switch (id) {
        // Shift + Scroll Lock -> Num Lock
        case SHIFT_NUM:
            shift_mod = get_mods()&MODS_SHIFT_MASK;
            if (record->event.pressed) {
                if (shift_mod) {
		    add_key(KC_NLCK);
                    send_keyboard_report(); // send Num Lock with shift + Scroll Lock
		    layer_invert(1); // toggle number pad layer (1)
                } else {
                    del_mods(shift_mod); // remove shift
                    add_key(KC_SLCK);
                    send_keyboard_report(); // send Scroll Lock
                    add_mods(shift_mod); // return shift but not sent
                }
            } else {
                if (shift_mod) {
		    del_key(KC_NLCK);
                    send_keyboard_report();
                } else {
                    del_key(KC_SLCK);
                    send_keyboard_report();
                }
            }
            break;
    }

};

enum macro_id {
    PASSWORD,
};

const uint16_t PROGMEM fn_actions[] = {
   [0] = ACTION_FUNCTION(SHIFT_NUM),	// num lock
   [1] = ACTION_LAYER_TAP_KEY(2, KC_CAPS),	// mouse and media
   [2] = ACTION_MACRO(PASSWORD),		// the password is 'Nipple'
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
      case PASSWORD:
	return (record->event.pressed ?
	    MACRO( I(0), D(LSHIFT), T(N), U(LSHIFT), T(I), T(P), T(P), T(L), T(E), END ) :
	    MACRO_NONE );
    }
    return MACRO_NONE;
}
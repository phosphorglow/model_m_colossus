#include "keymap_common.h"
#include "keyboard.h"
#include "action_layer.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap 0: Default Layer
     * ,---------------------------------------------------------------------------------------------------------------.
     * |Esc| | F1| F2| F3| F4|  |F5| F6| F7| F8|  |F9| F10| F11| F12|   PSCR|  SCRL|  PAUS|                            |
     * |---------------------------------------------------------------------------------------------------------------|
     * |---------------------------------------------------------------------------------------------------------------|
     * |`  |  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =| * Bspc|     INS|  HOME|  PGUP|    NLCK| PSLS| PAST| PMNS| |
     * |---------------------------------------------------------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|     DEL|   END|  PGDN|     P7|   P8|   P9| |PPLS| |
     * |--------------------------------------------------------------------------------------------------------|    |-|
     * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|* Return|                            P4|   P5|   P6| |  * |-|
     * |---------------------------------------------------------------------------------------------------------------|
     * |Shift * |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /| *   Shift|            UP |            P1|   P2|   P3| |PENT|-|
     * |--------------------------------------------------------------------------------------------------------|    |-|
     * |Ctrl|    |Alt |            Space          |Alt |    |Ctrl  |    LEFT| DOWN | RIGHT|    | *    P0| PDOT| |  * |-|
     * `---------------------------------------------------------------------------------------------------------------'
     */
    KEYMAP( \
        ESC,        F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,   F9,   F10,   F11,   F12,         PSCR,  SLCK, PAUS, \
        GRV,  1,    2,   3,   4,   5,   6,   7,   8,   9,    0,    MINS,  EQL,   BSLS, BSPC,  INS,   HOME, PGUP,        NLCK, PSLS,  PAST, PMNS, \
        TAB,  Q,    W,   E,   R,   T,   Y,   U,   I,   O,    P,    LBRC,  RBRC,  BSLS,        DEL,   END,  PGDN,        P7,   P8,    P9,   PPLS, \
        FN0,  A,    S,   D,   F,   G,   H,   J,   K,   L,    SCLN, QUOT,  BSLS,  ENT,                                   P4,   P5,    P6,   FN1,  \
        LSFT, NUBS, Z,   X,   C,   V,   B,   N,   M,   COMM, DOT,  SLSH,  RSFT,  RSFT,               UP,                P1,   P2,    P3,   PENT, \
        LCTL,       LALT,                    SPC,                  RALT,         RCTL,        LEFT,  DOWN, RIGHT,       NO,   P0,    PDOT, NO) ,
        
    KEYMAP( \
        TRNS,       TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS,        TRNS,  TRNS, FN2, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS, TRNS,  BTN1,  MS_U, BTN2,        NO,   NO,    NO,   NO,   \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS,        MS_L,  MS_D, MS_R,        MPRV, MPLY,  MNXT, NO,   \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS,                                  VOLD, MUTE,  VOLU, TRNS, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS,               TRNS,              NO,   NO,    NO,   NO,   \
        TRNS,       TRNS,                    TRNS,                 TRNS,         TRNS,        TRNS,  TRNS, TRNS,        TRNS, NO,    NO,   TRNS) ,
    
    KEYMAP( \
        TRNS,       TRNS,TRNS, FN3, FN4, FN5, FN6, FN7, FN8,  FN9, TRNS,  TRNS,  TRNS,        TRNS,  TRNS, FN2, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS, TRNS,  TRNS,  TRNS, TRNS,        TRNS, TRNS, TRNS, TRNS, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS,        TRNS,  TRNS, TRNS,        TRNS, TRNS, TRNS, TRNS, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS,                                  TRNS, TRNS, TRNS, TRNS, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS,               TRNS,              TRNS, TRNS, TRNS, TRNS, \
        TRNS,       TRNS,                    TRNS,                 TRNS,         TRNS,        TRNS,  TRNS, TRNS,        TRNS, TRNS, TRNS, TRNS)    
         
};

/*
* user defined action function
*/
enum function_id {
    PAUS_BOOT, // Caps Lock + Right Shift + Pause = DFU
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    if (record->event.pressed) dprint("P"); else dprint("R");
    if (record->tap.interrupted) dprint("i");

#   define MODS_MASK_1   (MOD_BIT(KC_RSHIFT))
    static uint8_t r_shift_mod;

    switch (id) {
        // Caps Lock + Right Shift + Pause = DFU
        case PAUS_BOOT:
            r_shift_mod = get_mods()&MODS_MASK_1;
            if (record->event.pressed) {
                if (r_shift_mod) {
		    del_mods(r_shift_mod);
		    send_keyboard_report();
		    bootloader_jump(); // DFU
                } else {
                    del_mods(r_shift_mod); // remove shift
                    add_key(KC_PAUS);
                    send_keyboard_report(); // send Scroll Lock
                    add_mods(r_shift_mod); // return shift but not sent
                }
            } else {
                if (r_shift_mod) {                   
                } else {
                    del_key(KC_PAUS);
                    send_keyboard_report();
                }
            }
            break;
    }

};

enum macro_id {
    CUT,
    COPY,
    PASTE,
    SELECTALL,
    TEST,
    TEST2,
    TEST3,
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_TAP_KEY(1, KC_CAPS),	// mouse and media etc.
    [1] = ACTION_LAYER_MOMENTARY(1),
    [2] = ACTION_FUNCTION(PAUS_BOOT),	// DFU BOOTLOADER  
    [3] = ACTION_MACRO(CUT),
    [4] = ACTION_MACRO(COPY),
    [5] = ACTION_MACRO(PASTE),
    [6] = ACTION_MACRO(SELECTALL),  
    [7] = ACTION_MACRO(TEST),
    [8] = ACTION_MACRO(TEST2),
    [9] = ACTION_MACRO(TEST3),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
      case CUT:
	return (record->event.pressed ?
	    MACRO( D(LCTRL), T(X), END ) :
	    MACRO( U(LCTRL), U(X), END ));

      case COPY:
	return (record->event.pressed ?
	    MACRO( D(LCTRL), D(C), END ) :
	    MACRO( U(LCTRL), U(C), END ));
    
      case PASTE:
	return (record->event.pressed ?
	    MACRO( D(LCTRL), D(V), END ) :
	    MACRO( U(LCTRL), U(V), END ));

      case SELECTALL:
	return (record->event.pressed ?
	    MACRO( D(LCTRL), D(A), END ) :
	    MACRO( U(LCTRL), U(A), END ));     

      case TEST:
	return (record->event.pressed ?
	    MACRO( I(0), D(LSHIFT), T(I), U(LSHIFT), T(N), T(V), T(O), T(I), T(C), T(E), T(SPC), T(T), T(O), D(LSHIFT), T(SCLN), U(LSHIFT), T(SPC), T(SPC), D(LCTRL), D(V), U(LCTRL), U(V), T(DOT), END ) :
   	    MACRO_NONE );      

      case TEST2:
	return (record->event.pressed ?
	    MACRO( I(5), T(TAB), T(ENT), T(TAB), T(ENT), T(TAB), T(TAB), T(TAB), T(SPC), T(TAB), T(ENT), END ) :
   	    MACRO_NONE );
	
      case TEST3:
	return (record->event.pressed ?
	    MACRO( I(5), D(LSHIFT), T(8), U(LSHIFT), T(SPC), T(ENT), T(BSPC), END ) :
   	    MACRO_NONE );
	
    }
    return MACRO_NONE;
}
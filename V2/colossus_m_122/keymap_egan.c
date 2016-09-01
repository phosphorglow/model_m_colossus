#include "keymap_common.h"
#include "keyboard.h"
#include "action_layer.h"
#include "bootloader.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        /* Keymap 0: Default Layer
     * ,-----------------------------------------------------------------------------------------------------------------------------.
     * |                 | F13| F14| F15| F16| F17| F18| F19| F20| F21|PSCR|SLCK|PAUS|                                               |
     * |-----------------------------------------------------------------------------------------------------------------------------|
     * |                 |  F1|  F2|  F3|  F4|  F5|  F6|  F7|  F8|  F9| F10| F11| F12|                                               |
     * |-----------------------------------------------------------------------------------------------------------------------------|
     * |-----------------------------------------------------------------------------------------------------------------------------|
     * |    | ESC|     ` |  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  * Bspc|    INS|  HOME|  PGUP|    NLCK| PSLS| PAST| PMNS| |
     * |-----------------------------------------------------------------------------------------------------------------------------|
     * |    |    |    Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|     \|    DEL|   END|  PGDN|     P7|   P8|   P9| |PPLS| |
     * |----------------------------------------------------------------------------------------------------------------------|    |-|
     * |    |    |    Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '| * Return|	     UP |             P4|   P5|   P6| |  * |-|
     * |----------------------------------------------------------------------------------------------------------------------|____|-|
     * |    |    |    Shift  *|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /| *    Shift|   LEFT| RGUI| RIGHT|      P1|   P2|   P3| |PENT|-|
     * |----------------------------------------------------------------------------------------------------------------------|    |-|
     * |    |LGUI|    Ctrl|    |Alt |            Space          |Alt |     |Ctrl  |        DOWN |            | *    P0| PDOT| |  * |-|
     * `-----------------------------------------------------------------------------------------------------------------------------'
     */   
	
    /* Layer 0 */
    KEYMAP( \
                              F13,  F14,  F15,  F16,  F17,  F18,  F19, F20,  F21,  PSCR, SLCK,  FN0, \
                              F1,   F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,   F10,  F11,   F12,  \
        NO, ESC,	GRV,  1,    2,   3,   4,   5,   6,   7,   8,   9,    0,    MINS,  EQL,   BSLS, BSPC,  INS,   HOME, PGUP, 	NLCK, PSLS,  PAST, PMNS, \
        NO, NO,	   	TAB,  Q,    W,   E,   R,   T,   Y,   U,   I,   O,    P,    LBRC,  RBRC,  BSLS,        DEL,   END,  PGDN, 	P7,   P8,    P9,   PPLS, \
        NO, NO,	   	CAPS, A,    S,   D,   F,   G,   H,   J,   K,   L,    SCLN, QUOT,  BSLS,  ENT,                UP, 		P4,   P5,    P6,   FN1,\
        NO, NO,	   	LSFT, NUBS, Z,   X,   C,   V,   B,   N,   M,   COMM, DOT,  SLSH,  NO,    RSFT,        LEFT,  RGUI, RIGHT,	P1,   P2,    P3,   PENT, \
        NO, LGUI,	LCTL,       LALT,                    SPC,                  RALT,         RCTL,               DOWN,              NO,   P0,    PDOT, NO) ,
	
    /* Layer 1 */
    KEYMAP( \
                              TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,  TRNS, \
                              TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,  TRNS, \
        TRNS, TRNS,	TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS, TRNS,  TRNS,  TRNS, TRNS,        NO,   NO,   NO,   NO,   \
        TRNS, TRNS,   	TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS,        TRNS,  TRNS, TRNS,        MPRV, MPLY, MNXT, NO,   \
        TRNS, TRNS,   	TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS,               TRNS,              VOLD, MUTE, VOLU, TRNS, \
        TRNS, TRNS,   	TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS,        TRNS,  TRNS, TRNS,        NO,   NO,   NO,   NO,   \
        TRNS, TRNS,	TRNS,       TRNS,                    TRNS,                 TRNS,         TRNS,               TRNS,              TRNS, NO,   NO,   TRNS)	
};

/*
* user defined action function
*/
enum function_id {
    PAUS_BOOT, // Left ALT + Right CTRL + Pause = DFU
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    if (record->event.pressed) dprint("P"); else dprint("R");
    if (record->tap.interrupted) dprint("i");

#   define MODS_MASK_1   (MOD_BIT(KC_LALT))
#   define MODS_MASK_2   (MOD_BIT(KC_RCTL))    
    static uint8_t lalt_rctl_mods;

    switch (id) {
        // Left ALT + Right CTRL + Pause = DFU
        case PAUS_BOOT:
            lalt_rctl_mods = get_mods()&MODS_MASK_1 && get_mods()&MODS_MASK_2;
            if (record->event.pressed) {
                if (lalt_rctl_mods) {
		    del_mods(lalt_rctl_mods);
		    send_keyboard_report();
		    bootloader_jump();
                } else {
                    del_mods(lalt_rctl_mods); // remove shift
                    add_key(KC_PAUS);
                    send_keyboard_report(); // send Scroll Lock
                    add_mods(lalt_rctl_mods); // return shift but not sent
                }
            } else {
                if (lalt_rctl_mods) {                   
                } else {
                    del_key(KC_PAUS);
                    send_keyboard_report();
                }
            }
            break;
    }

};

const uint16_t PROGMEM fn_actions[] = {
   [0] = ACTION_FUNCTION(PAUS_BOOT),		// DFU BOOTLOADER  
   [1] = ACTION_LAYER_MOMENTARY(1),   
};
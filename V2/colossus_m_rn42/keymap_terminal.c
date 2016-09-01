#include "keymap_common.h"
#include "keyboard.h"
#include "action_layer.h"
#include "bootloader.h"

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
        ESC,        F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,   F9,   F10,   F11,   F12,         PSCR,  SLCK, FN0, \
        GRV,  1,    2,   3,   4,   5,   6,   7,   8,   9,    0,    MINS,  EQL,   BSLS, BSPC,  INS,   HOME, PGUP,        NLCK, PSLS,  PAST, PMNS, \
        TAB,  Q,    W,   E,   R,   T,   Y,   U,   I,   O,    P,    LBRC,  RBRC,  BSLS,        DEL,   END,  PGDN,        P7,   P8,    P9,   PPLS, \
        CAPS, A,    S,   D,   F,   G,   H,   J,   K,   L,    SCLN, QUOT,  BSLS,  ENT,                                   P4,   P5,    P6,   FN1,  \
        LSFT, NUBS, Z,   X,   C,   V,   B,   N,   M,   COMM, DOT,  SLSH,  RSFT,  RSFT,               UP,                P1,   P2,    P3,   PENT, \
        LCTL,       LALT,                    SPC,                  RALT,         RCTL,        LEFT,  DOWN, RIGHT,       NO,   P0,    PDOT, NO) ,
        
    KEYMAP( \
        TRNS,       TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS,        TRNS,  TRNS, TRNS, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS, TRNS,  TRNS,  TRNS, TRNS,        NO,   NO,    NO,   NO,   \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS,        TRNS,  TRNS, TRNS,        MPRV, MPLY,  MNXT, NO,   \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS,                                  VOLD, MUTE,  VOLU, TRNS, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS,               TRNS,              NO,   NO,    NO,   NO,   \
        TRNS,       TRNS,                    TRNS,                 TRNS,         TRNS,        TRNS,  TRNS, TRNS,        TRNS, NO,    NO,   TRNS) 
         
};

/*
* user defined action function
*/
enum function_id {
    PAUS_BOOT, // Left ALT + Right ALT + Pause = DFU
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    if (record->event.pressed) dprint("P"); else dprint("R");
    if (record->tap.interrupted) dprint("i");

#   define MODS_MASK_1   (MOD_BIT(KC_LALT))
#   define MODS_MASK_2   (MOD_BIT(KC_RCTL))    
    static uint8_t lalt_ralt_mods;

    switch (id) {
        // Left ALT + Right ALT + Pause = DFU
        case PAUS_BOOT:
            lalt_ralt_mods = get_mods()&MODS_MASK_1 && get_mods()&MODS_MASK_2;
            if (record->event.pressed) {
                if (lalt_ralt_mods) {
		    del_mods(lalt_ralt_mods);
		    send_keyboard_report();
		    bootloader_jump();
                } else {
                    del_mods(lalt_ralt_mods); // remove shift
                    add_key(KC_PAUS);
                    send_keyboard_report(); // send Scroll Lock
                    add_mods(lalt_ralt_mods); // return shift but not sent
                }
            } else {
                if (lalt_ralt_mods) {                   
                } else {
                    del_key(KC_PAUS);
                    send_keyboard_report();
                }
            }
            break;
    }

};


const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_FUNCTION(PAUS_BOOT),	// DFU BOOTLOADER    
    [1] = ACTION_LAYER_MOMENTARY(1),
};

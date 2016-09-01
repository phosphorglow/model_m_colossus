#include "keymap_common.h"
#include "led.h"
#include "keyboard.h"
#include "action_layer.h"
#include <util/delay.h>
#include <avr/io.h>
#include "host.h"
#include "bootloader.h"

/* Phosphorglow's Layout
 * 
 * Holding shift and pressing Scroll Lock/Number Lock enables/disables the integrated number pad.
 * Pressing Scroll Lock/Number Lock without shift while the number pad is enabled switches between the numbers
 * and cursor keys by turning Number Lock on or off through the host OS.
 * 
 * Holding Right Control and pressing Page Up will put the bluefruit module into pairing mode.
 * 
 * Holding Caps Lock enables the mouse and media controls layer.
 * 
 * 
 * Please excuse my lack of code etiquette/knowledge. It's probably messy. It could probably be
 * done differently and neatly, but I'm not a programmer. I'm surprised I've figured out this much. :P
 * 
 */

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap 0: Default Layer
     * ,-------------------------------------------------------------------------------------.
     * |Esc| | F1| F2| F3| F4|  |F5| F6| F7| F8|  |F9| F10| F11| F12|   PSCR|  SCRL|  PAUS|  |
     * |-------------------------------------------------------------------------------------|
     * |-------------------------------------------------------------------------------------|
     * |`  |  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  Bspc\|	 INS|  HOME|  PGUP|  |
     * |-------------------------------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|	 DEL|   END|  PGDN|  |
     * |-------------------------------------------------------------------------------------|
     * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |                         |
     * |-------------------------------------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |	        UP |         |
     * |-------------------------------------------------------------------------------------|
     * |Ctrl|    |Alt |            Space          |Alt |    |Ctrl  |	LEFT| DOWN | RIGHT|  |
     * `-------------------------------------------------------------------------------------'
     */
        /* Layer 2: Mouse and Media, etc. 
        * ,-------------------------------------------------------------------------------------.
        * |   | |   |   |   |   |  |  |   |   |   |  |  |MPLY|MPRV|MNXT|       |      |      |  |
        * |-------------------------------------------------------------------------------------|
        * |-------------------------------------------------------------------------------------|
        * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |	   BTN1|  MS_U|  BTN2|  |
        * |-------------------------------------------------------------------------------------|
        * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |	   MS_L|  MS_D|  MS_R|  |
        * |-------------------------------------------------------------------------------------|
        * |    |    |    |    |   |   |   |   |   |   |   |   |       |                         |
        * |-------------------------------------------------------------------------------------|
        * |        |   |   |   |   |   |   |   |   |   |   |          |	              |         |
        * |-------------------------------------------------------------------------------------|
        * |    |    |    |                           |    |    |      |	   VOLD|  MUTE|  VOLU|  |
        * `-------------------------------------------------------------------------------------'
        */
    
    /* Keymap Template
     * ,-------------------------------------------------------------------------------------.
     * |   | |   |   |   |   |  |  |   |   |   |  |  |    |    |    |       |      |      |  |
     * |-------------------------------------------------------------------------------------|
     * |-------------------------------------------------------------------------------------|
     * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |	    |      |      |  |
     * |-------------------------------------------------------------------------------------|
     * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |	    |      |      |  |
     * |-------------------------------------------------------------------------------------|
     * |      |   |   |   |   |   |   |   |   |   |   |   |        |                         |
     * |-------------------------------------------------------------------------------------|
     * |        |   |   |   |   |   |   |   |   |   |   |          |	           |         |
     * |-------------------------------------------------------------------------------------|
     * |    |    |    |                           |    |    |      |	    |      |      |  |
     * `-------------------------------------------------------------------------------------'
     */
    
    KEYMAP( \
        /* Layer 0: Default */
	ESC,        F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,   F9,   F10,   F11,   F12,         PSCR,  FN0,  PAUS, \
        GRV,  1,    2,   3,   4,   5,   6,   7,   8,   9,    0,    MINS,  EQL,   BSLS, BSPC,  INS,   HOME, FN2, \
        TAB,  Q,    W,   E,   R,   T,   Y,   U,   I,   O,    P,    LBRC,  RBRC,  BSLS,        DEL,   END,  PGDN, \
        FN3,  A,    S,   D,   F,   G,   H,   J,   K,   L,    SCLN, QUOT,  BSLS,  ENT, \
        LSFT, NUBS, Z,   X,   C,   V,   B,   N,   M,   COMM, DOT,  SLSH,  RSFT,  RSFT,               UP, \
        LCTL,       LALT,                    SPC,                  RALT,         RCTL,        LEFT,  DOWN, RIGHT),

	/* Layer 1: Number Pad */        
    KEYMAP( \
        TRNS,       TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS,        TRNS,  FN1,  TRNS, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,P7,  P8,  P9,   TRNS, PMNS,  PPLS,  TRNS, TRNS,  TRNS,  TRNS, TRNS, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,P4,  P5,  P6,   TRNS, TRNS,  TRNS,  TRNS,        TRNS,  TRNS, TRNS, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,P1,  P2,  P3,   PAST, TRNS,  TRNS,  PENT, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,P0,  PCMM, PDOT, PSLS,  TRNS,  TRNS,               TRNS, \
        TRNS,       TRNS,                    TRNS,                 TRNS,         TRNS,        TRNS,  TRNS, TRNS),

    KEYMAP( \
        TRNS,       TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS,        TRNS,  TRNS, TRNS, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS, TRNS,  BTN1,  MS_U, BTN2, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS,        MS_L,  MS_D, MS_R, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS,               TRNS, \
        TRNS,       TRNS,                    TRNS,                 TRNS,         FN4,         TRNS,  TRNS, TRNS),  

          /* Layer 3: Hold Caps Lock: Volume, Media, L/R GUI.  */
    KEYMAP( \
        TRNS,       TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, MPLY,  MPRV,  MNXT,        TRNS,  TRNS, FN5,  \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS, TRNS,  TRNS,  TRNS, TRNS, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS,        TRNS,  TRNS, TRNS, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS,               TRNS, \
        TRNS,       LGUI,                    TRNS,                 RGUI,         TRNS,        VOLD,  MUTE, VOLU),  
          
	/* Layer 4: Mouse Scroll (Home/End when Right Control Held) */
    KEYMAP( \
        TRNS,       TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS,        TRNS,  TRNS, TRNS, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS, TRNS,  TRNS,  WH_U, TRNS, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS,        TRNS,  WH_D, TRNS, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS, \
        TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS,  TRNS,  TRNS,               TRNS, \
        TRNS,       TRNS,                    TRNS,                 TRNS,         TRNS,        TRNS,  TRNS, TRNS),
};

/*
* user defined action function
*/
enum function_id {
    SHIFT_NUM, // Shift + SCRL -> Number Pad Layer On
    SHIFT_NUM1, // Shift + Num -> Number Pad Layer Off
    BTPAIR, // LCTRL + RCTRL + PGUP -> BT Pair
    PAUS_BOOT, // Caps Lock + Right Shift + Pause = DFU
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    if (record->event.pressed) dprint("P"); else dprint("R");
    if (record->tap.interrupted) dprint("i");

#   define MODS_SHIFT_MASK   (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
    static uint8_t shift_mod;
#   define MODS_RCTRL_MASK   (MOD_BIT(KC_RCTRL))
    static uint8_t rctrl_mod;    
#   define MODS_MASK_1   (MOD_BIT(KC_RSHIFT))
    static uint8_t r_shift_mod;
    
    switch (id) {
        // Shift + Scroll Lock -> Number Pad Layer On
        case SHIFT_NUM:
            shift_mod = get_mods()&MODS_SHIFT_MASK;
            if (record->event.pressed) {
                if (shift_mod) {
		    layer_invert(1); // toggle number pad layer
		    DDR_NUMLAYER ^= (1<<BIT_NUMLAYER);	    
                } else {
                    del_mods(shift_mod); // remove shift
                    layer_invert(2); // toggle number pad layer
		    //DDR_EXTRA_LAYER ^= (1<<BIT_EXTRA_LAYER);
		    // ...because, come on, who uses scroll lock...?
		    //add_key(KC_SLCK);
                    //send_keyboard_report(); // send Scroll Lock
                    add_mods(shift_mod); // return shift but not sent
                }
            } else {
                if (shift_mod) {
                } else {
                    //del_key(KC_SLCK);
                    send_keyboard_report();
                }
            }
            break;
	    
	// Shift + Scroll Lock -> Number Pad Layer Off
        case SHIFT_NUM1:
            shift_mod = get_mods()&MODS_SHIFT_MASK;
            if (record->event.pressed) {
                if (shift_mod) {
		    layer_invert(1); // toggle number pad layer
		    DDR_NUMLAYER ^= (1<<BIT_NUMLAYER);
                } else {
                    del_mods(shift_mod); // remove shift
                    add_key(KC_NLCK);
                    send_keyboard_report(); // send Num Lock (toggles number pad in OS between numbers and cursors)
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

	// RCtrl + Page Up -> BT Pair
        case BTPAIR:
            rctrl_mod = get_mods()&MODS_RCTRL_MASK;
            if (record->event.pressed) {
                if (rctrl_mod) {
		      // 3V to pair pin on bluefruit for 5 seconds.
		      DDR_BF_PAIRB |= (1<<BIT_BF_PAIRB);
		      PORT_BF_PAIRB |= (1<<BIT_BF_PAIRB);
		      _delay_ms(5000);
		      DDR_BF_PAIRB &= ~(1<<BIT_BF_PAIRB);
		      PORT_BF_PAIRB &= ~(1<<BIT_BF_PAIRB);
                } else {
                    del_mods(rctrl_mod); // remove shift
                    add_key(KC_PGUP);
                    send_keyboard_report(); // send Page Up
                    add_mods(rctrl_mod); // return shift but not sent
                }
            } else {
                if (rctrl_mod) {
		    del_key(KC_PGUP);
                    send_keyboard_report();
                } else {
                    del_key(KC_PGUP);
                    send_keyboard_report();
                }
            }
            break;
	    
        // Caps Lock + Right Shift + Pause = DFU
        case PAUS_BOOT:
            r_shift_mod = get_mods()&MODS_MASK_1;
            if (record->event.pressed) {
                if (r_shift_mod) {
		    bootloader_jump(); // JUMP TO DFU BOOTLOADER
                } else {
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

const uint16_t PROGMEM fn_actions[] = {
   [0] = ACTION_FUNCTION(SHIFT_NUM),		// number pad layer on
   [1] = ACTION_FUNCTION(SHIFT_NUM1),		// number pad layer off
   [2] = ACTION_FUNCTION(BTPAIR),		// BT PAIR
   [3] = ACTION_LAYER_TAP_KEY(3, KC_CAPS),	// mouse and media etc.
   [4] = ACTION_LAYER_MOMENTARY(4),		// mouse and media etc. 
   [5] = ACTION_FUNCTION(PAUS_BOOT),		// DFU BOOTLOADER  
};
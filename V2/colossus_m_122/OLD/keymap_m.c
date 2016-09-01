#include "keymap_common.h"
#include "keyboard.h"
#include "action_layer.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        /* Keymap 0: Default Layer
     * ,-----------------------------------------------------------------------------------------------------------------------------.
     * |                 | F13| F14| F15| F16| F17| F18| F19| F20| F21| F22| F23| F24|                                               |
     * |-----------------------------------------------------------------------------------------------------------------------------|
     * |                 |  F1|  F2|  F3|  F4|  F5|  F6|  F7|  F8|  F9| F10| F11| F12|                                               |
     * |-----------------------------------------------------------------------------------------------------------------------------|
     * |-----------------------------------------------------------------------------------------------------------------------------|
     * | FN1| FN2|     ` |  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  * Bspc|    INS|  HOME|  PGUP|    NLCK| PSLS| PAST| PMNS| |
     * |-----------------------------------------------------------------------------------------------------------------------------|
     * | FN3| FN4|    Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|     \|    DEL|   END|  PGDN|     P7|   P8|   P9| |PPLS| |
     * |----------------------------------------------------------------------------------------------------------------------|----|-|
     * | FN5| FN6|    Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '| * Return|	     UP |             P4|   P5|   P6| |  * |-|
     * |----------------------------------------------------------------------------------------------------------------------|____|-|
     * | FN7| FN8|    Shift  *|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /| *    Shift|   LEFT| FN11 | RIGHT|     P1|   P2|   P3| |PENT|-|
     * |----------------------------------------------------------------------------------------------------------------------|----|-|
     * | FN9|FN10|    Ctrl|    |Alt |            Space          |Alt |     |Ctrl  |         DOWN |           | *    P0| PDOT| |  * |-|
     * `-----------------------------------------------------------------------------------------------------------------------____--'
     */   
    KEYMAP( \
                              F13,  F14,  F15,  F16,  F17,  F18,  F19,  F20,   F21,   F22,   F23,   F24, \
                              F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,    F9,    F10,   F11,   F12, \
        FN1, FN2,	GRV,  1,    2,   3,   4,   5,   6,   7,   8,   9,    0,    MINS,  EQL,   BSLS, BSPC,  INS,   HOME, PGUP, 	NLCK, PSLS,  PAST, PMNS, \
        FN3, FN4,	TAB,  Q,    W,   E,   R,   T,   Y,   U,   I,   O,    P,    LBRC,  RBRC,  BSLS,        DEL,   END,  PGDN, 	P7,   P8,    P9,   PPLS, \
        FN5, FN6,	CAPS, A,    S,   D,   F,   G,   H,   J,   K,   L,    SCLN, QUOT,  BSLS,  ENT,                UP, 		P4,   P5,    P6,   NO,\
        FN7, FN8,	LSFT, NUBS, Z,   X,   C,   V,   B,   N,   M,   COMM, DOT,  SLSH,  NO,    RSFT,        LEFT,  FN11, RIGHT,	P1,   P2,    P3,   PENT, \
        FN9, FN10,	LCTL,       LALT,                    SPC,                  RALT,         RCTL,               DOWN,              NO,   P0,    PDOT, NO) ,
        
         
};

const uint16_t PROGMEM fn_actions[] = {
};
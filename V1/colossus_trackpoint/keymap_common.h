/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef KEYMAP_COMMON_H
#define KEYMAP_COMMON_H

#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "keycode.h"
#include "action.h"
#include "action_macro.h"
#include "report.h"
#include "host.h"
#include "print.h"
#include "debug.h"
#include "keymap.h"


extern const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS];
extern const uint16_t fn_actions[];

/* IBM Model M 101/102 */
/* Colossus Model M Controller ver. 1 */


#define KEYMAP( \
    K72,      K53, K54, K64, K74, K76, K78, K69, K59, K56, K46, K4B, K4C,      K4F, K3F, K1E, \
    K52, K42, K43, K44, K45, K55, K57, K47, K48, K49, K4A, K5A, K58, K36, K66, K5C, K5E, K5D, 	K1B, K1C, K1D, K0D, \
    K62, K32, K33, K34, K35, K65, K67, K37, K38, K39, K3A, K6A, K68, K26,      K5B, K4E, K4D, 	K3B, K3C, K3D, K3E, \
    K63, K22, K23, K24, K25, K75, K77, K27, K28, K29, K2A, K7A, K1A, K16, 			K6B, K6C, K6D, K6E,\
    K61, K73, K12, K13, K14, K15, K05, K07, K17, K18, K19, K0A, K08, K11,           K7E, 	K2B, K2C, K2D, K2E, \
    K50,      K7F,                     K06,                K0F,      K10,      K0E, K0B, K0C, 	K7B, K7C, K7D, K2F \
) { \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_##K05, KC_##K06, KC_##K07, KC_##K08, KC_NO,    KC_##K0A, KC_##K0B, KC_##K0C, KC_##K0D, KC_##K0E, KC_##K0F }, \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17, KC_##K18, KC_##K19, KC_##K1A, KC_##K1B, KC_##K1C, KC_##K1D, KC_##K1E, KC_NO }, \
    { KC_NO,    KC_NO,    KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27, KC_##K28, KC_##K29, KC_##K2A, KC_##K2B, KC_##K2C, KC_##K2D, KC_##K2E, KC_##K2F }, \
    { KC_NO,    KC_NO,    KC_##K32, KC_##K33, KC_##K34, KC_##K35, KC_##K36, KC_##K37, KC_##K38, KC_##K39, KC_##K3A, KC_##K3B, KC_##K3C, KC_##K3D, KC_##K3E, KC_##K3F }, \
    { KC_NO,    KC_NO,    KC_##K42, KC_##K43, KC_##K44, KC_##K45, KC_##K46, KC_##K47, KC_##K48, KC_##K49, KC_##K4A, KC_##K4B, KC_##K4C, KC_##K4D, KC_##K4E, KC_##K4F }, \
    { KC_##K50, KC_NO,    KC_##K52, KC_##K53, KC_##K54, KC_##K55, KC_##K56, KC_##K57, KC_##K58, KC_##K59, KC_##K5A, KC_##K5B, KC_##K5C, KC_##K5D, KC_##K5E, KC_NO },  \
    { KC_NO,    KC_##K61, KC_##K62, KC_##K63, KC_##K64, KC_##K65, KC_##K66, KC_##K67, KC_##K68, KC_##K69, KC_##K6A, KC_##K6B, KC_##K6C, KC_##K6D, KC_##K6E, KC_NO },  \
    { KC_NO,    KC_NO,    KC_##K72, KC_##K73, KC_##K74, KC_##K75, KC_##K76, KC_##K77, KC_##K78, KC_NO,    KC_##K7A, KC_##K7B, KC_##K7C, KC_##K7D, KC_##K7E, KC_##K7F }  \
}

#endif






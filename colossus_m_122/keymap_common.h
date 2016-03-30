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

/* IBM Model M 122 */
/* Colossus Model M Controller */


#define KEYMAP( \
		     K79, K69, K6A, K59, K49, K4A, K39, K29, K2A, K19, K09, K0A, \
		     K7A, K7B, K6B, K5A, K5B, K4B, K3A, K3B, K2B, K1A, K1B, K0B, \
    K41, K42,   K44, K54, K55, K56, K57, K47, K48, K58, K5C, K5D, K5E, K4E, K4C, K43, K4F,    K4G, K4H, K5G, 	K5F, K5H, K5I, K50, \
    K51, K31,   K32, K34, K35, K36, K37, K27, K28, K38, K3C, K3D, K3E, K2E, K2C,    K2F,      K6G, K2G, K3G, 	K3F, K3H, K3I, K30, \
    K21, K22,   K12,   K64, K65, K66, K67, K77, K78, K68, K6C, K6D, K6E, K7E, K1E, K1F,            K7G,		K6F, K6H, K6I, K60, \
    K61, K62,   K03, K04, K14, K15, K16, K17, K07, K08, K18, K1C, K1D, K0E, K0D, K13,         K10, K7J, K6J,	K11, K1H, K1I, K0J, \
    K72, K71,   K70,      K00,                  K01,                   K73,      K02,              K7F,         K0F, K0H, K0I, K1J  \
) { \
    { KC_##K00, KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_NO,    KC_NO,    KC_##K07, KC_##K08, KC_##K09, KC_##K0A, KC_##K0B, KC_NO,    KC_NO,    KC_##K0E, KC_##K0F, KC_NO,    KC_##K0H, KC_##K0I, KC_##K0J }, \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17, KC_##K18, KC_##K19, KC_##K1A, KC_##K1B, KC_##K1C, KC_##K1D, KC_##K1E, KC_##K1F, KC_NO,    KC_##K1H, KC_##K1I, KC_##K1J }, \
    { KC_NO,    KC_##K21, KC_##K22, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_##K27, KC_##K28, KC_##K29, KC_##K2A, KC_##K2B, KC_##K2C, KC_NO,    KC_##K2E, KC_##K2F, KC_##K2G, KC_NO,    KC_NO,    KC_NO }, \
    { KC_##K30, KC_##K31, KC_##K32, KC_NO,    KC_##K34, KC_##K35, KC_##K36, KC_##K37, KC_##K38, KC_##K39, KC_##K3A, KC_##K3B, KC_##K3C, KC_##K3D, KC_##K3E, KC_##K3F, KC_##K3G, KC_##K3H, KC_##K3I, KC_NO }, \
    { KC_NO,    KC_##K41, KC_##K42, KC_##K43, KC_##K44, KC_NO,    KC_NO,    KC_##K47, KC_##K48, KC_##K49, KC_##K4A, KC_##K4B, KC_##K4C, KC_NO,    KC_##K4E, KC_##K4F, KC_##K4G, KC_##K4H, KC_NO,    KC_NO }, \
    { KC_##K50, KC_##K51, KC_NO,    KC_NO,    KC_##K54, KC_##K55, KC_##K56, KC_##K57, KC_##K58, KC_##K59, KC_##K5A, KC_##K5B, KC_##K5C, KC_##K5D, KC_##K5E, KC_##K5F, KC_##K5G, KC_##K5H, KC_##K5I, KC_NO },  \
    { KC_##K60, KC_##K61, KC_##K62, KC_NO,    KC_##K64, KC_##K65, KC_##K66, KC_##K67, KC_##K68, KC_##K69, KC_##K6A, KC_##K6B, KC_##K6C, KC_##K6D, KC_##K6E, KC_##K6F, KC_##K6G, KC_##K6H, KC_##K6I, KC_##K6J },  \
    { KC_##K70, KC_##K71, KC_##K72, KC_##K73, KC_NO,    KC_NO,    KC_NO,    KC_##K77, KC_##K78, KC_##K79, KC_##K7A, KC_##K7B, KC_NO,    KC_NO,    KC_##K7E, KC_##K7F, KC_##K7G, KC_NO,    KC_NO,    KC_##K7J }  \
}

#endif






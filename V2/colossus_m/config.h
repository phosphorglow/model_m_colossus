/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#ifndef CONFIG_H
#define CONFIG_H


/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    PhosphorGlow
#define PRODUCT         Model_M_V2.0
#define DESCRIPTION     Colossus Model M Controller V2.0

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 16

/* define if matrix has ghost */
#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for magic command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RCTL)) \
)

/* salt key for magic command, M matrix won't handle space in combination */
/* but I'm not entirely sure how to use this yet...                       */
/* #define BOOTMAGIC_KEY_SALT KC_Y */

/* 
CapsLock / NumLock / ScrolLock LED pin config 
for LED.c
PC1: -> NumLock LED   
PC3: -> CapsLock LED
PE1: -> ScrollLock LED
*/

#define DDR_NUMLCK DDRC
#define PORT_NUMLCK PORTC
#define BIT_NUMLCK 1

#define DDR_CAPSLCK DDRC
#define PORT_CAPSLCK PORTC
#define BIT_CAPSLCK 3

#define DDR_SCROLLLCK DDRE
#define PORT_SCROLLLCK PORTE
#define BIT_SCROLLLCK 1





#endif

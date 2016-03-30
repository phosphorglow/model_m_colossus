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
#define PRODUCT         Model_M_V1.0
#define DESCRIPTION     Colossus Model M Controller

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 16

/* define if matrix has ghost */
#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE  1

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for magic command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RCTL)) \
)


/* 
CapsLock / NumLock / ScrolLock LED pin config combined 12FPC
for LED.c
PB4: -> NumLock LED 
PB3: -> CapsLock LED
PB2: -> ScrollLock LED

CapsLock / NumLock / ScrolLock LED pin config separate 4pin FPC (reversed mounting)
for LED.c
PB0: -> NumLock LED 
PB2: -> CapsLock LED
PB3: -> ScrollLock LED

CapsLock / NumLock / ScrolLock LED pin config yellow wires with JST connector
for LED.c
PB2: -> NumLock LED 
PB4: -> CapsLock LED
PB3: -> ScrollLock LED
*/

#define DDR_NUMLCK DDRB
#define PORT_NUMLCK PORTB
#define BIT_NUMLCK 4

#define DDR_CAPSLCK DDRB
#define PORT_CAPSLCK PORTB
#define BIT_CAPSLCK 3

#define DDR_SCROLLLCK DDRB
#define PORT_SCROLLLCK PORTB
#define BIT_SCROLLLCK 2

#define DDR_ELWIRE DDRB
#define PORT_ELWIRE PORTB
#define BIT_ELWIRE 0

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//  #  define NO_DEBUG

/* disable print */
//#  define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

/* PS/2 mouse USART version */
#ifdef PS2_USE_USART
#if defined(__AVR_ATmega16U4__) || defined(__AVR_AT90USB1286__)
/* XCK for clock line and RXD for data line */
#define PS2_CLOCK_PORT  PORTD
#define PS2_CLOCK_PIN   PIND
#define PS2_CLOCK_DDR   DDRD
#define PS2_CLOCK_BIT   5
#define PS2_DATA_PORT   PORTD
#define PS2_DATA_PIN    PIND
#define PS2_DATA_DDR    DDRD
#define PS2_DATA_BIT    2

/* synchronous, odd parity, 1-bit stop, 8-bit data, sample at falling edge */
/* set DDR of CLOCK as input to be slave */
#define PS2_USART_INIT() do {   \
    PS2_CLOCK_DDR &= ~(1<<PS2_CLOCK_BIT);   \
    PS2_DATA_DDR &= ~(1<<PS2_DATA_BIT);     \
    UCSR1C = ((1 << UMSEL10) |  \
              (3 << UPM10)   |  \
              (0 << USBS1)   |  \
              (3 << UCSZ10)  |  \
              (0 << UCPOL1));   \
    UCSR1A = 0;                 \
    UBRR1H = 0;                 \
    UBRR1L = 0;                 \
} while (0)
#define PS2_USART_RX_INT_ON() do {  \
    UCSR1B = ((1 << RXCIE1) |       \
              (1 << RXEN1));        \
} while (0)
#define PS2_USART_RX_POLL_ON() do { \
    UCSR1B = (1 << RXEN1);          \
} while (0)
#define PS2_USART_OFF() do {    \
    UCSR1C = 0;                 \
    UCSR1B &= ~((1 << RXEN1) |  \
                (1 << TXEN1));  \
} while (0)
#define PS2_USART_RX_READY      (UCSR1A & (1<<RXC1))
#define PS2_USART_RX_DATA       UDR1
#define PS2_USART_ERROR         (UCSR1A & ((1<<FE1) | (1<<DOR1) | (1<<UPE1)))
#define PS2_USART_RX_VECT       USART1_RX_vect
#endif
#endif

#endif

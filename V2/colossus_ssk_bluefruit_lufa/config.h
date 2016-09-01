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
#define PRODUCT         ModelMSSK
#define DESCRIPTION     Colossus Model M Controller

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 16

/* define if matrix has ghost */
#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Locking resynchronize hack 
#define LOCKING_RESYNC_ENABLE
*/

/* key combination for magic command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RCTL)) \
)

/* USART configuration
 *     asynchronous, 9600baud, 8-data bit, non parity, 1-stop bit, no flow control
 */
#define SERIAL_UART_BAUD       9600
#define SERIAL_UART_DATA       UDR1
#define SERIAL_UART_UBRR       ((F_CPU/(16UL*SERIAL_UART_BAUD))-1)
#define SERIAL_UART_RXD_VECT   USART1_RX_vect
#define SERIAL_UART_TXD_READY  (UCSR1A&(1<<UDRE1))
#define SERIAL_UART_INIT()     do { \
    UBRR1L = (uint8_t) SERIAL_UART_UBRR;       /* baud rate */ \
    UBRR1H = (uint8_t) (SERIAL_UART_UBRR>>8);  /* baud rate */ \
    UCSR1B = (1<<TXEN1);                /* TX: enable */ \
    UCSR1C = (0<<UPM11) | (0<<UPM10) | /* parity: none(00), even(01), odd(11) */ \
             (0<<UCSZ12) | (1<<UCSZ11) | (1<<UCSZ10); /* data-8bit(011) */ \
    sei(); \
} while(0)

/* 
* Extra pins used by Bluefruit EzKey

PE7 (INT0): <- BAT_SWITCH  Battery active (from USB 5V, active high)
PD6: -> BAT_LED Battery LED (and also Teensy LED)
PE6: -> BF_RESET Bluefruit Reset (active low)
PE3: -> BF_PAIRB Bluefruit Pairing button (active high)
PF0 (ADC0): reserved <- later: BAT_VOLT Battery voltage ADC, check battery
level)
UART:
PD2:(UART RX): <- Serial Bluefruit RX
PD3:(UART TX): -> Serial Bluefruit TX

*/

/*
#define DDR_BAT_SWITCH DDRF
#define PORT_BAT_SWITCH PORTF
#define BIT_BAT_SWITCH 3
#define PIN_BAT_SWITCH PINF

#define DDR_BAT_LED DDRF
#define PORT_BAT_LED PORTF
#define BIT_BAT_LED 2

#define DDR_BF_RESET DDRF
#define PORT_BF_RESET PORTF
#define BIT_BF_RESET 1

#define DDR_BAT_VOLT DDRF
#define PORT_BAT_VOLT PORTF
#define BIT_BAT_VOLT 0

*/

#define DDR_BF_PAIRB DDRD
#define PORT_BF_PAIRB PORTD
#define BIT_BF_PAIRB 6



/* 
CapsLock / NumLock / ScrolLock LED pin config 
for LED.c
PE1: -> CapsLock LED
PC3: -> ScrollLock LED
PC1: -> NumLock LED 
*/

#define DDR_CAPSLCK DDRE
#define PORT_CAPSLCK PORTE
#define BIT_CAPSLCK 1
 
#define DDR_NUMLAYER DDRC
#define PORT_NUMLAYER PORTC
#define BIT_NUMLAYER 1
 
#define DDR_EXTRA_LAYER DDRC
#define PORT_EXTRA_LAYER PORTB
#define BIT_EXTRA_LAYER 3

/*#define DDR_ESC DDRB
#define PORT_ESC PORTB
#define BIT_ESC 0*/

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

#endif

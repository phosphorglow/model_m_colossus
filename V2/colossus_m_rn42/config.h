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
#define DESCRIPTION     t.m.k firmware for Colossus Model M Controller V2.0

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

/* A few tweaks to make the mousekeys slower and easier... */
#define MOUSEKEY_TIME_TO_MAX 50
#define MOUSEKEY_MAX_SPEED 6
#define MOUSEKEY_WHEEL_MAX_SPEED 8
#define MOUSEKEY_WHEEL_TIME_TO_MAX 60

/* USART configuration
 *     asynchronous, 9600baud, 8-data bit, non parity, 1-stop bit, no flow control
 */
    #define UCSR1D _SFR_MEM8(0xCB)
    #define RTSEN 0
    #define CTSEN 1

    #define SERIAL_UART_BAUD        9600
    #define SERIAL_UART_DATA        UDR1
    #define SERIAL_UART_UBRR        ((F_CPU/(16.0*SERIAL_UART_BAUD)-1+0.5))
    #define SERIAL_UART_RXD_VECT    USART1_RX_vect
    #define SERIAL_UART_TXD_READY   (UCSR1A&(1<<UDRE1))
    #define SERIAL_UART_INIT()      do { \
        UBRR1L = (uint8_t) SERIAL_UART_UBRR;       /* baud rate */ \
        UBRR1H = ((uint16_t)SERIAL_UART_UBRR>>8);  /* baud rate */ \
        UCSR1B |= (1<<RXCIE1) | (1<<RXEN1); /* RX interrupt, RX: enable */ \
        UCSR1B |= (0<<TXCIE1) | (1<<TXEN1); /* TX interrupt, TX: enable */ \
        UCSR1C |= (0<<UPM11) | (0<<UPM10);  /* parity: none(00), even(01), odd(11) */ \
        UCSR1D |= (0<<RTSEN) | (0<<CTSEN);  /* RTS, CTS(no flow control by hardware) */ \
        DDRD |= (1<<1); PORTD &= ~(1<<1);   /* RTS for flow control by firmware */ \
        sei(); \
    } while(0)
    #define SERIAL_UART_RTS_LO()    do { PORTD &= ~(1<<1); } while (0)
    #define SERIAL_UART_RTS_HI()    do { PORTD |=  (1<<1); } while (0)

/* 
CapsLock / NumLock / ScrolLock LED pin config 
for LED.c
PE1: -> ScrollLock LED
PC3: -> CapsLock LED
PC1: -> NumLock LED 
*/

#define DDR_SCROLLLCK DDRE
#define PORT_SCROLLLCK PORTE
#define BIT_SCROLLLCK 1

#define DDR_CAPSLCK DDRC
#define PORT_CAPSLCK PORTC
#define BIT_CAPSLCK 3

#define DDR_NUMLCK DDRC
#define PORT_NUMLCK PORTC
#define BIT_NUMLCK 1



#endif

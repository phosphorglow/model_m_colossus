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

/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"


#ifndef DEBOUNCE
#define DEBOUNCE	0
#endif
static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static matrix_row_t read_cols(void);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);


inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

void matrix_init(void)
{
    // JTAG disable for PORT F. write JTD bit twice within four cycles.
    MCUCR |= (1<<JTD);
    MCUCR |= (1<<JTD);

    // initialize row and col
    unselect_rows();
    init_cols();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }
}

uint8_t matrix_scan(void)
{
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        select_row(i);
        _delay_us(30);  // without this wait read unstable value.
        matrix_row_t cols = read_cols();
        if (matrix_debouncing[i] != cols) {
            matrix_debouncing[i] = cols;
            if (debouncing) {
                debug("bounce!: "); debug_hex(debouncing); debug("\n");
            }
            debouncing = DEBOUNCE;
        }
        unselect_rows();
    }

    if (debouncing) {
        if (--debouncing) {
            _delay_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }

    return 1;
}

bool matrix_is_modified(void)
{
    if (debouncing) return false;
    return true;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        pbin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += bitpop16(matrix[i]);
    }
    return count;
}


 /* Column pin configuration
 * col: 0   1   2   3   4   5   6   7   8   9   a   b   c   d   e   f   g   h   i   j
 * pin: a0  a1  a2  a3  a4  a5  a6  a7  c7  c6  c5  c4  c3  c2  c1  c0  e1  e0  d7  d5	
 */
 static void  init_cols(void)
{
    // Input with pull-up(DDR:0, PORT:1)
    DDRA  &= ~(1<<0 |1<<1 |1<<2 |1<<3 | 1<<4 | 1<<5 | 1<<6 | 1<<7);
    PORTA |=  (1<<0 |1<<1 |1<<2 |1<<3 | 1<<4 | 1<<5 | 1<<6 | 1<<7);
    DDRC  &= ~(1<<7 | 1<<6 | 1<<5 | 1<<4 | 1<<3 | 1<<2 | 1<<1 | 1<<0);
    PORTC |=  (1<<7 | 1<<6 | 1<<5 | 1<<4 | 1<<3 | 1<<2 | 1<<1 | 1<<0);
    DDRE  &= ~(1<<1 | 1<<0);
    PORTE |=  (1<<1 | 1<<0);
    DDRD  &= ~(1<<7 | 1<<5);
    PORTD |=  (1<<7 | 1<<5);  
}

static matrix_row_t read_cols(void)
{
    return (PINA&(1<<0) ? 0 : (1<<0)) |
           (PINA&(1<<1) ? 0 : (1<<1)) |
           (PINA&(1<<2) ? 0 : (1<<2)) |
           (PINA&(1<<3) ? 0 : (1<<3)) |
	   (PINA&(1<<4) ? 0 : (1<<4)) |
           (PINA&(1<<5) ? 0 : (1<<5)) |
           (PINA&(1<<6) ? 0 : (1<<6)) |
           (PINA&(1<<7) ? 0 : (1<<7)) |
           (PINC&(1<<7) ? 0 : (1<<8)) |
           (PINC&(1<<6) ? 0 : (1<<9)) |
           (PINC&(1<<5) ? 0 : (1<<10)) |
           (PINC&(1<<4) ? 0 : (1<<11)) |
           (PINC&(1<<3) ? 0 : (1<<12)) |
           (PINC&(1<<2) ? 0 : (1<<13)) |
           (PINC&(1<<1) ? 0 : (1<<14)) |
           (PINC&(1<<0) ? 0 : (1UL<<15)) |
           (PINE&(1<<1) ? 0 : (1UL<<16)) |
           (PINE&(1<<0) ? 0 : (1UL<<17)) |
           (PIND&(1<<7) ? 0 : (1UL<<18)) |
           (PIND&(1<<5) ? 0 : (1UL<<19));
}

/* row pin configuration
 * row: 0   1   2   3   4   5   6   7   
 * pin: b5  b6  b7  e4  e5  d0  d1  d4    
 */

static void unselect_rows(void)
{
    // Hi-Z(DDR:0, PORT:0) to unselect
    DDRB  &= ~0b11100000;
    PORTB &= ~0b11100000;
    DDRE  &= ~0b00110000;
    PORTE &= ~0b00110000;
    DDRD  &= ~0b00010011;
    PORTD &= ~0b00010011;
}

static void select_row(uint8_t row)
{
    // Output low(DDR:1, PORT:0) to select
    switch (row) {
        case 7:
            DDRD  |= (1<<4);
            PORTD &= ~(1<<4);
            break;
        case 6:
            DDRD  |= (1<<1);
            PORTD &= ~(1<<1);
            break;
        case 5:
            DDRD  |= (1<<0);
            PORTD &= ~(1<<0);
            break;
        case 4:
            DDRE  |= (1<<5);
            PORTE &= ~(1<<5);
            break;
        case 3:
            DDRE  |= (1<<4);
            PORTE &= ~(1<<4);
            break;
        case 2:
            DDRB  |= (1<<7);
            PORTB &= ~(1<<7);
            break;
        case 1:
            DDRB  |= (1<<6);
            PORTB &= ~(1<<6);
            break;
        case 0:
            DDRB  |= (1<<5);
            PORTB &= ~(1<<5);
            break;
    }
}

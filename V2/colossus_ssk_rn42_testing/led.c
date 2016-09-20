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

#include <avr/io.h>
#include "stdint.h"
#include "led.h"
    
/* LED pin configuration defined in config.h
 *
 * Wiring: Port (Sinking GND) <-- Resistor & LED
 * 
 */

 void led_set(uint8_t usb_led)
{
    DDR_CAPSLCK |= (1<<BIT_CAPSLCK);

    if (usb_led & (1<<USB_LED_CAPS_LOCK))
    {
        PORT_CAPSLCK &= ~(1<<BIT_CAPSLCK);
    }
    else
    {
        PORT_CAPSLCK |= (1<<BIT_CAPSLCK);
    }
}

void led_layer_set(uint32_t state) {
    DDR_NUMLAYER |= (1<<BIT_NUMLAYER);
    DDR_EXTRA_LAYER |= (1<<BIT_EXTRA_LAYER);  

    if ((1<<1 & state) != 0) 
    {
        PORT_NUMLAYER &= ~(1<<BIT_NUMLAYER);
    }
    else
    {
        PORT_NUMLAYER |= (1<<BIT_NUMLAYER);
    }

    if ((1<<2 & state) != 0) 
    {
        PORT_EXTRA_LAYER &= ~(1<<BIT_EXTRA_LAYER);
    }
    else
    {
        PORT_EXTRA_LAYER |= (1<<BIT_EXTRA_LAYER);
    }
  
}


/*
Bluefruit Protocol for TMK firmware
Author: Benjamin Gould, 2013
Based on code Copyright 2011 Jun Wako <wakojun@gmail.com>

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

#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"
#include "keyboard.h"
#include "lufa.h"
#include "host.h"
#include "timer.h"
#include "print.h"
#include "debug.h"
#include "sendchar.h"
#include "suspend.h"
#include "bluefruit.h"

int main(void)
{   
    clock_prescale_set(clock_div_1);
    bluefruit_pins_init();  // bluefruit & battery special pins
    USB_Device_EnableSOFEvents();
    print_set_sendchar(sendchar); // set sendchar function for print.

    //debug_keyboard = true;
    //debug_mouse = true;
    /* Disable watchdog if enabled by bootloader/fuses */
    //MCUSR &= ~(1 << WDRF);

    sei(); // interrupt enable?
	
#if defined(INTERRUPT_CONTROL_ENDPOINT)
        ;
#else
        USB_USBTask();
#endif	

    // If battery switch is on and USB unplugged, use BT, else use USB.
    // Soooo... hardware-wise, it's like this:
    // PF0 runs through a 10k resistor to USB 5V. If USB 5V is not
    // present, PF0 gets pulled down to ground through the 10k and a 40k resistor.
    
    _delay_ms(3000); // this delay is only here at the moment because of a stupid hardware decision.
    
    if (!(PINF & (1<<3))) {
      
	USB_Init();
    
	_delay_ms(1000); 

	keyboard_init();

	print("Initializing keyboard...\n"); 
      
    // Turn on Bluefruit using a transistor
        DDRB   = _BV(PB0);
        PORTB |= _BV(PB0);
	 
        host_set_driver(bluefruit_driver());
	
	serial_init();

        while (1) {
            keyboard_task();
        }

    } else {
      
    USB_Init();
    
    _delay_ms(1000);

    print("Initializing keyboard...\n");
    keyboard_init();   
    print("Setting host driver to LUFA...\n");
    host_set_driver(&lufa_driver);
    keyboard_task();
    if (USB_DeviceState != DEVICE_STATE_Configured) {
	  DDR_EXTRA_LAYER ^= (1<<BIT_EXTRA_LAYER);
	  print("USB plugged in, but not configured: assuming charger.\n");
      } else {
    }

#ifdef SLEEP_LED_ENABLE
        sleep_led_init();
#endif
      
      //  Put Bluefruit in RESET state (low)
      //  DDR_BF_RESET |= (1<<BIT_BF_RESET);
      //  PORT_BF_RESET &= ~(1<<BIT_BF_RESET);
        
        // wait an extra second for the PC's operating system
        // to load drivers and do whatever it does to actually
        // be ready for input
        
	_delay_ms(1000);
        print("Main loop");
        while (1) {
            while (USB_DeviceState == DEVICE_STATE_Suspended) {
                suspend_power_down();
                if (USB_Device_RemoteWakeupEnabled && suspend_wakeup_condition()) {
                    USB_Device_SendRemoteWakeup();
                }
            }
            keyboard_task(); 
        }
#if !defined(INTERRUPT_CONTROL_ENDPOINT)
        USB_USBTask();
#endif    
    }
}

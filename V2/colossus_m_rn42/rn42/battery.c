#include <avr/io.h>
#include <util/delay.h>
#include "battery.h"


/*
 * Battery
 */

void battery_init(void)
{
    // blink 
    battery_led(LED_ON);  _delay_ms(500);
    battery_led(LED_OFF); _delay_ms(500);
    battery_led(LED_ON);  _delay_ms(500);
    battery_led(LED_OFF); _delay_ms(500);
    
    // LED indicates charger status
    battery_led(LED_CHARGER);

    // ADC setting for voltage monitor
    // Ref:2.56V band-gap, Input:ADC0(PF0), Prescale:128(16MHz/128=125KHz)
    ADMUX = (1<<REFS1) | (1<<REFS0);
    ADCSRA = (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
    // digital input buffer disable(24.9.5)
//    DIDR0 = (1<<ADC0D) | (1<<ADC4D) | (1<<ADC7D);
//    DIDR1 = (1<<AIN0D);
//    DIDR2 = (1<<ADC8D) | (1<<ADC9D) | (1<<ADC11D) | (1<<ADC12D) | (1<<ADC13D);

    // ADC disable voltage divider(PF4)
    DDRB  |=  (1<<5);
    PORTB |=  (1<<5);
}

// Indicator for battery
void battery_led(battery_led_t val)
{
    if (val == LED_TOGGLE) {
        // Toggle LED
        DDRE  |=  (1<<5);
        PINE  |=  (1<<5);
    } else if (val == LED_ON) {
        // On overriding charger status
        DDRE  |=  (1<<5);
        PORTE &= ~(1<<5);
    } else if (val == LED_OFF) {
        // Off overriding charger status
        DDRE  |=  (1<<5);
        PORTE |=  (1<<5);
    } else {
        // Display charger status
        DDRE  &= ~(1<<5);
        PORTE &= ~(1<<5);
    }
}

bool battery_charging(void)
{
    if (!(USBSTA&(1<<VBUS))) return false;

    // Charger Status:
    //   MCP73831   MCP73832   LTC4054  Status
    //   Hi-Z       Hi-Z       Hi-Z     Shutdown/No Battery
    //   Low        Low        Low      Charging
    //   Hi         Hi-Z       Hi-Z     Charged

    // preserve last register status
    uint8_t ddre_prev  = DDRE;
    uint8_t porte_prev = PORTE;

    // Input with pullup
    DDRE  &= ~(1<<7);
    PORTE |=  (1<<7);
    _delay_ms(1);
    bool charging = PINE&(1<<7) ? false : true;

    // restore last register status
    DDRE  = (DDRE&~(1<<7))  | (ddre_prev&(1<<7));
    PORTE = (PORTE&~(1<<7)) | (porte_prev&(1<<7));

    // TODO: With MCP73831 this can not get stable status when charging.
    // LED is powered from PSEL line(USB or Lipo)
    // due to weak low output of STAT pin?
    // due to pull-up'd via resitor and LED?
    return charging;
}

// Returns voltage in mV
uint16_t battery_voltage(void)
{
    // ADC disable voltage divider(PF4)
    DDRB  |=  (1<<5);
    PORTB &= ~(1<<5);

    volatile uint16_t bat;
    ADCSRA |= (1<<ADEN);
    _delay_ms(1);   // wait for charging S/H capacitance

    ADCSRA |= (1<<ADSC);
    while (ADCSRA & (1<<ADSC)) ;
    bat = ADC;

    ADCSRA &= ~(1<<ADEN);

    // ADC disable voltage divider(PF4)
    DDRB  |=  (1<<5);
    PORTB |=  (1<<5);

    return (bat - BATTERY_ADC_OFFSET) * BATTERY_ADC_RESOLUTION;
}

static bool low_voltage(void) {
    static bool low = false;
    uint16_t v = battery_voltage();
    if (v < BATTERY_VOLTAGE_LOW_LIMIT) {
        low = true;
    } else if (v > BATTERY_VOLTAGE_LOW_RECOVERY) {
        low = false;
    }
    return low;
}

battery_status_t battery_status(void)
{
    if (USBSTA&(1<<VBUS)) {
        /* powered */
        return battery_charging() ? CHARGING : FULL_CHARGED;
    } else {
        /* not powered */
        return low_voltage() ? LOW_VOLTAGE : DISCHARGING;
    }
}

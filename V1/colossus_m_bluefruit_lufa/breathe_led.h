#ifndef BREATHE_LED_H
#define BREATHE_LED_H


#ifdef BREATHE_LED_ENABLE

void breathe_led_init(void);
void breathe_led_enable(void);
void breathe_led_disable(void);
void breathe_led_toggle(void);

#else

#define breathe_led_init()
#define breathe_led_enable()
#define breathe_led_disable()
#define breathe_led_toggle()

#endif

#endif

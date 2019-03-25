#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

FILE lcd_str = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);
int main(void)
{
    lcd_init();
	stderr = &lcd_str;
	fprintf(stderr, "HELLO AVR\n");

	DDRB = 1;
	while(1)
    {
        PORTB ^= 1;
        _delay_ms(100);
    }
}

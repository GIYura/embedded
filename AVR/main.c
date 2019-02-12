#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
    DDRB = 1;
    while(1)
    {
        PORTB ^= 1;
        _delay_ms(150);
    }
    return 0;
}

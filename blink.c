#define F_CPU 20000000UL

// PB1

#include<util/delay.h>
#include<avr/io.h>


int main(void) {
    // PORTB
    DDRB |= (1 << DDB5);
    DDRB |= (1 << DDB1);
    while (1) {
        PORTB |= (1 << PB5);
        PORTB &= ~(1 << PB5);
        _delay_ms(500);
        PORTB |= (1 << PB1);
        PORTB &= ~(1 << PB5);
        _delay_ms(500);
        PORTB &= ~(1 << PB5);
     }
 }

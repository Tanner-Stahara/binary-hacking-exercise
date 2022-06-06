#define F_CPU 16000000UL

#include<util/delay.h>
#include<avr/io.h>

uint8_t read_number(void) {
    uint8_t out = 0;
    uint8_t digit = 0;
    PORTF |= (1 << PF4);
    while(digit < 4) {
        if (!(PINF & (1 << PINF6))) {
            out = out << 1;
            out |= 1;
            digit += 1;
            PORTF |= (1 << PF1);
            _delay_ms(300);
        } else if (!(PINF & (1 << PINF5))) {
            out = out << 1;
            digit += 1;
            PORTF |= (1 << PF2);
            _delay_ms(300);
        }
        PORTF &= ~(1 << PF1);
        PORTF &= ~(1 << PF2);
        _delay_ms(50);
    }
    PORTF &= ~(1 << PF1);
    PORTF &= ~(1 << PF2);
    PORTF &= ~(1 << PF3);
    PORTF &= ~(1 << PF4);
    return out;
}

void send_code (uint8_t code) {
    PORTJ &= ~(1 << PJ1);
    _delay_ms(20);
    if(code & (1 << 0)) {
        PORTJ |= (1 << PJ0);
    } else {
        PORTJ &= ~(1 << PJ0);
    }
    if(code & (1 << 1)) {
        PORTH |= (1 << PH1);
    } else {
        PORTH &= ~(1 << PH1);
    }
    if(code & (1 << 2)) {
        PORTH |= (1 << PH0);
    } else {
        PORTH &= ~(1 << PH0);
    }
    if(code & (1 << 3)) {
        PORTD |= (1 << PD3);
    } else {
        PORTD &= ~(1 << PD3);
    }

    PORTJ |= (1 << PJ1);
}

int main(void) {

    DDRB |= (1 << DDB7);
    DDRF |= (1 << DDF1);
    DDRF |= (1 << DDF2);
    DDRF |= (1 << DDF3);
    DDRF |= (1 << DDF4);

    DDRJ |= (1 << DDJ1);  // CLOCK
    DDRJ |= (1 << DDJ0);  // bit 0
    DDRH |= (1 << DDH1);  // bit 1
    DDRH |= (1 << DDH0);  // bit 2
    DDRD |= (1 << DDD3);  // bit 3

    PORTJ &= ~(1 << PJ1);

    while (1) {
        for (uint8_t code = 0; code < 16; code++) {
            send_code(code);
            PORTF &= ~(1 << PF1);
            PORTF &= ~(1 << PF2);
            PORTF &= ~(1 << PF3);
            PORTF &= ~(1 << PF4);
            PORTF |= (code << 1);
            _delay_ms(20);
        }
    }
}

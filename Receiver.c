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
 
int main(void) {
 
   // uint8_t correct_code = 0b1010;

    DDRF |= (1 << DDF1);
    DDRF |= (1 << DDF2);
    DDRF |= (1 << DDF3);
    DDRF |= (1 << DDF4);
	DDRF |= (1 << DDF0);

	uint8_t digit0 = 0;
	uint8_t digit1 = 0;
	uint8_t digit2 = 0;
	uint8_t digit3 = 0;
	uint8_t current_code = 0;
 
    uint8_t correct_code = read_number();

    while (1) {
		if (!(PIND & (1 << PIND3))) {
			current_code = 0;
			if (!(PINH & (1 << PINH0))) {
				digit0 = 1;
				current_code += 1;
			} else {
				digit0 = 0;
			}
			if (!(PINH & (1 << PINH1))) {
				digit1 = 1;
				current_code += 2;
			} else {
				digit1 = 0;
			}
			if (!(PINJ & (1 << PINJ0))) {
				digit2 = 1;
				current_code += 4;
			} else {
				digit2 = 0;
			}
			if (!(PINJ & (1 << PINJ1))) {
				digit3 = 1;
				current_code += 8;
			} else {
				digit3 = 0;
			}
		}
		
		if (current_code == correct_code) {
			PORTF |= (1 << PF0);
		} else { 
			PORTF &= ~(1 << PF0);
		}
		
        PORTF |= (digit0 << PF1); 
		PORTF |= (digit1 << PF2); 
		PORTF |= (digit2 << PF3); 
		PORTF |= (digit3 << PF4); 
        _delay_ms(500);
        PORTF &= ~(1 << PF1);
        PORTF &= ~(1 << PF2);
        PORTF &= ~(1 << PF3);
        PORTF &= ~(1 << PF4);
        _delay_ms(500);
     }   
 }
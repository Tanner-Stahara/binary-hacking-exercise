#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include<util/delay.h>

int main(void) {
    while(1) {
        _delay_ms(1000);
    }   
    return 0;
}

#!/bin/bash
set -e
avr-gcc -mmcu=atmega2560 -Wall -O2 -o program.out "$1" 
avr-objcopy -j .text -O ihex program.out program.hex
sudo avrdude -p atmega2560 -c stk500 -P /dev/ttyACM0 -U flash:w:program.hex:i -D 

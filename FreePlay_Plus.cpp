/**
 * @file FreePlay_Plus.cpp
 * 
 * @version 2.2
 * @author Eric Conner (Eric@EricConner.net)
 * @copyright Copyright (c) 2013-2021 EricConner.net
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
 * THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <avr/io.h>
#include <util/delay.h>

#define COIN 0x01
#define P2 0x02
#define P1 0x04
#define X2 0x10

#define shortDelay 100
#define longDelay 500

void coinPulse(int pulse_number = 1) {
	for (int i = 0; i < pulse_number; i++) {
		PORTB &= ~COIN;
		_delay_ms(shortDelay);
		PORTB |= COIN;
		_delay_ms(shortDelay);
	}
}

void output(int player) {
	int coins = 0;
	
	if (player == P2) {
		coins = 2;
	} else {
		coins = 1;
	}
	
	_delay_ms(shortDelay);
	
	if ((PINB & X2) == 0) {
		coinPulse(coins * 2);
	} else {
		coinPulse(coins);
	}
	
	DDRB |= player;
	PORTB &= ~player;
	_delay_ms(shortDelay);
	
	PORTB |= player;
	DDRB &= ~player;
	_delay_ms(longDelay);
}

int main(void) {
	DDRB = 0x01;
	PORTB = 0x1F;
	
	while (1) {
		if ((PINB & P1) == 0) {
			output(P1);
		} else if ((PINB & P2) == 0) {
			output(P2);
		}
	}
}

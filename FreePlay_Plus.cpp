/*
  Author:   Eric Conner
  Date:     05-01-2013
  Project:  Arcade FreePlay+
  Version:  v2.2
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

/*
 * timer0.c
 *
 * Created: 10/10/2023 6:07:47 pm
 *  Author: 2023 CS/EE209 T5
 */ 
#include "cpu.h"
#include "timer0.h"
#include "display.h"

#define F_CPU 2000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

void timer0_init() {
	TCCR0A = 0b00000010; // WGM0[2..0]: Waveform Generation Mode set to 010 (Clear on Compare Match with OCR0A as Top)
	TCCR0B = 0b00000100; // CS0[2..0]: Clock Select set to 100 (I/O Clock/256)
	OCR0A = 38; //
}

ISR(TIMER0_COMPA_vect) {
	send_next_character_to_display();
}


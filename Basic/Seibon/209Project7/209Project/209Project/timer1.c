/*
 * timer1.c
 *
 * Created: 10/10/2023 6:28:44 pm
 *  Author: Jenny W
 */ 
#define F_CPU 2000000UL
// timer1.c

#include "timer1.h"
#include "adc.h"  // Include the ADC module header if needed
#include <avr/io.h>
#include <avr/interrupt.h>

void timer1_init() {
	// Configure Timer1 for CTC (Clear Timer on Compare Match) mode
	TCCR1B |= (1 << WGM12);

	// Set the prescaler to 256
	TCCR1B |= (1 << CS12);

	// Set the value for 0.02ms (50 kHz) interval (adjust as needed)
	OCR1A = 100;  // 2000000 / (256 * 50k) = 156.25, so OCR1A = 156 - 1
	// Enable Timer1 Compare Match A interrupt
	TIMSK1 |= (1 << OCIE1A);
}

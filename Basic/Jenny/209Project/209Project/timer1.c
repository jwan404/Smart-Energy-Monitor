/*
 * timer1.c
 *
 * Created: 10/10/2023 6:28:44 pm
 *  Author: Jenny W
 */ 
// timer1.c
#include "cpu.h"
#include "timer1.h"
#include "adc.h"  // Include the ADC module header if needed
#include "energyCalculations.h"
#include "display.h"
#include "uart.h"
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

uint16_t channel = 0;

void timer1_init() {
	// Configure Timer1 for CTC (Clear Timer on Compare Match) mode
	TCCR1B |= (1 << WGM12);

	// Set the prescaler to 256
	TCCR1B |= (1 << CS12);

	// Set the value for 2ms interval
	OCR1A = 14;
	
	EICRA |= (1 << ISC01) | (1 << ISC00); // Rising edge trigger
	// Enable INT0 external interrupt
	EIMSK |= (1 << INT0);
}


ISR	(INT0_vect){
	// Start ADC conversion on channel 0
	ADMUX = 0b01000000;
	ADCSRA |= (1 << ADSC);
	
	// Set the prescaler to 256
	TCCR1B |= (1 << CS12);
}



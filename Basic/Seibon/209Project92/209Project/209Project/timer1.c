/*
 * timer1.c
 *
 * Created: 10/10/2023 6:28:44 pm
 *  Author: 2023 CS/EE209 T5
 */ 
// timer1.c
#include "cpu.h"
#include "timer1.h"
#include "adc.h"
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

uint16_t channel = 0;

void timer1_init() {
	// Configure Timer1 for CTC (Clear Timer on Compare Match) mode
	TCCR1B |= (1 << WGM12) | (1 << CS10);

	// Set the value for 0.1ms interval
	OCR1A = 199;
	
	EICRA |= (1 << ISC01) | (1 << ISC00); // Rising edge trigger
	
	//Enable INT0 external interrupt
	EIMSK |= (1 << INT0);
}


ISR	(INT0_vect){

	TCNT1 = 0; //Writing the counter value to 0
	ADCSRA |= (1 << ADSC); //For starting conversions
	EIMSK &= ~(1 << INT0); //External interrupt enable
}



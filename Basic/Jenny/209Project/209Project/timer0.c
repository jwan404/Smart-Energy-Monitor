/*
 * timer0.c
 *
 * Created: 10/10/2023 6:07:47 pm
 *  Author: Jenny W
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
	TCCR0A = 0b00000010;
	TCCR0B = 0b00000100;
	OCR0A = 195;
}



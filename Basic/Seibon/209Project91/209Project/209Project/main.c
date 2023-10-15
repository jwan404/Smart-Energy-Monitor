/*
 * 209Project.c
 *
 * Created: 10/10/2023 1:11:47 pm
 * Author : 2023 CS/EE209 T5
 */ 

//Our .h files
#include "cpu.h"
#include "uart.h"
#include "adc.h"
#include "display.h"
#include "timer0.h"
#include "timer1.h"
#include "energyCalculations.h"


//Libraries
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint16_t Vac[NUM_SAMPLES] = {};
volatile uint16_t IL[NUM_SAMPLES] = {};



int main(void)
{
	uart_init(9600);
	adc_init();
	timer0_init();
	timer1_init();
	init_display();
	
	// Enable Timer1 Compare Match A interrupt
	TIMSK1 |= (1 << OCIE1A);
	
	sei();
    /* Replace with your application code */
    while (1) 
    {
		//send_next_character_to_display();
		//_delay_ms(500);
	 }
	  
}


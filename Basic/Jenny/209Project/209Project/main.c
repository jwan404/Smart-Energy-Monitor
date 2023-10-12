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
#include "globals.h"


//Libraries
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

const uint8_t NUM_SAMPLES = 100;
extern uint16_t Vac[NUM_SAMPLES] = {};
extern uint16_t IL[NUM_SAMPLES] = {};

float Vref = 2.1;  // Assuming a 2.1V reference voltage


int main(void)
{
	uart_init(9600);
	adc_init();
	timer0_init();
	timer1_init();
	init_display();
	
	sei();
    /* Replace with your application code */
    while (1) 
    {
	
		  
	 }
	  
}


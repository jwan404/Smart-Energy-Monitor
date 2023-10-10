/*
 * 209Project.c
 *
 * Created: 10/10/2023 4:04:06 pm
 * Author : skim641
 */ 

//Our .h files
#include "uart.h"
#include "adc.h"

//Libraries
#include <avr/io.h>


int main(void)
{
	//Initializing:
	uart_init();
	adc_init();
	DDRB = 0b00110011;
	DDRC = 0b01111111;
	DDRD = 0b00000000;
	
	/* Replace with your application code */
	while (1)
	{
		
	}
}
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
	//Initializing registers:
	uart_init();
	adc_init();
	DDRB = 0b00110011;
	DDRC = 0b01111111;
	DDRD = 0b00000000;
	
	//Initializing variables:
	volatile uint8_t channel; //for ADC
	volatile uint16_t voltage;
	volatile uint16_t current;
	volatile uint16_t power;
	volatile uint8_t digit[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; //segment patterns
		
	
	/* Replace with your application code */
	while (1)
	{
		//Get voltage, current and power from ADC
		channel = 0;
		voltage = adc_read(channel);
		channel = 1;
		current = adc_read(channel)/0.5; //Voltage across shunt resistor, divided by shunt resistor value
		power = voltage * current;
		
		//Displaying info on LCD
		
		
		//Displaying info via UART
	}
}
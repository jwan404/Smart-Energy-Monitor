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
#include <stdio.h>


int main(void)
{
	//Initializing registers:
	uart_init(9600);
	adc_init();
	DDRB = 0b00110011;
	DDRC = 0b01111111;
	DDRD = 0b00000000;
	
	//Initializing variables:
	volatile uint8_t channel; //for ADC
	volatile uint8_t voltage;
	volatile uint8_t current;
	volatile uint8_t power;
	volatile uint8_t energy;
	//volatile uint8_t digit[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; //segment patterns
		
	
	/* Replace with your application code */
	while (1)
	{
		//Get voltage, current and power from ADC
		channel = 0;
		voltage = (adc_read(channel)*5/1024-2.1)/(0.5/22);
		channel = 1;
		current = (adc_read(channel)/0.5*5/1024-2.1)/(0.5/22); //Voltage across shunt resistor, divided by shunt resistor value
		power = voltage * current;
		
		//Displaying info on LCD and via UART (based on progress review work)
		char voltage_char[50];
		char current_char[50];
		char power_char[50];
		char energy_char[50];
		
		sprintf(voltage_char, "RMS Voltage is: %d.%d\n\r", (uint8_t) voltage, (uint8_t) (voltage * 10) % 10);
		sprintf(current_char, "Peak Current is: %d\n\r", (uint8_t) current);
		sprintf(power_char, "Power is: %d.%d%d\n\r\n\r", (uint8_t)power, (uint8_t) (power * 10) % 10, (uint8_t) (power * 100) % 10);
	}
}
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



int main(void)
{
	uart_init(9600);
	init_display();	
	adc_init();
	timer0_init();
	timer1_init();
	
	// Access Vrms and Ipk
	uint16_t localVrms = Vrms;
	uint16_t localIpk = Ipk;
	uint16_t localPower = power;
	
	// Variables for ADC results
//	uint16_t local_adc_result = adc_result;
	
	// Variables for calculations
	uint16_t local_sum = sum;
	uint16_t local_sum_I = sum_I;
	
	
	// Create character array for each parameter
	char voltage_char[50];
	char current_char[50];
	char power_char[50];
	
	// Stores information inside of character array
	sprintf(voltage_char, "RMS Voltage is: %d.%d\n\r", (uint16_t) localVrms, (uint16_t) (localVrms * 10.0) % 10);
	sprintf(current_char, "Peak Current is: %d\n\r", (uint16_t) localIpk);
	sprintf(power_char, "Power is: %d.%d%d\n\r\n\r", (uint16_t)localPower, (uint16_t) (localPower * 10.0) % 10, (uint16_t) (localPower * 100.0) % 10);
	
	sei();
    /* Replace with your application code */
    while (1) 
    {
		// Transmit array to terminal.
		trans_array(voltage_char);
		trans_array(current_char);
		trans_array(power_char);
		
		// Delay by 1 second
		_delay_ms(1000);
		
		// Load Vrms value into the display buffer
		Vrms = sqrt(local_sum / NUM_SAMPLES);
		separate_and_load_characters((uint16_t)(Vrms * 100), 1);
		send_next_character_to_display();

		_delay_ms(1000);

		uint16_t Irms = sqrt(local_sum_I / NUM_SAMPLES);
		Ipk = calculateIpk(Irms);
		separate_and_load_characters((uint16_t)(Ipk * 100), 1);
		send_next_character_to_display();
		
		_delay_ms(1000);
		
		power = calculatePower(Vrms, Irms);
		separate_and_load_characters((uint16_t)(power * 100), 1);
		send_next_character_to_display();
	 }
	  
}


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

float Vref;
volatile float Vrms;
volatile float Ipk;
volatile float power;
// Variables for ADC results
volatile float adc_result;
// Variables for calculations
uint16_t Vac[NUM_SAMPLES];
extern volatile uint16_t adc0_result[NUM_SAMPLES];
uint16_t IL[NUM_SAMPLES];
extern volatile uint16_t adc1_result[NUM_SAMPLES];
 volatile float sum;
 volatile float sum_I;
 volatile float voltage_mv;


int main(void)
{
	uart_init(9600);
	init_display();	
	adc_init();
	timer0_init();
	timer1_init();
	
	// Create character array for each parameter
	char voltage_char[50];
	char current_char[50];
	char rmsCurrent_char[50];
	char power_char[50];
	
	 	
	// Initialize Timer0 for 10ms interrupt intervals
	TIMSK0 |= (1 << OCIE0A); // Enable Timer0 overflow interrupt

	sei();
	
    /* Replace with your application code */
    while (1) 
    {
		
		//Do conversion
		for (uint8_t i = 0; i < NUM_SAMPLES; i++)
		{
			Vac[i] = (adc_convert_mv((adc0_result[i]) * 20.5) * 1.05);
			IL[i] = (adc_convert_mv((adc1_result[i])/ 1.1));
		}
		
		// Calculate Vrms and Irms
		 	for (uint8_t k = 0; k < NUM_SAMPLES; k++) {
		 		sum += Vac[k] * Vac[k];
		 		sum_I += IL[k] * IL[k];
			}
		
		// 	Load Vrms value into the display buffer
		Vrms = sqrt(sum / NUM_SAMPLES);
		uint16_t localVrms = Vrms;
		
		float Irms = sqrt(sum_I / NUM_SAMPLES);
		uint16_t localIrms = Irms;
		Ipk = calculateIpk(Irms);
		uint16_t localIpk = Ipk;
		
		power = calculatePower(Vrms, Irms);
		uint16_t localPower = power / 100;
		
		// Stores information inside of character array
		sprintf(voltage_char, "RMS Voltage is: %d%d.%d\n\r", (uint16_t) (localVrms / 100), (uint16_t) (localVrms / 10.0) % 10, (uint16_t) (localVrms % 10));
		sprintf(current_char, "Peak Current is: %d mA\n\r", (uint16_t) localIpk);
		sprintf(rmsCurrent_char, "RMS Current is: %d mA\n\r",(uint16_t) localIrms);
		sprintf(power_char, "Power is: %d.%d%d\n\r\n\r", (uint16_t)(localPower / 100), (uint16_t) (localPower / 10.0) % 10, (uint16_t) (localPower % 10));
		
		// Transmit array to terminal.
		trans_array(voltage_char);
		//Load Vrms value into the display buffer
		separate_and_load_characters((uint16_t)(localVrms), 2);
		_delay_ms(100);

		trans_array(current_char);
		trans_array(rmsCurrent_char);
		//uint16_t Irms = sqrt(local_sum_I / NUM_SAMPLES);
		separate_and_load_characters((uint16_t)(localIpk), 0);
		_delay_ms(100);
		
		separate_and_load_characters((uint16_t)(localPower), 1);
		trans_array(power_char);
	 	_delay_ms(100);
		 
		 _delay_ms(1000);

		sum = 0;
		sum_I = 0;
	 }
	 
	  
}


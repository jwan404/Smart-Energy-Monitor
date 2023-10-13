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
#include <math.h>
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

float Vref = 2.1;
uint16_t channel = 0;

void timer1_init() {
	// Configure Timer1 for CTC (Clear Timer on Compare Match) mode
	TCCR1B |= (1 << WGM12);

	// Set the prescaler to 256
	//TCCR1B |= (1 << CS12);

	// Set the value for 2ms interval
	OCR1A = 14;

	// Enable Timer1 Compare Match A interrupt
	TIMSK1 |= (1 << OCIE1A);
	
	EICRA |= (1 << ISC01) | (1 << ISC00); // Rising edge trigger

	// Enable INT0 external interrupt
	EIMSK |= (1 << INT0);
}

ISR(TIMER1_COMPA_vect) {
	// This code will be executed every 0.002ms

	// Variables for ADC results
	uint16_t adc_result_ch0;
	uint16_t adc_result_ch1;

	// Variables for calculations
	uint16_t Vac[NUM_SAMPLES];
	uint16_t IL[NUM_SAMPLES];
	uint16_t sum = 0;
	uint16_t sum_I = 0;
	uint16_t voltage_0_mv = 0;
	uint16_t voltage_ch0 = 0;
	uint16_t voltage_1_mv= 0;
	uint16_t voltage_ch1 = 0;

	for (int i = 0; i < NUM_SAMPLES; i++)
	{
		if (channel == 0)
		{
			adc_result_ch0 = adc_read_channel_single_conversion(channel);
			//Convert adc to mv
			voltage_0_mv = adc_convert_mv(adc_result_ch0);
			
			// Calculate voltage for each channel
			voltage_ch0 = (voltage_0_mv * 1000) * Vref / 1024.0;
			
			// Calculate Vac for the i-th sample
			Vac[i] = (voltage_ch0) / ((1/23) * 1.12)/*(Gvs * Gvo)*/;
			channel = 1;
		} 
		else if (channel == 1)
		{
		 adc_result_ch1 = adc_read_channel_single_conversion(channel);
		//Convert adc to mv
		 voltage_1_mv = adc_convert_mv(adc_result_ch1);
		 
		 // Calculate voltage for each channel
		 voltage_ch1 = (voltage_1_mv * 1000) * Vref / 1024.0;
		 
		 // Calculate Vac for the i-th sample
		 IL[i] =  (((voltage_ch1) / 0.5 * 2.2)/*(Gis * Gio)*/ / 0.5);
		  channel = 0;
		}
		
	}
	
	// Calculate Vrms and Irms
	for (uint8_t i = 0; i < NUM_SAMPLES; i++) {
		sum += Vac[i] * Vac[i];
		sum_I += IL[i] * IL[i];
	}

	uint16_t Vrms = sqrt(sum / NUM_SAMPLES);
	
//	uint16_t power = calculatePower(Vrms, Irms);
//	uint16_t energy = calculateEnergy(power, 0.002); // Modify the time as needed

	// Load Vrms value into the display buffer
	separate_and_load_characters((uint16_t)(Vrms * 100), 1);
	send_next_character_to_display();

	//separate_and_load_characters(1456, 1);
	uint16_t Irms = sqrt(sum_I / NUM_SAMPLES);
	uint16_t Ipk = calculateIpk(Irms);
	separate_and_load_characters((uint16_t)(Ipk * 100), 1);
	send_next_character_to_display();
/*	// Transmit Vrms, Ipk, power, and energy through UART
	trans_float(Vrms);
	trans_float(Ipk);
	trans_float(power);
	trans_float(energy); */

	// Send the characters to the display
	
}

ISR	(INT0_vect){
	TCCR1B |= (1 << CS12);  // Start Timer1 with a prescaler of 256

	
}



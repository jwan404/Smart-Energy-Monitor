/*
 * adc.c
 *
 * Created: 10/10/2023 1:14:58 pm
 *  Author: skim641
 */ 

//Code from ADC lab
#include "cpu.h"
#include "adc.h"
#include "energyCalculations.h"
#include "display.h"
#include "timer1.h"

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>

float Vref = 2.1;
	uint16_t Vrms = 0;
	uint16_t Ipk = 0;
	uint16_t power = 0;
	// Variables for ADC results
	uint16_t adc_result;
	
	// Variables for calculations
	uint16_t Vac[NUM_SAMPLES];
	uint16_t IL[NUM_SAMPLES];
	uint16_t sum = 0;
	uint16_t sum_I = 0;

void adc_init() {
	ADMUX = 0b01000010;
	ADCSRA = 0b11000100;
	ADCSRB = 0b00000000;
	DIDR0 = 0b00000000;
}

uint16_t adc_read_channel_single_conversion(uint8_t channel) {
	ADMUX &= 0xF0; //Clear channel selection
	//ADMUX |= channel; //Set the channel to convert
	ADMUX |= channel;
	ADCSRA |= (1 << ADSC); //Starting an ADC conversion
	while ((ADCSRA & (1 << ADIF)) == 0) { //ADIF bit is checked to see if it is 0
		; //If ADIF bit is not 1, wait until it becomes 1
	}
	return ADC; //Alternatively you can write return ADC;
}

// Function to convert raw ADC count to millivolts (mV)
uint16_t adc_convert_mv(uint16_t raw_adc_value) {

	// Calculate the voltage resolution in millivolts (mV) per ADC count
	float voltage_resolution_mV = Vref / 1024.0;  // 10-bit ADC

	// Calculate the voltage value in millivolts (mV) from the raw ADC count
	uint16_t voltage_mV = (uint16_t)(raw_adc_value * voltage_resolution_mV);

	return voltage_mV;
}

ISR(ADC_vect) {
	// This code will be executed every 0.002ms
	
	// Variables to track the current channel
	static uint8_t channel = 0;

	for (int i = 0; i < NUM_SAMPLES; i++) {
		// Read from the current channel
		adc_result = adc_read_channel_single_conversion(channel);

		// Convert adc to mV
		uint16_t voltage_mv = adc_convert_mv(adc_result);

		// Calculate Vac or IL for the i-th sample based on the channel
		if (channel == 0) {
			// Calculate Vac
			Vac[i] = (voltage_mv * 1000) / ((1/23) * 1.12);
			} else {
			// Calculate IL
			IL[i] = ((voltage_mv * 1000) / (0.5 * 2.2)) / 0.5;
		}

		// Switch to the other channel
		channel = (channel == 0) ? 1 : 0;
	}

	// Calculate Vrms and Irms
	for (uint8_t i = 0; i < NUM_SAMPLES; i++) {
		sum += Vac[i] * Vac[i];
		sum_I += IL[i] * IL[i];
	}
// 	Load Vrms value into the display buffer
// 		Vrms = sqrt(sum / NUM_SAMPLES);
// 		separate_and_load_characters((uint16_t)(Vrms * 100), 1);
// 		send_next_character_to_display();
// 	
// 		_delay_ms(100);
// 	
// 		uint16_t Irms = sqrt(sum_I / NUM_SAMPLES);
// 		Ipk = calculateIpk(Irms);
// 		separate_and_load_characters((uint16_t)(Ipk * 100), 1);
// 		send_next_character_to_display();
// 		
// 		_delay_ms(100);
// 		
// 		power = calculatePower(Vrms, Irms);
// 		separate_and_load_characters((uint16_t)(power * 100), 1);
// 		send_next_character_to_display();

}	

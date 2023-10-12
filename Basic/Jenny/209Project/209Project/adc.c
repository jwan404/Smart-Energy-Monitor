/*
 * adc.c
 *
 * Created: 10/10/2023 1:14:58 pm
 *  Author: skim641
 */ 

//Code from ADC lab
#include "cpu.h"
#include "adc.h"

#include <avr/io.h>
#include <stdint.h>

void adc_init() {
	ADMUX = 0b01000010;
	ADCSRA = 0b10000100;
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
	// Define the ADC reference voltage (Vref) in volts
	float Vref = 2.1;  // Assuming a 2.1V reference voltage

	// Calculate the voltage resolution in millivolts (mV) per ADC count
	float voltage_resolution_mV = Vref / 1024.0;  // 10-bit ADC

	// Calculate the voltage value in millivolts (mV) from the raw ADC count
	uint16_t voltage_mV = (uint16_t)(raw_adc_value * voltage_resolution_mV);

	return voltage_mV;
}
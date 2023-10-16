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

extern float Vref;
extern volatile float Vrms;
extern volatile float Ipk;
extern volatile float power;
// Variables for ADC results
extern volatile float adc_result;
// Variables for calculations
extern uint16_t Vac[NUM_SAMPLES];
extern uint16_t IL[NUM_SAMPLES];
extern volatile float sum;
extern volatile float sum_I;

extern volatile float voltage_mv;

volatile uint16_t adc0_result[NUM_SAMPLES];
volatile uint16_t adc1_result[NUM_SAMPLES];


void adc_init() {
	// setting Vcc
	ADMUX |= (1 << REFS0);
	// enabling adc and autotriggering with prescaler of 8
	ADCSRA |= (1 << ADEN) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADATE) | (1 << ADIE);
	ADCSRB |= (1 << ADTS1) | (1 << ADTS0);
}

float adc_read_channel_single_conversion(uint8_t channel) {
	ADMUX &= 0xF0; //Clear channel selection
	ADMUX |= channel;
	
	return ADC; //Alternatively you can write return ADC;
}

// Function to convert raw ADC count to millivolts (mV)
float adc_convert_mv(float raw_adc_value) {

	// Calculate the voltage resolution in millivolts (mV) per ADC count
	float voltage_resolution_mV = 5000 / 1024.0;  // 10-bit ADC

	// Calculate the voltage value in millivolts (mV) from the raw ADC count
	float voltage_mV = (float)(raw_adc_value * voltage_resolution_mV - 2100);

	return voltage_mV;
}

ISR(ADC_vect) {
	// This code will be executed every 0.1ms

	// Variables to track the current channel
	
	for (uint8_t i = 0; i < NUM_SAMPLES; i++) {
		adc0_result[i] = adc_read_channel_single_conversion(0);
// 		voltage_mv = adc_convert_mv(adc_result);
// 		Vac[i] = ((voltage_mv ) * 23);

	}
	for (uint8_t j = 0; j < NUM_SAMPLES; j++) {
		adc1_result[j] = adc_read_channel_single_conversion(1);
// 		voltage_mv = adc_convert_mv(adc_result);
// 		IL[j] = ((voltage_mv ) / 1.12);
	}

	


	//clearing compare match
	TIFR0 |= (1 << OCF0A);
}	

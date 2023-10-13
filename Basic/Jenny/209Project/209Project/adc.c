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
#include "timer1.h"

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

float Vref = 2.1;
uint8_t i = 0;

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
		if (ADMUX = 0b01000000)
		{
			adc_result_ch0 = adc_read_channel_single_conversion(0);
			//Convert adc to mv
			voltage_0_mv = adc_convert_mv(adc_result_ch0);
			
			// Calculate voltage for each channel
			voltage_ch0 = (voltage_0_mv * 1000) ;
			
			// Calculate Vac for the i-th sample
			Vac[i] = (voltage_ch0) / ((1/23) * 1.12)/*(Gvs * Gvo)*/;
			
			ADMUX = 0b01000001;
		}
		else if (ADMUX = 0b01000001)
		{
			adc_result_ch1 = adc_read_channel_single_conversion(1);
			//Convert adc to mv
			voltage_1_mv = adc_convert_mv(adc_result_ch1);
			
			// Calculate voltage for each channel
			voltage_ch1 = (voltage_1_mv * 1000);
			
			// Calculate Vac for the i-th sample
			IL[i] =  (((voltage_ch1) / 0.5 * 2.2)/*(Gis * Gio)*/ / 0.5);
		}
	}
	
	// Calculate Vrms and Irms
	for (uint8_t i = 0; i < NUM_SAMPLES; i++) {
		sum += Vac[i] * Vac[i];
		sum_I += IL[i] * IL[i];
	}
	//Load Vrms value into the display buffer
	uint16_t Vrms = sqrt(sum / NUM_SAMPLES);
	separate_and_load_characters((uint16_t)(Vrms * 100), 1);
	send_next_character_to_display();
	
	_delay_ms(1000);
	
	//separate_and_load_characters(1456, 1);
	uint16_t Irms = sqrt(sum_I / NUM_SAMPLES);
	uint16_t Ipk = calculateIpk(Irms);
	separate_and_load_characters((uint16_t)(Ipk * 100), 1);
	send_next_character_to_display();
	
	//	uint16_t power = calculatePower(Vrms, Irms);
	//	uint16_t energy = calculateEnergy(power, 0.002); // Modify the time as neede
	
/*	// Transmit Vrms, Ipk, power, and energy through UART
	trans_float(Vrms);
	trans_float(Ipk);
	trans_float(power);
	trans_float(energy); */

}
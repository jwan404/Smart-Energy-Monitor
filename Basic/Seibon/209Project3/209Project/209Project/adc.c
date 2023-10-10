/*
 * adc.c
 *
 * Created: 10/10/2023 1:14:58 pm
 *  Author: skim641
 */ 

//Code from ADC lab

#include "adc.h"

#include <avr/io.h>
#include <stdint.h>

void adc_init(){
	ADMUX = 0b01000010;
	ADCSRA = 0b10000100;
	ADCSRB = 0b00000000;
	DIDR0 = 0b00000000;
}

uint16_t adc_read(uint8_t chan){
	//Set channel
	ADMUX &= 0xF0;
	if (chan == 1){
		ADMUX |= 0x01;
		}else if (chan == 0){
		ADMUX |= 0x00;
		}else{
		ADMUX |= 0x02;
	}
	//Start ADC conversion
	ADCSRA |= (1 << ADSC);
	//Polls for conversion to finish
	while((ADCSRA & (1<<ADIF)) == 0){
		;
	}
	//Read+return ADC result
	return ((ADCL << 0) | (ADCH << 8));
}

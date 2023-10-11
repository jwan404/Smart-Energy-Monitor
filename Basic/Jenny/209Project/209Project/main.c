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

//Libraries
#include <avr/io.h>
volatile uint16_t Vac[101] = {};

int main(void)
{
	uart_init(9600);
	adc_init();
	timer0_init();
	timer1_init();
    /* Replace with your application code */
    while (1) 
    {
		// Read ADC value from channel 2 (modify as needed)
		for (int i = 0; i < 100; i++)
		{
			Vac[i] = (ADC0Value[i] * (5/1024) - 2.1) / (Gvs*Gvo); // Display this value
		}
		uint16_t adc_result = adc_read_channel_single_conversion(0);
		uint16_t adc_result = adc_read_channel_single_conversion(1);

    }
}


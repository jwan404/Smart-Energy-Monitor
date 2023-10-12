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

//Libraries
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#define NUM_SAMPLES 100

volatile uint16_t Vac[NUM_SAMPLES] = {};
volatile uint16_t IL[NUM_SAMPLES] = {};

float Vref = 2.1;  // Assuming a 2.1V reference voltage


int main(void)
{
	uart_init(9600);
	adc_init();
	timer0_init();
	timer1_init();
	init_display();
	
    /* Replace with your application code */
    while (1) 
    {
		
		 for (int i = 0; i < NUM_SAMPLES; i++)
		 {
			 // Wait for Timer1 to reach the desired interval (0.02ms)
			 while (!(TIFR1 & (1 << OCF1A)));

			 // Clear Timer1 Compare Match A flag
			 TIFR1 |= (1 << OCF1A);
			 
			 uint16_t adc_result_ch0 = adc_read_channel_single_conversion(0);
			 uint16_t adc_result_ch1 = adc_read_channel_single_conversion(1);

			 // Calculate voltage for each channel
			 float voltage_ch0 = adc_result_ch0 * Vref / 1024.0;
			 float voltage_ch1 = adc_result_ch1 * Vref / 1024.0;

			 // Calculate Vac for the i-th sample
			 Vac[i] = (voltage_ch0) / (0.1 * 1)/*(Gvs * Gvo)*/;
			 IL[i] =  (((voltage_ch1) / (0.5 * 2)/*(Gvs_1 * Gvo_1)*/) / 0.5);
			 
		 }

		 // Calculate Vrms using Riemann sum
		 float sum = 0.0;
		 float sum_I = 0.0;
		 for (int i = 0; i < NUM_SAMPLES; i++) {
			 sum += Vac[i] * Vac[i];
			 sum_I = IL[i] * IL[i];
		 }

		 float Vrms = sqrt(sum / NUM_SAMPLES);
		 float Irms = sqrt(sum_I / NUM_SAMPLES);
		 float Ipk = Irms * (sqrt(2));
		 
		 // Calculate power and energy (modify as needed)
		 float power = Vrms * Irms;  // Calculate power based on Vrms and Irms
		 float energy = power * 0.002;  // Calculate energy based on power and time
		 
		 // Load Vrms value into the display buffer
		 separate_and_load_characters((uint16_t)(Vrms * 100), 2);
		 separate_and_load_characters((uint16_t)(Ipk * 100), 2);
		 
		  // Transmit Vrms, Ipk, power, and energy through UART
		  trans_float(Vrms);
		  trans_float(Ipk);
		  trans_float(power);
		  trans_float(energy);

		 // Send the characters to the display
		 send_next_character_to_display();
	 }
	  
}


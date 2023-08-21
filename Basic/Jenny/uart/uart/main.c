/*
 * uart.c
 *
 * Created: 21/08/2023 3:53:25 pm
 * Author : Jenny W
 */ 

#define   PeakVoltage    14.5
#define   PeakCurrent   125
#define   Power         1.60
#include "uart.h"
#include "cpu.h"
#include <avr/io.h> //Needed for using the macros for register addresses
#include <string.h> //Needed for using strlen()
#include <util/delay.h> //Needed for using _delay_ms()
#include <stdio.h>
#include <stdint.h>

int main(void)
{
	 uart_init(9600); //Initializing the UART to 9600 baud, 8N1, with no parity
	 
   while (1) 
    {
		// Convert floating-point values to integers for digit extraction
		uint16_t peak_voltage = PeakVoltage * 10; // Convert to integer (X.YZ -> XYZ)
		uint16_t peak_current = PeakCurrent;
		uint16_t power_int = Power * 100; // Convert to integer (X.YZ -> XYZ)
		
        // Variables to store extracted digits as characters
		char rmsDigit1, rmsDigit2, rmsDigit3;
		extract_digits(peak_voltage, &rmsDigit1, &rmsDigit2, &rmsDigit3);

		char peakDigit1, peakDigit2, peakDigit3;
		extract_digits(peak_current, &peakDigit1, &peakDigit2, &peakDigit3);

		char powerDigit1, powerDigit2, powerDigit3;
		extract_digits(power_int, &powerDigit1, &powerDigit2, &powerDigit3);
		
		// Transmit each digit to the terminal.
		uart_transmit_array("RMS Voltage is: ");
		uart_transmit_byte(rmsDigit1);
		uart_transmit_byte(rmsDigit2);
		uart_transmit_byte('.');
		uart_transmit_byte(rmsDigit3);
		
		uart_transmit_array("\n\r");
		
		uart_transmit_array("Peak Current is: ");
		uart_transmit_byte(peakDigit1);
		uart_transmit_byte(peakDigit2);
		uart_transmit_byte(peakDigit3);
		
		uart_transmit_array("\n\r");
		
		uart_transmit_array("Power is: ");
		uart_transmit_byte(powerDigit1);
		uart_transmit_byte('.');
		uart_transmit_byte(powerDigit2);
		uart_transmit_byte(powerDigit3);
		
		uart_transmit_array("\n\r");
		uart_transmit_array("\n\r");

		_delay_ms(1000); // Delay by 1 second
    } 
}


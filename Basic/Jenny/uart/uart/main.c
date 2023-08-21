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
	char voltage_char[50];
	char current_char[50];
	char power_char[50];
		
	sprintf(voltage_char, "RMS Voltage is: %d.%d\n\r", (uint8_t) PeakVoltage, (uint8_t) (PeakVoltage * 10.0) % 10);
	sprintf(current_char, "Peak Current is: %d\n\r", (uint8_t) PeakCurrent);
	sprintf(power_char, "Power is: %d.%d%d\n\r\n\r", (uint8_t)Power, (uint8_t) (Power * 10.0) % 10, (uint8_t) (Power * 100.0) % 10);


   while (1) 
    {
		
		uart_transmit_array(voltage_char);
		uart_transmit_array(current_char);
		uart_transmit_array(power_char);

		_delay_ms(1000); // Delay by 1 second
    } 
}


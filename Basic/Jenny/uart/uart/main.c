/*
 * uart.c
 *
 * Created: 21/08/2023 3:53:25 pm
 * Author : Jenny W
 */ 

#define   PeakVoltage    14.5
#define   PeakCurrent   125
#define   Power         1.60
#include <avr/io.h> //Needed for using the macros for register addresses
#include <string.h> //Needed for using strlen()
#include <util/delay.h> //Needed for using _delay_ms()
#include <stdio.h>
#include <stdint.h>
#include "cpu.h"

int main(void)
{
	 uart_init(9600); //Initializing the UART to 9600 baud, 8N1, with no parity
	 
   while (1) 
    {
		uart_transmit_array("RMS Voltage is: ");
		uart_transmit_byte('.');
		// uart_transmit_array("\n\r")
		uart_transmit_byte(10);
		uart_transmit_byte(13);
		uart_transmit_array("Peak current is: ");
		uart_transmit_byte(10);
		uart_transmit_byte(13);
		uart_transmit_array("Power is: ");
		uart_transmit_byte(10);
		uart_transmit_byte(13);
		_delay_ms(1000);
    } 
}


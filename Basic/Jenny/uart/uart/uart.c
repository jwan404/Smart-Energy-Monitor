/*
 * uart.c
 *
 * Created: 21/08/2023 4:57:55 pm
 *  Author: Jenny W
 */ 
#include "cpu.h"
#include "uart.h"
#include <avr/io.h> //Needed for using the macros for register addresses
#include <string.h> //Needed for using strlen()
#include <util/delay.h> //Needed for using _delay_ms()
#include <stdio.h>
#include <stdint.h>

void uart_init(uint32_t baud_rate){
	UCSR0A = 0b00000000; //None of the settings here are used
	UCSR0B = 0b00001000; //Set TXEN0 bit to 1 (enable transmit) and UCSZ02 bit to 0 (8 data bits)
	//To improve readability we should aim to write this in the form "UCSR0B = (1<<TXEN0);"
	UCSR0C = 0b00000110; //UMSEL0[1..0]=00 (UART mode), UPM0[1..0]=00 (no parity),
	//USBS0=0 (1 stop-bit), UCSZ0[1..0]=11 (8 data bits)
	UBRR0 = 2000000 / (16 * baud_rate) - 1;
	//Set UBRR0 as per baud rate formula
}

void uart_transmit_byte(char byte){
	while ((UCSR0A & 0b00100000) == 0){ //UDRE0 bit is checked to see if it is 0
		; //If UDRE0 bit is not 0, wait until it becomes 0
	}
	//Put the byte to be sent into the UDR0 register
	UDR0 = byte;
}

//This function transmits an array of bytes via the UART using uart_transmit_byte(char byte) function
void uart_transmit_array(char* msg){
	//Loop through each byte in the array
	for (uint8_t i = 0; i < strlen(msg); i++){
		uart_transmit_byte(msg[i]); //Transmit each byte using uart_transmit_byte(char byte)
	}
}

uint16_t extract_digits(uint16_t number, uint16_t index){
	
	
}
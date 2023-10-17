/*
 * uart.c
 *
 * Created: 10/10/2023 1:14:29 pm
 *  Author: 2023 CS/EE209 T5
 */ 

//Code from ADC lab
#include "cpu.h"
#include "uart.h"
#include <avr/io.h>
#include <string.h>

void uart_init(uint32_t baud){
	UCSR0A = 0b00000000; //UDRE0 (Data Register Empty) is set to 0
	UCSR0B = 0b00001000; //TXEN0 (Transmitter Enable) is set to 1
	UCSR0C = 0b00000110; //UCSZ0[1..0]: Character Size = 8-bits
	UBRR0 = 2000000/(16*baud)-1; 
}
void trans_byte(char byte){
	while ((UCSR0A & 0b00100000) == 0){ //Wait until UDR0 is ready for new data
		;
	}
	UDR0 = byte; //Load the ASCII value of character to UDR0
}
void trans_array(char* msg){
	for (uint8_t i = 0; i < strlen(msg); i++){
		trans_byte(msg[i]);
	}
}


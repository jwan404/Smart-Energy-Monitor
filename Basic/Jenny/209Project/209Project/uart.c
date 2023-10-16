/*
 * uart.c
 *
 * Created: 10/10/2023 1:14:29 pm
 *  Author: skim641
 */ 

//Code from ADC lab
#include "cpu.h"
#include "uart.h"
#include <avr/io.h>

void uart_init(uint32_t baud){
	UCSR0A = 0b00000000;
	UCSR0B = 0b00001000;
	UCSR0C = 0b00000110;
	UBRR0 = 2000000/(16*baud)-1;
}
void trans_byte(char byte){
	while ((UCSR0A & 0b00100000) == 0){
		;
	}
	UDR0 = byte;
}
void trans_array(char* msg){
	for (uint8_t i = 0; i < strlen(msg); i++){
		trans_byte(msg[i]);
	}
}

void trans_float(uint16_t value) {
	char buffer[20];
	snprintf(buffer, sizeof(buffer), "%f\n", value);
	trans_array(buffer);
}
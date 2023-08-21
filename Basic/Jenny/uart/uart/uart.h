/*
 * uart.h
 *
 * Created: 21/08/2023 4:58:11 pm
 *  Author: Jenny W
 */ 

#include <stdint.h>

#ifndef UART_H_
#define UART_H_
void uart_init(uint32_t baud_rate);
void uart_transmit_byte(char byte);
void uart_transmit_array(char* msg);
uint16_t extract_digits(uint16_t number, uint16_t index);

#endif /* UART_H_ */
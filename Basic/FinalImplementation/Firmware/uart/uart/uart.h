/*
 * uart.h
 *
 * Created: 21/08/2023 4:58:11 pm
 *  Author: Jenny W
 */ 

#include <stdint.h>

#ifndef UART_H_
#define UART_H_
void uart_init(uint32_t baud_rate); // sets baud rate
void uart_transmit_byte(char byte); // transmit byte
void uart_transmit_array(char* msg); // transmit array
#endif /* UART_H_ */
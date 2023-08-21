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
void extract_digits(int number, char *digit1, char *digit2, char *digit3);
#endif /* UART_H_ */
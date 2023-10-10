/*
 * uart.h
 *
 * Created: 10/10/2023 1:14:50 pm
 *  Author: skim641
 */ 


#ifndef UART_H_
#define UART_H_

#include <stdint.h>

void uart_init(uint32_t baud);
void trans_byte(char byte);
void trans_array(char* msg);

#endif /* UART_H_ */
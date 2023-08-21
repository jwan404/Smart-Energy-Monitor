/*
 * uart.c
 *
 * Created: 21/08/2023 3:53:25 pm
 * Author : Jenny W, Seibon K
 */ 

#define F_CPU 2000000UL //Defining system clock frequency
#include <avr/io.h> //Needed for using the macros for register addresses
#include <string.h> //Needed for using strlen()
#include <util/delay.h> //Needed for using _delay_ms()

#define RMSVoltage 14.5 //Format XX.X
#define PeakCurrent 125 //Format XXX
#define Power 1.60  //Format X.XX
​
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
void extract_char_digits(char *digits, float value){
	//Multiples value by 100 then converts to string
    char strValue[7];
    value *= 100;
	int intValue = (int) value;
	scanf("%d", &intValue);
	sprintf(strValue, "%d", intValue);
	//Adds the first 3 digits to the digits array
	for (int i = 0; i < 3; i++){
    	digits[i] = strValue[i];
    }	
}
//This function transmits an array of bytes via the UART using uart_transmit_byte(char byte) function
void uart_transmit_array(char* msg){
	//Loop through each byte in the array
	for (uint8_t i = 0; i < strlen(msg); i++){
		uart_transmit_byte(msg[i]); //Transmit each byte using uart_transmit_byte(char byte)
	}
}
​
int main() {
	
	uart_init(9600);
	while (1)
	{ 
		//Initialise arrays for three different values
		char digits1[3], digits2[3]; digits3[3];
		extract_char_digits(digits1, RMSVoltage);
		extract_char_digits(digits2, PeakCurrent);
		extract_char_digits(digits3, Power);

		//Print out voltage info
		uart_transmit_array("RMS Voltage is: ");
		uart_transmit_byte(digits1[0]);
		uart_transmit_byte(digits1[1]);
		uart_transmit_byte('.')
		uart_transmit_byte(digits1[2]);
		uart_transmit_array("\n\r");

		//Print out current info
		uart_transmit_array("Peak Current is: ");
		uart_transmit_byte(digits2[0]);
		uart_transmit_byte(digits2[1]);
		uart_transmit_byte(digits2[2]);
		uart_transmit_array("\n\r");

		//Print out power info
		uart_transmit_array("Power is: ");
		uart_transmit_byte(digits3[0]);
		uart_transmit_byte('.')
		uart_transmit_byte(digits3[1]);
		uart_transmit_byte(digits3[2]);
		uart_transmit_array("\n\r");
    }
		 
}


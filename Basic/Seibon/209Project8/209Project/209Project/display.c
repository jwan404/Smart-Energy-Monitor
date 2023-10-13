/*
 * display.c
 *
 * Created: 10/10/2023 5:38:36 pm
 *  Author: Jenny W
 */ 
#include "display.h"
#include <avr/io.h>
#include <avr/interrupt.h>

const uint8_t seg_pattern[10]={0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111};

//4 characters to be displayed on Ds1 to Ds 4
static volatile uint8_t disp_characters[4]={0,0,0,0};

//The current digit (e.g. the 1's, the 10's) of the 4-digit number we're displaying
static volatile uint8_t disp_position = 0;	

void init_display(void){
	//TODO: Finish this function
	//Configure DDR bits of the I/O pins connected to the display
	// Configure shift register control pins as outputs
	DDRC |= (1 << PORTC3) | (1 << PORTC4) | (1 << PORTC5);
	//Ds 1, Ds 2, Ds 3, Ds 4
	
	DDRD |= (1 << PORTD4) | (1 << PORTD5) | (1 << PORTD6) | (1 << PORTD7);
	//SHCP = 3 SHST = 5 SHDS = 4
}

//Populate the array ‘disp_characters[]’ by separating the four digits of ‘number’
//and then looking up the segment pattern from ‘seg_pattern[]’
void separate_and_load_characters(uint16_t number, uint8_t decimal_pos){
	
	// Separate each digit from ‘number’, and assign segment pattern to each digit
	// e.g. if value to display is 1230 the separated digits will be '1’, ‘2’, ‘3’ and ‘0’
	disp_characters[0] = seg_pattern[(number / 1000) % 10];
	disp_characters[1] = seg_pattern[(number / 100) % 10];
	disp_characters[2] = seg_pattern[(number / 10) % 10];
	disp_characters[3] = seg_pattern[number % 10];
	
	//if statement for decimal point.
	if (decimal_pos == disp_position) {
		disp_characters[disp_position] |= (1 << 7); // Set the decimal point bit
	}
}

void send_next_character_to_display(void){
	//TODO: finish this function
	// Ensure SH_CP and SH_ST are both set to logic 0
	PORTC &= ~(1 <<	PORTC3);
	PORTC &= ~(1 << PORTC5);
	//1. Based on ‘disp_position’, load the digit to send to a local variable
	uint8_t digit;
	digit = disp_characters[disp_position];
	
	
	PORTD |= (1 << PORTD4) | (1 << PORTD5) |(1 << PORTD6) |(1 << PORTD7);
	//2. Send this bit pattern to the shift-register as in Q2.2
	// Shift out the bits to the shift register
	for (int8_t i = 7; i >= 0; i--) {
		// Set the SH_DS pin to be either "0" or "1" as per the bit being transferred to the shift register
		if (digit & (1 << i)) {
			PORTC |= (1 << PORTC4);
			} else {
			PORTC &= ~(1 << PORTC4);
		}

		// Toggle the SH_CP pin on (i.e., "1") and off (i.e., "0") to "shift in" this bit to the shift register
		PORTC |= (1 << PORTC3);
		PORTC &= ~(1 << PORTC3);
	}
	//4. Latch the output by toggling SH_ST pin as in Q2.2
	// Toggle the SH_ST pin on (i.e., "1") and off (i.e., "0") to latch the output
	PORTC |= (1 << PORTC5);
	PORTC &= ~(1 << PORTC5);
	
	//5. Now, depending on the value of pos, enable the correct digit
	switch (disp_position)
	{
		case 0:
		PORTD &= ~(1 << PORTD4);
		break;
		case 1:
		PORTD &= ~(1 << PORTD5);
		break;
		case 2:
		PORTD &= ~(1 << PORTD6);
		break;
		case 3:
		PORTD &= ~(1 << PORTD7);
		break;
		default:
		break;
	}
	
	
	// (i.e. set Ds1, Ds2, Ds3 and Ds4 appropriately)
	//6. Increment ‘disp_position’ so the next of the 4 digits will be displayed
	// when function is called again from ISR (reset ‘disp_position’ after 3)
	disp_position++;

	// Reset ‘disp_position’ after 3 to start over
	if (disp_position >= 4) {
		disp_position = 0;
	}
}
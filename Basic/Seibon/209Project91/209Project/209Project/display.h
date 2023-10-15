/*
 * display.h
 *
 * Created: 10/10/2023 5:38:51 pm
 *  Author: Jenny W
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_
#include <stdint.h>


void init_display(void);
void separate_and_load_characters(uint16_t number, uint8_t decimal_pos);
void send_next_character_to_display(void);



#endif /* DISPLAY_H_ */
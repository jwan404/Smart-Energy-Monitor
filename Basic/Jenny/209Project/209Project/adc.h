/*
 * adc.h
 *
 * Created: 10/10/2023 1:15:15 pm
 *  Author: skim641
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void adc_init();
uint16_t adc_read(uint8_t chan);

#endif /* ADC_H_ */
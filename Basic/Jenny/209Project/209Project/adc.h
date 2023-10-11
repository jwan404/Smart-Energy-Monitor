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
uint16_t adc_read_channel_single_conversion(uint8_t channel);
uint16_t adc_convert_mv(uint16_t raw_adc_value);

#endif /* ADC_H_ */
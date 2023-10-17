/*
 * adc.h
 *
 * Created: 10/10/2023 1:15:15 pm
 *  Author: 2023 CS/EE209 T5
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void adc_init();
float adc_read_channel_single_conversion(uint8_t channel);
float adc_convert_mv(float raw_adc_value);





#endif /* ADC_H_ */
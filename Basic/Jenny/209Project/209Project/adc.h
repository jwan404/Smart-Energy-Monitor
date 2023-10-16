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
float adc_read_channel_single_conversion(uint8_t channel);
float adc_convert_mv(float raw_adc_value);

extern float Vref;
extern volatile float Vrms;
extern volatile float Ipk;
extern volatile float power;
// Variables for ADC results
extern volatile float adc_result;
// Variables for calculations
extern volatile uint16_t Vac[NUM_SAMPLES];
extern volatile uint16_t IL[NUM_SAMPLES];
extern volatile float sum;
extern volatile float sum_I;

extern volatile float voltage_mv;



#endif /* ADC_H_ */
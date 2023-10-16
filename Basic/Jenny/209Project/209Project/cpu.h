/*
 * cpu.h
 *
 * Created: 10/10/2023 4:18:10 pm
 *  Author: Jenny W
 */ 


#ifndef CPU_H_
#define CPU_H_
#define F_CPU 2000000UL 
#include <stdint.h>
#define NUM_SAMPLES 50

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

#endif /* CPU_H_ */
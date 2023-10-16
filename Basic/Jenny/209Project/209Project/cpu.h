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
extern volatile uint16_t Vrms;
extern volatile uint16_t Ipk;
extern volatile uint16_t power;
// Variables for ADC results
extern volatile uint16_t adc_result;
// Variables for calculations
extern volatile uint16_t Vac[NUM_SAMPLES];
extern volatile uint16_t IL[NUM_SAMPLES];
extern volatile uint16_t sum;
extern volatile uint16_t sum_I;

extern volatile uint16_t voltage_mv;

#endif /* CPU_H_ */
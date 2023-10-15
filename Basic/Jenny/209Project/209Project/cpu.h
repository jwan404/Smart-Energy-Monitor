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
#define NUM_SAMPLES 100

extern float Vref;
extern uint16_t Vrms;
extern uint16_t Ipk;
extern uint16_t power;
// Variables for ADC results
extern uint16_t adc_result;
// Variables for calculations
extern uint16_t Vac[NUM_SAMPLES];
extern uint16_t IL[NUM_SAMPLES];
extern uint16_t sum;
extern uint16_t sum_I;

#endif /* CPU_H_ */
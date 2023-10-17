/*
 * energyCalculations.c
 *
 * Created: 12/10/2023 6:31:55 pm
 *  Author: Jenny W
 */ 
// energyCalculations.c
#include "cpu.h"
#include "energyCalculations.h"
#include "adc.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>

// uint16_t Vac[NUM_SAMPLES];
// uint16_t IL[NUM_SAMPLES];

// uint16_t calculateVrms(uint16_t* samples, uint8_t numSamples) {
// 	uint32_t sum = 0;
// 
// 	for (uint8_t i = 0; i < numSamples; i++) {
// 		sum += (uint32_t)samples[i] * samples[i];
// 	}
// 
// 	return sqrt(sum / numSamples);
// }
// 
// uint16_t calculateIrms(uint16_t* samples, uint8_t numSamples) {
// 	uint32_t sum = 0;
// 
// 	for (uint8_t i = 0; i < numSamples; i++) {
// 		sum += (uint32_t)samples[i] * samples[i];
// 	}
// 
// 	return sqrt(sum / numSamples);
// }

float calculateIpk(float Irms) {
	return Irms * sqrt(2);
}

float calculatePower(float Vrms, float Irms) {
	return Vrms * Irms;
}



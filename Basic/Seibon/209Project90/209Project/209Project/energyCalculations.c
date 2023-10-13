/*
 * energyCalculations.c
 *
 * Created: 12/10/2023 6:31:55 pm
 *  Author: Jenny W
 */ 
// energyCalculations.c
#include "energyCalculations.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>

uint16_t calculateVrms(uint16_t* samples, uint8_t numSamples) {
	uint32_t sum = 0;

	for (uint8_t i = 0; i < numSamples; i++) {
		sum += (uint32_t)samples[i] * samples[i];
	}

	return sqrt(sum / numSamples);
}

uint16_t calculateIrms(uint16_t* samples, uint8_t numSamples) {
	uint32_t sum = 0;

	for (uint8_t i = 0; i < numSamples; i++) {
		sum += (uint32_t)samples[i] * samples[i];
	}

	return sqrt(sum / numSamples);
}

uint16_t calculateIpk(uint16_t Irms) {
	return Irms * sqrt(2);
}

uint16_t calculatePower(uint16_t Vrms, uint16_t Irms) {
	return Vrms * Irms;
}

uint16_t calculateEnergy(uint16_t power, uint16_t time) {
	return power * time;
}

/*
 * energyCalculations.h
 *
 * Created: 12/10/2023 6:32:15 pm
 *  Author: Jenny W
 */ 


#ifndef ENERGYCALCULATIONS_H_
#define ENERGYCALCULATIONS_H_
#include <stdint.h>



uint16_t calculateVrms(uint16_t* samples, uint8_t numSamples);
uint16_t calculateIrms(uint16_t* samples, uint8_t numSamples);
float calculateIpk(float Irms);
float calculatePower(float Vrms, float Irms);


#endif /* ENERGYCALCULATIONS_H_ */
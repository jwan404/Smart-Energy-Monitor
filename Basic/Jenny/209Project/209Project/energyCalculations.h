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
uint16_t calculateIpk(uint16_t Irms);
uint16_t calculatePower(uint16_t Vrms, uint16_t Irms);
uint16_t calculateEnergy(uint16_t power, uint16_t time);


#endif /* ENERGYCALCULATIONS_H_ */
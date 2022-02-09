/*
 * TMC2660.h
 *
 *  Created on: Jan 26, 2022
 *      Author: simon
 */
#pragma once

#include "main.h"

#ifndef INC_TMC2660_H_
#define INC_TMC2660_H_


#define DRVCTRL 0
#define CHOPCONF 1
#define SMARTEN 2
#define SGCSCONF 3
#define DRVCONF 4

struct TMC2660{

	uint32_t registers[5];

	uint32_t response;
};

void TMC2660_Init(SPI_HandleTypeDef *hspi);
void TMC2660_SPI_TransmitReceive(SPI_HandleTypeDef *hspi, uint32_t data, struct TMC2660 *motor, uint8_t motor_index);


#endif /* INC_TMC2660_H_ */

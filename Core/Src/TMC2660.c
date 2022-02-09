/*
 * TMC2660.c
 *
 *  Created on: Jan 26, 2022
 *      Author: simon
 */

#include "TMC2660.h"
#include "main.h"

struct TMC2660 motor[3];

void TMC2660_Init(SPI_HandleTypeDef *hspi){
	for(uint8_t i = 0; i < 2; i++){
		motor[i].registers[DRVCTRL] = 0x00000;		//Set up registers
		motor[i].registers[CHOPCONF] = 0x90131;
		motor[i].registers[SMARTEN] = 0xA0000;
		motor[i].registers[SGCSCONF] = 0xD051F;
		motor[i].registers[DRVCONF] = 0xEF03F;


		for(uint8_t j = 0; j < 5; i++){						// Trasmit init for every register in every driver
			TMC2660_SPI_TransmitReceive(hspi, motor[i].registers[j], motor, i);
		}
	}
}

void TMC2660_SPI_TransmitReceive(SPI_HandleTypeDef *hspi, uint32_t data, struct TMC2660 *motor, uint8_t motor_index){


	uint8_t pRxData[3];
	uint8_t pData[3];
	pData[0] = (data & 0xFF0000) >> 16;
	pData[1] = (data & 0x00FF00) >> 8;
	pData[2] = data & 0x0000FF;

	switch(motor_index) {
	case 0:
		HAL_GPIO_WritePin(CS_Azi_GPIO_Port, CS_Azi_Pin, GPIO_PIN_RESET);
		HAL_SPI_TransmitReceive(hspi, pData, pRxData, 3, 10);
		HAL_GPIO_WritePin(CS_Azi_GPIO_Port, CS_Alt_Pin, GPIO_PIN_SET);
		break;

	case 1:
		HAL_GPIO_WritePin(CS_Alt_GPIO_Port, CS_Alt_Pin, GPIO_PIN_RESET);
		HAL_SPI_TransmitReceive(hspi, pData, pRxData, 3, 10);
		HAL_GPIO_WritePin(CS_Alt_GPIO_Port, CS_Alt_Pin, GPIO_PIN_SET);
		break;
	/*
	case 2:
		HAL_GPIO_WritePin(CS_Pol_GPIO_Port, CS_Pol_Pin, GPIO_PIN_RESET);
		HAL_SPI_TransmitReceive(hspi1, pData, pRxData, 3, 10);
		HAL_GPIO_WritePin(CS_Pol_GPIO_Port, CS_Pol_Pin, GPIO_PIN_SET);
		break;
	*/
	}
	motor[motor_index].response = ((uint32_t)pRxData[0]) << 16;
}

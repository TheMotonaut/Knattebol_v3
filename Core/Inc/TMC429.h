/*
 * TMC429.h
 *
 *  Created on: Jan 26, 2022
 *      Author: simon
 */
#pragma once

#include "main.h"

#ifndef INC_TMC429_H_
#define INC_TMC429_H_

//Addresses
#define X_TARGET 		0x0
#define V_MIN 			0x2
#define V_MAX 			0x3
#define V_TARGET 		0x4
#define A_MAX 			0x6
#define PROP 			0x9
#define MODE 			0xA
#define PULSE_RAMP 		0xC
#define IF_CONFIG_429 	0x34
#define GLOBAL_PAR 		0x3F

//Reg bits
#define EN_SD 			0x20
#define EN_RFR 			0x80
#define SDO_INT 		0x2
#define INV_REF 		0x1
#define MOT1R 			0x200000
#define REFMUX 			0x100000

struct TMC429{
	struct Motor{
		int32_t x_target;
		int32_t x_actual;
		uint32_t v_min;
		uint32_t v_max;
		int32_t v_target;
		uint32_t acc_max;
		uint32_t mode;
		uint32_t p_mul;
		uint32_t p_div;
		uint32_t pulse_div;
		uint32_t ramp_div;
	}motors[3];


	uint32_t if_configuration_429;
	uint32_t stpdiv_429;
	uint32_t response;
}controller;

void TMC429_Init(SPI_HandleTypeDef *hspi);
void TMC429_Set_X_Target(SPI_HandleTypeDef *hspi, uint8_t motor_index);
void TMC429_Set_Vel_Target(SPI_HandleTypeDef *hspi, uint8_t motor_index);
void TMC429_Set_Vel_Min(SPI_HandleTypeDef *hspi, uint8_t motor_index);
void TMC429_Set_Vel_Max(SPI_HandleTypeDef *hspi, uint8_t motor_index);
void TMC429_Set_Acc_Max(SPI_HandleTypeDef *hspi, uint8_t motor_index);
void TMC429_Register_Write(SPI_HandleTypeDef *hspi, uint8_t address, uint32_t data);
void TMC429_Register_Read(SPI_HandleTypeDef *hspi, uint8_t address);
uint8_t TMC429_CheckFollow();




#endif /* INC_TMC429_H_ */

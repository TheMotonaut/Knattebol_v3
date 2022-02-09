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
#define X_TARGET 0x0
#define V_MIN 0x2
#define V_MAX 0x3
#define V_TARGET 0x4
#define A_MAX 0x6
#define PROP 0x9
#define MODE 0xA
#define PULSE_RAMP 0xC
#define IF_CONFIG_429 0x4
#define GLOBAL_PAR 0xF



struct TMC429{
	struct Motor{
		uint32_t x_target;
		uint32_t x_actual;
		uint32_t v_min;
		uint32_t v_max;
		uint32_t v_target;
		uint32_t acc_max;
		uint32_t mode[3];
		uint32_t p_mul;
		uint32_t p_div;
		uint32_t pulse_div;
		uint32_t ramp_di;
	}motors[3];



	uint32_t if_configuration_429;
	uint32_t stpdiv_429;
	uint32_t response;
}controller;

void TMC429_If_Conf(SPI_HandleTypeDef *hspi);
void TMC429_Set_X_Target(SPI_HandleTypeDef *hspi, uint8_t motor_index);
void TMC429_Set_Vel_Target(SPI_HandleTypeDef *hspi, uint8_t motor_index);
void TMC429_Set_Vel_Min(SPI_HandleTypeDef *hspi, uint8_t motor_index);
void TMC429_Set_Vel_Max(SPI_HandleTypeDef *hspi, uint8_t motor_index);
void TMC429_Set_Acc_Max(SPI_HandleTypeDef *hspi, uint8_t motor_index);
void TMC429_Register_Write(SPI_HandleTypeDef *hspi, uint8_t address, uint32_t data);
void TMC429_Register_Read(SPI_HandleTypeDef *hspi, uint8_t address);




#endif /* INC_TMC429_H_ */
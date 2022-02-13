/*
 * TMC429.c
 *
 *  Created on: Jan 26, 2022
 *      Author: simon
 */

#include "TMC429.h"
#include "main.h"

#define FOLLOW_MASK 0b00010101

void TMC429_Init(SPI_HandleTypeDef *hspi){
	uint32_t data = 0;

	for(uint8_t i = 0; i < 3; i++){
		controller.motors[i].x_target = 0x0;
		controller.motors[i].v_min = 0x0;
		controller.motors[i].v_max = 0x0;
		controller.motors[i].v_target = 0x0;
		controller.motors[i].p_div = 0x0;
		controller.motors[i].p_mul = 0x0;
		controller.motors[i].mode = 0x0;
		controller.motors[i].pulse_div = 0x0;
		controller.motors[i].ramp_div = 0x0;
		controller.motors[i].acc_max = 0x0;

		data = controller.motors[i].pulse_div << 4;
		data = (data|controller.motors[i].ramp_div) << 8;

		TMC429_Register_Write(hspi, (i<<5)|(PROP << 1), data);

		TMC429_Set_Vel_Min(hspi, i);
		TMC429_Set_Vel_Max(hspi, i);
		TMC429_Set_Acc_Max(hspi, i);
	}
	controller.if_configuration_429 = EN_SD;
	controller.stpdiv_429 = 0x0;

	TMC429_Register_Write(hspi, IF_CONFIG_429, controller.if_configuration_429);
	TMC429_Register_Write(hspi,GLOBAL_PAR , controller.stpdiv_429 << 8);
}

void TMC429_Set_X_Target(SPI_HandleTypeDef *hspi, uint8_t motor_index){
	uint8_t address = X_TARGET;

	address = (motor_index << 5)|(address << 1);

	TMC429_Register_Write(hspi, address, controller.motors[motor_index].x_target);
}

void TMC429_Set_Vel_Target(SPI_HandleTypeDef *hspi, uint8_t motor_index){
	uint8_t address = V_TARGET;

	address = (motor_index << 5)|(address << 1);
	TMC429_Register_Write(hspi, address, controller.motors[motor_index].v_target);
}

void TMC429_Set_Vel_Min(SPI_HandleTypeDef *hspi, uint8_t motor_index){
	uint8_t address = V_MIN;

	address = (motor_index << 5)|(address << 1);
	TMC429_Register_Write(hspi, address, controller.motors[motor_index].v_min);
}

void TMC429_Set_Vel_Max(SPI_HandleTypeDef *hspi, uint8_t motor_index){
	uint8_t address = V_MAX;

	address = (motor_index << 5)|(address << 1);
	TMC429_Register_Write(hspi, address, controller.motors[motor_index].v_max);
}

void TMC429_Set_Acc_Max(SPI_HandleTypeDef *hspi, uint8_t motor_index){
	uint8_t address = A_MAX;

	// BASED ON TRINAMIC steprocker code

	int32_t pdiv, pmul, pm, pd;
	float p, p_reduced;
	int32_t ramp_div = controller.motors[motor_index].ramp_div;
	int32_t pulse_div = controller.motors[motor_index].pulse_div;

	if(ramp_div >= pulse_div){
		p = controller.motors[motor_index].acc_max / (128.0 * (1 << (ramp_div - pulse_div)));
	}else{
		p = controller.motors[motor_index].acc_max / (128.0 / (1 << (ramp_div - pulse_div)));
	}

	p_reduced = p * 0.988; //Magic Number

	for(pdiv = 0; pdiv <= 13; pdiv++){
		pmul = (int32_t)(p_reduced * 8.0 * (1 << pdiv)) - 128;

	    if((0 <= pmul) && (pmul <= 127)){
	      pm = pmul + 128;
	      pd = pdiv;
	    }
	}

	uint32_t data = (pm << 8)|pd;

	controller.motors[motor_index].p_div = pd;
	controller.motors[motor_index].p_mul = pm;

	address = (motor_index << 5)|(address << 1);
	TMC429_Register_Write(hspi, address, data);
	TMC429_Register_Write(hspi, address, controller.motors[motor_index].acc_max);
}

void TMC429_Register_Write(SPI_HandleTypeDef *hspi, uint8_t address, uint32_t data){
	uint8_t pData[4];
	pData[0] = address << 1;

	pData[1] = (data & 0xFF0000) >> 16;
	pData[2] = (data & 0x00FF00) >> 8;
	pData[3] = data & 0x0000FF;

	HAL_GPIO_WritePin(GPIOB, CS_Ctrl_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_SPI_Transmit(hspi, pData, sizeof(pData), 100);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOB, CS_Ctrl_Pin, GPIO_PIN_SET);
}
void TMC429_Register_Read(SPI_HandleTypeDef *hspi, uint8_t address){
	uint8_t pTxData[4];
	uint8_t pRxData[4];

	pTxData[0] = (address << 1)|0b1;

	HAL_GPIO_WritePin(GPIOB, CS_Ctrl_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_SPI_TransmitReceive(hspi, pTxData, pRxData, sizeof(pRxData), 100);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOB, CS_Ctrl_Pin, GPIO_PIN_SET);

	controller.response = pRxData[0];
}

uint8_t TMC429_CheckFollow(){
	return ((controller.response & FOLLOW_MASK) == FOLLOW_MASK);
}

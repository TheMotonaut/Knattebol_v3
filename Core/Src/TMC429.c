/*
 * TMC429.c
 *
 *  Created on: Jan 26, 2022
 *      Author: simon
 */

#include "TMC429.h"
#include "main.h"



void TMC429_If_Conf(SPI_HandleTypeDef *hspi){

	for(uint8_t i = 0; i < 3; i++){
		controller.motors[i].x_target = 0x0;
		controller.motors[i].v_min = 0x0;
		controller.motors[i].v_max = 0x0;
		controller.motors[i].v_target = 0x0;
		controller.motors[i].mode[0] = 0x0;
		controller.motors[i].mode[1] = 0x0;
		controller.motors[i].mode[2] = 0x0;
		controller.motors[i].acc_max = 0x0;
	}
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

	address = (motor_index << 5)|(address << 1);
	TMC429_Register_Write(hspi, address, controller.motors[motor_index].acc_max);
}

void TMC429_Register_Write(SPI_HandleTypeDef *hspi, uint8_t address, uint32_t data){
	uint8_t pData[4];
	pData[0] = address;

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

}

void TMC429_CheckFollow(){
	return (controller.motors[0].x_actual != controller.motors[0].x_target)|(controller.motors[1].x_actual != controller.motors[1].x_targe)|(controller.motors[2].x_actual != controller.motors[2].x_targe);
}

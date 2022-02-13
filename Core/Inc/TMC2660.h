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


#define DRVCTRL 	0x0
#define CHOPCONF 	0x4
#define SMARTEN 	0x2
#define SGCSCONF 	0x3
#define DRVCONF 	0x4

#define INTPOL 		0x200
#define DEDGE 		0x100

#define CHM 		0x4000		//Chopper mode
#define RNDTF		0x2000		//Random TOFF time

#define SEIMIN		0x8000		//Minimum CoolStep current

#define SFILT		0x10000		//StallGuard2 filter enable

#define TST			0x10000		//Reserved TEST mode
#define DISS2G		0x400
#define OTSENS		0x8
#define	SHRTSENS	0x4
#define	EN_PFD		0x2
#define EN_S2VS		0x1

//Response
#define STST		0x80
#define	OLB			0x40
#define OLA			0x20
#define	SHORTB		0x10
#define SHORTA		0x8
#define OTPW		0x4
#define OT			0x2
#define	SG			0x1

struct TMC2660{
	uint32_t registers[5];
	uint32_t response;
};

void TMC2660_Init(SPI_HandleTypeDef *hspi);
void TMC2660_SPI_TransmitReceive(SPI_HandleTypeDef *hspi, uint32_t data, struct TMC2660 *motor, uint8_t motor_index);


#endif /* INC_TMC2660_H_ */

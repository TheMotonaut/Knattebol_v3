/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void SET_LED(uint16_t led);
void RESET_LED(uint16_t led);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define REFR2_Pin GPIO_PIN_2
#define REFR2_GPIO_Port GPIOC
#define INT1_Pin GPIO_PIN_3
#define INT1_GPIO_Port GPIOC
#define CS_Azi_Pin GPIO_PIN_1
#define CS_Azi_GPIO_Port GPIOA
#define SG_TST_ALT_Pin GPIO_PIN_2
#define SG_TST_ALT_GPIO_Port GPIOA
#define CS_Alt_Pin GPIO_PIN_3
#define CS_Alt_GPIO_Port GPIOA
#define REFR1_Pin GPIO_PIN_4
#define REFR1_GPIO_Port GPIOA
#define REFR3_Pin GPIO_PIN_4
#define REFR3_GPIO_Port GPIOC
#define REF1_Pin GPIO_PIN_5
#define REF1_GPIO_Port GPIOC
#define REF2_Pin GPIO_PIN_0
#define REF2_GPIO_Port GPIOB
#define SG_TST_POL_Pin GPIO_PIN_1
#define SG_TST_POL_GPIO_Port GPIOB
#define ENN_Pin GPIO_PIN_10
#define ENN_GPIO_Port GPIOB
#define LED1_Pin GPIO_PIN_12
#define LED1_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_13
#define LED2_GPIO_Port GPIOB
#define LED3_Pin GPIO_PIN_14
#define LED3_GPIO_Port GPIOB
#define REF3_Pin GPIO_PIN_15
#define REF3_GPIO_Port GPIOB
#define CS_Ctrl_Pin GPIO_PIN_8
#define CS_Ctrl_GPIO_Port GPIOB
#define SG_TST_Azi_Pin GPIO_PIN_9
#define SG_TST_Azi_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
//STATES
uint8_t state;
#define CONFIGURE 	0x1
#define FOLLOW		0x2
#define LOCKED 		0x3

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

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
#include "stm32f1xx_hal.h"

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
extern int pwm_signal;
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define pwm1_Pin GPIO_PIN_0
#define pwm1_GPIO_Port GPIOA
#define pwm2_Pin GPIO_PIN_1
#define pwm2_GPIO_Port GPIOA
#define AN1_Pin GPIO_PIN_3
#define AN1_GPIO_Port GPIOA
#define AN2_Pin GPIO_PIN_4
#define AN2_GPIO_Port GPIOA
#define BN1_Pin GPIO_PIN_5
#define BN1_GPIO_Port GPIOA
#define BN2_Pin GPIO_PIN_6
#define BN2_GPIO_Port GPIOA
#define CN1_Pin GPIO_PIN_7
#define CN1_GPIO_Port GPIOA
#define CN2_Pin GPIO_PIN_0
#define CN2_GPIO_Port GPIOB
#define DN1_Pin GPIO_PIN_1
#define DN1_GPIO_Port GPIOB
#define DN2_Pin GPIO_PIN_2
#define DN2_GPIO_Port GPIOB
#define wifi_RST_Pin GPIO_PIN_12
#define wifi_RST_GPIO_Port GPIOB
#define wifi_EN_Pin GPIO_PIN_13
#define wifi_EN_GPIO_Port GPIOB
#define TG1_Pin GPIO_PIN_11
#define TG1_GPIO_Port GPIOA
#define TG2_Pin GPIO_PIN_12
#define TG2_GPIO_Port GPIOA
#define Chassis_D2_Pin GPIO_PIN_15
#define Chassis_D2_GPIO_Port GPIOA
#define Chassis_D1_Pin GPIO_PIN_3
#define Chassis_D1_GPIO_Port GPIOB
#define Chassis_C2_Pin GPIO_PIN_4
#define Chassis_C2_GPIO_Port GPIOB
#define Chassis_C1_Pin GPIO_PIN_5
#define Chassis_C1_GPIO_Port GPIOB
#define Chassis_B2_Pin GPIO_PIN_6
#define Chassis_B2_GPIO_Port GPIOB
#define Chassis_B1_Pin GPIO_PIN_7
#define Chassis_B1_GPIO_Port GPIOB
#define Chassis_A1_Pin GPIO_PIN_8
#define Chassis_A1_GPIO_Port GPIOB
#define Chassis_A2_Pin GPIO_PIN_9
#define Chassis_A2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

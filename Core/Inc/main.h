/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_2_Pin GPIO_PIN_13
#define LED_2_GPIO_Port GPIOB
#define LED_1_Pin GPIO_PIN_14
#define LED_1_GPIO_Port GPIOB
#define AXIS_X2_DIR_Pin GPIO_PIN_9
#define AXIS_X2_DIR_GPIO_Port GPIOD
#define AXIS_X_DIR_Pin GPIO_PIN_10
#define AXIS_X_DIR_GPIO_Port GPIOD
#define AXIS_X_PULSE_Pin GPIO_PIN_11
#define AXIS_X_PULSE_GPIO_Port GPIOD
#define AXIS_Y_DIR_Pin GPIO_PIN_12
#define AXIS_Y_DIR_GPIO_Port GPIOD
#define AXIS_Y_PULSE_Pin GPIO_PIN_13
#define AXIS_Y_PULSE_GPIO_Port GPIOD
#define AXIS_X_EN_Pin GPIO_PIN_14
#define AXIS_X_EN_GPIO_Port GPIOD
#define AXIS_Y_EN_Pin GPIO_PIN_15
#define AXIS_Y_EN_GPIO_Port GPIOD
#define AXIS_X_SWITCH_Pin GPIO_PIN_6
#define AXIS_X_SWITCH_GPIO_Port GPIOD
#define AXIS_X_SWITCH_EXTI_IRQn EXTI9_5_IRQn
#define AXIS_X_SWITCHD7_Pin GPIO_PIN_7
#define AXIS_X_SWITCHD7_GPIO_Port GPIOD
#define AXIS_X_SWITCHD7_EXTI_IRQn EXTI9_5_IRQn
#define BUT_Pin GPIO_PIN_5
#define BUT_GPIO_Port GPIOB
#define BUT_EXTI_IRQn EXTI9_5_IRQn
#define EXTI_INPUT_ENC_Pin GPIO_PIN_8
#define EXTI_INPUT_ENC_GPIO_Port GPIOB
#define EXTI_INPUT_ENC_EXTI_IRQn EXTI9_5_IRQn
#define GPIO_INPUT_ENC_Pin GPIO_PIN_9
#define GPIO_INPUT_ENC_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

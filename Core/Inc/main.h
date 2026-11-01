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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_1_Pin GPIO_PIN_13
#define LED_1_GPIO_Port GPIOC
#define LED_2_Pin GPIO_PIN_14
#define LED_2_GPIO_Port GPIOC
#define LED_3_Pin GPIO_PIN_15
#define LED_3_GPIO_Port GPIOC
#define BUT_S_Pin GPIO_PIN_0
#define BUT_S_GPIO_Port GPIOC
#define BUT_SW2_Pin GPIO_PIN_1
#define BUT_SW2_GPIO_Port GPIOC
#define BUT_SW1_Pin GPIO_PIN_2
#define BUT_SW1_GPIO_Port GPIOC
#define DS18B20_1WIRE_Pin GPIO_PIN_3
#define DS18B20_1WIRE_GPIO_Port GPIOC
#define SPI_CS_Pin GPIO_PIN_4
#define SPI_CS_GPIO_Port GPIOA
#define TS_Z_Pin GPIO_PIN_10
#define TS_Z_GPIO_Port GPIOB
#define VP_ENABLE_Pin GPIO_PIN_11
#define VP_ENABLE_GPIO_Port GPIOB
#define AXIS_Z_DIR_Pin GPIO_PIN_12
#define AXIS_Z_DIR_GPIO_Port GPIOB
#define AXIS_Z_EN_Pin GPIO_PIN_13
#define AXIS_Z_EN_GPIO_Port GPIOB
#define AXIS_Y_DIR_Pin GPIO_PIN_14
#define AXIS_Y_DIR_GPIO_Port GPIOB
#define AXIS_Y_EN_Pin GPIO_PIN_15
#define AXIS_Y_EN_GPIO_Port GPIOB
#define SPINDLE_Pin GPIO_PIN_6
#define SPINDLE_GPIO_Port GPIOC
#define AXIS_Z_PULSE_Pin GPIO_PIN_7
#define AXIS_Z_PULSE_GPIO_Port GPIOC
#define AXIS_Y_PULSE_Pin GPIO_PIN_8
#define AXIS_Y_PULSE_GPIO_Port GPIOC
#define AXIS_X_PULSE_Pin GPIO_PIN_9
#define AXIS_X_PULSE_GPIO_Port GPIOC
#define AXIS_X_DIR_Pin GPIO_PIN_11
#define AXIS_X_DIR_GPIO_Port GPIOA
#define AXIS_X_EN_Pin GPIO_PIN_12
#define AXIS_X_EN_GPIO_Port GPIOA
#define EPPROM_WP_Pin GPIO_PIN_10
#define EPPROM_WP_GPIO_Port GPIOC
#define CULLER_Pin GPIO_PIN_11
#define CULLER_GPIO_Port GPIOC
#define AXIS_X_LIM_Pin GPIO_PIN_12
#define AXIS_X_LIM_GPIO_Port GPIOC
#define AXIS_X_LIM_EXTI_IRQn EXTI15_10_IRQn
#define AXIS_Y_LIM_Pin GPIO_PIN_2
#define AXIS_Y_LIM_GPIO_Port GPIOD
#define AXIS_Y_LIM_EXTI_IRQn EXTI2_IRQn
#define AXIS_Z_LIM_Pin GPIO_PIN_3
#define AXIS_Z_LIM_GPIO_Port GPIOB
#define AXIS_Z_LIM_EXTI_IRQn EXTI3_IRQn
#define GPIO_INPUT_ENC_Pin GPIO_PIN_4
#define GPIO_INPUT_ENC_GPIO_Port GPIOB
#define EXTI_INPUT_ENC_Pin GPIO_PIN_5
#define EXTI_INPUT_ENC_GPIO_Port GPIOB
#define EXTI_INPUT_ENC_EXTI_IRQn EXTI9_5_IRQn
#define BUT_Pin GPIO_PIN_8
#define BUT_GPIO_Port GPIOB
#define BUT_EXTI_IRQn EXTI9_5_IRQn
#define LASER_PULSE_Pin GPIO_PIN_9
#define LASER_PULSE_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

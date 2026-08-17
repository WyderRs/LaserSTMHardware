/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"

#include "../lib/LCD2004.h"
#include "../lib/DriverLib.h"
#include "../lib/SD.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim14;

UART_HandleTypeDef huart1;

osThreadId default_taskHandle;
osThreadId table_taskHandle;
osThreadId display_taskHandle;
osThreadId control_taskHandle;
/* USER CODE BEGIN PV */
/********************************************************/


/* display */
char display_buf[20];
/* table */

/********************************************************/
uint16_t time = 0;
uint32_t idle_tick;
extern FATFS fs;
extern FIL fil;



Point_t point;
/********************************************************/
/* Functions */










/********************************************************/
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM14_Init(void);
static void MX_USART1_UART_Init(void);
void TASK_default(void const * argument);
void TASK_table(void const * argument);
void TASK_display(void const * argument);
void TASK_control(void const * argument);

/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_TIM14_Init();
  MX_USART1_UART_Init();
  MX_FATFS_Init();
  /* USER CODE BEGIN 2 */


//  HAL_TIM_Base_Start_IT(&htim14);



  tbInit();
  LCD_Init(0x4E, 20, 4);
  LCD_Clear();

  LCD_SetCursor(0, 0);
  LCD_WriteString("Bootting...");

  HAL_Delay(1000);
  tbDriver(ON);

  HAL_Delay(1000);
  tbDriver(OFF);
//  tbMove(10, 10, 0);


  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of default_task */
  osThreadDef(default_task, TASK_default, osPriorityIdle, 0, 128);
  default_taskHandle = osThreadCreate(osThread(default_task), NULL);

  /* definition and creation of table_task */
  osThreadDef(table_task, TASK_table, osPriorityNormal, 0, 128);
  table_taskHandle = osThreadCreate(osThread(table_task), NULL);

  /* definition and creation of display_task */
  osThreadDef(display_task, TASK_display, osPriorityNormal, 0, 128);
  display_taskHandle = osThreadCreate(osThread(display_task), NULL);

  /* definition and creation of control_task */
  osThreadDef(control_task, TASK_control, osPriorityNormal, 0, 128);
  control_taskHandle = osThreadCreate(osThread(control_task), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */

//  pvPortMalloc(xWantedSize);
//  vPortFree(pv);



  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM14 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM14_Init(void)
{

  /* USER CODE BEGIN TIM14_Init 0 */

  /* USER CODE END TIM14_Init 0 */

  /* USER CODE BEGIN TIM14_Init 1 */

  /* USER CODE END TIM14_Init 1 */
  htim14.Instance = TIM14;
  htim14.Init.Prescaler = 36-1;
  htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim14.Init.Period = 10-1;
  htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM14_Init 2 */

  /* USER CODE END TIM14_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LED_1_Pin|LED_2_Pin|LED_3_Pin|DS18B20_1WIRE_Pin
                          |GPIO_PIN_4|GPIO_PIN_5|AXIS_Y_PULSE_Pin|AXIS_Y_EN_Pin
                          |AXIS_X_DIR_Pin|AXIS_X_PULSE_Pin|CULLER_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, SPINDLE_Pin|SPI_CS_Pin|AXIS_X_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|SPINDLEB10_Pin
                          |AXIS_Z_DIR_Pin|AXIS_Z_PULSE_Pin|AXIS_Z_EN_Pin|AXIS_Y_DIR_Pin
                          |LASER_PULSE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_1_Pin LED_2_Pin LED_3_Pin DS18B20_1WIRE_Pin
                           PC4 PC5 AXIS_Y_PULSE_Pin AXIS_Y_EN_Pin
                           AXIS_X_DIR_Pin AXIS_X_PULSE_Pin CULLER_Pin */
  GPIO_InitStruct.Pin = LED_1_Pin|LED_2_Pin|LED_3_Pin|DS18B20_1WIRE_Pin
                          |GPIO_PIN_4|GPIO_PIN_5|AXIS_Y_PULSE_Pin|AXIS_Y_EN_Pin
                          |AXIS_X_DIR_Pin|AXIS_X_PULSE_Pin|CULLER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : BUT_S_Pin BUT_SW2_Pin BUT_SW1_Pin */
  GPIO_InitStruct.Pin = BUT_S_Pin|BUT_SW2_Pin|BUT_SW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : SPINDLE_Pin SPI_CS_Pin AXIS_X_EN_Pin */
  GPIO_InitStruct.Pin = SPINDLE_Pin|SPI_CS_Pin|AXIS_X_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : ENC_IN_EXTI_Pin */
  GPIO_InitStruct.Pin = ENC_IN_EXTI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ENC_IN_EXTI_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : ENC_IN_GPIO_Pin */
  GPIO_InitStruct.Pin = ENC_IN_GPIO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ENC_IN_GPIO_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 SPINDLEB10_Pin
                           AXIS_Z_DIR_Pin AXIS_Z_PULSE_Pin AXIS_Z_EN_Pin AXIS_Y_DIR_Pin
                           LASER_PULSE_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|SPINDLEB10_Pin
                          |AXIS_Z_DIR_Pin|AXIS_Z_PULSE_Pin|AXIS_Z_EN_Pin|AXIS_Y_DIR_Pin
                          |LASER_PULSE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : VP_ENABLE_Pin GPIO_INPUT_ENC_Pin */
  GPIO_InitStruct.Pin = VP_ENABLE_Pin|GPIO_INPUT_ENC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : AXIS_X_LIM_Pin */
  GPIO_InitStruct.Pin = AXIS_X_LIM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(AXIS_X_LIM_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : AXIS_Y_LIM_Pin */
  GPIO_InitStruct.Pin = AXIS_Y_LIM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(AXIS_Y_LIM_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : AXIS_Z_LIM_Pin EXTI_INPUT_ENC_Pin BUT_Pin */
  GPIO_InitStruct.Pin = AXIS_Z_LIM_Pin|EXTI_INPUT_ENC_Pin|BUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

	if (htim->Instance == TIM14) {
		dl_CheckPWM();

	}
}




void vApplicationIdleHook(int tag) {

//	__NOP();
	idle_tick++;

}
/* USER CODE END 4 */

/* USER CODE BEGIN Header_TASK_default */
/**
  * @brief  Function implementing the default_task thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_TASK_default */
void TASK_default(void const * argument)
{
  /* USER CODE BEGIN 5 */


//	TickType_t xLastWakeTime;
//	const TickType_t xFrequency = 250 / portTICK_PERIOD_MS;


  /* Infinite loop */
  for(;;)
  {
//	  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
//	  osDelay(500);




//	  vTaskDelayUntil(&xLastWakeTime, xFrequency);
	  // vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_TASK_table */
/**
* @brief Function implementing the table_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TASK_table */
void TASK_table(void const * argument)
{
  /* USER CODE BEGIN TASK_table */





  /* Infinite loop */
  for(;;)
  {

	  if (1) {


		  tbMove(point.x, point.y, point.z);

	  }






  }
  /* USER CODE END TASK_table */
}

/* USER CODE BEGIN Header_TASK_display */
/**
* @brief Function implementing the display_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TASK_display */
void TASK_display(void const * argument)
{
  /* USER CODE BEGIN TASK_display */







  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	  osDelay(500);








  }
  /* USER CODE END TASK_display */
}

/* USER CODE BEGIN Header_TASK_control */
/**
* @brief Function implementing the control_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TASK_control */
void TASK_control(void const * argument)
{
  /* USER CODE BEGIN TASK_control */





  /* Infinite loop */
  for(;;)
  {







    osDelay(1);





  }
  /* USER CODE END TASK_control */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

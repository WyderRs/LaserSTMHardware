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
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include <stdbool.h>

#include "../lib/LCD2004.h"
#include "../lib/SD.h"
#include "../lib/tableTool.h"
#include "../lib/g_code.h"
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
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim11;
TIM_HandleTypeDef htim14;

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;

/* USER CODE BEGIN PV */
/********************************************************/


/********************************************************/
uint16_t time = 0;
uint32_t idle_tick;
extern FATFS fs;
extern FIL fil;
extern Tool_Typedef tTool;

//Point_t point;
/********************************************************/


/********************************************************/
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM14_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM11_Init(void);
static void MX_TIM3_Init(void);
static void MX_ADC1_Init(void);
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
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_TIM14_Init();
  MX_USART1_UART_Init();
  MX_FATFS_Init();
  MX_TIM11_Init();
  MX_TIM3_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */

  tInit();
  LCD_Init(0x4E, 20, 4);
  LCD_Clear();
  LCD_SetCursor(0, 0);
  LCD_WriteString("Reset");
  LCD_SetCursor(1, 0);
  LCD_WriteString("Coordinates...");

//  tHome();
//  LCD_Clear();

//  LCD_SetCursor(0, 0);
//  LCD_WriteString("Tool ready");
//
//  LCD_SetCursor(1, 0);
//  LCD_WriteString("Please, press");
//  LCD_SetCursor(2, 0);
//  LCD_WriteString("enter button");
//
//  while(!tTool.Encoder.Button_state) {}
//  tTool.Encoder.Button_state = 0;

//  LCD_Clear();
//  LCD_SetCursor(0, 1);
//  LCD_WriteString(":Hand mode");
//  LCD_SetCursor(1, 1);
//  LCD_WriteString(":USB mode");
//  LCD_SetCursor(2, 1);
//  LCD_WriteString(":SD mode");
//  LCD_SetCursor(3, 1);
//  LCD_WriteString(":Settings");
//
//  LCD_SetCursor(0, 0);
//  LCD_WriteChar(0x7E);
//
//  uint8_t disp_pos = 0;

  /**************************************************************************/
//  while(1) {
//	  if (tTool.Encoder.count_last_rotate > 0) {
//		  if (tTool.Encoder.current_rotate_side == Forward) {
//			  if (disp_pos < 4) disp_pos++;
//			  if (disp_pos < 4) {
//				  if (disp_pos != 0) {
//					  LCD_SetCursor(disp_pos - 1, 0);
//					  LCD_WriteChar(' ');
//				  }
//				  LCD_SetCursor(disp_pos, 0);
//				  LCD_WriteChar(0x7E);
//			  }
//		  }
//		  else {
//			  if (disp_pos > 0) disp_pos--;
//			  if ((disp_pos <= 3) && (disp_pos >= 0)) {
//				  if (disp_pos != 3) {
//					  LCD_SetCursor(disp_pos + 1, 0);
//					  LCD_WriteChar(' ');
//				  }
//				  LCD_SetCursor(disp_pos, 0);
//				  LCD_WriteChar(0x7E);
//			  }
//		  }
//		  tTool.Encoder.count_last_rotate = 0;
//	  }
//	  if (tTool.Encoder.Button_state == true) {
//		  tTool.Encoder.Button_state = false;
//		  if (disp_pos == 0) {
//			  tTool.WorkMode = Hand_Mode;
//			  LCD_Clear();
//			  LCD_SetCursor(0, 0);
//			  LCD_WriteString("Mode:Hand_X");
//
//			  char buf[3][20] = {0, };
//			  float x = 0, y = 0, z = 0;
//			  float trg_cord = 0;
//			  enum sid_t {
//				  _x = 0,
//				  _y,
//				  _z,
//			  } sid;
//			  sid = _x;
//			  while(1) {
//				  if (tTool.Encoder.count_last_rotate >= 1) {
//					  if (tTool.Encoder.current_rotate_side == Forward) {
////						  x += tTool.Settings.stpLineValue;
//						  trg_cord += 5;
//					  }
//					  else if (tTool.Encoder.current_rotate_side == BackForward) {
//
////						  if (x > tTool.Settings.stpLineValue) x -= tTool.Settings.stpLineValue;
//						  if (trg_cord > 5) trg_cord -= 5;
//					  }
//					  if (sid == _x) {
//						  x = trg_cord;
//						  tMoveGlobal(x, y, z);
//					  }
//					  else if (sid == _y) {
//						  y = trg_cord;
//						  tMoveGlobal(x, y, z);
//					  }
//					  else if (sid == _z) {
//						  z = trg_cord;
//						  tMoveGlobal(x, y, z);
//					  }
//
//
////					  LCD_SetCursor(1, 1);
////					  sprintf(buf[0], "X:%.4f    ", tTool.head.tAxis[0].current_pos_coord);
////					  LCD_WriteString(buf[0]);
////					  LCD_SetCursor(2, 1);
////					  sprintf(buf[1], "Y:%.4f    ", tTool.head.tAxis[1].current_pos_coord);
////					  LCD_WriteString(buf[1]);
////					  LCD_SetCursor(3, 1);
////					  sprintf(buf[2], "Z:%.4f    ", tTool.head.tAxis[2].current_pos_coord);
////					  LCD_WriteString(buf[2]);
//
//					  tTool.Encoder.count_last_rotate = 0;
//				  }
//				  if (tTool.Encoder.Button_state == true) {
//					  tTool.Encoder.Button_state = false;
//
//					  if (sid == _x) x = trg_cord;
//					  else if (sid == _y) y = trg_cord;
//					  else if (sid == _z) z = trg_cord;
//					  trg_cord = 0;
//
//					  LCD_Clear();
//
//					  LCD_SetCursor(0, 1);
//					  LCD_WriteString(":Exit");
//					  LCD_SetCursor(1, 1);
//					  LCD_WriteString(":AXIS_X");
//					  LCD_SetCursor(2, 1);
//					  LCD_WriteString(":AXIS_Y");
//					  LCD_SetCursor(3, 1);
//					  LCD_WriteString(":AXIS_Z");
//					  LCD_SetCursor(0, 0);
//					  LCD_WriteChar(0x7E);
//
//					  disp_pos = 0;
//					  while (1) {
//						  if (tTool.Encoder.count_last_rotate > 0) {
//							  if (tTool.Encoder.current_rotate_side == Forward) {
//								  if (disp_pos < 3) disp_pos++;
//								  if (disp_pos < 4) {
//									  if (disp_pos != 1) {
//										  LCD_SetCursor(disp_pos - 1, 0);
//										  LCD_WriteChar(' ');
//									  }
//									  LCD_SetCursor(disp_pos, 0);
//									  LCD_WriteChar(0x7E);
//								  }
//							  }
//							  else {
//								  if (disp_pos > 1) disp_pos--;
//								  if ((disp_pos <= 3) && (disp_pos >= 0)) {
//									  if (disp_pos != 3) {
//										  LCD_SetCursor(disp_pos + 1, 0);
//										  LCD_WriteChar(' ');
//									  }
//									  LCD_SetCursor(disp_pos, 0);
//									  LCD_WriteChar(0x7E);
//								  }
//							  }
//							  tTool.Encoder.count_last_rotate = 0;
//						  }
//						  if (tTool.Encoder.Button_state == true) {
//							  if (disp_pos == 4) disp_pos = 3;
//							  if (disp_pos == 1) sid = _x;
//							  else if (disp_pos == 2) sid = _y;
//							  else if (disp_pos == 3) sid = _z;
//
//							  LCD_Clear();
//							  LCD_SetCursor(0, 0);
//							  if (sid == _x) LCD_WriteString("Mode:Hand_X");
//							  else if (sid == _y) LCD_WriteString("Mode:Hand_Y");
//							  else if (sid == _z) LCD_WriteString("Mode:Hand_Z");
//
//							  tTool.Encoder.Button_state = false;
//							  break;
//						  }
//					  }
//				  }
//			  }
//		  }
//		  else if (disp_pos == 1) {
//			  LCD_Clear();
//			  LCD_SetCursor(0, 0);
//			  LCD_WriteString("Mode:USB (AUTO)");
//
//			  break;
//		  }
//		  tTool.Encoder.Button_state = false;
//	  }
//  }

//  GC_G0(30, 30, 30);
//  HAL_Delay(1000);
//  tMoveSetSpeed(10);
//  GC_G1(50, 50, 50);
//  GC_G28(GC_Z_AXIS);









//  HAL_Delay(1000);





  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

//	  if(tTool.VCP_Config.VCP_command_IsReceived) {
//		  for (uint32_t i = 0; i < tTool.VCP_Config.VCP_cnt_last_file; i++) {
//			  DATA_GCODE[i] = tTool.VCP_Config.VCP_data[i + 2];
//		  }
//		  StartGCodeStorage((unsigned char*)&DATA_GCODE);
//		  memset(&tTool.VCP_Config.VCP_data[0], '\0', sizeof(tTool.VCP_Config.VCP_data));
//		  tTool.VCP_Config.VCP_command_IsReceived = false;
//
//		  HAL_UART_Transmit_IT(&huart1, (uint8_t*)"OK", 2);
//	  }






//	  HAL_Delay(500);
//	  LED_FREE_OP_TGL;



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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

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
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 72-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 100-1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief TIM11 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM11_Init(void)
{

  /* USER CODE BEGIN TIM11_Init 0 */

  /* USER CODE END TIM11_Init 0 */

  /* USER CODE BEGIN TIM11_Init 1 */

  /* USER CODE END TIM11_Init 1 */
  htim11.Instance = TIM11;
  htim11.Init.Prescaler = 72-1;
  htim11.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim11.Init.Period = 10-1;
  htim11.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim11.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim11) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM11_Init 2 */

  /* USER CODE END TIM11_Init 2 */

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
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);

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
                          |GPIO_PIN_4|GPIO_PIN_5|EPPROM_WP_Pin|CULLER_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, SPI_CS_Pin|AXIS_X_DIR_Pin|AXIS_X_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|TS_Z_Pin
                          |AXIS_Z_DIR_Pin|AXIS_Z_EN_Pin|AXIS_Y_EN_Pin|LASER_PULSE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(AXIS_Y_DIR_GPIO_Port, AXIS_Y_DIR_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : LED_1_Pin LED_2_Pin LED_3_Pin DS18B20_1WIRE_Pin
                           PC4 PC5 EPPROM_WP_Pin CULLER_Pin */
  GPIO_InitStruct.Pin = LED_1_Pin|LED_2_Pin|LED_3_Pin|DS18B20_1WIRE_Pin
                          |GPIO_PIN_4|GPIO_PIN_5|EPPROM_WP_Pin|CULLER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : BUT_S_Pin BUT_SW2_Pin BUT_SW1_Pin */
  GPIO_InitStruct.Pin = BUT_S_Pin|BUT_SW2_Pin|BUT_SW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : SPI_CS_Pin AXIS_X_DIR_Pin AXIS_X_EN_Pin */
  GPIO_InitStruct.Pin = SPI_CS_Pin|AXIS_X_DIR_Pin|AXIS_X_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 TS_Z_Pin
                           AXIS_Z_DIR_Pin AXIS_Z_EN_Pin AXIS_Y_DIR_Pin AXIS_Y_EN_Pin
                           LASER_PULSE_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|TS_Z_Pin
                          |AXIS_Z_DIR_Pin|AXIS_Z_EN_Pin|AXIS_Y_DIR_Pin|AXIS_Y_EN_Pin
                          |LASER_PULSE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : VP_ENABLE_Pin */
  GPIO_InitStruct.Pin = VP_ENABLE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(VP_ENABLE_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : AXIS_X_LIM_Pin */
  GPIO_InitStruct.Pin = AXIS_X_LIM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(AXIS_X_LIM_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : AXIS_Y_LIM_Pin */
  GPIO_InitStruct.Pin = AXIS_Y_LIM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(AXIS_Y_LIM_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : AXIS_Z_LIM_Pin */
  GPIO_InitStruct.Pin = AXIS_Z_LIM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(AXIS_Z_LIM_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : GPIO_INPUT_ENC_Pin */
  GPIO_InitStruct.Pin = GPIO_INPUT_ENC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIO_INPUT_ENC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : EXTI_INPUT_ENC_Pin */
  GPIO_InitStruct.Pin = EXTI_INPUT_ENC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(EXTI_INPUT_ENC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BUT_Pin */
  GPIO_InitStruct.Pin = BUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BUT_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */





/* USER CODE END 4 */

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

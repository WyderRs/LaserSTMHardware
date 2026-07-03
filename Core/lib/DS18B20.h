/*
 * DS18B20.h
 *
 *  Created on: Jun 15, 2026
 *      Author: makar
 */

#ifndef LIB_DS18B20_H_
#define LIB_DS18B20_H_

#include "stm32f1xx_hal.h"  // или соответствующая версия для вашего контроллера

//--------------------------------------------------
#define SKIP_ROM 			0
#define NO_SKIP_ROM 		1
//--------------------------------------------------
#define RESOLUTION_9BIT 	0x1F
#define RESOLUTION_10BIT 	0x3F
#define RESOLUTION_11BIT 	0x5F
#define RESOLUTION_12BIT 	0x7F
//--------------------------------------------------
void DS18B20_PortInit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint8_t DS18B20_init(uint8_t mode);
void DS18B20_MeasureTemperCmd(uint8_t mode, uint8_t DevNum);
void DS18B20_ReadStratcpad(uint8_t mode, uint8_t *Data, uint8_t DevNum);
uint8_t DS18B20_GetSign(uint16_t dt);
float DS18B20_Convert(uint16_t dt);

uint8_t DS18B20_ReadRom(uint8_t number_devices);
void DS18B20_ReadTempALL(float *temp);
//--------------------------------------------------





#endif /* LIB_DS18B20_H_ */

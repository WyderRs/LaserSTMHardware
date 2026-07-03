/*
 * DS18B20.c
 *
 *  Created on: Jun 15, 2026
 *      Author: makar
 */


#include "DS18B20.h"
#include <string.h>
#include <stdbool.h>


extern TIM_HandleTypeDef htim14;

GPIO_TypeDef* 	DS_PORT;
uint16_t 		DS_PIN;

uint8_t DS18B20_Addr[3][8];


// Временные задержки (настройте под ваш STM32)
static void delay_us(uint32_t useconds) {
    // Проверяем инициализацию таймера
    if (__HAL_TIM_GET_COUNTER(&htim14) == 0) {
        __HAL_TIM_SET_COUNTER(&htim14, 0);
    }

    uint32_t start = __HAL_TIM_GET_COUNTER(&htim14);
    while ((__HAL_TIM_GET_COUNTER(&htim14) - start) < useconds);
}
void DS18B20_PortInit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
	DS_PORT = GPIOx;
	DS_PIN	= GPIO_Pin;
	HAL_GPIO_DeInit(GPIOx, GPIO_Pin);
	DS_PORT->CRL |= GPIO_CRL_MODE3;
	DS_PORT->CRL |= GPIO_CRL_CNF3_0;
	DS_PORT->CRL &= ~GPIO_CRL_CNF3_1;
}
uint8_t  DS18B20_Reset(void) {
	uint16_t status;
	DS_PORT->ODR &= ~GPIO_ODR_ODR3;
	delay_us(485);
	DS_PORT->ODR |= GPIO_ODR_ODR3;
	delay_us(65);
	status = DS_PORT->IDR & GPIO_IDR_IDR3;
	delay_us(500);
	return (status ? 1 : 0);
}
uint8_t DS18B20_ReadBit(void) {
	uint8_t bit = 0;
	DS_PORT->ODR &= ~GPIO_ODR_ODR3;
	delay_us(2);
	DS_PORT->ODR |= GPIO_ODR_ODR3;
	delay_us(13);
	bit = (DS_PORT->IDR & GPIO_IDR_IDR3 ? 1 : 0);
	delay_us(45);
	return bit;
}
uint8_t DS18B20_ReadByte(void) {
	uint8_t data = 0;
	for (uint8_t i = 0; i <= 7; i++)
	data += DS18B20_ReadBit() << i;
	return data;
}
void DS18B20_WriteBit(uint8_t bit) {
	DS_PORT->ODR &= ~GPIO_ODR_ODR3;
	delay_us(bit ? 3 : 65);
	DS_PORT->ODR |= GPIO_ODR_ODR3;
	delay_us(bit ? 65 : 3);
}
void DS18B20_WriteByte(uint8_t dt) {
	for (uint8_t i = 0; i < 8; i++)
	{
		DS18B20_WriteBit(dt >> i & 1);
		delay_us(5);
	}
}
uint8_t DS18B20_init(uint8_t mode) {
	if(DS18B20_Reset()) return 1;
	if(mode == SKIP_ROM)
	{
		//SKIP ROM
		DS18B20_WriteByte(0xCC);
		//WRITE SCRATCHPAD
		DS18B20_WriteByte(0x4E);
		//TH REGISTER 100 градусов
		DS18B20_WriteByte(0x64);
		//TL REGISTER - 30 градусов
		DS18B20_WriteByte(0x9E);
		//Resolution 12 bit
		DS18B20_WriteByte(RESOLUTION_12BIT);
	}
	return 0;
}
void DS18B20_MeasureTemperCmd(uint8_t mode, uint8_t DevNum) {
	DS18B20_Reset();
	if(mode == SKIP_ROM)
	{
		//SKIP ROM
		DS18B20_WriteByte(0xCC);
	}
	//CONVERT T
	DS18B20_WriteByte(0x44);
}
void DS18B20_ReadStratcpad(uint8_t mode, uint8_t *Data, uint8_t DevNum) {
	uint8_t i;
	DS18B20_Reset();
	if(mode == SKIP_ROM)
	{
		//SKIP ROM
		DS18B20_WriteByte(0xCC);
	}
	//READ SCRATCHPAD
	DS18B20_WriteByte(0xBE);
	for(i = 0; i < 8; i++)
	{
		Data[i] = DS18B20_ReadByte();
	}
}
uint8_t DS18B20_GetSign(uint16_t dt) {
	//Проверим 3-й бит
	if (dt & (1 << 3)) return 1;
	else return 0;
}
float DS18B20_Convert(uint16_t dt) {
	float t;
	t = (float)((dt & 0x07FF) >> 4); //отборосим знаковые и дробные биты
	//Прибавим дробную часть
	t += (float)(dt & 0x000F) / 16.0f;
	return t;
}
uint8_t DS18B20_ReadRom(uint8_t number_devices) {

	_Bool bit[2] 				= {0, };

	uint8_t conf_last_inx	 	= 12;
	_Bool 	conf_last_state 	= 0;
	uint8_t conf_prelast_inx	 = 13;

	for (uint8_t dev = 0; dev < number_devices; dev++) {


		DS18B20_Reset();
		DS18B20_WriteByte(0xF0);

		for (uint8_t byte = 0; byte < 8; byte++) {

			for (uint8_t bt = 0; bt < 8; bt++) {
				bit[0] = DS18B20_ReadBit();
				bit[1] = DS18B20_ReadBit();

				/* 1 and 0 = conflict */
				if ((bit[0] == 0) && (bit[1] == 0)) {
					if (conf_last_inx == (8 * byte + bt)) {
						DS18B20_WriteBit(1);
						conf_last_state = 1;
						conf_last_inx = conf_prelast_inx;
					}

					else if (dev == 0) {
						DS18B20_WriteBit(0);
						conf_last_state = 0;
						conf_last_inx 			= 8 * byte + bt;
					}

					else {
						DS18B20_WriteBit(0);
						conf_last_state = 0;
					}
					conf_prelast_inx 			= 8 * byte + bt;

					if (conf_last_state) DS18B20_Addr[dev][byte] |= (1 << bt);
					else DS18B20_Addr[dev][byte] &= ~(1 << bt);
				}
				/* 0 */
				else if ((bit[0] == 0) && (bit[1] == 1)) {

					DS18B20_Addr[dev][byte] &= ~(1 << bt);
					DS18B20_WriteBit(0);
				}
				/* 1 */
				else if ((bit[0] == 1) && (bit[1] == 0)) {

					DS18B20_Addr[dev][byte] |= (1 << bt);
					DS18B20_WriteBit(1);
				}
				/* ERROR */
				else if ((bit[0] == 1) && (bit[1] == 1)) {
				}
			}
		}

	}



	// 40 64 206 128 227 225 60 189
	// 40 28  112 128 227 225 60 3
	// 40 246 209 128 227 225 60 27

	return 0;
}




void DS18B20_ReadTempALL(float *temp) {
	DS18B20_Reset();

	DS18B20_WriteByte(0xCC);
	DS18B20_WriteByte(0x44);

	HAL_Delay(1000);

	for (uint8_t dev = 0; dev < 3; dev++) {
		DS18B20_Reset();

		uint8_t Data[8] = {0, };
		DS18B20_WriteByte(0x55);
		for (uint8_t i = 0; i < 8; i++) DS18B20_WriteByte(DS18B20_Addr[dev][i]);

		//READ SCRATCHPAD
		DS18B20_WriteByte(0xBE);
		for(uint8_t j = 0; j < 8; j++) {
			Data[j] = DS18B20_ReadByte();
		}
		uint16_t raw_temper = ((uint16_t)Data[1] << 8) | Data[0];
		temp[dev] 		= DS18B20_Convert(raw_temper);

	}
}







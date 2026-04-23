/*
 * LCD1602.h
 *
 *  Created on: Feb 16, 2026
 *      Author: makar
 */

#ifndef INC_LCD1602_H_
#define INC_LCD1602_H_



#include "stm32f1xx_hal.h"
#include "stdbool.h"

#define LCD1602_ADDR		0x4E

/* Параметры дисплея */
#define LCD_COLS            16
#define LCD_ROWS            2


/* Биты PCF8574 */
#define LCD_BACKLIGHT       0x08   /* P3 – подсветка (1=вкл) */
#define LCD_EN              0x04   /* P2 – строб */
#define LCD_RW              0x02   /* P1 – R/W */
#define LCD_RS              0x01   /* P0 – RS */

/* Параметры дисплея */
#define LCD_COLS            16
#define LCD_ROWS            2

/* ************** FUNCTIONS ************** */
_Bool LCD1602_Init();
void LCD1602_SetCursor(uint8_t row, uint8_t col);
void LCD1602_WriteChar(char c);
void LCD1602_WriteString(const char *str);
void LCD1602_Backlight(uint8_t state);










#endif /* INC_LCD1602_H_ */

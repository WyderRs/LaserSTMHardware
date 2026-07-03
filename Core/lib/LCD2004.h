/*
 * LCD2004.h
 *
 *  Created on: May 24, 2026
 *      Author: makar
 */

#ifndef LIB_LCD2004_H_
#define LIB_LCD2004_H_

#include "stm32f1xx.h"
#include "stdbool.h"

#define MAX_HAL_DELAY		10000

/* Биты PCF8574 */
#define LCD_BACKLIGHT       0x08   /* P3 – подсветка (1=вкл) */
#define LCD_EN              0x04   /* P2 – строб */
#define LCD_RW              0x02   /* P1 – R/W */
#define LCD_RS              0x01   /* P0 – RS */


typedef struct LCD2004_t {
	uint8_t	 lcd_addr;
	uint16_t lcd_row;
	uint16_t lcd_col;

	_Bool Backlight;

} LCD2004_t ;


_Bool LCD_Init(uint8_t addr, uint16_t col, uint16_t row);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_WriteChar(char c);
void LCD_WriteString(const char *str);
void LCD_Backlight(uint8_t state);
void LCD_Clear();









#endif /* LIB_LCD2004_H_ */

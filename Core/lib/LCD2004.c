/*
 * LCD2004.c
 *
 *  Created on: May 24, 2026
 *      Author: makar
 */

#include "LCD2004.h"


extern I2C_HandleTypeDef 	hi2c1;
LCD2004_t LCD2004;



static void DelayMs(uint32_t ms) {
	for(uint32_t i = 0; i < ms * 1000; i++) {}
}


static void LCD_WriteNibble(uint8_t nibble, uint8_t rs)
{
    uint8_t data = (nibble << 4) | (LCD2004.Backlight << 3) | rs;

    HAL_I2C_Mem_Write(&hi2c1, LCD2004.lcd_addr, 0, I2C_MEMADD_SIZE_8BIT,
                      &data, 1, MAX_HAL_DELAY);

    data |= LCD_EN;   /* EN = 1 */
    HAL_I2C_Mem_Write(&hi2c1, LCD2004.lcd_addr, 0, I2C_MEMADD_SIZE_8BIT,
                      &data, 1, MAX_HAL_DELAY);

    data &= ~LCD_EN;  /* EN = 0 */
    HAL_I2C_Mem_Write(&hi2c1, LCD2004.lcd_addr, 0, I2C_MEMADD_SIZE_8BIT,
                      &data, 1, MAX_HAL_DELAY);
}

static void LCD_WriteByte(uint8_t byte, uint8_t rs)
{
	LCD_WriteNibble(byte >> 4, rs);
	LCD_WriteNibble(byte & 0x0F, rs);
    if (byte == 0x01 || byte == 0x02 ||
        (byte >= 0x28 && byte <= 0x2F)) {
        DelayMs(10);
//    	for(uint32_t i = 0; i < 10000; i++) {}
    } else {
        DelayMs(10);
//    	for(uint32_t i = 0; i < 10000; i++) {}
    }
}

_Bool LCD_Init(uint8_t addr, uint16_t col, uint16_t row) {

	LCD2004.lcd_addr 	= addr;
	LCD2004.lcd_col		= col;
	LCD2004.lcd_row 	= row;
	LCD2004.Backlight	= true;

    /* Ждём, пока LCD проснётся (> 15 мс после питания) */
    DelayMs(50);

    /* Функция set 8-bit (3 раза) – инициализируем 4-битный режим */
    LCD_WriteNibble(0x03, 0);
    DelayMs(5);
    LCD_WriteNibble(0x03, 0);
    DelayMs(1);
    LCD_WriteNibble(0x03, 0);
    DelayMs(1);
    LCD_WriteNibble(0x02, 0); /* переход в 4-битный режим */
    DelayMs(1);

    /* Настройка размера дисплея (Function Set)
       DL = 0 (4-бит режим)
       N  = 1 (2 строки или 4 строки в режиме 2004)
       F  = 0 (5x8 точек)
    */
    uint8_t functionSet = 0x20; /* Базовое значение: 4-бит, 1 строка, 5x8 */
    if (row > 1) {
        functionSet |= 0x08; /* Устанавливаем бит N (многострочный режим) */
    }
    LCD_WriteByte(functionSet, 0);

    LCD_WriteByte(0x08, 0); /* дисплей выкл */
    LCD_WriteByte(0x01, 0); /* очистка */
    DelayMs(2);
    LCD_WriteByte(0x06, 0); /* режим инкремента */
    LCD_WriteByte(0x0C, 0); /* дисплей вкл, курсор выкл */

	return 0;
}
void LCD_SetCursor(uint8_t row, uint8_t col)
{
    uint8_t offset;

    /* Автоматический выбор адресации в зависимости от количества строк */
    if (LCD2004.lcd_row == 4) {
        /* Адресация для 2004 (4 строки) */
        uint8_t row_offsets_2004[] = {0x00, 0x40, 0x14, 0x54};
        if (row >= 4) row = 3;
        offset = row_offsets_2004[row];
    } else {
        /* Адресация для 1602 (2 строки) */
        uint8_t row_offsets_1602[] = {0x00, 0x40};
        if (row >= 2) row = 1;
        offset = row_offsets_1602[row];
    }

    LCD_WriteByte(0x80 | (offset + col), 0);
}

void LCD_WriteChar(char c)
{
	LCD_WriteByte(c, LCD_RS);
}

void LCD_WriteString(const char *str)
{
	uint8_t cnt = 0;
    while (*str) {
    	if (cnt < LCD2004.lcd_col) {
    		LCD_WriteChar(*str++);
    		cnt++;
    	}
    	else {str++;}
    }
}

void LCD_Backlight(uint8_t state)
{
	LCD2004.Backlight = state;
    uint8_t dummy = 0;
    HAL_I2C_Mem_Write(&hi2c1, LCD2004.lcd_addr, 0, I2C_MEMADD_SIZE_8BIT, &dummy, 1, MAX_HAL_DELAY);
}
void LCD_Clear()
{
	LCD_WriteByte(0x01, 0);
}











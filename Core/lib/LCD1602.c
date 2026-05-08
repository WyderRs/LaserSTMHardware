/*
 * LCD1602.c
 *
 *  Created on: Feb 16, 2026
 *      Author: makar
 */



#include "LCD1602.h"

extern I2C_HandleTypeDef 	hi2c1;
static uint8_t            	backlight;


static void lcd_write_nibble(uint8_t nibble, uint8_t rs)
{
    uint8_t data = (nibble << 4) | LCD_BACKLIGHT | rs;
    backlight = LCD_BACKLIGHT;
    HAL_I2C_Mem_Write(&hi2c1, LCD1602_ADDR, 0, I2C_MEMADD_SIZE_8BIT,
                      &data, 1, HAL_MAX_DELAY);

    data |= LCD_EN;   /* EN = 1 */
    HAL_I2C_Mem_Write(&hi2c1, LCD1602_ADDR, 0, I2C_MEMADD_SIZE_8BIT,
                      &data, 1, HAL_MAX_DELAY);

    data &= ~LCD_EN;  /* EN = 0 */
    HAL_I2C_Mem_Write(&hi2c1, LCD1602_ADDR, 0, I2C_MEMADD_SIZE_8BIT,
                      &data, 1, HAL_MAX_DELAY);
}

static void lcd_write_byte(uint8_t byte, uint8_t rs)
{
    lcd_write_nibble(byte >> 4, rs);
    lcd_write_nibble(byte & 0x0F, rs);
    if (byte == 0x01 || byte == 0x02 ||
        (byte >= 0x28 && byte <= 0x2F)) {
        HAL_Delay(2);  /* команды долгие */
    } else {
        HAL_Delay(1);
    }
}




_Bool LCD1602_Init()
{
    backlight = LCD_BACKLIGHT;

    /* PCF8574 уже должен быть инициализирован в CubeMX / HAL */

    /* 1. Ждём, пока LCD проснётся (> 15 мс после питания) */
    HAL_Delay(50);

    /* 2. Функция set 8-bit (3 раза) – инициализируем 4-битный режим */
    lcd_write_nibble(0x03, 0);
    HAL_Delay(5);
    lcd_write_nibble(0x03, 0);
    HAL_Delay(1);
    lcd_write_nibble(0x03, 0);
    HAL_Delay(1);
    lcd_write_nibble(0x02, 0); /* переход в 4-битный режим */
    HAL_Delay(1);

    lcd_write_byte(0x28, 0); /* 2 строки, 5×8, 4-битный */
    lcd_write_byte(0x08, 0); /* дисплей выкл */
    lcd_write_byte(0x01, 0); /* очистка */
    HAL_Delay(2);
    lcd_write_byte(0x06, 0); /* режим инкремента */
    lcd_write_byte(0x0C, 0); /* дисплей вкл, курсор выкл */



	return 0;
}
void LCD1602_SetCursor(uint8_t row, uint8_t col)
{
    static const uint8_t offsets[] = {0x00, 0x40};
    lcd_write_byte(0x80 | (offsets[row] + col), 0);
}

void LCD1602_WriteChar(char c)
{
    lcd_write_byte(c, LCD_RS);
}

void LCD1602_WriteString(const char *str)
{
    while (*str) LCD1602_WriteChar(*str++);
}

void LCD1602_Backlight(uint8_t state)
{
    backlight = state ? LCD_BACKLIGHT : 0;
    uint8_t dummy = 0;
    HAL_I2C_Mem_Write(&hi2c1, LCD1602_ADDR, 0, I2C_MEMADD_SIZE_8BIT, &dummy, 1, HAL_MAX_DELAY);
}
void LCD1602_Clear()
{
	lcd_write_byte(0x01, 0);
}







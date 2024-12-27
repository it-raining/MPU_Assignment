/*
 * i2c-lcd.h
 *
 *  Created on: Dec 27, 2024
 *      Author: HP
 */

#ifndef INC_I2C_LCD_H_
#define INC_I2C_LCD_H_

#include "main.h"

#define LCD_ADDR 0x42

// LCD use 4-bit mode
// WRITE CMD MODE
// 0000 0100

#define LCD_CMD_DIS 0x0C
#define LCD_CMD_EN 0x08

#define LCD_CMD_MSB_EN(data)    ((data) & 0xF0)         | LCD_CMD_DIS
#define LCD_CMD_MSB_DIS(data)   ((data) & 0xF0)         | LCD_CMD_EN
#define LCD_CMD_LSB_EN(data)    (((data) << 4) & 0xF0)  | LCD_CMD_DIS
#define LCD_CMD_LSB_DIS(data)   (((data) << 4) & 0xF0)  | LCD_CMD_EN

// WRITE DATA MODE
#define LCD_DATA_DIS 0x0D
#define LCD_DATA_EN 0x09

#define LCD_DATA_MSB_EN(data)    ((data) & 0xF0)        | LCD_DATA_DIS
#define LCD_DATA_MSB_DIS(data)   ((data) & 0xF0)        | LCD_DATA_EN
#define LCD_DATA_LSB_EN(data)    (((data) << 4) & 0xF0) | LCD_DATA_DIS
#define LCD_DATA_LSB_DIS(data)   (((data) << 4) & 0xF0) | LCD_DATA_EN

// LCD commands
#define LCD_CLEAR_DISPLAY 0x01
#define LCD_CURSOR_SHIFT 0x10
#define LCD_4BIT_MODE 0x28
#define LCD_DISPLAY_AND_DISABLE_CURSOR 0x0C
#define LCD_CURSOR_INCREMENT 0x06
#define LCD_BACKLIGHT_ON 0x08

#define LCD_FREQ 10 // Hz 10hz = 400ms period

void Init_I2C(I2C_HandleTypeDef* hal_i2c);
void lcd_init();
void lcd_send_string(char *str);
void lcd_clear(void);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_backlight_on();
void lcd_display_number(int16_t num);
void lcd_display_mode();

#endif /* INC_I2C_LCD_H_ */

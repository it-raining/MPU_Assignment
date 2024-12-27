/*
 * i2c-lcd.c
 *
 *  Created on: Dec 27, 2024
 *      Author: HP
 */
#include "i2c-lcd.h"
I2C_HandleTypeDef *hi2c;


void lcd_backlight_on() {
	uint8_t data[1] = { LCD_BACKLIGHT_ON };
	HAL_I2C_Master_Transmit(hi2c, LCD_ADDR, (uint8_t*) data, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Transmit(hi2c, LCD_ADDR, (uint8_t*) data, 1, HAL_MAX_DELAY);
}
void Init_I2C(I2C_HandleTypeDef *hal_i2c) {
	hi2c = hal_i2c;
	lcd_init();
}
static uint8_t lcd_send_cmd(uint8_t cmd) {
	uint8_t buffer[4] = { LCD_CMD_MSB_EN(cmd), LCD_CMD_MSB_DIS(cmd),
			LCD_CMD_LSB_EN(cmd), LCD_CMD_LSB_DIS(cmd) };
	if (HAL_I2C_Master_Transmit(hi2c, LCD_ADDR, (uint8_t*) buffer, 4,
	HAL_MAX_DELAY) != HAL_OK) {
		return 0;
	}
	return 1;
}

static uint8_t lcd_send_data(uint8_t data) {
	uint8_t buffer[4] = { LCD_DATA_MSB_EN(data), LCD_DATA_MSB_DIS(data),
			LCD_DATA_LSB_EN(data), LCD_DATA_LSB_DIS(data) };
	if (HAL_I2C_Master_Transmit(hi2c, LCD_ADDR, (uint8_t*) buffer, 4,
	HAL_MAX_DELAY) != HAL_OK) {
		return 0;
	}
	return 1;
}


static void generate_str_from_mode(uint8_t status, char *str) {
	switch (status) {
	case RED:
		strcpy(str, "R");
		break;
	case GREEN:
		strcpy(str, "G");
		break;
	case AMBER:
		strcpy(str, "A");
		break;
	default:
		strcpy(str, "UNKNOWN");
		break;
	}
}
void lcd_init() {
	// Init LCD
	// 4 bit initialisation
	HAL_Delay(50);  // wait for >40ms
	lcd_send_cmd(0x30);
	HAL_Delay(5);  // wait for >4.1ms
	lcd_send_cmd(0x30);
	HAL_Delay(1);  // wait for >100us
	lcd_send_cmd(0x30);
	HAL_Delay(10);
	lcd_send_cmd(0x20);  // 4bit mode
	HAL_Delay(10);

	// dislay initialisation
	lcd_send_cmd(0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	lcd_send_cmd(0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(1);
	lcd_send_cmd(0x01);  // clear display
	HAL_Delay(1);
	HAL_Delay(1);
	lcd_send_cmd(0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	lcd_send_cmd(0x0C);

}

void lcd_send_string(char *str) {
	while (*str) {
		lcd_send_data(*str++);
	}
}

void lcd_clear(void) {
	lcd_send_cmd(LCD_CLEAR_DISPLAY);
	HAL_Delay(2);
}

void lcd_set_cursor(uint8_t row, uint8_t col) {
	uint8_t addr = 0;
	if (col >= 20)
		col = 0;
	if (row == 0) {
		addr = 0x80 + col;
	} else if (row == 1) {
		addr = 0xC0 + col;
	}
	lcd_send_cmd(addr);
}

void lcd_display_number(int16_t num) {
	char buffer[16];
	sprintf(buffer, "%d", num);
	lcd_send_string(buffer);
}

void lcd_display_mode(void) {
	lcd_clear();
	int curent_value = buffer;
	char buffer[6];
	char temp[16];
	switch (mode) {
	case AUTO:

		lcd_set_cursor(0, 0);
		lcd_send_string("MODE : AUTO");

		generate_str_from_mode(line_1, buffer);

		lcd_set_cursor(1, 0);
		sprintf(temp, "%s %d\0", buffer, count_1);
		lcd_send_string(temp);

		strcpy(temp, "");
		generate_str_from_mode(line_2, buffer);
		lcd_set_cursor(1, 8);
		sprintf(temp, "%s %d\0", buffer, count_2);
		lcd_send_string(temp);
		break;

	case MANUAL:

		generate_str_from_mode(line_1, buffer);

		lcd_set_cursor(0, 0);
		lcd_send_string("MODE : MANUAL");

		lcd_set_cursor(1, 0);
		sprintf(temp, "1: %s\0", buffer);
		lcd_send_string(temp);

		generate_str_from_mode(line_2, buffer);

		strcpy(temp, "");
		lcd_set_cursor(1, 10);
		sprintf(temp, "2: %s\0", buffer);
		lcd_send_string(temp);

		break;

	case MODIFY:

		generate_str_from_mode(line_1, buffer);

		lcd_set_cursor(0, 0);
		lcd_send_string("MODE : TUNING");

		lcd_set_cursor(1, 0);
		sprintf(temp, "%s TIME: %d\0", buffer, curent_value);
		lcd_send_string(temp);
		break;

	default:
		lcd_set_cursor(0, 0);
		lcd_send_string("MODE : UNKNOWN");
		break;
	}
}


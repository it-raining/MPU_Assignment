/*
 * led_processing.c
 *
 *  Created on: Oct 6, 2024
 *      Author: HP
 */

#include <fsm_traffic_light.h>
uint8_t led_buffer[NO_OF_7SEG] = { 0 };

// SCANNING 4 7SEG-LED TO DISPLAY NUMBER //

void update_buffer(uint8_t num_1, uint8_t num_2) {
	char temp[16];
	int state = line_1;
	lcd_clear_display();
	lcd_goto_XY(1, 0);
	switch (mode) {
	case AUTO:
		lcd_send_string(" MODE : AUTO");

		lcd_goto_XY(2, 0);
		sprintf(temp, "1: %d", num_1);
		lcd_send_string(temp);

		lcd_goto_XY(2, 8);
		strcpy(temp, "");
		sprintf(temp, "2: %d", num_2);
		lcd_send_string(temp);
		break;
	case MANUAL:
		lcd_send_string(" MODE : MANUAL");

		// Line 1 state
		state = line_1;
		lcd_goto_XY(2, 0);
		switch (state) {
		case RED:
			sprintf(temp, "st:RED");
			break;
		case AMBER:
			sprintf(temp, "st:AMBER");
			break;
		case GREEN:
			sprintf(temp, "st:GREEN");
			break;
		default:
			sprintf(temp, "st:----");
			break;
		}
		lcd_send_string(temp);

		// Line 2 state
		state = line_2;
		lcd_goto_XY(2, 8);
		switch (state) {
		case RED:
			sprintf(temp, "st:RED");
			break;
		case AMBER:
			sprintf(temp, "st:AMBER");
			break;
		case GREEN:
			sprintf(temp, "st:GREEN");
			break;
		default:
			sprintf(temp, "st:----");
			break;
		}
		lcd_send_string(temp);
		break;
	case MODIFY:
		lcd_send_string(" MODE : MODIFY");
		// Line 1 state
		state = line_1;
		lcd_goto_XY(2, 0);
		switch (state) {
		case RED:
			sprintf(temp, "st:RED");
			break;
		case AMBER:
			sprintf(temp, "st:AMBER");
			break;
		case GREEN:
			sprintf(temp, "st:GREEN");
			break;
		default:
			sprintf(temp, "st:----");
			break;
		}
		lcd_send_string(temp);

		lcd_goto_XY(2, 8);
		sprintf(temp, "val: %d", buffer);
		lcd_send_string(temp);
		break;
	default:
		break;
	}

}
void update_led_traffic() {
	switch (line_1) {
	case RED:
		HAL_GPIO_WritePin(LED_A_1_GPIO_Port, LED_A_1_Pin, 1);
		HAL_GPIO_WritePin(LED_B_1_GPIO_Port, LED_B_1_Pin, 1);
		if (count_1 <= 0) {
			line_1 = GREEN;
			count_1 = green_light;
		}
		break;
	case GREEN:
		HAL_GPIO_WritePin(LED_A_1_GPIO_Port, LED_A_1_Pin, 0);
		HAL_GPIO_WritePin(LED_B_1_GPIO_Port, LED_B_1_Pin, 1);
		if (count_1 <= 0) {
			line_1 = AMBER;
			count_1 = amber_light;
		}
		break;
	case AMBER:
		HAL_GPIO_WritePin(LED_A_1_GPIO_Port, LED_A_1_Pin, 1);
		HAL_GPIO_WritePin(LED_B_1_GPIO_Port, LED_B_1_Pin, 0);
		if (count_1 <= 0) {
			line_1 = RED;
			count_1 = red_light;
		}
		break;
	}
	//	LED_RED_2_GPIO_Port->ODR |= ALL_LED;
	switch (line_2) {
	case RED:
		HAL_GPIO_WritePin(LED_A_2_GPIO_Port, LED_A_2_Pin, 1);
		HAL_GPIO_WritePin(LED_B_2_GPIO_Port, LED_B_2_Pin, 1);
		if (count_2 <= 0) {
			line_2 = GREEN;
			count_2 = green_light;
		}
		break;
	case GREEN:
		HAL_GPIO_WritePin(LED_A_2_GPIO_Port, LED_A_2_Pin, 0);
		HAL_GPIO_WritePin(LED_B_2_GPIO_Port, LED_B_2_Pin, 1);
		if (count_2 <= 0) {
			line_2 = AMBER;
			count_2 = amber_light;
		}
		break;
	case AMBER:
		HAL_GPIO_WritePin(LED_A_2_GPIO_Port, LED_A_2_Pin, 1);
		HAL_GPIO_WritePin(LED_B_2_GPIO_Port, LED_B_2_Pin, 0);
		if (count_2 <= 0) {
			line_2 = RED;
			count_2 = red_light;
		}
		break;
	}
}

// AUTOMATIC RUN DEFINE //
void fsm_for_auto(void) {
	update_buffer(count_1, count_2);
	update_led_traffic();
	if (count_1 > 0)
		count_1 = count_1 - 1;
	if (count_2 > 0)
		count_2 = count_2 - 1;
}
void fsm_for_manual(void) {
	count_1 = 1;
	count_2 = 1;
	update_buffer(0, 0);
	update_led_traffic();
}

void fsm_for_modify() {
	update_buffer(0, 0);
	switch (line_1) {
	case RED:
		update_buffer(01, buffer);
		HAL_GPIO_WritePin(LED_A_1_GPIO_Port, LED_A_1_Pin, 1);
		HAL_GPIO_WritePin(LED_B_1_GPIO_Port, LED_B_1_Pin, 1);
		HAL_GPIO_WritePin(LED_A_2_GPIO_Port, LED_A_2_Pin, 1);
		HAL_GPIO_WritePin(LED_B_2_GPIO_Port, LED_B_2_Pin, 1);
		break;
	case AMBER:
		update_buffer(02, buffer);
		HAL_GPIO_WritePin(LED_A_1_GPIO_Port, LED_A_1_Pin, 1);
		HAL_GPIO_WritePin(LED_B_1_GPIO_Port, LED_B_1_Pin, 0);
		HAL_GPIO_WritePin(LED_A_2_GPIO_Port, LED_A_2_Pin, 1);
		HAL_GPIO_WritePin(LED_B_2_GPIO_Port, LED_B_2_Pin, 0);
		break;
	case GREEN:
		update_buffer(03, buffer);
		HAL_GPIO_WritePin(LED_A_1_GPIO_Port, LED_A_1_Pin, 0);
		HAL_GPIO_WritePin(LED_B_1_GPIO_Port, LED_B_1_Pin, 1);
		HAL_GPIO_WritePin(LED_A_2_GPIO_Port, LED_A_2_Pin, 0);
		HAL_GPIO_WritePin(LED_B_2_GPIO_Port, LED_B_2_Pin, 1);
		break;
	default:
		break;
	}
}

void fsm_for_traffic_light(void) {
	switch (mode) {
	case INIT:
		LED_A_1_GPIO_Port->ODR |= ALL_LED;
		amber_light = red_light - green_light; // adjust timing
		count_1 = red_light;
		count_2 = green_light;
		line_1 = RED, line_2 = GREEN;
		mode = AUTO;
		break;
	case AUTO:
		buffer++;
		if (buffer % 2 == 1)
			fsm_for_auto();
		break;
	case MANUAL:
		fsm_for_manual();
		break;
	case MODIFY:
		fsm_for_modify();
		break;
	default:
		break;
	}
}

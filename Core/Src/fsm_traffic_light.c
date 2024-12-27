/*
 * led_processing.c
 *
 *  Created on: Oct 6, 2024
 *      Author: HP
 */

#include <fsm_traffic_light.h>
uint8_t led_buffer[NO_OF_7SEG] = { 0 };
uint8_t count_1, count_2;
static uint8_t scanning_idx = 0;
uint16_t EN_Pin[NO_OF_7SEG] = { EN0_Pin, EN1_Pin, EN2_Pin, EN3_Pin };

void display7SEG(int num) {
	SEG_0_GPIO_Port->ODR &= ~ALL_SEG;
	switch (num) {
	case 0:
		SEG_0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_0); // 0
		break;
	case 1:
		SEG_0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_1); // 1
		break;
	case 2:
		SEG_0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_2); // 2
		break;
	case 3:
		SEG_0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_3); // 3
		break;
	case 4:
		SEG_0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_4); // 4
		break;
	case 5:
		SEG_0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_5); // 5
		break;
	case 6:
		SEG_0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_6); // 6
		break;
	case 7:
		SEG_0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_7); // 7
		break;
	case 8:
		SEG_0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_8); // 8
		break;
	case 9:
		SEG_0_GPIO_Port->ODR |= (ALL_SEG & ~NUM_9); // 9
		break;
	default:
		SEG_0_GPIO_Port->ODR |= (ALL_SEG); // Turn off all segments
	}
}

// SCANNING 4 7SEG-LED TO DISPLAY NUMBER //

void update_buffer(uint8_t num_1, uint8_t num_2) {
	led_buffer[0] = num_1 / 10;
	led_buffer[1] = num_1 % 10;
	led_buffer[2] = num_2 / 10;
	led_buffer[3] = num_2 % 10;
}
void scanning_led(void) {
	EN0_GPIO_Port->ODR |= (EN0_Pin | EN1_Pin | EN2_Pin | EN3_Pin);
	display7SEG(led_buffer[scanning_idx]);
	EN0_GPIO_Port->ODR &= ~(EN_Pin[scanning_idx]);
	scanning_idx = (scanning_idx + 1) % NO_OF_7SEG;
}
void update_led_traffic() {
	LED_RED_1_GPIO_Port->ODR |= ALL_LED;
	switch (line_1) {
	case RED:
		LED_RED_1_GPIO_Port->ODR &= ~(LED_RED_1_Pin);
		if (count_1 <= 0) {
			line_1 = GREEN;
			count_1 = green_light;
		}
		break;
	case GREEN:
		LED_GREEN_1_GPIO_Port->ODR &= ~(LED_GREEN_1_Pin);
		if (count_1 <= 0) {
			line_1 = AMBER;
			count_1 = amber_light;
		}
		break;
	case AMBER:
		LED_AMBER_1_GPIO_Port->ODR &= ~(LED_AMBER_1_Pin);
		if (count_1 <= 0) {
			line_1 = RED;
			count_1 = red_light;
		}
		break;
	}
	//	LED_RED_2_GPIO_Port->ODR |= ALL_LED;
	switch (line_2) {
	case RED:
		LED_RED_2_GPIO_Port->ODR &= ~(LED_RED_2_Pin);
		if (count_2 <= 0) {
			line_2 = GREEN;
			count_2 = green_light;
		}
		break;
	case GREEN:
		LED_RED_2_GPIO_Port->ODR &= ~(LED_GREEN_2_Pin);
		if (count_2 <= 0) {
			line_2 = AMBER;
			count_2 = amber_light;
		}
		break;
	case AMBER:
		LED_RED_2_GPIO_Port->ODR &= ~(LED_AMBER_2_Pin);
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
	update_led_traffic();
}

void fsm_for_modify() {
	switch (line_1) {
	case RED:
		update_buffer(01, buffer);
		HAL_GPIO_TogglePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin);
		HAL_GPIO_TogglePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin);
		break;
	case AMBER:
		update_buffer(02, buffer);
		HAL_GPIO_TogglePin(LED_AMBER_1_GPIO_Port, LED_AMBER_1_Pin);
		HAL_GPIO_TogglePin(LED_AMBER_2_GPIO_Port, LED_AMBER_2_Pin);
		break;
	case GREEN:
		update_buffer(03, buffer);
		HAL_GPIO_TogglePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin);
		HAL_GPIO_TogglePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin);
		break;
	}
}

void fsm_for_traffic_light(void) {
	switch (mode) {
	case INIT:
		LED_RED_1_GPIO_Port->ODR |= ALL_LED;
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
		buffer++;
		if (buffer % 2 == 1)
			fsm_for_manual();
		break;
	case MODIFY:
		fsm_for_modify();
		break;
	default:
		break;
	}
}

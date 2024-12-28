/*
 * fsm_for_button.c
 *
 *  Created on: Dec 27, 2024
 *      Author: HP
 */

#include "fsm_for_button.h"

enum ButtonState button_state[NO_OF_BUTTONS] = { 1, 1, 1 };

void fsm_for_button(void) {
	////////////////// BUTTON 1 ////////////////////////////
	switch (button_state[MODIFY_BUTTON]) {
	case BUTTON_RELEASED:
		if (is_button_pressed(MODIFY_BUTTON)) {
			LED_A_1_GPIO_Port->ODR |= ALL_LED;
			switch (mode) {
			case AUTO:
				mode = MANUAL;
				line_1 = RED;
				line_2 = GREEN;
				break;
			case MANUAL:
				mode = MODIFY;
				buffer = red_light;
				line_1 = RED;
				line_2 = RED;
				break;
			case MODIFY:
				mode = INIT;
				break;
			default:
				mode = INIT;
				break;
			}
			button_state[MODIFY_BUTTON] = BUTTON_PRESSED;
		}
		break;
	case BUTTON_PRESSED:
		if (!is_button_pressed(MODIFY_BUTTON)) {
			button_state[MODIFY_BUTTON] = BUTTON_RELEASED;
		} else {
			if (is_button_pressed_1s(MODIFY_BUTTON)) {
				button_state[MODIFY_BUTTON] = BUTTON_PRESSED_MORE_THAN_1_SECOND;
			}
		}
		break;
	case BUTTON_PRESSED_MORE_THAN_1_SECOND:
		if (!is_button_pressed(MODIFY_BUTTON)) {
			button_state[MODIFY_BUTTON] = BUTTON_RELEASED;
		}
		break;
	}
	////////////////// BUTTON 2 ////////////////////////////

	switch (button_state[STATE_BUTTON]) {
	case BUTTON_RELEASED:
		if (is_button_pressed(STATE_BUTTON)) {
			button_state[STATE_BUTTON] = BUTTON_PRESSED;
		}
		break;
	case BUTTON_PRESSED:
		if (!is_button_pressed(STATE_BUTTON)) {
			switch (mode) {
			case MANUAL:
				line_1 = (line_1 + 1) % NO_OF_STATE;
				line_2 = (line_2 + 1) % NO_OF_STATE;
				break;
			case MODIFY:
				line_1 = (line_1 + 1) % NO_OF_STATE;
				switch (line_1) {
				case RED:
					buffer = red_light;
					break;
				case AMBER:
					buffer = amber_light;
					break;
				case GREEN:
					buffer = green_light;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
			button_state[STATE_BUTTON] = BUTTON_RELEASED;
		} else {
			if (is_button_pressed_1s(STATE_BUTTON)) {
				if (mode == MODIFY) {
					switch (line_1) {
					case RED:
						red_light = buffer;
						break;
					case AMBER:
						amber_light = buffer;
						break;
					case GREEN:
						green_light = buffer;
						break;
					default:
						break;
					}
				}
				button_state[STATE_BUTTON] = BUTTON_PRESSED_MORE_THAN_1_SECOND;
			}
		}
		break;
	case BUTTON_PRESSED_MORE_THAN_1_SECOND:
		if (!is_button_pressed(STATE_BUTTON)) {
			button_state[STATE_BUTTON] = BUTTON_RELEASED;
		}
		break;
	}

	////////////////// BUTTON 3 ////////////////////////////
	switch (button_state[INC_BUTTON]) {
	case BUTTON_RELEASED:
		if (is_button_pressed(INC_BUTTON)) {
			button_state[INC_BUTTON] = BUTTON_PRESSED;
		}
		break;
	case BUTTON_PRESSED:
		if (!is_button_pressed(INC_BUTTON)) {
			if (mode == MODIFY) {
				if (line_1 == GREEN && buffer >= red_light)
					buffer = 0;
				buffer++;

			}
			button_state[INC_BUTTON] = BUTTON_RELEASED;
		} else {
			if (is_button_pressed_1s(INC_BUTTON)) {
				button_state[INC_BUTTON] = BUTTON_PRESSED_MORE_THAN_1_SECOND;
			}
		}
		break;
	case BUTTON_PRESSED_MORE_THAN_1_SECOND:
		if (!is_button_pressed(INC_BUTTON)) {
			button_state[INC_BUTTON] = BUTTON_RELEASED;
		}
		break;
	}
}


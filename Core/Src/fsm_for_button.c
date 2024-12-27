/*
 * fsm_for_button.c
 *
 *  Created on: Dec 27, 2024
 *      Author: HP
 */

#include "fsm_for_button.h"

enum ButtonState button_state[NO_OF_BUTTONS];

void fsm_for_button(void) {
	////////////////// BUTTON 1 ////////////////////////////
	switch (button_state[MODIFY_BUTTON]) {
	case BUTTON_RELEASED:
		if (is_button_pressed(MODIFY_BUTTON)) {
			LED_RED_1_GPIO_Port->ODR |= ALL_LED;
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

	switch (button_state[INCREASE_BUTTON]) {
	case BUTTON_RELEASED:
		if (is_button_pressed(INCREASE_BUTTON)) {
			buffer = (buffer + 1) % 100;
			button_state[INCREASE_BUTTON] = BUTTON_PRESSED;
		}
		break;
	case BUTTON_PRESSED:
		if (!is_button_pressed(INCREASE_BUTTON)) {
			button_state[INCREASE_BUTTON] = BUTTON_RELEASED;
		} else {
			if (is_button_pressed_1s(INCREASE_BUTTON)) {
				button_state[INCREASE_BUTTON] =
						BUTTON_PRESSED_MORE_THAN_1_SECOND;
			}
		}
		break;
	case BUTTON_PRESSED_MORE_THAN_1_SECOND:
		if (!is_button_pressed(INCREASE_BUTTON)) {
			button_state[INCREASE_BUTTON] = BUTTON_RELEASED;
		}
		//		if (is_avail(HOLD) == 1) {
		//			buffer = (buffer + 1) % 100;
		//			setTimer(HOLD, HALF_SEC);
		//		}
		break;
	}
	switch (button_state[SET_BUTTON]) {
	case BUTTON_RELEASED:
		if (is_button_pressed(SET_BUTTON)) {
			switch (mode) {
			case MODIFY_RED:
				red_light = buffer;
				break;
			case MODIFY_AMBER:
				amber_light = buffer;
				break;
			case MODIFY_GREEN:
				green_light = buffer;
				break;
			default:
			}
			button_state[SET_BUTTON] = BUTTON_PRESSED;
		}
		break;
	case BUTTON_PRESSED:
		if (!is_button_pressed(SET_BUTTON)) {
			button_state[SET_BUTTON] = BUTTON_RELEASED;
		} else {
			if (is_button_pressed_1s(SET_BUTTON)) {
				button_state[SET_BUTTON] = BUTTON_PRESSED_MORE_THAN_1_SECOND;
			}
		}
		break;
	case BUTTON_PRESSED_MORE_THAN_1_SECOND:
		if (!is_button_pressed(SET_BUTTON)) {
			button_state[SET_BUTTON] = BUTTON_RELEASED;
		}
		break;
	}
}

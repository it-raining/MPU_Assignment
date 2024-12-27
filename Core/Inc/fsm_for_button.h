/*
 * fsm_for_button.h
 *
 *  Created on: Dec 27, 2024
 *      Author: HP
 */

#ifndef INC_FSM_FOR_BUTTON_H_
#define INC_FSM_FOR_BUTTON_H_
#include "main.h"
#include "input_reading.h"
enum ButtonState {
	BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND
};

void fsm_for_button(void);

#endif /* INC_FSM_FOR_BUTTON_H_ */

/*
 * input_reading.h
 *
 *  Created on: Oct 4, 2024
 *      Author: HP
 */

#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_
#include "main.h"

#define NO_OF_BUTTONS 3
#define MODIFY_BUTTON 0
#define INCREASE_BUTTON 1
#define SET_BUTTON 2
#define DURATION_FOR_AUTO_INCREASING 100
#define BUTTON_IS_PRESSED GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET


void button_reading(void);
unsigned char is_button_pressed(unsigned char index);
unsigned char is_button_pressed_1s(unsigned char index);
#endif /* INC_INPUT_READING_H_ */

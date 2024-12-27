/*
 * input_reading.c
 *
 *  Created on: Oct 4, 2024
 *      Author: HP
 */
#include "input_reading.h"

static GPIO_PinState buttonBuffer[NO_OF_BUTTONS] = { 1, 1, 1 };
static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS] = { 0 };
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS] = { 0 };
static uint8_t flagForButtonPress1s[NO_OF_BUTTONS] = { 0 };
static uint16_t counterForButtonPress1s[NO_OF_BUTTONS] = { 0 };
GPIO_TypeDef *BTN_Port[NO_OF_BUTTONS] = { BTN1_GPIO_Port, BTN2_GPIO_Port,
		BTN3_GPIO_Port };
uint16_t BTN_Pin[NO_OF_BUTTONS] = { BTN1_Pin, BTN2_Pin, BTN3_Pin };

void button_reading(void) {
	for (uint8_t i = 0; i < NO_OF_BUTTONS; i++) {
//		buttonBuffer[i] = GPIO_PIN_SET;
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BTN_Port[i], BTN_Pin[i]);
		if (debounceButtonBuffer1[i] == debounceButtonBuffer2[i])
			buttonBuffer[i] = debounceButtonBuffer2[i];
		if (buttonBuffer[i] == BUTTON_IS_PRESSED) {
			// if a button is pressed , we start counting
			if (counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING) {
				counterForButtonPress1s[i]++;
			} else {
				flagForButtonPress1s[i] = 1;
				// todo
			}
		} else {
			counterForButtonPress1s[i] = 0;
			flagForButtonPress1s[i] = 0;
		}
	}
}
unsigned char is_button_pressed(uint8_t index) {
	if (index >= NO_OF_BUTTONS)
		return 0;
	return (buttonBuffer[index] == BUTTON_IS_PRESSED);
}
unsigned char is_button_pressed_1s(unsigned char index) {
	if (index >= NO_OF_BUTTONS)
		return 0xff;
	return (flagForButtonPress1s[index] == 1);
}

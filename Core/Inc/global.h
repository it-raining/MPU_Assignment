/*
 * global.h
 *
 *  Created on: Nov 25, 2024
 *      Author: HP
 */
#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_
#include "main.h"
#define ONE_SEC 1000
#define ALL_LED (LED_RED_1_Pin | LED_GREEN_1_Pin | LED_AMBER_1_Pin | LED_RED_2_Pin | LED_GREEN_2_Pin | LED_AMBER_2_Pin)

typedef enum {
	INIT, AUTO, MANUAL, MODIFY
} MODE;
typedef enum {
	RED, GREEN, AMBER
} STATE;

extern MODE mode;
extern STATE line_1, line_2;
extern uint8_t buffer;
extern uint8_t red_light, amber_light, green_light;
extern uint32_t state_ID;
#endif /* INC_GLOBAL_H_ */

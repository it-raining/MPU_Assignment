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
#define ALL_LED (LED_A_1_Pin | LED_B_1_Pin | LED_A_2_Pin | LED_B_2_Pin)
#define NO_OF_STATE 3
#define NO_OF_MODE 4

typedef enum {
	INIT, AUTO, MANUAL, MODIFY
} MODE;
typedef enum {
	RED, GREEN, AMBER
} STATE;

extern MODE mode;
extern STATE line_1, line_2;
extern uint8_t count_1, count_2;
extern uint8_t buffer;
extern uint8_t red_light, amber_light, green_light;
extern uint32_t state_ID;
#endif /* INC_GLOBAL_H_ */

/*
 * led_processing.h
 *
 *  Created on: Oct 6, 2024
 *      Author: HP
 */

#ifndef INC_LED_PROCESSING_H_
#define INC_LED_PROCESSING_H_
#include "main.h"
#include "fsm_for_button.h"
#include "i2c-lcd.h"

#define NO_OF_7SEG 4 	//fixed
#define SCANNING_FREQ 	1 //Hz
#define BLINKY_FREQ 	1 //Hz
#define EXPIRED_PERIOD	10000 //ms

void fsm_for_traffic_light(void);

#endif /* INC_LED_PROCESSING_H_ */

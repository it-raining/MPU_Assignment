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


#define NUM_0   (SEG_0_Pin | SEG_1_Pin | SEG_2_Pin | SEG_3_Pin | SEG_4_Pin | SEG_5_Pin)
#define NUM_1   (SEG_1_Pin | SEG_2_Pin)
#define NUM_2   (SEG_0_Pin | SEG_1_Pin | SEG_3_Pin | SEG_4_Pin | SEG_6_Pin)
#define NUM_3   (SEG_0_Pin | SEG_1_Pin | SEG_2_Pin | SEG_3_Pin | SEG_6_Pin)
#define NUM_4   (SEG_1_Pin | SEG_2_Pin | SEG_5_Pin | SEG_6_Pin)
#define NUM_5   (SEG_0_Pin | SEG_2_Pin | SEG_3_Pin | SEG_5_Pin | SEG_6_Pin)
#define NUM_6   (SEG_0_Pin | SEG_2_Pin | SEG_3_Pin | SEG_4_Pin | SEG_5_Pin | SEG_6_Pin)
#define NUM_7   (SEG_0_Pin | SEG_1_Pin | SEG_2_Pin)
#define NUM_8   (SEG_0_Pin | SEG_1_Pin | SEG_2_Pin | SEG_3_Pin | SEG_4_Pin | SEG_5_Pin | SEG_6_Pin)
#define NUM_9   (SEG_0_Pin | SEG_1_Pin | SEG_2_Pin | SEG_3_Pin | SEG_5_Pin | SEG_6_Pin)
#define ALL_SEG (SEG_0_Pin | SEG_1_Pin | SEG_2_Pin | SEG_3_Pin | SEG_4_Pin | SEG_5_Pin | SEG_6_Pin)


void scanning_led(void);
void fsm_for_traffic_light(void);

#endif /* INC_LED_PROCESSING_H_ */

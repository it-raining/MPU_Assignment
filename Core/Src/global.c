/*
 * global.c
 *
 *  Created on: Nov 25, 2024
 *      Author: HP
 */
#include "global.h"

MODE mode = INIT;
STATE line_1 = RED, line_2 = GREEN;
uint8_t buffer = 0;
uint32_t state_ID = 0;
uint8_t red_light = 5;
uint8_t amber_light = 2;
uint8_t green_light = 3;

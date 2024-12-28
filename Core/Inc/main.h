/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "scheduler.h"
#include "global.h"
#include "input_reading.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define SEG_0_Pin GPIO_PIN_0
#define SEG_0_GPIO_Port GPIOC
#define SEG_1_Pin GPIO_PIN_1
#define SEG_1_GPIO_Port GPIOC
#define SEG_2_Pin GPIO_PIN_2
#define SEG_2_GPIO_Port GPIOC
#define SEG_3_Pin GPIO_PIN_3
#define SEG_3_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define RED_LED_Pin GPIO_PIN_5
#define RED_LED_GPIO_Port GPIOA
#define SEG_4_Pin GPIO_PIN_4
#define SEG_4_GPIO_Port GPIOC
#define SEG_5_Pin GPIO_PIN_5
#define SEG_5_GPIO_Port GPIOC
#define LED_A_2_Pin GPIO_PIN_10
#define LED_A_2_GPIO_Port GPIOB
#define EN0_Pin GPIO_PIN_12
#define EN0_GPIO_Port GPIOB
#define EN1_Pin GPIO_PIN_13
#define EN1_GPIO_Port GPIOB
#define EN2_Pin GPIO_PIN_14
#define EN2_GPIO_Port GPIOB
#define EN3_Pin GPIO_PIN_15
#define EN3_GPIO_Port GPIOB
#define SEG_6_Pin GPIO_PIN_6
#define SEG_6_GPIO_Port GPIOC
#define BTN1_Pin GPIO_PIN_7
#define BTN1_GPIO_Port GPIOC
#define LED_BLUE_Pin GPIO_PIN_9
#define LED_BLUE_GPIO_Port GPIOC
#define BTN3_Pin GPIO_PIN_8
#define BTN3_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define LED_B_1_Pin GPIO_PIN_3
#define LED_B_1_GPIO_Port GPIOB
#define LED_B_2_Pin GPIO_PIN_4
#define LED_B_2_GPIO_Port GPIOB
#define LED_A_1_Pin GPIO_PIN_5
#define LED_A_1_GPIO_Port GPIOB
#define BTN2_Pin GPIO_PIN_6
#define BTN2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

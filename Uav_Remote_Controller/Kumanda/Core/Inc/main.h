/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define Extra_Pot1_ADC_Pin GPIO_PIN_0
#define Extra_Pot1_ADC_GPIO_Port GPIOA
#define Extra_Pot2_ADC_Pin GPIO_PIN_1
#define Extra_Pot2_ADC_GPIO_Port GPIOA
#define Throttle_Pot_ADC_Pin GPIO_PIN_4
#define Throttle_Pot_ADC_GPIO_Port GPIOA
#define Yaw_Pot_ADC_Pin GPIO_PIN_5
#define Yaw_Pot_ADC_GPIO_Port GPIOA
#define Roll_Pot_ADC_Pin GPIO_PIN_6
#define Roll_Pot_ADC_GPIO_Port GPIOA
#define Pitch_Pot_ADC_Pin GPIO_PIN_7
#define Pitch_Pot_ADC_GPIO_Port GPIOA
#define Battery_Voltage_ADC_Pin GPIO_PIN_0
#define Battery_Voltage_ADC_GPIO_Port GPIOB
#define NRF_CSN_Pin GPIO_PIN_14
#define NRF_CSN_GPIO_Port GPIOB
#define NRF_CE_Pin GPIO_PIN_15
#define NRF_CE_GPIO_Port GPIOB
#define NRF_IRQ_Pin GPIO_PIN_8
#define NRF_IRQ_GPIO_Port GPIOA
#define Switch4_input_Pin GPIO_PIN_6
#define Switch4_input_GPIO_Port GPIOB
#define Switch3_input_Pin GPIO_PIN_7
#define Switch3_input_GPIO_Port GPIOB
#define Switch2_input_Pin GPIO_PIN_8
#define Switch2_input_GPIO_Port GPIOB
#define Switch1_input_Pin GPIO_PIN_9
#define Switch1_input_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

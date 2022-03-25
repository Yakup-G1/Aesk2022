/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "AESK_NRF24.h"
#include "AESK_Data_Pack_lib.h"
#include "FlightDatas.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

  bool onReceiveFlag = true;

  float yaw;
  float roll;
  float pitch;
  float altitude;
  uint16_t motor1;
  uint16_t motor2;
  uint16_t motor3;
  uint16_t motor4;
  float yawError;
  float rollError;
  float pitchError;
  float altitudeError;
  float latitude_f32;
  float longtitude_f32;

  uint64_t thisNode = 0x11223344AA;
  uint64_t node = 0x11223344BB;

//  uint64_t thisNode = 0x11223344CC;
//  uint64_t node = 0x11223344AA;
//
//  uint16_t adc1;
//  uint16_t adc2;
//  uint16_t adc3;
//  uint16_t adc4;
//  uint16_t adc5;
//  uint16_t adc6;
//  uint16_t adc7;
//  uint16_t adc8;
//  uint16_t adc9;
//  uint16_t adc10;

  uint16_t indexTx;

  uint16_t counter = 0;

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */
void onReceive(uint8_t * pack, uint16_t len);
void parseBuffer(uint8_t * buffer);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  AESK_NRF24_DATA_Init(48, thisNode, &onReceive);
  AESK_NRF24_Init(&hspi1, NRF_CSN_GPIO_Port, NRF_CSN_Pin, NRF_CE_Pin);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  if(tt.time_task_t.task_50_Hz == 1 && onReceiveFlag == 1)
	  {
		  counter += 1;
		  indexTx = 2;

//		  adc1 = counter*50/500;
//		  adc2 = counter*100/500;
//		  adc3 = counter*150/500;
//		  adc4 = counter*200/500;
//		  adc5 = counter*250/500;
//		  adc6 = counter*300/500;
//		  adc7 = counter*350/500;
//		  adc8 = counter*400/500;
//		  adc9 = counter*450/500;
//		  adc10 = counter*500/500;
//
//		  AESK_UINT16toUINT8_LE(&adc1, aesk_nrf24_data.TxBuffer,&indexTx);
//		  AESK_UINT16toUINT8_LE(&adc2, aesk_nrf24_data.TxBuffer,&indexTx);
//		  AESK_UINT16toUINT8_LE(&adc3, aesk_nrf24_data.TxBuffer,&indexTx);
//		  AESK_UINT16toUINT8_LE(&adc4, aesk_nrf24_data.TxBuffer,&indexTx);
//		  AESK_UINT16toUINT8_LE(&adc5, aesk_nrf24_data.TxBuffer,&indexTx);
//		  AESK_UINT16toUINT8_LE(&adc6, aesk_nrf24_data.TxBuffer,&indexTx);
//		  AESK_UINT16toUINT8_LE(&adc7, aesk_nrf24_data.TxBuffer,&indexTx);
//		  AESK_UINT16toUINT8_LE(&adc8, aesk_nrf24_data.TxBuffer,&indexTx);
//		  AESK_UINT16toUINT8_LE(&adc9, aesk_nrf24_data.TxBuffer,&indexTx);
//		  AESK_UINT16toUINT8_LE(&adc10, aesk_nrf24_data.TxBuffer,&indexTx);

		  yaw = counter*255/500;
		  roll = counter*180/500;
		  pitch = counter*180/500;
		  altitude = counter;
		  motor1 = 1000 + counter*700/500;
		  motor2 = 1000 + counter*700/500;
		  motor3 = 1000 + counter*700/500;
		  motor4 = 1000 + counter*700/500;
		  yawError = yaw - 55;
		  rollError = roll - 45;
		  pitchError = pitch - 45;
		  altitudeError = altitude - 3;
		  latitude_f32 = 41.02539 - counter*0.0001;
		  longtitude_f32 = 28.88818 - counter*0.0001;

		  AESK_FLOAT32toUINT8_LE(&yaw,aesk_nrf24_data.TxBuffer,&indexTx);
		  AESK_FLOAT32toUINT8_LE(&roll,aesk_nrf24_data.TxBuffer,&indexTx);
		  AESK_FLOAT32toUINT8_LE(&pitch,aesk_nrf24_data.TxBuffer,&indexTx);
		  AESK_FLOAT32toUINT8_LE(&altitude, aesk_nrf24_data.TxBuffer,&indexTx);

		  AESK_UINT16toUINT8_LE(&motor1,aesk_nrf24_data.TxBuffer ,&indexTx);
		  AESK_UINT16toUINT8_LE(&motor2,aesk_nrf24_data.TxBuffer ,&indexTx);
		  AESK_UINT16toUINT8_LE(&motor3,aesk_nrf24_data.TxBuffer ,&indexTx);
		  AESK_UINT16toUINT8_LE(&motor4,aesk_nrf24_data.TxBuffer ,&indexTx);

		  AESK_FLOAT32toUINT8_LE(&yawError,aesk_nrf24_data.TxBuffer ,&indexTx);
		  AESK_FLOAT32toUINT8_LE(&rollError,aesk_nrf24_data.TxBuffer ,&indexTx);
		  AESK_FLOAT32toUINT8_LE(&pitchError,aesk_nrf24_data.TxBuffer ,&indexTx);
		  AESK_FLOAT32toUINT8_LE(&altitudeError,aesk_nrf24_data.TxBuffer ,&indexTx);

		  AESK_FLOAT32toUINT8_LE(&latitude_f32,aesk_nrf24_data.TxBuffer ,&indexTx);
		  AESK_FLOAT32toUINT8_LE(&longtitude_f32,aesk_nrf24_data.TxBuffer ,&indexTx);

		  aesk_nrf24_data.TxBuffer[0] = 'A';
		  aesk_nrf24_data.TxBuffer[1] = indexTx;

		  AESK_NRF24_WritePack(aesk_nrf24_data.TxBuffer, indexTx, node);

		  if(counter == 500)
			  counter = 0;

		  tt.time_task_t.task_50_Hz = 0;
	  }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, NRF_CE_Pin|NRF_CSN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : NRF_CE_Pin NRF_CSN_Pin */
  GPIO_InitStruct.Pin = NRF_CE_Pin|NRF_CSN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : NRF_IRQ_Pin */
  GPIO_InitStruct.Pin = NRF_IRQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(NRF_IRQ_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	onReceiveFlag = 0;

	AESK_NRF24_ReadPack();

	onReceiveFlag = 1;
}
void onReceive(uint8_t * pack, uint16_t len)
{
	if(*pack == 'P' || *pack == 'G')
		AESK_NRF24_WritePack(pack, len, node);

	parseBuffer(pack);

	onReceiveFlag = 1;
}

void parseBuffer(uint8_t * buffer)
{
	uint16_t index = 2;

	if(aesk_nrf24_data.RxBuffer[0] == 'P')
	{
		AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.RollPitchKp,buffer,&index);
		AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.RollPitchKi,buffer,&index);
		AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.RollPitchKd,buffer,&index);

		AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.YawKp,buffer,&index);
		AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.YawKi,buffer,&index);
		AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.YawKd,buffer,&index);

		AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.AltitudeKp,buffer,&index);
		AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.AltitudeKi,buffer,&index);
		AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.AltitudeKd,buffer,&index);

		AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.GpsKp,buffer,&index);
		AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.GpsKi,buffer,&index);
		AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.GpsKd,buffer,&index);

		AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.Ext1Kp,buffer,&index);
		AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.Ext1Ki,buffer,&index);
		AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.Ext1Kd,buffer,&index);

		AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.Ext2Kp,buffer,&index);
		AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.Ext2Ki,buffer,&index);
		AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.Ext2Kd,buffer,&index);


		aesk_Rx_Datas_Float.floatRollPitchKp = (float)aesk_Rx_Datas_Int.RollPitchKp/100000;
		aesk_Rx_Datas_Float.floatRollPitchKi = (float)aesk_Rx_Datas_Int.RollPitchKi/100000;
		aesk_Rx_Datas_Float.floatRollPitchKd = (float)aesk_Rx_Datas_Int.RollPitchKd/100000;

		aesk_Rx_Datas_Float.floatYawKp = (float)aesk_Rx_Datas_Int.YawKp/100000;
		aesk_Rx_Datas_Float.floatYawKi = (float)aesk_Rx_Datas_Int.YawKi/100000;
		aesk_Rx_Datas_Float.floatYawKd = (float)aesk_Rx_Datas_Int.YawKd/100000;

		aesk_Rx_Datas_Float.floatAltitudeKp = (float)aesk_Rx_Datas_Int.AltitudeKp/100000;
		aesk_Rx_Datas_Float.floatAltitudeKi = (float)aesk_Rx_Datas_Int.AltitudeKi/100000;
		aesk_Rx_Datas_Float.floatAltitudeKd = (float)aesk_Rx_Datas_Int.AltitudeKd/100000;

		aesk_Rx_Datas_Float.floatGpsKp = (float)aesk_Rx_Datas_Int.GpsKp/100000;
		aesk_Rx_Datas_Float.floatGpsKi = (float)aesk_Rx_Datas_Int.GpsKi/100000;
		aesk_Rx_Datas_Float.floatGpsKd = (float)aesk_Rx_Datas_Int.GpsKd/100000;

		aesk_Rx_Datas_Float.floatExt1Kp = (float)aesk_Rx_Datas_Int.Ext1Kp/100000;
		aesk_Rx_Datas_Float.floatExt1Ki = (float)aesk_Rx_Datas_Int.Ext1Ki/100000;
		aesk_Rx_Datas_Float.floatExt1Kd = (float)aesk_Rx_Datas_Int.Ext1Kd/100000;

		aesk_Rx_Datas_Float.floatExt2Kp = (float)aesk_Rx_Datas_Int.Ext2Kp/100000;
		aesk_Rx_Datas_Float.floatExt2Ki = (float)aesk_Rx_Datas_Int.Ext2Ki/100000;
		aesk_Rx_Datas_Float.floatExt2Kd = (float)aesk_Rx_Datas_Int.Ext2Kd/100000;
	}

}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */


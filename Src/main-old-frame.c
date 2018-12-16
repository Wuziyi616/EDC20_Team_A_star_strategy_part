/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"

/* USER CODE BEGIN Includes */
#include "wifiControl.h"
#include "Core.h"
#include <math.h>
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
uint8_t huanchong[1];
volatile int GetValidData = 0;

extern volatile struct PassengerInfo passengers[MaxPassengerNum];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
int calculateDistance(struct Position aimP, struct Position myP);

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	  // wzy?init
	
	HAL_GPIO_WritePin(WIFI1_GPIO_Port, WIFI1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(WIFI2_GPIO_Port, WIFI2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(WIFI3_GPIO_Port, WIFI3_Pin, GPIO_PIN_SET);
	WifiInit(&huart2);
	
	init();
	
	HAL_UART_Receive_IT(&huart2, huanchong, 1);
	
	/***************/
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
		
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
		GetValidData = 0;
		while(GetValidData == 0){}
			
		//SerialPrintNewChar("a1\r\n",&huart1);	
			
		DecodeCarBInfo();
			
		DecodePassengers();
			
		struct Position aimp;
		struct Position myp = getCarB_pos();
			
		//SerialPrintNewChar("a2\r\n",&huart1);
					
		int result=Searching_Passenger(&CarBinformation);
		struct Path path = CarBinformation.curPath;
		
		/*SerialPrintNewChar("result:\r\n",&huart1);	
		SerialPrintNum(result,&huart1);*/
		
		for (int i = 0; i < MaxPositionsPerPath; i++)
		{
			//SerialPrintNewChar("a3\r\n",&huart1);
			
			GetValidData = 0;
			while(GetValidData == 0);
			
			//SerialPrintNewChar("a4:",&huart1);
			//SerialPrintNum(i,&huart1);
			//SerialPrintNewChar("\r\n",&huart1);
			
			if(!path.key_points[i])
			{
				//return 0;
				break;
			}
			
			//SerialPrintNewChar("a5\r\n",&huart1);
			
			aimp = *path.key_points[i];
			
			//SerialPrintNewChar("a5_1\r\n",&huart1);
			
			CodeAimP(aimp);
			
			/*SerialPrintNewChar("myp:\r\n",&huart1);
			SerialPrintPoint(myp,&huart1);
			SerialPrintNewChar("aimp:\r\n",&huart1);
			SerialPrintPoint(aimp,&huart1);
			
			SerialPrintNewChar("passengerNum:\r\n",&huart1);
			SerialPrintNum(CarBinformation.passenger_num,&huart1);
			*/
			
			/*SerialPrintNewChar("dis:",&huart1);
			int dis = calculateDistance(myp,aimp);
			SerialPrintNum(dis,&huart1);
			SerialPrintNewChar("\r\n",&huart1);
			SerialPrintNum(calculateDistance(myp,aimp),&huart1);*/
			//SerialPrintNum(22,&huart1);
			
			while(calculateDistance(myp,aimp) > 8)
			{
				//SerialPrintNewChar("a6\r\n",&huart1);
				
				
				GetValidData = 0;
				while(GetValidData == 0);
				
				//SerialPrintNewChar("a7\r\n",&huart1);
				
				DecodeCarBInfo();
				myp = getCarB_pos();
				
				CodeMyP(myp);
				
				//SerialPrintNewChar("a8\r\n",&huart1);
				
				HAL_UART_Transmit(&huart1, messageTransimit, 10, 0xFFFF);
				
				/*static int i=0;
				i++;
				if(i==5)
				{
					i=0;
					char output[50];
					sprintf(output,"{A%d:%d:%d:%d:%d:%d}$",myp.X,myp.Y,aimp.X,aimp.Y,0,0);
					SerialPrintNewChar(output,&huart1);
				}*/
				
			}
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

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USART1 init function */
static void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART2 init function */
static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, WIFI1_Pin|WIFI2_Pin|WIFI3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(TIME_GPIO_GPIO_Port, TIME_GPIO_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : WIFI1_Pin WIFI2_Pin WIFI3_Pin */
  GPIO_InitStruct.Pin = WIFI1_Pin|WIFI2_Pin|WIFI3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : TIME_GPIO_Pin */
  GPIO_InitStruct.Pin = TIME_GPIO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TIME_GPIO_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
int calculateDistance(struct Position aimP, struct Position myP)
{
	int delta_x = aimP.X - myP.X;
	int delta_y = aimP.Y - myP.Y;
	
	int aim2meDistance = (int)sqrt(delta_x*delta_x + delta_y*delta_y);
	aim2meDistance = aim2meDistance > 0 ? aim2meDistance:(-aim2meDistance);
	
	return (aim2meDistance);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART2)
	{
		HAL_GPIO_WritePin(TIME_GPIO_GPIO_Port, TIME_GPIO_Pin, GPIO_PIN_SET);
		
		whole_message[message_index]= huanchong[0];
		message_index=receiveIndexAdd(message_index,1);
		
		if(checkBeginningNew() == 1)
		{
			message_head = message_index;
		}
		
		if(whole_message[receiveIndexMinus(message_index,2)]==0x0D
			&& whole_message[receiveIndexMinus(message_index,1)]==0x0A)
		{
			if(receiveIndexMinus(message_index,message_head) == 64)
			{
				GetValidData = 1;  //ÒÆµ½ÏÂÃæ
				
				//HAL_UART_Transmit(&huart1, "a",1,0xFFFF);
				
				int index = message_head;
				
				for(int i=0;i<64;i++)
				{
					messageReceive[i]= whole_message[index];
					index=receiveIndexAdd(index,1);
				}
			}
			else
			{
				message_head = message_index;
			}
		}
	
		HAL_GPIO_WritePin(TIME_GPIO_GPIO_Port, TIME_GPIO_Pin, GPIO_PIN_RESET);
		
		HAL_UART_Receive_IT(&huart2, huanchong, 1);
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
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
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

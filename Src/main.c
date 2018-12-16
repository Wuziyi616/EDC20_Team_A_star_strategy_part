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
#include "Decode.h"
#include "urkax.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
extern volatile struct PassengerInfo passengers[MaxPassengerNum];
volatile char game_start_flag=0;

//volatile struct CarInfo *myCar_index= &CarAinformation;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

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
	
	HAL_GPIO_WritePin(CAR_TYPE_OUTPUT_GPIO_Port, CAR_TYPE_OUTPUT_Pin, GPIO_PIN_SET);
	myCar = what_car_type();
	/*SerialPrintNewChar("Car_type:",&huart1);
	char out[2];
	out[0]=myCar;
	SerialPrintNewChar(out,&huart1);*/
	
	WifiInit(&huart2);
	
	init();
	
	myp.X=0; myp.Y=0;
	aimp.X=0; aimp.Y=0;
	
	HAL_UART_Receive_IT(&huart2, huanchong, 1);	
	/*********************Init end***********************************/
	
	/********************start part**********************************/
	struct Position PosTemp;
	
	start_transimit=0;
	
	GetValidData = 0;
	while(GetValidData == 0){}
	
	if(myCar=='A')
	{
		(aimp).X=185; (aimp).Y=30;
		CodeStartAngle(1);
	}
	else if(myCar=='B')
	{
		(aimp).X=30; (aimp).Y=185;
		CodeStartAngle(0);
	}

	start_transimit=1;
	//CodeStartAngle(startAngleAndAim(&myp, &aimp));
		
	do
	{
		GetValidData = 0;
		while(GetValidData == 0){}
		
		myp=getMyP();
			
		//SerialPrintNewChar("start part\n", &huart1);	
		//SerialPrintNewChar("myp:\n",&huart1);
		//SerialPrintPoint(myp, &huart1);
		//SerialPrintNewChar("aimp:\n",&huart1);
		//SerialPrintPoint(aimp, &huart1);	
			
	}while(get_distance(&myp, &aimp) > 8 || game_start_flag==0);
	/**************************start part end***********************************/
	
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

		//SerialPrintNewChar("while1 start\n",&huart1);	
		
		copyFlag=0;
			
		myp = getMyP();
		//myp=myCar_index->pos;
			
		aimp = myp;
			
		clear_car(myCar=='A'?&CarAinformation:&CarBinformation);
		//clear_car(myCar_index);
			
		volatile struct Path path;
				
		//SerialPrintNewChar("for passengerIndex start\n",&huart1);	
			
		char getPassengerFlag=0;
		
		if(first_passenger_flag==1)//开局不跟对手抢
		{
			first_passenger_flag=0;
			for(int passengerIndex=0;passengerIndex<getPassengersNum();passengerIndex++)
			{
				char A_first_passenger_bool = 0;   
				char B_first_passenger_bool = 0;
				
				A_first_passenger_bool = (passengers[passengerIndex].start_pos.X>=passengers[passengerIndex].start_pos.Y);
				B_first_passenger_bool = (passengers[passengerIndex].start_pos.X<passengers[passengerIndex].start_pos.Y);
			
				if(myCar=='A'&&(A_first_passenger_bool))//myCar_index == &CarAinformation)
				{
					getPassengerFlag=1;
					
					PosTemp=passengers[passengerIndex].start_pos;
					get_nearest_path(&path, myp, &PosTemp);
		
					//SerialPrintNewChar("Aget first passenger\n",&huart1);
					//SerialPrintNum(passengerIndex,&huart1);
					
					break;
				}
				else if(myCar=='B' && B_first_passenger_bool)//myCar_index == &CarBinformation)
				{
					getPassengerFlag=1;
					
					PosTemp=passengers[passengerIndex].start_pos;
					get_nearest_path(&path, myp, &PosTemp);
					
					//SerialPrintNewChar("Bget first passenger\n",&huart1);
					//SerialPrintNum(passengerIndex,&huart1);
					
					break;
				}
			}
		}
		
		for(int passengerIndex=0;passengerIndex<getPassengersNum();passengerIndex++)
		{
			if(myCar=='A'&&(passengers[passengerIndex].State == 0x01))//myCar_index == &CarAinformation)
			{
				getPassengerFlag=1;
				
				PosTemp=passengers[passengerIndex].end_pos;
				get_nearest_path(&path, myp, &PosTemp);
	
				//SerialPrintNewChar("Aget passenger or first passenger\n",&huart1);
				//SerialPrintNum(passengerIndex,&huart1);
				
				break;
			}
			else if(myCar=='B' && (passengers[passengerIndex].State == 0x02))//myCar_index == &CarBinformation)
			{
				getPassengerFlag=1;
				
				PosTemp=passengers[passengerIndex].end_pos;
				get_nearest_path(&path, myp, &PosTemp);
				
				//SerialPrintNewChar("Bget passenger or first passenger\n",&huart1);
				//SerialPrintNum(passengerIndex,&huart1);
				
				break;
			}
		}
		
			
		//SerialPrintNewChar("for passengerIndex end\n",&huart1);
		
		if(getPassengerFlag==0)
		{			
			//SerialPrintNewChar("calculatePassengersScore_Path\n",&huart1);
		
			calculatePassengersScore_Path();
			
			//SerialPrintNewChar("search passenger start 1\n",&huart1);
			int result=Searching_Passenger();//myCar_index);
			//SerialPrintNewChar("result:\n",&huart1);
			//SerialPrintNum(result, &huart1);
			
			while(!result)
			{
				copyFlag=1;
				GetValidData = 0;
				while(GetValidData == 0){}
				copyFlag=0;
					
				//SerialPrintNewChar("calculatePassengersScore_Path2\n",&huart1);
					
				calculatePassengersScore_Path();
					
				//SerialPrintNewChar("search passenger start 1\n",&huart1);
				result=Searching_Passenger();//myCar_index);
				//SerialPrintNewChar("result:\n",&huart1);
				//SerialPrintNum(result, &huart1);
			}
			
			//path = myCar_index->curPath;
			path = (myCar=='A'?CarAinformation:CarBinformation).curPath;
		}

		copyFlag=1;

		//SerialPrintNewChar("search passenger end\n",&huart1);
		
		for (int i = 0; i < MaxPositionsPerPath; i++)
		{
			GetValidData = 0;
			while(GetValidData == 0);
			
			//SerialPrintNewChar("for maxpositions start\n",&huart1);
			
			if(!path.key_points[i])
			{
				//SerialPrintNewChar("for path key break\n",&huart1);
				break;
			}
			
			//SerialPrintNewChar("for maxposition 111\n",&huart1);
			
			aimp = myp;
			
			char change_flag = 0;
			char stop_flag=0;
			int m_a_distance;
			
			//SerialPrintNewChar("for maxposition 222\n",&huart1);
			
			char temp_first_time=1;
			aimp = *path.key_points[i];
			struct Position reserved_aimp = aimp;
			
			//SerialPrintNewChar("for maxposition 333\n",&huart1);
			//SerialPrintNewChar("for maxposition aimp:\n",&huart1);
			//SerialPrintPoint(aimp, &huart1);
			
			do
			{
				GetValidData = 0;
				while(GetValidData == 0);
									
				struct Position temp_aimp, enemyp;
				
				myp = getMyP();
				enemyp=getEnemyP();
				int add_or_not=ifToAvoidEnemy_extend(&myp, &reserved_aimp, &enemyp, 30, 33, &temp_aimp);
				
				if(add_or_not==1)
				{
					aimp=temp_aimp;
					
					//SerialPrintNewChar("temp aim avoid\n",&huart1);
					
					if(temp_first_time==1)
					{
						i--;
					}
					temp_first_time=0;
				}
				else if(add_or_not==2)
				{
					aimp=myp;
					stop_flag=1;
					
					//SerialPrintNewChar("can not move\n",&huart1);
					
					if(temp_first_time==1)
					{
						i--;
					}
					temp_first_time=0;
				}
				else
				{
					aimp = reserved_aimp;
					stop_flag=0;
				}
				
				m_a_distance=get_distance(&myp, &aimp);
				
				change_flag = passengersInfoChange();
				
				static int poutput_index=0;
				poutput_index++;
				if(poutput_index == 4)
				{
					poutput_index=0;
					//SerialPrintNewChar("m:\n",&huart1);
					//SerialPrintPoint(myp, &huart1);
					//SerialPrintNewChar("a:\n",&huart1);
					//SerialPrintPoint(aimp, &huart1);
					
					//SerialPrintNewChar("c_f:",&huart1);
					//SerialPrintNum(change_flag, &huart1);
					
					//SerialPrintNewChar("dis:",&huart1);
					//SerialPrintNum(m_a_distance, &huart1);
					
					/*char blueteeth_output[50];
					sprintf(blueteeth_output,"{A%d:%d:%d:%d:%d:%d}$\n",myp.X,myp.Y,aimp.X,aimp.Y,0,0);
					HAL_UART_Transmit(&huart1, (uint8_t*)blueteeth_output, strlen(blueteeth_output)+1, 0xFFFF);*/
				}
				
				if(change_flag >= 1)
				{
					break;
				}
			}while((m_a_distance > 8) || stop_flag==1);
			
			if(change_flag >= 1)
			{
				break;
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
  HAL_GPIO_WritePin(GPIOC, TIME_GPIO_Pin|CAR_TYPE_OUTPUT_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : WIFI1_Pin WIFI2_Pin WIFI3_Pin */
  GPIO_InitStruct.Pin = WIFI1_Pin|WIFI2_Pin|WIFI3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : TIME_GPIO_Pin CAR_TYPE_OUTPUT_Pin */
  GPIO_InitStruct.Pin = TIME_GPIO_Pin|CAR_TYPE_OUTPUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : CAR_TYPE_INPUT_Pin */
  GPIO_InitStruct.Pin = CAR_TYPE_INPUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(CAR_TYPE_INPUT_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART2)
	{
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
				//HAL_UART_Transmit(&huart1, "a",1,0xFFFF);				
				int index = message_head;
				
				if(copyFlag)
				{
					for(int i=0;i<64;i++)
					{
						messageReceive[i]= whole_message[index];
						index=receiveIndexAdd(index,1);
					}
					
					DecodePassengers();
					DecodeCarBInfo();
					DecodeCarAInfo();
				}
								
				struct Position myp_temp=getMyP();
				struct Position aimp_temp=aimp;
				//struct Position myp_temp=myCar_index->pos;
				
				DecodeRoundInfo();
				if(roundInformation.GameState!=0x01)
				{
					game_start_flag=0;
					CodeStopSignal(1);
				}
				else
				{
					game_start_flag=1;
					CodeStopSignal(0);
				}
				
				CodeMyP(myp_temp);
				CodeAimP(aimp_temp);
				
				//SerialPrintNewChar("#",&huart1);
				
				if(start_transimit==1)
				{
					HAL_UART_Transmit(&huart1, messageTransimit, 10, 0xFFFF);
				}
				
				GetValidData = 1;
			}
			else
			{
				message_head = message_index;
			}
		}
		
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

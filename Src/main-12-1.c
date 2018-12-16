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
volatile struct Position aimp, myp;
char myCar='B';
volatile char copyFlag = 1;
char first_passenger_flag=1;
//volatile struct CarInfo *myCar_index= &CarAinformation;

extern volatile struct PassengerInfo passengers[MaxPassengerNum];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
int calculateDistance(volatile struct Position aimP, volatile struct Position myP);
int startAngleAndAim(volatile struct Position *myp, volatile struct Position *aimp);
struct Position getMyP(void); 
char passengersInfoChange(void);
char ifToAvoidCircle(struct Position myp, struct Position aimp, struct Position *temp_aimp);
char what_car_type(void);

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
	struct Position endPosTemp;
	
	GetValidData = 0;
	while(GetValidData == 0){}
		
	myp=getMyP();
	//myp=myCar_index->pos;
	CodeStartAngle(startAngleAndAim(&myp, &aimp));
		
	do
	{
		GetValidData = 0;
		while(GetValidData == 0){}
		
		myp=getMyP();	
		//myp=myCar_index->pos;	
			
		SerialPrintNewChar("start part\n", &huart1);	
		SerialPrintNewChar("myp:\n",&huart1);
		SerialPrintPoint(myp, &huart1);
		SerialPrintNewChar("aimp:\n",&huart1);
		SerialPrintPoint(aimp, &huart1);	
			
	}while(calculateDistance(myp, aimp)>8);
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

		SerialPrintNewChar("while1 start\n",&huart1);	
			
		myp = getMyP();
		//myp=myCar_index->pos;
			
		aimp = myp;
			
		clear_car(myCar=='A'?&CarAinformation:&CarBinformation);
		//clear_car(myCar_index);
			
		volatile struct Path path;
				
		SerialPrintNewChar("for passengerIndex start\n",&huart1);
			
		char getPassengerFlag=0;
		for(int passengerIndex=0;passengerIndex<getPassengersNum();passengerIndex++)
		{
			char A_first_passenger_bool = 0;   //开局不跟对手抢，
			char B_first_passenger_bool = 0;
			
			if(first_passenger_flag==1)
			{
				first_passenger_flag=0;
				A_first_passenger_bool = (passengers[passengerIndex].start_pos.X>=passengers[passengerIndex].start_pos.Y);
				B_first_passenger_bool = (passengers[passengerIndex].start_pos.X<passengers[passengerIndex].start_pos.Y);
			}
			
			if(myCar=='A'&&(passengers[passengerIndex].State == 0x01 || A_first_passenger_bool))//myCar_index == &CarAinformation)
			{
				getPassengerFlag=1;
				
				endPosTemp=passengers[passengerIndex].end_pos;
				get_nearest_path(&path, &myp, &endPosTemp);
	
				SerialPrintNewChar("Aget passenger or first passenger\n",&huart1);
				SerialPrintNum(passengerIndex,&huart1);
				
				break;
			}
			else if(myCar=='B' && (passengers[passengerIndex].State == 0x02 || B_first_passenger_bool))//myCar_index == &CarBinformation)
			{
				getPassengerFlag=1;
				
				endPosTemp=passengers[passengerIndex].end_pos;
				get_nearest_path(&path, &myp, &endPosTemp);
				
				SerialPrintNewChar("Bget passenger or first passenger\n",&huart1);
				SerialPrintNum(passengerIndex,&huart1);
				
				break;
			}
		}
			
		SerialPrintNewChar("for passengerIndex end\n",&huart1);
		
		if(getPassengerFlag==0)
		{
			copyFlag=0;
			
			SerialPrintNewChar("calculatePassengersScore_Path\n",&huart1);
		
			calculatePassengersScore_Path();
			
			SerialPrintNewChar("search passenger start 1\n",&huart1);
			int result=Searching_Passenger(myCar=='A'?&CarAinformation:&CarBinformation);//myCar_index);
			SerialPrintNewChar("result:\n",&huart1);
			SerialPrintNum(result, &huart1);
			
			while(!result)
			{
				GetValidData = 0;
				while(GetValidData == 0){}
				
				SerialPrintNewChar("calculatePassengersScore_Path2\n",&huart1);
					
				calculatePassengersScore_Path();
					
				SerialPrintNewChar("search passenger start 1\n",&huart1);
				result=Searching_Passenger(myCar=='A'?&CarAinformation:&CarBinformation);//myCar_index);
				SerialPrintNewChar("result:\n",&huart1);
				SerialPrintNum(result, &huart1);
			}
			
			//path = myCar_index->curPath;
			path = (myCar=='A'?CarAinformation:CarBinformation).curPath;
			
			copyFlag=1;
		}
		
		SerialPrintNewChar("search passenger end\n",&huart1);
		
		for (int i = 0; i < MaxPositionsPerPath; i++)
		{
			GetValidData = 0;
			while(GetValidData == 0);
			
			SerialPrintNewChar("for maxpositions start\n",&huart1);
			
			if(!path.key_points[i])
			{
				break;
			}
			
			aimp = myp;
			aimp = *path.key_points[i];
			
			locate(&myp);
			
			struct Position temp_aimp;
			int add_or_not=ifToAvoidCircle(myp, aimp, &temp_aimp);
			
			if(add_or_not==1)
			{
				aimp=temp_aimp;
				i--;
			}
			
			char change_flag = 0;
			int m_a_distance;
			
			do
			{
				GetValidData = 0;
				while(GetValidData == 0);
				
				//SerialPrintNewChar("X\n",&huart1);
				
				myp = getMyP();
				//myp=myCar_index->pos;
				//locate(&myp);
				
				m_a_distance=calculateDistance(myp,aimp);
				
				change_flag = passengersInfoChange();
				
				static int poutput_index=0;
				poutput_index++;
				if(poutput_index == 1)
				{
					poutput_index=0;
					SerialPrintNewChar("m:\n",&huart1);
					SerialPrintPoint(myp, &huart1);
					SerialPrintNewChar("a:\n",&huart1);
					SerialPrintPoint(aimp, &huart1);
					
					SerialPrintNewChar("c_f:",&huart1);
					SerialPrintNum(change_flag, &huart1);
					
					SerialPrintNewChar("dis:",&huart1);
					SerialPrintNum(m_a_distance, &huart1);
				}
				
				if(change_flag >= 1)
				{
					break;
				}
			}while((m_a_distance > 8));  // && (!is_front_position(&myp, &aimp)))
			
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

//跳线帽接PC11 PC12则返回'A',否则返回B
char what_car_type(void)
{
	if(HAL_GPIO_ReadPin(CAR_TYPE_INPUT_GPIO_Port, CAR_TYPE_INPUT_Pin) == GPIO_PIN_SET)
	{
		return 'A';
	}
	else
	{
		return 'B';
	}
}

void better_path(struct Path *path, struct Position myp)
{
	
}

char ifToAvoidCircle(struct Position myp, struct Position aimp, struct Position *temp_aimp)
{
	if(!inInterSection_0(myp.X, myp.Y) && !inInterSection_0(aimp.X, aimp.Y))//myp和aimp不在圆盘附近
	{
		return 0;
	}

	struct Position circleO; //圆盘圆心
	circleO.X=50;circleO.Y=50;
	
	int m_a_x=aimp.X-myp.X;
	int m_a_y=aimp.Y-myp.Y;
	
	int m_o_x=circleO.X-myp.X;
	int m_o_y=circleO.Y-myp.Y;
	
	int a_o_x=circleO.X-aimp.X;
	int a_o_y=circleO.Y-aimp.Y;
	
	int ao_ma_dian_ji=a_o_x*m_a_x+a_o_y*m_a_y;
	int ma_mo_dian_ji=m_o_x*m_a_x+m_o_y*m_a_y;
	
	if(ao_ma_dian_ji>=0 || ma_mo_dian_ji <= 0)
	{
		return 0;
	}
	
	int cha_ji=(m_a_x*m_o_y-m_a_y*m_o_x);
	int cha_ji_abs= (cha_ji>0? cha_ji : (-cha_ji));
	
	//double m_o_dis=(double)sqrt(m_o_x*m_o_x+m_o_y*m_o_y);
	double m_a_dis=(double)sqrt(m_a_x*m_a_x+m_a_y*m_a_y);
	
	int distance = (double)cha_ji_abs/(m_a_dis+1e-6);
	
	if(distance>= 15) //距离大于半径
	{
		return 0;
	}
	
	/***************计算temp_aimp*********************/
	int m_a_ver_x=m_a_y;
	int m_a_ver_y=-m_a_x;
	
	int distance_t_O=25;  //temp_aimp与圆心的距离
	
	int o_t_x=(double)m_a_ver_x*(double)distance_t_O/(m_a_dis+1e-6);
	int o_t_y=(double)m_a_ver_y*(double)distance_t_O/(m_a_dis+1e-6);
	
	if(cha_ji < 0)
	{
		o_t_x = -o_t_x;
		o_t_y = -o_t_y;
	}
	
	temp_aimp->X=circleO.X+o_t_x;
	temp_aimp->Y=circleO.Y+o_t_y;
	
	return 1;
}

char passengersInfoChange(void)
{
	static volatile uint8_t last_passengerNum = 0;
	static volatile struct PassengerInfo lastPassengers[MaxPassengerNum];
	
	int changeFlag = 0;
	
	if(last_passengerNum != 0)
	{
		if(last_passengerNum != getPassengersNum())
		{
			changeFlag = 1;
		}
		else
		{
			for(int i=0; i<getPassengersNum();i++)
			{
				if(lastPassengers[i].State != passengers[i].State)
				{
					changeFlag = 2;
				}
				
				else if(  (lastPassengers[i].start_pos.X != passengers[i].start_pos.X)
					|| (lastPassengers[i].start_pos.Y != passengers[i].start_pos.Y))
				{
					changeFlag = 3;
				}
				
				else if(  (lastPassengers[i].end_pos.X != passengers[i].end_pos.X)
					|| (lastPassengers[i].end_pos.Y != passengers[i].end_pos.Y))
				{
					changeFlag = 4;
				}
			}
		}
	}
	
	for(int i=0;i<MaxPassengerNum;i++)
	{
		lastPassengers[i]=passengers[i];
	}
	
	last_passengerNum = getPassengersNum();
	
	return changeFlag;
}

struct Position getMyP(void)
{
	if(myCar=='A')
	{
		DecodeCarAInfo();
		return getCarA_pos();
	}
	else if(myCar=='B')
	{
		DecodeCarBInfo();
		return getCarB_pos();
	}
}

//1表示角度初始值为-90；0表示角度初始值为179；
int startAngleAndAim(volatile struct Position *myp, volatile struct Position *aimp)
{
	struct Position RightDownStartPos, LeftUpStartPos;
	RightDownStartPos.X=187; RightDownStartPos.Y=66;
	LeftUpStartPos.X=68; LeftUpStartPos.Y=185;
	
	if(calculateDistance(RightDownStartPos,*myp)<=30)
	{
		(*aimp).X=187; (*aimp).Y=29;
		return 1;
	}
	else if(calculateDistance(LeftUpStartPos,*myp)<=30)
	{
		(*aimp).X=27; (*aimp).Y=185;
		return 0;
	}
	//25 20
	return -1;
}

int calculateDistance(volatile struct Position aimP, volatile struct Position myP)
{
	return get_distance(&myP, &aimP);
}

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
				//struct Position myp_temp=myCar_index->pos;
				
				DecodeRoundInfo();
				if(roundInformation.GameState!=0x01)
				{
					CodeStopSignal(1);
				}
				else
				{
					CodeStopSignal(0);
				}
				
				CodeMyP(myp_temp);
				CodeAimP(aimp);
				
				//SerialPrintNewChar("#",&huart1);
				HAL_UART_Transmit(&huart1, messageTransimit, 10, 0xFFFF);
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

#include "Output.h"

uint8_t messageTransimit[10] = {0xFF, 0xFE, 0, 0, 0, 0, 0x20, 0, 0x66, 0x65};

int num2char(unsigned char *str, double num1)
{
	int index = 0;
	
	if(num1 < 0)
	{
		str[0] = '-';
		index++;
		
		num1 = -num1;
	}
	
	int high;
	double low;
	double num=num1;
	int n=0;
	char ch[16];
	int i;
	high=(int)num;
	low=num-high;
	if(high==0)
	{
		str[index]='0';
		index++;
	}
	
	while(high>0)
	{
		ch[n]='0'+high%10;
		n++;
		high=high/10;
	}
	
	for(i=n-1;i>=0;i--)
	{
		str[index]=ch[i];
		index++;
	}
	
	num-=(int)num;
	double tp=0.1;
	str[index]='.';
	index++;
	
	if(num<=0.1)
	{
		str[index]='0';
		index++;
	}
	
	while(num>0.1)
	{
		num-=tp*(int)(low*10);
		tp/=10;
		str[index]='0'+(int)(low*10);
		index++;
		low=low*10.0-(int)(low*10);
	}
	
	str[index] = '\n';
	str[index+1]= '\r';
	str[index+2]='\0';
	
	return index+2;
}

void SerialPrintNum(double num,UART_HandleTypeDef*huart)
{
	/*
	unsigned char transLeft[20];
	uint8_t lenth = num2char(transLeft,(double)num);
						
	HAL_UART_Transmit(huart, (uint8_t*)transLeft,lenth , 0xFFFF);
	*/
}

void SerialPrintNewChar(char* output, UART_HandleTypeDef*huart)
{
	//SerialPrintChar((uint8_t*)output, strlen(output),huart);
}

void SerialPrintChar(uint8_t* output, uint8_t lenth,UART_HandleTypeDef*huart)
{
	//HAL_UART_Transmit(huart, (uint8_t*)output, lenth, 0xFFFF);
}

void SerialPrintPoint(struct Position p,UART_HandleTypeDef*huart)
{
	/*
	SerialPrintChar((uint8_t*)"X:",2,huart);
	SerialPrintNum(p.X,huart);
	SerialPrintChar((uint8_t*)"Y:",2,huart);
	SerialPrintNum(p.Y,huart);
	SerialPrintChar((uint8_t*)"\r\n",2,huart);
	*/
}

void CodeMyP(volatile struct Position p)
{
	messageTransimit[2] = (p.X) & 0x00FF;
	messageTransimit[3] = (p.Y) & 0x00FF;
	messageTransimit[6] = (messageTransimit[6] & (0xFF - 0x08)) + (((p.X) & 0x0100) >> 5);
	messageTransimit[6] = (messageTransimit[6] & (0xFF - 0x04)) + (((p.Y) & 0x0100) >> 6);
}

void CodeAimP(volatile struct Position p)
{
	messageTransimit[4] = (p.X) & 0x00FF;
	messageTransimit[5] = (p.Y) & 0x00FF;
	messageTransimit[6] = (messageTransimit[6] & (0xFF - 0x02))+(((p.X) & 0x0100) >> 7);
	messageTransimit[6] = (messageTransimit[6] & (0xFF - 0x01)) + (((p.Y) & 0x0100) >> 8);
}

//1表示角度初始值为-90；0表示角度初始值为179；
void CodeStartAngle(char x)
{
	if(x==1)
	{
		messageTransimit[6] = (messageTransimit[6] & (0xFF - 0x80)) + (0x01 << 7);
	}
}

void CodeUpdateSignal(int flag)
{
	if(flag == 1)
	{
		messageTransimit[6] &= (0xFF); 
	}
	else
	{
		messageTransimit[6] &= (0xDF);
	}
}

void CodeStopSignal(int flag)
{
	if(flag == 1)
	{
		messageTransimit[6] = (messageTransimit[6] & (0xFF - 0x10)) + (0x01 << 4);
	}
	else
	{
		messageTransimit[6] = (messageTransimit[6] & (0xFF - 0x10));
	}
}

//static int i=0;
	//信息解释与对应
	//0---当前坐标x
	//1---当前坐标y
	//2---目标坐标x
	//3---目标坐标y
	//4---00000000最低四位对应1234补充位（坐标高位）  第三位表示目标值是否更新 1是0否  第四位表示是否停机---1是   0  否   其余为0
	//7---校验  暂定0x66           其余位也暂定为0x66

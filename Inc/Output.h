#ifndef OUTPUT_H
#define OUTPUT_H

#include "stm32f1xx_hal.h"
#include "Decode.h"
#include <string.h>

void SerialPrintNum(double num,UART_HandleTypeDef*huart);
void SerialPrintChar(uint8_t* output, uint8_t lenth,UART_HandleTypeDef*huart);
void SerialPrintNewChar(char* output, UART_HandleTypeDef*huart);
int num2char(unsigned char *str, double num1 );

void SerialPrintPoint(struct Position p,UART_HandleTypeDef*huart);

void CodeMyP(volatile struct Position p);
void CodeAimP(volatile struct Position p);
void CodeUpdateSignal(int flag);
void CodeStopSignal(int flag);
void CodeStartAngle(char x);

extern uint8_t messageTransimit[10];

#endif

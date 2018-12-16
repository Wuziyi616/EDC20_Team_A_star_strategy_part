#include "wifiControl.h"

uint8_t NameCode[50] = "AT+CWJAP=\"EDC20\",\"12345678\"\r\n";
//uint8_t NameCode[50] = "AT+CWJAP=\"OPPO A33m\",\"a123456789\"\r\n";

void WifiInit(UART_HandleTypeDef*huart)
{
	uint8_t receive_wifi_init[10];
	HAL_UART_Transmit(huart,(uint8_t*)"AT\r\n", 5, 0xFFFF);
	//HAL_Delay(3000);
	HAL_UART_Receive(huart, receive_wifi_init, 1, 3000);
	/*SerialPrintChar("AT\r\n", 5, huart);
	HAL_Delay(3000);
	SerialPrintChar((uint8_t*)"AT+CWMODE=3\r\n", 14, huart);
	HAL_Delay(3000);
	//HAL_UART_Receive(huart, receive_wifi_init, 1, 3000);
	
	SerialPrintChar((uint8_t*)"AT+RST\r\n", 9, huart);
	HAL_Delay(3000);
	//HAL_UART_Receive(huart, receive_wifi_init, 1, 3000);
	*/
	HAL_UART_Transmit(huart,(uint8_t*)NameCode, strlen(NameCode)+1, 0xFFFF);
	HAL_Delay(5000);
	//HAL_UART_Receive(huart, receive_wifi_init, 1, 3000);
	
	//SerialPrintChar((uint8_t*)"AT+CIPSTART=\"TCP\",\"192.168.1.116\",20000\r\n", 42,huart);
	char at_cip[50]="AT+CIPSTART=\"TCP\",\"192.168.1.124\",20000\r\n";
	HAL_UART_Transmit(huart,(uint8_t*)at_cip, strlen(at_cip)+1,0xFFFF);
	HAL_Delay(3000);
	//HAL_UART_Receive(huart, receive_wifi_init, 1, 3000);
	
	//SerialPrintChar((uint8_t*)"AT+CIPSTART=\"TCP\",\"192.168.1.116\",20000\r\n", 42, huart);
	HAL_UART_Transmit(huart,(uint8_t*)at_cip, strlen(at_cip)+1,0xFFFF);
	//HAL_Delay(3000);
	HAL_UART_Receive(huart, receive_wifi_init, 1, 3000);
}

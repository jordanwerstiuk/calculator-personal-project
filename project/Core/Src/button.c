/*
 * 	button.c
 *
 * 	Description: Provides functions related to both button functionality and testing
 *
 *  Created on: Apr 3, 2024
 *	Author: Jordan Werstiuk
 */



/* Includes ------------------------------------------------------------------*/
#include "button.h"


/* Variables -----------------------------------------------------------------*/
UART_HandleTypeDef huart3;
char UART3_rxBuffer[USART_RX_BUF_SIZE] = "Test";

/*
Edit the pin numbers based on the CubeMX configuration
Edit the corresponding chars to allow for the easiest PCB trace routing
given the proposed button layout on the calculator
 */
pinMappings pinsA[13] = {
    {GPIO_PIN_0, '0'},
    {GPIO_PIN_1, '1'},
    {GPIO_PIN_2, '2'},
    {GPIO_PIN_3, '3'},
    {GPIO_PIN_4, '4'},
    {GPIO_PIN_5, '5'},
    {GPIO_PIN_6, '6'},
    {GPIO_PIN_7, '7'},
    {GPIO_PIN_8, '8'},
    {GPIO_PIN_9, '9'},
    {GPIO_PIN_10, '+'},
    {GPIO_PIN_12, '*'},
    {GPIO_PIN_15, '.'}
  };

  pinMappings pinsB[9] = {
    {GPIO_PIN_0, '/'},
    {GPIO_PIN_1, '^'},
    {GPIO_PIN_3, 'E'},
    {GPIO_PIN_4, '_'},
    {GPIO_PIN_5, 'D'},
    {GPIO_PIN_8, '='},
    {GPIO_PIN_9, 'A'},
	{GPIO_PIN_12, '-'},
    {GPIO_PIN_15, 'P'}
  };


/* Functions -----------------------------------------------------------------*/
int _write(int file, char *ptr, int len) {
	HAL_UART_Transmit_IT(&huart3, (uint8_t*)ptr, len);
	return len;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	printf("%s\r\n", UART3_rxBuffer);
    HAL_UART_Receive_IT(&huart3, (uint8_t*)UART3_rxBuffer, sizeof(UART3_rxBuffer));
}

int buttonPressed(GPIO_TypeDef *gpioPort, uint16_t pinNum) {
	//Using pull-up resistors, so pressed is logic level 0
	return !HAL_GPIO_ReadPin(gpioPort, pinNum);
}

void blinkLED(int duration) {
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
	HAL_Delay(duration);
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
}



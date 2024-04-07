/*
 * 	button.c
 *
 * 	Description: Provides functions related to button functionality and testing
 *
 *  Created on: Apr 3, 2024
 *	Author: Jordan Werstiuk
 */



/* Includes ------------------------------------------------------------------*/
#include "button.h"


/* Variables -----------------------------------------------------------------*/
UART_HandleTypeDef huart3;
char UART3_rxBuffer[USART_RX_BUF_SIZE];

uint16_t buttonPins[NUM_BUTTONS]= {GPIO_PIN_0, GPIO_PIN_1};


/* Functions -----------------------------------------------------------------*/
int _write(int file, char *ptr, int len) {
	HAL_UART_Transmit_IT(&huart3, (uint8_t*)ptr, len);
	return len;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	printf("%hu\r\n", *UART3_rxBuffer);
    HAL_UART_Receive_IT(&huart3, UART3_rxBuffer, 1);
}

void displayNumConsole(int num) {

}

int buttonPressed(GPIO_TypeDef *gpioPort, uint16_t pinNum) {
	return HAL_GPIO_ReadPin(gpioPort, pinNum);
}

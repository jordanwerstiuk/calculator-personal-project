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

uint16_t buttonPins[NUM_BUTTONS]= {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3,
		GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7, GPIO_PIN_8, GPIO_PIN_9,
		GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14};


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
	//Using built-in pull-up resistors, so pressed is logic level 0
	return !HAL_GPIO_ReadPin(gpioPort, pinNum);
}

void displayNumConsole(int num) {

}

void blinkLED(int duration) {
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
	HAL_Delay(duration);
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
}



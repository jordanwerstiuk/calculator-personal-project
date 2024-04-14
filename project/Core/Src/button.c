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

uint16_t buttonPins[NUM_BUTTONS]= {GPIO_PIN_0, GPIO_PIN_1};
GPIO_TypeDef *LEDport = GPIOB;
uint16_t LEDpin = GPIO_PIN_9;


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
	HAL_GPIO_WritePin(LEDport, LEDpin, GPIO_PIN_SET);
	HAL_Delay(duration);
	HAL_GPIO_WritePin(LEDport, LEDpin, GPIO_PIN_RESET);
}



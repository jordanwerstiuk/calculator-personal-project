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
int NUM_BUTTONS = 2;
uint16_t buttonPins[NUM_BUTTONS]= {GPIO_PIN_0, GPIO_PIN_1};


/* Functions -----------------------------------------------------------------*/
int _write(int file, char *ptr, int len)
{
	HAL_UART_Transmit_IT(&huart1, (uint8_t*)ptr, len);
	return len;
}

void displayNumConsole(int num) {

}

int buttonPressed(GPIO_TypeDef *gpioPort, uint16_t pinNum) {
	return HAL_GPIO_ReadPin(gpioPort, pinNum);
}

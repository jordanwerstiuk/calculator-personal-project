/*
 * 	button.h
 *
 * 	Description: Header file containing variable declarations and function prototypes for button.c
 *
 *  Created on: Apr 3, 2024
 *	Author: Jordan Werstiuk
 */



/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUTTON_H
#define __BUTTON_H


/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "main.h"


/* Includes ------------------------------------------------------------------*/
#define NUM_BUTTONS 19
#define USART_RX_BUF_SIZE 8


/* Variables -----------------------------------------------------------------*/
extern UART_HandleTypeDef huart3;
extern char UART3_rxBuffer[USART_RX_BUF_SIZE];

extern uint16_t buttonPins[NUM_BUTTONS];


/* Function prototypes  ------------------------------------------------------*/
int _write(int file, char *ptr, int len);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
int buttonPressed(GPIO_TypeDef *gpioPort, uint16_t pinNum);
void blinkLED(int duration);

#endif /* __BUTTON_H */

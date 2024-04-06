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
#include "stm32f1xx_hal.h"


/* Variables -----------------------------------------------------------------*/
extern int NUM_BUTTONS;
extern uint16_t buttonPins[NUM_BUTTONS];


/* Function prototypes  ------------------------------------------------------*/
int _write(int file, char *ptr, int len);
void testDisplayNum(int num);
bool buttonPressed();


#endif /* __BUTTON_H */

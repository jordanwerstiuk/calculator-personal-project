/*
 * 	display.h
 *
 * 	Description: Header file containing variable declarations and function prototypes for display.c
 *
 *  Created on: Apr 5, 2024
 *	Author: Jordan Werstiuk
 */



/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DISPLAY_H
#define __DISPLAY_H


/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "string.h"
#include "stdio.h"

/* Defines ------------------------------------------------------------------*/
#define CLEAR_DISPLAY 0x01
#define RETURN_HOME 0x02

#define FUNCTION_SET 0x20
#define BIT_4 0x00
#define LINES_2 0x08
#define DOTS_5X8 0x00

#define DISPLAY_MODE_SET 0x08
#define DISPLAY 0x04
#define CURSOR 0x02
#define BLINK 0x01

#define ENTRY_MODE_SET 0x06
#define SHIFT 0x01
#define NO_SHIFT 0x00
#define INCREMENT_INDEX 0x02
#define DECREMENT_INDEX 0x00

#define BACKLIGHT 0x08
#define REGISTER_SELECT 0x01
#define ENABLE 0x04

/* Variables -----------------------------------------------------------------*/
extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim1;

extern const uint8_t LCD_ADDR;

/* Function prototypes  ------------------------------------------------------*/
char* formatOutput(void);
void printOutput(void);
void sendCommand(uint8_t command);
void sendChar(uint8_t c, uint8_t mode);
void send4Bits(uint8_t c, uint8_t mode);
void LCD_Init(void);
void Delay_us(uint16_t usDuration);


#endif /* __DISPLAY_H */

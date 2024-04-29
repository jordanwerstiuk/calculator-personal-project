/*
 * 	display.c
 *
 * 	Description: Provides functions related to displaying the numbers and calculations on the LCD display, including I2C communication
 *
 *  Created on: Apr 5, 2024
 *	Author: Jordan Werstiuk
 */



/* Includes ------------------------------------------------------------------*/
#include "display.h"
#include "math.h"

/* Variables -----------------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
TIM_HandleTypeDef htim1;

const uint8_t LCD_ADDR = 0x27 << 1;

/* Functions -----------------------------------------------------------------*/
char* formatOutput() {
    static char firstNum[20];
    double num1 = 5673; //placeholder until I add in the actual variables
    sprintf(firstNum, "%f", num1);
    return firstNum;
}

void printOutput() {
	char* output = formatOutput();
	for (int i = 0; i < strlen(output); i++)
	    sendChar((uint8_t) output[i], REGISTER_SELECT);
}

void sendCommand(uint8_t command) {
	sendChar(command, 0);
}

void sendChar(uint8_t data, uint8_t mode) {
	uint8_t first4Bits = data & 0b11110000;
	uint8_t last4Bits = (data & 0b00001111) << 4;
	send4Bits(first4Bits, mode);
	send4Bits(last4Bits, mode);
}

void send4Bits(uint8_t data, uint8_t mode) {
	data |= mode | BACKLIGHT;
	HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, (uint8_t*) &data, 1, HAL_MAX_DELAY);
	data |= ENABLE;
	HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, (uint8_t*) &data, 1, HAL_MAX_DELAY);
	Delay_us(20);
	data |= ~ENABLE;
	HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, (uint8_t*) &data, 1, HAL_MAX_DELAY);
	Delay_us(20);
}

void LCD_Init() {
	//Turning on the LCD backlight
	uint8_t backlight = BACKLIGHT;
	HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, (uint8_t*) &backlight, 1, HAL_MAX_DELAY);
	HAL_Delay(1000);

	//Send sequence for initializing 4-bit mode
	for (int i = 0; i < 3; i++) {
		send4Bits(0b00100000, 0);
		Delay_us(4500);
	}
	send4Bits(0b00110000, 0);
	Delay_us(100);

	//Configure functionality as desired
	uint8_t functionModes = BIT_4 | LINES_2 | DOTS_5X8;
	sendCommand(FUNCTION_SET | functionModes);
	uint8_t displayModes = DISPLAY | CURSOR;
	sendCommand(DISPLAY_MODE_SET | displayModes);
	sendCommand(CLEAR_DISPLAY);
	Delay_us(2000);
	uint8_t entryModes = SHIFT | INCREMENT_INDEX;
	sendCommand(ENTRY_MODE_SET | entryModes);
	Delay_us(4500);

	sendCommand(RETURN_HOME);
	Delay_us(2000);
}

void Delay_us(uint16_t usDuration) {
	__HAL_TIM_SET_COUNTER(&htim1, 0);
	while (__HAL_TIM_GET_COUNTER(&htim1) < usDuration);
}

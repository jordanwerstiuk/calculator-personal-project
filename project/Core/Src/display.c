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

uint8_t backlight;

/* Functions -----------------------------------------------------------------*/
void print1Char(char c) { //TESTING FUNCTION
	sendCommand(CLEAR_DISPLAY);
	Delay_us(2000);
	positionCursor(1, 1);
	sendChar(c, DATA_REGISTER);
}

char* formatOutput() {
    static char firstNum[20];
    double num1 = 5; //placeholder until I add in the actual variables
    sprintf(firstNum, "%.2f", num1);
    return "NICE"; //also a placeholder
}

void print() {
	char* output = formatOutput();
	for (int i = 0; i < strlen(output); i++)
	    sendChar((uint8_t) output[i], DATA_REGISTER);
}

void sendCommand(uint8_t command) {
	sendChar(command, INSTRUCTION_REGISTER);
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
	data &= ~ENABLE;
	HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, (uint8_t*) &data, 1, HAL_MAX_DELAY);
	Delay_us(20);
}

void positionCursor(int row, int col) {
	col--;
	if (row == 2)
		col += 0x40;
	sendCommand(DDRAM_ADDR_SET | col);
}

void LCD_Init() {
	//Configure the backlight here as desired
	backlight = BACKLIGHT;
	HAL_Delay(50);
	HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, (uint8_t*) &backlight, 1, HAL_MAX_DELAY);
	HAL_Delay(1000);

	//Send sequence for initializing 4-bit mode
	for (int i = 0; i < 3; i++) {
		send4Bits(0b00110000, 0);
		Delay_us(4500);
	}
	send4Bits(0b00100000, 0);
	Delay_us(100);

	//Configure functionality here as desired
	uint8_t functionModes = BIT_4 | LINES_2 | DOTS_5X8;
	uint8_t displayModes = DISPLAY | CURSOR; //add | CURSOR here to turn it on
	uint8_t entryModes = NO_SHIFT | INCREMENT_INDEX;

	//Communicate the functionality we chose
	sendCommand(FUNCTION_SET | functionModes);
	sendCommand(DISPLAY_MODE_SET | displayModes);
	sendCommand(CLEAR_DISPLAY);
	Delay_us(2000);
	sendCommand(ENTRY_MODE_SET | entryModes);
	Delay_us(4500);

	sendCommand(RETURN_HOME);
	Delay_us(2000);
}

void Delay_us(uint32_t usDuration) {
	__HAL_TIM_SET_COUNTER(&htim1, 0);
	while (__HAL_TIM_GET_COUNTER(&htim1) < usDuration);
}

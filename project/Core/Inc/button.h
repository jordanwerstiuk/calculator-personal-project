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


/* Private includes ----------------------------------------------------------*/


/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/
extern int NUM_BUTTONS;


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
/* USER CODE BEGIN EFP */

/* USER CODE END EFP */


/* Private defines -----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __BUTTON_H */

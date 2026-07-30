/*
 * API_GPIO.h
 *
 *  Created on: 28 jul 2026
 *      Author: GRUPO 5_2026
 *      GUZMÁN CARDOSO MELANI
 *      SANCHEZ LUCIANA NATALÍ
 *      CAMPBELL SAMUEL
 *      PALACIOS FRANCO
 */

#ifndef API_INC_API_GPIO_H_
#define API_INC_API_GPIO_H_
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Typedefs ------------------------------------------------------------------*/
typedef bool bool_t;

/* Public function prototypes ------------------------------------------------*/
void writeLedOn_GPIO(uint16_t LED_Pin);
void writeLedOff_GPIO(uint16_t LED_Pin);
void toggleLed_GPIO(uint16_t LED_Pin);
bool_t readButton_GPIO(void);

#endif /* API_INC_API_GPIO_H_ */

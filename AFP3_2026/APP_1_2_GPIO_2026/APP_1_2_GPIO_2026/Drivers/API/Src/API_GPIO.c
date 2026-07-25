/*
 * API_GPIO.c
 *
 *  Created on: 24 jul 2026
 *      Author:
 *      SAMUEL CAMPBELL
 *      PALCIOS FRANCO
 *      GUZMÁN CARDOSO MELANI
 *      SANCHEZ LUCIANA
 */
#include "API_GPIO.h"
void GPIO_STATUS_ON(GPIO_TypeDef* port,uint16_t pin){
	HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
}
void GPIO_STATUS_OFF(GPIO_TypeDef* port,uint16_t pin){
	HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
}
bool lecturaboton(GPIO_TypeDef* port,uint16_t pin){
	return HAL_GPIO_ReadPin(port, pin);

}


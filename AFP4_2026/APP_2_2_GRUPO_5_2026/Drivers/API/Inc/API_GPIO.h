/*
 * API_GPIO.h
 *
 *  Created on: 24 jul 2026
 *      Author:
 *      SAMUEL CAMPBELL
 *      PALCIOS FRANCO
 *      GUZMÁN CARDOSO MELANI
 *      SANCHEZ LUCIANA
 *
 */

#ifndef API_INC_API_GPIO_H_
#define API_INC_API_GPIO_H_
#include "main.h"
#include "stdbool.h"
void GPIO_STATUS_ON(GPIO_TypeDef* port,uint16_t pin);
void GPIO_STATUS_OFF(GPIO_TypeDef* port,uint16_t pin);
bool lecturaboton(GPIO_TypeDef* port,uint16_t pin);

#endif /* API_INC_API_GPIO_H_ */

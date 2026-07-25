/*
 * API_GPIO.h
 *
 *  Created on: 23 jul 2026
 *      Author: GRUPO 5_2026
 *      GUZMÁN CARDOSO MELANI
 *      SANCHEZ LUCIANA NATALÍ
 *      CAMPBELL SAMUEL
 *      PALACIOS FRANCO
 */

/* API_GPIO.h */
#ifndef API_INC_API_GPIO_H_
#define API_INC_API_GPIO_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>

/* Exported types ------------------------------------------------------------*/
typedef uint16_t led_t;          /* Tipo de dato para pines de LEDs */
typedef bool buttonStatus_t;     /* Tipo booleano para el estado del pulsador */

/* Exported functions prototypes ---------------------------------------------*/

void writeLedOn_GPIO(led_t LDx);
void writeLedOff_GPIO(led_t LDx);
void toggleLed_GPIO(led_t LDx);
//buttonStatus_t readButton_GPIO(void);

#endif /* API_INC_API_GPIO_H_ */


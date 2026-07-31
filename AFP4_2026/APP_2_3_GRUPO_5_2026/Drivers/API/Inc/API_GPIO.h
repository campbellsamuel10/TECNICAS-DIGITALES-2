/*
 * API_GPIO.h
 *
 *  Created on: 30 jul 2026
 *      Author: Grupo 5_2026
 *               GUZMAN CARDOSO MELANI
 *               SANCHEZ LUCIANA NATALI
 *               CAMPBELL SAMUEL
 *               PALACIOS FRANCO
 */
/**
  ******************************************************************************
  * @file    API_gpio.h
  * @brief   Módulo de abstracción para el control de GPIOs y secuencias de LEDs.
  ******************************************************************************
  */
/*
 * API_gpio.h
 *
 *  Created on: 25 jul 2026
 *      Author: Grupo 5_2026
 */

#ifndef API_GPIO_H_
#define API_GPIO_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "API_delay.h"
#include <stdbool.h>

/* Exported types ------------------------------------------------------------*/
typedef enum {
    SECUENCIA_1 = 1,
    SECUENCIA_2,
    SECUENCIA_3,
    SECUENCIA_4,
    SECUENCIA_MAX = SECUENCIA_4
} secuencia_t;

/* Exported functions prototypes ---------------------------------------------*/
void API_GPIO_Init(void);
void API_GPIO_Apagar_LEDs(void);
bool API_GPIO_Boton_Presionado(void);
void API_GPIO_Ejecutar_Secuencia(secuencia_t secuencia);

#endif /* API_GPIO_H_ */


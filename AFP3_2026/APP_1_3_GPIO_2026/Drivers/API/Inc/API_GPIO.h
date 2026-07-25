/*
 * API_GPIO.h
 *
 *  Created on: 25 jul 2026
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

#ifndef API_GPIO_H_
#define API_GPIO_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdbool.h>

/* Exported types ------------------------------------------------------------*/
/**
 * @brief Lista de secuencias disponibles para los LEDs
 */
typedef enum {
    SECUENCIA_1 = 1,
    SECUENCIA_2,
    SECUENCIA_3,
    SECUENCIA_4,
    SECUENCIA_MAX = SECUENCIA_4
} secuencia_t;

/* Exported functions prototypes ---------------------------------------------*/

/**
  * @brief  Inicializa los periféricos de GPIO (LEDs y Pulsador).
  */
void API_GPIO_Init(void);

/**
  * @brief  Apaga todos los LEDs del sistema.
  */
void API_GPIO_Apagar_LEDs(void);

/**
  * @brief  Lee el estado del botón de usuario con gestión de antirrebote.
  * @retval true si se detectó una pulsación válida (flanco de subida), false en caso contrario.
  */
bool API_GPIO_Boton_Presionado(void);

/**
  * @brief  Ejecuta la secuencia especificada.
  * @param  secuencia: Número de secuencia a ejecutar (SECUENCIA_1 a SECUENCIA_4).
  */
void API_GPIO_Ejecutar_Secuencia(secuencia_t secuencia);

#endif /* API_GPIO_H_ */

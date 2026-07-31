/*
 * API_delay.h
 *
 *  Created on: 28 jul 2026
 *      Author: GRUPO 5_2026
 *      GUZMÁN CARDOSO MELANI
 *      SANCHEZ LUCIANA NATALÍ
 *      CAMPBELL SAMUEL
 *      PALACIOS FRANCO
 */

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h" // Incluye la biblioteca HAL para HAL_GetTick()
#include <stdbool.h>        // Permite usar el tipo 'bool' y 'true/false'
#include <stdint.h>         // Tipos enteros de ancho fijo (uint32_t)
#include <stddef.h>         // Definición de NULL

/* Exported types ------------------------------------------------------------*/

// Tipo de dato para las marcas de tiempo en milisegundos
typedef uint32_t tick_t;

// Tipo booleano personalizado
typedef bool bool_t;

// Estructura de control para el retardo no bloqueante
typedef struct {
    tick_t startTime; /**< Marca de tiempo inicial */
    tick_t duration;  /**< Duración del retardo en ms */
    bool_t running;   /**< Flag indicador de conteo activo */
} delay_t;

/* Exported functions prototypes ---------------------------------------------*/

/**
  * @brief  Inicializa la duración del retardo y pone running en false.
  * @param  delay: Puntero a la estructura delay_t.
  * @param  duration: Duración en milisegundos.
  */
void delayInit(delay_t * delay, tick_t duration);

/**
  * @brief  Evalúa si se cumplió el tiempo del retardo de forma no bloqueante.
  * @param  delay: Puntero a la estructura delay_t.
  * @retval bool_t: true si el tiempo expiro, false en caso contrario.
  */
bool_t delayRead(delay_t * delay);

/**
  * @brief  Modifica la duración de un retardo existente.
  * @param  delay: Puntero a la estructura delay_t.
  * @param  duration: Nueva duración en milisegundos.
  */
void delayWrite(delay_t * delay, tick_t duration);

#endif /* API_INC_API_DELAY_H_ */

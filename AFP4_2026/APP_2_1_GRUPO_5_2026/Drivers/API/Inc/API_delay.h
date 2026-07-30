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
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h" // HAL necesaria para acceder a HAL_GetTick()

/* Typedefs ------------------------------------------------------------------*/
typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct {
    tick_t startTime;
    tick_t duration;
    bool_t running;
} delay_t;

/* Public function prototypes ------------------------------------------------*/
/**
  * @brief Inicializa la estructura del retardo.
  * @param delay: Puntero a la estructura delay_t.
  * @param duration: Tiempo de retardo en milisegundos.
  */
void delayInit(delay_t * delay, tick_t duration);

/**
  * @brief Verifica si el tiempo del retardo transcurrió.
  * @param delay: Puntero a la estructura delay_t.
  * @retval true si se cumplió el tiempo, false en caso contrario.
  */
bool_t delayRead(delay_t * delay);

/**
  * @brief Cambia el tiempo de duración de un retardo existente.
  * @param delay: Puntero a la estructura delay_t.
  * @param duration: Nuevo tiempo en milisegundos.
  */
void delayWrite(delay_t * delay, tick_t duration);

#endif /* API_INC_API_DELAY_H_ */

/*
 * API_delay.h
 *
 *  Created on: 30 jul 2026
 *      Author:
 */
/*
 * API_delay.h
 *
 *  Created on: 2026
 *      Author: Grupo 5_2026
 */

#ifndef API_DELAY_H_
#define API_DELAY_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h" // Necesario para HAL_GetTick()

/* Exported types ------------------------------------------------------------*/
typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct {
    tick_t startTime;
    tick_t duration;
    bool_t running;
} delay_t;

/* Exported functions prototypes ---------------------------------------------*/
void delayInit(delay_t * delay, tick_t duration);
bool_t delayRead(delay_t * delay);
void delayWrite(delay_t * delay, tick_t duration);

#endif /* API_DELAY_H_ */

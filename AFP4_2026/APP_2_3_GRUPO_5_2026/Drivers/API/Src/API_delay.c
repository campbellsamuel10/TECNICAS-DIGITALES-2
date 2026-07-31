/*
 * API_delay.c
 *  Created on: 30 jul 2026
 *      Author: GRUPO 5_2026
 *      GUZMÁN CARDOSO MELANI
 *      SANCHEZ LUCIANA NATALÍ
 *      CAMPBELL SAMUEL
 *      PALACIOS FRANCO
 */
#include "main.h"
#include "API_delay.h"
/**
  * @brief Iniacializacion del delay,establece la duracion.
  */
void delayInit(delay_t * delay, tick_t duration) {

    delay->duration = duration;
    delay->running = false;
}
/**
  * @brief Revisa si ya paso el tiempo correspondiente al dealy.
  */
bool_t delayRead(delay_t * delay) {
	{if (delay->running){
        if ((HAL_GetTick() - delay->startTime) >= delay->duration) {
            delay->running = false; // El tiempo se cumplió
            return true;
        }
        else  {
    return false;
           }
	}
 else {
        delay->startTime = HAL_GetTick();
        delay->running = true;
        return false;
       }
}
}
/**
	  * @brief Describe el tiempo de duracion.
	  */
void delayWrite(delay_t * delay, tick_t duration) {

	    delay->duration = duration;
}


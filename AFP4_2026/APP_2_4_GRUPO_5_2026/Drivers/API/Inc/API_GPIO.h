/*
 * API_GPIO.h
 *
 *  Created on: 28 jul 2026
 *      Author: Grupo 5_2026
 *               GUZMAN CARDOSO MELANI
 *               SANCHEZ LUCIANA NATALI
 *               CAMPBELL SAMUEL
 *               PALACIOS FRANCO
 */
/**
  ******************************************************************************
  * @file    API_gpio.h
  * @brief   Driver de abstracción para el control de LEDs por frecuencias de parpadeo.
  ******************************************************************************
  */

#ifndef API_GPIO_H_
#define API_GPIO_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdbool.h>

/* Exported types ------------------------------------------------------------*/
/**
 * @brief Estados de frecuencia para el parpadeo de los LEDs
 */
typedef enum {
    ESTADO_TIEMPO_100MS = 0,
    ESTADO_TIEMPO_250MS,
    ESTADO_TIEMPO_500MS,
    ESTADO_TIEMPO_1000MS,
    ESTADO_TIEMPO_MAX = ESTADO_TIEMPO_1000MS
} estado_frecuencia_t;

/* Exported functions prototypes ---------------------------------------------*/

/**
  * @brief  Inicializa los periféricos y el estado interno del driver.
  */
void API_GPIO_Init(void);

/**
  * @brief  Apaga todos los LEDs gestionados por la API.
  */
void API_GPIO_Apagar_LEDs(void);

/**
  * @brief  Genera un retardo en milisegundos (abstrae la llamada HAL_Delay).
  * @param  delay_ms: Tiempo en milisegundos.
  */
void API_GPIO_Delay(uint32_t delay_ms);

/**
  * @brief  Evalúa la lectura del botón con filtro antirrebote y flanco de subida.
  * @retval true si se detecta una pulsación válida, false en caso contrario.
  */
bool API_GPIO_Boton_Presionado(void);

/**
  * @brief  Ejecuta la acción de parpadeo según el estado de frecuencia activo.
  * @param  estado: Estado de la frecuencia activa.
  */
void API_GPIO_Ejecutar_Frecuencia(estado_frecuencia_t estado);

#endif /* API_GPIO_H_ */

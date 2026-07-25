/*
 * API_GPIO.c
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
  * @file    API_gpio.c
  * @brief   Implementación de la API de GPIOs para control de frecuencia de LEDs.
  ******************************************************************************
  */

#include "API_GPIO.h"

/* Private variables ---------------------------------------------------------*/
static uint8_t boton_previo = 0;

// Arreglo privado con los tiempos de retardo asociados a cada estado
static const uint32_t tiempos_ms[] = {100, 250, 500, 1000};

/* Private HAL Wrappers ------------------------------------------------------*/

static void API_GPIO_Escribir_Pin(uint16_t GPIO_Pin, GPIO_PinState PinState) {
    HAL_GPIO_WritePin(GPIOB, GPIO_Pin, PinState);
}

static void API_GPIO_Toggle_Pin(uint16_t GPIO_Pin) {
    HAL_GPIO_TogglePin(GPIOB, GPIO_Pin);
}

static GPIO_PinState API_GPIO_Leer_Boton(void) {
    return HAL_GPIO_ReadPin(USER_BTN_GPIO_Port, USER_BTN_Pin);
}

/* Public functions ----------------------------------------------------------*/

void API_GPIO_Init(void) {
    API_GPIO_Apagar_LEDs();
    boton_previo = 0;
}

void API_GPIO_Apagar_LEDs(void) {
    API_GPIO_Escribir_Pin(LD1_Pin | LD2_Pin | LD3_Pin, GPIO_PIN_RESET);
}

void API_GPIO_Delay(uint32_t delay_ms) {
    HAL_Delay(delay_ms);
}

bool API_GPIO_Boton_Presionado(void) {
    bool detectado = false;
    uint8_t boton_actual = API_GPIO_Leer_Boton();

    // Detección de flanco de subida con antirrebote simple
    if (boton_actual == GPIO_PIN_SET && boton_previo == 0) {
        API_GPIO_Delay(50); // Antirrebote
        if (API_GPIO_Leer_Boton() == GPIO_PIN_SET) {
            detectado = true;
        }
    }
    boton_previo = boton_actual;
    return detectado;
}

void API_GPIO_Ejecutar_Frecuencia(estado_frecuencia_t estado) {
    // Alternar los 3 LEDs simultáneamente
    API_GPIO_Toggle_Pin(LD1_Pin | LD2_Pin | LD3_Pin);

    // Esperar el tiempo configurado para el estado actual
    if (estado <= ESTADO_TIEMPO_MAX) {
        API_GPIO_Delay(tiempos_ms[estado]);
    } else {
        API_GPIO_Delay(tiempos_ms[ESTADO_TIEMPO_100MS]);
    }
}


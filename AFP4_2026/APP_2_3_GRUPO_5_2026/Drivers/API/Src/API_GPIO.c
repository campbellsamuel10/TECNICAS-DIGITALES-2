/*
 * API_GPIO.c
 *
 *  Created on: 30 jul 2026
 *      Author:Grupo 5_2026
 *               GUZMAN CARDOSO MELANI
 *               SANCHEZ LUCIANA NATALI
 *               CAMPBELL SAMUEL
 *               PALACIOS FRANCO
 */
/**
  ******************************************************************************
  * @file    API_gpio.c
  * @brief   Implementación del driver de GPIO y secuencias.
  ******************************************************************************
  */
/*
 * API_gpio.c
 *
 *  Created on: 25 jul 2026
 *      Author: Grupo 5_2026
 */

#include "API_GPIO.h"

/* Private variables --------------------------------------------------------- */
static uint8_t boton_previo = 0;

// Delays para las secuencias y antirrebote
static delay_t delay_secuencia1;
static delay_t delay_secuencia2;
static delay_t delay_led1_sec3, delay_led2_sec3, delay_led3_sec3;
static delay_t delay_secuencia4;
static delay_t delay_antirrebote;

/* Public functions ----------------------------------------------------------*/

void API_GPIO_Init(void) {
    API_GPIO_Apagar_LEDs();
    boton_previo = 0;

    // Inicialización de delays no bloqueantes
    delayInit(&delay_secuencia1, 150);
    delayInit(&delay_secuencia2, 300);

    delayInit(&delay_led1_sec3, 100);
    delayInit(&delay_led2_sec3, 300);
    delayInit(&delay_led3_sec3, 600);

    delayInit(&delay_secuencia4, 150);

    delayInit(&delay_antirrebote, 50);
}

void API_GPIO_Apagar_LEDs(void) {
    HAL_GPIO_WritePin(GPIOB, LD1_Pin | LD2_Pin | LD3_Pin, GPIO_PIN_RESET);
}

bool API_GPIO_Boton_Presionado(void) {
    bool detectado = false;
    uint8_t boton_actual = HAL_GPIO_ReadPin(USER_BTN_GPIO_Port, USER_BTN_Pin);

    // Detección de flanco de subida con antirrebote no bloqueante
    if (boton_actual == GPIO_PIN_SET && boton_previo == 0) {
        if (delayRead(&delay_antirrebote)) {
            if (HAL_GPIO_ReadPin(USER_BTN_GPIO_Port, USER_BTN_Pin) == GPIO_PIN_SET) {
                detectado = true;
            }
        }
    } else {
        // Mantiene reseteado el delay si no hay intento de presionar
        delay_antirrebote.running = false;
    }

    boton_previo = boton_actual;
    return detectado;
}

/* Secuencias No Bloqueantes -------------------------------------------------*/

static void Secuencia_1(void) {
    static uint8_t paso = 0;

    if (delayRead(&delay_secuencia1)) {
        switch (paso) {
            case 0:
                HAL_GPIO_WritePin(GPIOB, LD1_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOB, LD2_Pin | LD3_Pin, GPIO_PIN_RESET);
                paso = 1;
                break;
            case 1:
                HAL_GPIO_WritePin(GPIOB, LD2_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOB, LD1_Pin | LD3_Pin, GPIO_PIN_RESET);
                paso = 2;
                break;
            case 2:
                HAL_GPIO_WritePin(GPIOB, LD3_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOB, LD1_Pin | LD2_Pin, GPIO_PIN_RESET);
                paso = 0;
                break;
        }
    }
}

static void Secuencia_2(void) {
    if (delayRead(&delay_secuencia2)) {
        HAL_GPIO_TogglePin(GPIOB, LD1_Pin | LD2_Pin | LD3_Pin);
    }
}

static void Secuencia_3(void) {
    if (delayRead(&delay_led1_sec3)) {
        HAL_GPIO_TogglePin(GPIOB, LD1_Pin);
    }
    if (delayRead(&delay_led2_sec3)) {
        HAL_GPIO_TogglePin(GPIOB, LD2_Pin);
    }
    if (delayRead(&delay_led3_sec3)) {
        HAL_GPIO_TogglePin(GPIOB, LD3_Pin);
    }
}

static void Secuencia_4(void) {
    static uint8_t estado = 0;

    if (delayRead(&delay_secuencia4)) {
        if (estado == 0) {
            HAL_GPIO_WritePin(GPIOB, LD1_Pin | LD3_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, LD2_Pin, GPIO_PIN_RESET);
            estado = 1;
        } else {
            HAL_GPIO_WritePin(GPIOB, LD1_Pin | LD3_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, LD2_Pin, GPIO_PIN_SET);
            estado = 0;
        }
    }
}

void API_GPIO_Ejecutar_Secuencia(secuencia_t secuencia) {
    switch (secuencia) {
        case SECUENCIA_1:
            Secuencia_1();
            break;
        case SECUENCIA_2:
            Secuencia_2();
            break;
        case SECUENCIA_3:
            Secuencia_3();
            break;
        case SECUENCIA_4:
            Secuencia_4();
            break;
        default:
            API_GPIO_Apagar_LEDs();
            break;
    }
}



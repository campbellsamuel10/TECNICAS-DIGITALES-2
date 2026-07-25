/*
 * API_GPIO.c
 *
 *  Created on: 25 jul 2026
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

/* Includes ------------------------------------------------------------------*/
#include "API_gpio.h"

/* Private variables ---------------------------------------------------------*/
static uint8_t boton_previo = 0;

/* Funciones Privadas (Auxiliares para las secuencias) -----------------------*/

static void Secuencia_1(void) {
    HAL_GPIO_WritePin(GPIOB, LD1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, LD2_Pin | LD3_Pin, GPIO_PIN_RESET);
    HAL_Delay(150);

    HAL_GPIO_WritePin(GPIOB, LD2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, LD1_Pin | LD3_Pin, GPIO_PIN_RESET);
    HAL_Delay(150);

    HAL_GPIO_WritePin(GPIOB, LD3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, LD1_Pin | LD2_Pin, GPIO_PIN_RESET);
    HAL_Delay(150);
}

static void Secuencia_2(void) {
    HAL_GPIO_TogglePin(GPIOB, LD1_Pin | LD2_Pin | LD3_Pin);
    HAL_Delay(300);
}

static void Secuencia_3(void) {
    static uint32_t t_led1 = 0, t_led2 = 0, t_led3 = 0;
    uint32_t now = HAL_GetTick();

    if (now - t_led1 >= 100) {
        HAL_GPIO_TogglePin(GPIOB, LD1_Pin);
        t_led1 = now;
    }
    if (now - t_led2 >= 300) {
        HAL_GPIO_TogglePin(GPIOB, LD2_Pin);
        t_led2 = now;
    }
    if (now - t_led3 >= 600) {
        HAL_GPIO_TogglePin(GPIOB, LD3_Pin);
        t_led3 = now;
    }
    HAL_Delay(10);
}

static void Secuencia_4(void) {
    HAL_GPIO_WritePin(GPIOB, LD1_Pin | LD3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, LD2_Pin, GPIO_PIN_RESET);
    HAL_Delay(150);

    HAL_GPIO_WritePin(GPIOB, LD1_Pin | LD3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, LD2_Pin, GPIO_PIN_SET);
    HAL_Delay(150);
}

/* Public functions ----------------------------------------------------------*/

void API_GPIO_Init(void) {
    API_GPIO_Apagar_LEDs();
    boton_previo = 0;
}

void API_GPIO_Apagar_LEDs(void) {
    HAL_GPIO_WritePin(GPIOB, LD1_Pin | LD2_Pin | LD3_Pin, GPIO_PIN_RESET);
}

bool API_GPIO_Boton_Presionado(void) {
    bool detectado = false;
    uint8_t boton_actual = HAL_GPIO_ReadPin(USER_BTN_GPIO_Port, USER_BTN_Pin);

    // Detección de flanco de subida con antirrebote simple
    if (boton_actual == GPIO_PIN_SET && boton_previo == 0) {
        HAL_Delay(50); // Filtro de rebote mecánico
        if (HAL_GPIO_ReadPin(USER_BTN_GPIO_Port, USER_BTN_Pin) == GPIO_PIN_SET) {
            detectado = true;
        }
    }
    boton_previo = boton_actual;
    return detectado;
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


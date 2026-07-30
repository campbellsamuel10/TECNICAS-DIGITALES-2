/*
 * API_GPIO.c
 *
 *  Created on: 28 jul 2026
 *      Author: GRUPO 5_2026
 *      GUZMÁN CARDOSO MELANI
 *      SANCHEZ LUCIANA NATALÍ
 *      CAMPBELL SAMUEL
 *      PALACIOS FRANCO
 */
#include "API_GPIO.h"
#include "main.h"

/**
  * @brief Enciende un LED especificado.
  */
void writeLedOn_GPIO(uint16_t LED_Pin) {
    HAL_GPIO_WritePin(GPIOB, LED_Pin, GPIO_PIN_SET);
}

/**
  * @brief Apaga un LED especificado.
  */
void writeLedOff_GPIO(uint16_t LED_Pin) {
    HAL_GPIO_WritePin(GPIOB, LED_Pin, GPIO_PIN_RESET);
}

/**
  * @brief Conmuta (toggle) el estado de un LED especificado.
  */
void toggleLed_GPIO(uint16_t LED_Pin) {
    HAL_GPIO_TogglePin(GPIOB, LED_Pin);
}

/**
  * @brief Lee el estado del botón azul de la placa NUCLEO.
  * @retval true si está presionado, false si está suelto.
  */
bool_t readButton_GPIO(void) {
    // Para placas NUCLEO donde el botón se activa en alto (GPIO_PIN_SET):
    if (HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin) == GPIO_PIN_SET) {
        return true;
    }
    return false;
}

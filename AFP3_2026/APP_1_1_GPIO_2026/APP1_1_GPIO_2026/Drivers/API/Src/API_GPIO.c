/*
 * API_GPIO.c
 *
 *  Created on: 23 jul 2026
 *      Author: GRUPO 5_2026
 *      GUZMÁN CARDOSO MELANI
 *      SANCHEZ LUCIANA NATALÍ
 *      CAMPBELL SAMUEL
 *      PALACIOS FRANCO
 */

/* API_GPIO.c */
#include "main.h"

#include "API_GPIO.h"

/* Declaration of variables --------------------------------------------------*/
led_t LDx;

/* Function definitions ------------------------------------------------------*/

/**
  * @brief  Inicialización de módulos GPIO
  * @retval None
  */



/**
  * @brief  Enciende un LED especificado
  * @param  LDx: Pin del LED a encender
  */
void writeLedOn_GPIO(led_t LDx)
{
    HAL_GPIO_WritePin(GPIOB, LDx, GPIO_PIN_SET);
}

/**
  * @brief  Apaga un LED especificado
  * @param  LDx: Pin del LED a apagar
  */
void writeLedOff_GPIO(led_t LDx)
{
    HAL_GPIO_WritePin(GPIOB, LDx, GPIO_PIN_RESET);
}

/**
  * @brief  Conmuta (toggle) el estado de un LED especificado
  * @param  LDx: Pin del LED a conmutar
  */
void toggleLed_GPIO(led_t LDx)
{
    HAL_GPIO_TogglePin(GPIOB, LDx);
}

/**
  * @brief  Lee el estado del pulsador de usuario
  * @retval Estado lógico del pulsador (true/false)
  */
/*buttonStatus_t readButton_GPIO(void)
{
    return (buttonStatus_t)HAL_GPIO_ReadPin(GPIOC, USER_Btn_Pin);
}
*/


/*
 * API_debounce.c
 *
 *  Created on: 3 oct 2026
 *      Author: GRUPO 5_2026
 *      GUZMÁN CARDOSO MELANI
 *      SANCHEZ LUCIANA NATALÍ
 *      CAMPBELL SAMUEL
 *      PALACIOS FRANCO
 */

/*Includes -------------------------------------------------------------------*/
#include "API_debounce.h"
#include "API_delay.h"
#include "API_GPIO.h"

/*Defines --------------------------------------------------------------------*/
#define DEBOUNCE_DELAY 40 // Tiempo (en ms) de espera para el antirrebote

/*Declaracion de variables (privadas del módulo) */
static debounceState_t actualState; // Almacena el estado actual de la FSM
static bool keyPressed = false;     // Flag para indicar una pulsación completada
delay_t debounceDelay;              // Estructura de delay para el antirrebote

/*Define functions -----------------------------------------------------------*/

/**
  * @brief  Devuelve 'true' si la tecla fue presionada (y consume el evento).
  * @brief  Asume tecla activa alta (true = presionado).
  * @param  None
  * @retval bool: 'true' si hubo una pulsación nueva, 'false' de lo contrario.
  */
bool readKey(void)
{
	bool keyPressDetected = false;

	if (keyPressed)
	{
		keyPressDetected = true;
		keyPressed = false; // Consumir el evento
	}

	return keyPressDetected;
}

/**
  * @brief  Carga el estado inicial de la MEF y configura el delay.
  * @param  None
  * @retval None
  */
void debounceFSM_init(void)
{
	actualState = BUTTON_UP;
	keyPressed = false;
	delayInit(&debounceDelay, DEBOUNCE_DELAY);
}

/**
  * @brief  Desarrollo de la MEF de debounce.
  * @param  buttonRead: 'true' si el botón está presionado, 'false' si está liberado.
  * @retval None
  */
void debounceFSM_update(bool buttonRead)
{
	switch (actualState)
	{
	case BUTTON_UP:
		if (buttonRead)
		{
			actualState = BUTTON_FALLING;
			delayRead(&debounceDelay);
		}
		break;

	case BUTTON_FALLING:
		if (delayRead(&debounceDelay))
		{
			if (buttonRead)
			{
				buttonPressed();
				keyPressed = true;
				actualState = BUTTON_DOWN;
			}
			else
			{
				actualState = BUTTON_UP;
			}
		}
		break;

	case BUTTON_DOWN:
		if (!buttonRead)
		{
			actualState = BUTTON_RISING;
			delayRead(&debounceDelay);
		}
		break;

	case BUTTON_RISING:
		if (delayRead(&debounceDelay))
		{
			if (!buttonRead)
			{
				buttonReleased();
				actualState = BUTTON_UP;
			}
			else
			{
				actualState = BUTTON_DOWN;
			}
		}
		break;

	default:
		debounceFSM_init();
		break;
	}
}

/**
  * @brief  Evento (callback) que se ejecuta cuando se detecta "tecla presionada".
  * @brief  Aquí se coloca la acción inmediata a realizar al presionar.
  * @param  none
  * @retval None
  */
void buttonPressed(void)
{
    toggleLed_GPIO(LD1_Pin); // Invierte el LED1 en el flanco descendente confirmado
}

/**
  * @brief  Evento (callback) que se ejecuta cuando se detecta "tecla liberada".
  * @brief  Aquí se coloca la acción inmediata a realizar al liberar.
  * @param  none
  * @retval None
  */
void buttonReleased(void)
{
    toggleLed_GPIO(LD3_Pin); // Invierte el LED3 en el flanco ascendente confirmado
}


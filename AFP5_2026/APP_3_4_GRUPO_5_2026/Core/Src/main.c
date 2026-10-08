/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body - App 1.4 con MEF Debounce
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "API_GPIO.h"
#include "API_delay.h"
#include "API_debounce.h"

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LED1 LD1_Pin  // LED Verde
#define LED2 LD2_Pin  // LED Azul
#define LED3 LD3_Pin  // LED Rojo

// Tiempos de alternancia predefinidos (ms)
#define TIEMPO_1   100
#define TIEMPO_2   250
#define TIEMPO_3   500
#define TIEMPO_4  1000
/* USER CODE END PD */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();

  /* USER CODE BEGIN 2 */
  uint16_t leds[3] = {LED1, LED2, LED3};
  uint8_t secuencia = 1;

  // 1. Sincronización: asegurar que los tres LEDs comiencen apagados
  for (uint8_t i = 0; i < 3; i++)
  {
      writeLedOff_GPIO(leds[i]);
  }

  // 2. Inicializar retardo no bloqueante con Tiempo 1 (100 ms)
  delay_t delay_leds;
  delayInit(&delay_leds, TIEMPO_1);

  // 3. Inicializar la MEF de antirrebote
  debounceFSM_init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      /* 1. Actualización continua de la MEF de antirrebote */
      debounceFSM_update(readButton_GPIO());

      /* 2. Detección de nueva pulsación (evento consumido) */
      if (readKey())
      {
          secuencia++;
          if (secuencia > 4)
          {
              secuencia = 1;
          }

          switch (secuencia)
          {
              case 1:
                  delayWrite(&delay_leds, TIEMPO_1);
                  break;
              case 2:
                  delayWrite(&delay_leds, TIEMPO_2);
                  break;
              case 3:
                  delayWrite(&delay_leds, TIEMPO_3);
                  break;
              case 4:
                  delayWrite(&delay_leds, TIEMPO_4);
                  break;
          }
      }

      /* 3. Conmutación 100% simultánea de los 3 LEDs */
      if (delayRead(&delay_leds))
      {
          for (uint8_t i = 0; i < 3; i++)
          {
              toggleLed_GPIO(leds[i]);
          }
      }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif

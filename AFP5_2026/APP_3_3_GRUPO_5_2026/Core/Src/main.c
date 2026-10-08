/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : App 1.3 - Control de secuencias de LEDs con FSM Debounce
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdbool.h>
#include <stdint.h>
#include "API_GPIO.h"
#include "API_delay.h"
#include "API_debounce.h"

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LED1 LD1_Pin // GREEN LED
#define LED2 LD2_Pin // BLUE LED
#define LED3 LD3_Pin // RED LED

#define RETARDO_100MS 100
#define RETARDO_150MS 150
#define RETARDO_300MS 300
#define RETARDO_600MS 600

#define CANT_LED 3
/* USER CODE END PD */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */
static uint16_t LEDS[CANT_LED] = {LED1, LED2, LED3};

/* Delays independientes para no interferir entre secuencias */
static delay_t timer_sec1;
static delay_t timer_sec2;
static delay_t timer_sec3_led1;
static delay_t timer_sec3_led2;
static delay_t timer_sec3_led3;
static delay_t timer_sec4;

static uint8_t secuencia_activa = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_USART3_UART_Init(void);

/* USER CODE BEGIN PFP */
static void apagarTodosLosLeds(void);
static void inicializarSecuencia(uint8_t sec);
static void ejecutarSecuencia1(void);
static void ejecutarSecuencia2(void);
static void ejecutarSecuencia3(void);
static void ejecutarSecuencia4(void);
/* USER CODE END PFP */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART3_UART_Init();

  /* USER CODE BEGIN 2 */
  /* Inicialización del antirrebote y la primera secuencia */
  debounceFSM_init();
  inicializarSecuencia(secuencia_activa);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* 1. Actualización de la MEF de antirrebote leyendo el botón */
    bool estadoBoton = readButton_GPIO();
    debounceFSM_update(estadoBoton);

    /* 2. Detección de pulsación y transición de secuencia */
    if (readKey())
    {
      secuencia_activa++;
      if (secuencia_activa >= 4)
      {
        secuencia_activa = 0;
      }
      inicializarSecuencia(secuencia_activa);
    }

    /* 3. Ejecución no bloqueante de la secuencia seleccionada */
    switch (secuencia_activa)
    {
      case 0:
        ejecutarSecuencia1();
        break;

      case 1:
        ejecutarSecuencia2();
        break;

      case 2:
        ejecutarSecuencia3();
        break;

      case 3:
        ejecutarSecuencia4();
        break;

      default:
        secuencia_activa = 0;
        inicializarSecuencia(secuencia_activa);
        break;
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/* USER CODE BEGIN 4 */

static void apagarTodosLosLeds(void)
{
  writeLedOff_GPIO(LEDS[0]);
  writeLedOff_GPIO(LEDS[1]);
  writeLedOff_GPIO(LEDS[2]);
}

/**
  * @brief  Prepara las variables y estados de salida de cada secuencia al entrar en ella.
  */
static void inicializarSecuencia(uint8_t sec)
{
  apagarTodosLosLeds();

  switch (sec)
  {
    case 0:
      delayInit(&timer_sec1, RETARDO_150MS);
      writeLedOn_GPIO(LEDS[0]); // Inicia con el primer LED encendido
      break;

    case 1:
      delayInit(&timer_sec2, RETARDO_300MS);
      writeLedOn_GPIO(LEDS[0]);
      writeLedOn_GPIO(LEDS[1]);
      writeLedOn_GPIO(LEDS[2]);
      break;

    case 2:
      delayInit(&timer_sec3_led1, RETARDO_100MS);
      delayInit(&timer_sec3_led2, RETARDO_300MS);
      delayInit(&timer_sec3_led3, RETARDO_600MS);
      break;

    case 3:
      delayInit(&timer_sec4, RETARDO_150MS);
      writeLedOn_GPIO(LEDS[0]);  // LED1 ON
      writeLedOff_GPIO(LEDS[1]); // LED2 OFF
      writeLedOn_GPIO(LEDS[2]);  // LED3 ON
      break;

    default:
      break;
  }
}

/**
  * @brief  Secuencia 1: Rotación cíclica LED1 -> LED2 -> LED3 cada 150 ms.
  */
static void ejecutarSecuencia1(void)
{
  static uint8_t indiceLed = 0;

  if (delayRead(&timer_sec1))
  {
    writeLedOff_GPIO(LEDS[indiceLed]);
    indiceLed++;
    if (indiceLed >= CANT_LED)
    {
      indiceLed = 0;
    }
    writeLedOn_GPIO(LEDS[indiceLed]);
  }
}

/**
  * @brief  Secuencia 2: Parpadeo simultáneo de los 3 LEDs cada 300 ms.
  */
static void ejecutarSecuencia2(void)
{
  if (delayRead(&timer_sec2))
  {
    toggleLed_GPIO(LEDS[0]);
    toggleLed_GPIO(LEDS[1]);
    toggleLed_GPIO(LEDS[2]);
  }
}

/**
  * @brief  Secuencia 3: LED1 (100 ms), LED2 (300 ms), LED3 (600 ms) independientes.
  */
static void ejecutarSecuencia3(void)
{
  if (delayRead(&timer_sec3_led1))
  {
    toggleLed_GPIO(LEDS[0]);
  }

  if (delayRead(&timer_sec3_led2))
  {
    toggleLed_GPIO(LEDS[1]);
  }

  if (delayRead(&timer_sec3_led3))
  {
    toggleLed_GPIO(LEDS[2]);
  }
}

/**
  * @brief  Secuencia 4: Alternancia a 150 ms en contrafase (LED1 y LED3 vs LED2).
  */
static void ejecutarSecuencia4(void)
{
  if (delayRead(&timer_sec4))
  {
    toggleLed_GPIO(LEDS[0]);
    toggleLed_GPIO(LEDS[1]);
    toggleLed_GPIO(LEDS[2]);
  }
}

/* USER CODE END 4 */

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
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

  /** Initializes the CPU, AHB and APB buses clocks
  */
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

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{
  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "crc.h"
#include "dac.h"
#include "dma.h"
#include "fdcan.h"
#include "i2c.h"
#include "quadspi.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"
#include "fmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_cdc_if.h"
#include "lcd.h"
#include "lcd_demo.h"
#include "ugui.h"
#include "lcd_ugui.h"
#include "XPT2046_touch.h"
#include "joystick.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	coord_t joystick_raw={0,0}, joystick_new={0,0}, joystick_prev={0,0};
	joystick_t joystick;
	char MSG[100]={0};
	uint16_t touch_x = 0, touch_y = 0;

	char str[50];
	float bitrate;

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_FMC_Init();
  MX_I2C2_Init();
  MX_UART4_Init();
  MX_UART5_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_QUADSPI1_Init();
  MX_SPI1_Init();
  MX_TIM5_Init();
  MX_TIM8_Init();
  MX_TIM20_Init();
  MX_ADC3_Init();
  MX_DAC1_Init();
  MX_DAC2_Init();
  MX_FDCAN2_Init();
  MX_I2C1_Init();
  MX_TIM15_Init();
  MX_USART3_UART_Init();
  MX_USB_Device_Init();
  MX_DMA_Init();
  MX_CRC_Init();
  /* USER CODE BEGIN 2 */

  MX_ADC4_Init();	//bug workaround: https://community.st.com/s/question/0D50X0000BVnBhASQV/bug-report-dma-and-adc-initialization-order-changed-in-stm32f4-hal-v1241-causing-incorrect-adc-operation

  for (uint8_t i=0;i<3;i++)
  {
	  HAL_Delay(100);
	  HAL_GPIO_WritePin(GPIOF, LED0_Pin|LED1_Pin|LED2_Pin|LED3_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOC, LED4_Pin|LED5_Pin|LED6_Pin|LED7_Pin, GPIO_PIN_SET);
	  HAL_Delay(100);
	  HAL_GPIO_WritePin(GPIOF, LED0_Pin|LED1_Pin|LED2_Pin|LED3_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOC, LED4_Pin|LED5_Pin|LED6_Pin|LED7_Pin, GPIO_PIN_RESET);
  }

  LCD_Init();
  LCD_UG_init();

  LCD_Intro_LogoSlide(140,200);
  bitrate = DrawColors(0,0,80);

  UG_SetForecolor(C_WHITE);
  UG_FontSelect(&FONT_8X12);
  sprintf(str,"%.2f MB/s, %.0f fps",bitrate/(1024*1024),bitrate/(100.0*180*2));
  UG_PutString(5,105,str);

  // to mi deli
  UG_SetForecolor(C_WHITE);
  UG_FontSelect(&FONT_16X26);
  UG_PutString(5,205,"To mi deli, Borut!");

  joystick_init(&joystick);
  HAL_ADC_Start_DMA(&hadc4, &joystick_raw, 2);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  //LEDs and KEYs
	 HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, !HAL_GPIO_ReadPin(BTN_OK_GPIO_Port, BTN_OK_Pin));
	 HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, !HAL_GPIO_ReadPin(BTN_DOWN_GPIO_Port, BTN_DOWN_Pin));
	 HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, !HAL_GPIO_ReadPin(BTN_RIGHT_GPIO_Port, BTN_RIGHT_Pin));
	 HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, !HAL_GPIO_ReadPin(BTN_UP_GPIO_Port, BTN_UP_Pin));
	 HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, !HAL_GPIO_ReadPin(BTN_LEFT_GPIO_Port, BTN_LEFT_Pin));
	 HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, !HAL_GPIO_ReadPin(BTN_ESC_GPIO_Port, BTN_ESC_Pin));
	 HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, !HAL_GPIO_ReadPin(JOY_BTN_GPIO_Port, JOY_BTN_Pin));

	 if (!HAL_GPIO_ReadPin(BTN_ESC_GPIO_Port, BTN_ESC_Pin))
	 {
		 UG_FillFrame(200, 0, 319, 120, C_BLACK);
	 }

	 //Joystick
	 joystick_get(&joystick_raw, &joystick_new, &joystick);
	 UG_DrawCircle(joystick_prev.x+250, joystick_prev.y+50,3, C_BLACK);
	 UG_DrawCircle(joystick_new.x+250, joystick_new.y+50,3, C_YELLOW);

	 joystick_prev.x = joystick_new.x;
	 joystick_prev.y = joystick_new.y;

	 //Touch
	 if(XPT2046_TouchPressed())
	 {
		uint16_t x = 0, y = 0;
		HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, 1);
		if(XPT2046_TouchGetCoordinates(&x, &y, 0))
		{
			touch_x = x;
			touch_y = y;
			UG_FillCircle(x, y,2, C_GREEN);
		}
	 }
	 else HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, 0);

	 UG_DrawCircle(250, 50, 50, C_RED);

	 //USART and USB
	 sprintf(MSG, "Joystick X:%05d, Y:%05d, Touch: X:%05d, Y:%05d    \r",joystick_raw.x,joystick_raw.y, touch_x, touch_y);

	 HAL_UART_Transmit(&huart3, MSG, strlen(MSG), 100);
	 CDC_Transmit_FS(MSG, strlen(MSG));

	 HAL_Delay(20);
  }

  /* USER CODE END 3 */
}

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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 42;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV6;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
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
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

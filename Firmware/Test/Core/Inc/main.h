/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

#include "stm32g4xx_ll_usart.h"
#include "stm32g4xx_ll_rcc.h"
#include "stm32g4xx_ll_bus.h"
#include "stm32g4xx_ll_cortex.h"
#include "stm32g4xx_ll_system.h"
#include "stm32g4xx_ll_utils.h"
#include "stm32g4xx_ll_pwr.h"
#include "stm32g4xx_ll_gpio.h"
#include "stm32g4xx_ll_dma.h"

#include "stm32g4xx_ll_exti.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define JOY_BTN_Pin GPIO_PIN_13
#define JOY_BTN_GPIO_Port GPIOC
#define BTN_ESC_Pin GPIO_PIN_14
#define BTN_ESC_GPIO_Port GPIOC
#define BTN_OK_Pin GPIO_PIN_15
#define BTN_OK_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_3
#define LED1_GPIO_Port GPIOF
#define LED2_Pin GPIO_PIN_4
#define LED2_GPIO_Port GPIOF
#define LED3_Pin GPIO_PIN_5
#define LED3_GPIO_Port GPIOF
#define PWM2_Pin GPIO_PIN_7
#define PWM2_GPIO_Port GPIOF
#define PWM3_Pin GPIO_PIN_8
#define PWM3_GPIO_Port GPIOF
#define PWM4_Pin GPIO_PIN_9
#define PWM4_GPIO_Port GPIOF
#define PWM5_Pin GPIO_PIN_10
#define PWM5_GPIO_Port GPIOF
#define MCI_Pin GPIO_PIN_0
#define MCI_GPIO_Port GPIOF
#define AD5_Pin GPIO_PIN_1
#define AD5_GPIO_Port GPIOF
#define LED4_Pin GPIO_PIN_0
#define LED4_GPIO_Port GPIOC
#define LED5_Pin GPIO_PIN_1
#define LED5_GPIO_Port GPIOC
#define LED6_Pin GPIO_PIN_2
#define LED6_GPIO_Port GPIOC
#define LED7_Pin GPIO_PIN_3
#define LED7_GPIO_Port GPIOC
#define LED0_Pin GPIO_PIN_2
#define LED0_GPIO_Port GPIOF
#define AD0_Pin GPIO_PIN_0
#define AD0_GPIO_Port GPIOA
#define AD1_Pin GPIO_PIN_1
#define AD1_GPIO_Port GPIOA
#define AD2_Pin GPIO_PIN_2
#define AD2_GPIO_Port GPIOA
#define AD3_Pin GPIO_PIN_3
#define AD3_GPIO_Port GPIOA
#define DAC1_Pin GPIO_PIN_4
#define DAC1_GPIO_Port GPIOA
#define AD8_Pin GPIO_PIN_5
#define AD8_GPIO_Port GPIOA
#define DAC2_Pin GPIO_PIN_6
#define DAC2_GPIO_Port GPIOA
#define QSPI_IO2_Pin GPIO_PIN_7
#define QSPI_IO2_GPIO_Port GPIOA
#define AD4_Pin GPIO_PIN_4
#define AD4_GPIO_Port GPIOC
#define AD6_Pin GPIO_PIN_5
#define AD6_GPIO_Port GPIOC
#define QSPI_IO1_Pin GPIO_PIN_0
#define QSPI_IO1_GPIO_Port GPIOB
#define QSPI_IO0_Pin GPIO_PIN_1
#define QSPI_IO0_GPIO_Port GPIOB
#define AD7_Pin GPIO_PIN_2
#define AD7_GPIO_Port GPIOB
#define ARDUINO_CS_Pin GPIO_PIN_11
#define ARDUINO_CS_GPIO_Port GPIOF
#define PWM6_Pin GPIO_PIN_12
#define PWM6_GPIO_Port GPIOF
#define PWM7_Pin GPIO_PIN_13
#define PWM7_GPIO_Port GPIOF
#define PWM8_Pin GPIO_PIN_14
#define PWM8_GPIO_Port GPIOF
#define PWM9_Pin GPIO_PIN_15
#define PWM9_GPIO_Port GPIOF
#define QSPI_CLK_Pin GPIO_PIN_10
#define QSPI_CLK_GPIO_Port GPIOB
#define QSPI_NCS_Pin GPIO_PIN_11
#define QSPI_NCS_GPIO_Port GPIOB
#define CAN2_RX_Pin GPIO_PIN_12
#define CAN2_RX_GPIO_Port GPIOB
#define CAN2_TX_Pin GPIO_PIN_13
#define CAN2_TX_GPIO_Port GPIOB
#define AD9_Pin GPIO_PIN_11
#define AD9_GPIO_Port GPIOD
#define AD10_Pin GPIO_PIN_12
#define AD10_GPIO_Port GPIOD
#define AD11_Pin GPIO_PIN_13
#define AD11_GPIO_Port GPIOD
#define PWM10_Pin GPIO_PIN_6
#define PWM10_GPIO_Port GPIOC
#define PWM11_Pin GPIO_PIN_7
#define PWM11_GPIO_Port GPIOC
#define BTN_UP_Pin GPIO_PIN_0
#define BTN_UP_GPIO_Port GPIOG
#define BTN_DOWN_Pin GPIO_PIN_1
#define BTN_DOWN_GPIO_Port GPIOG
#define PWM12_Pin GPIO_PIN_8
#define PWM12_GPIO_Port GPIOC
#define PWM13_Pin GPIO_PIN_9
#define PWM13_GPIO_Port GPIOC
#define USB_MCU_N_Pin GPIO_PIN_11
#define USB_MCU_N_GPIO_Port GPIOA
#define USB_MCU_P_Pin GPIO_PIN_12
#define USB_MCU_P_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define QSPI_IO3_Pin GPIO_PIN_6
#define QSPI_IO3_GPIO_Port GPIOF
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define LIN_TX_Pin GPIO_PIN_12
#define LIN_TX_GPIO_Port GPIOC
#define LCD_RS_Pin GPIO_PIN_5
#define LCD_RS_GPIO_Port GPIOG
#define BTN_LEFT_Pin GPIO_PIN_6
#define BTN_LEFT_GPIO_Port GPIOG
#define CAN_STBY_Pin GPIO_PIN_7
#define CAN_STBY_GPIO_Port GPIOG
#define BTN_RIGHT_Pin GPIO_PIN_8
#define BTN_RIGHT_GPIO_Port GPIOG
#define LIN_RX_Pin GPIO_PIN_2
#define LIN_RX_GPIO_Port GPIOD
#define LCD_RST_Pin GPIO_PIN_3
#define LCD_RST_GPIO_Port GPIOD
#define LCD_RD_Pin GPIO_PIN_4
#define LCD_RD_GPIO_Port GPIOD
#define LCD_WR_Pin GPIO_PIN_5
#define LCD_WR_GPIO_Port GPIOD
#define TOUCH_PENIRQ_Pin GPIO_PIN_6
#define TOUCH_PENIRQ_GPIO_Port GPIOD
#define LCD_CS_Pin GPIO_PIN_7
#define LCD_CS_GPIO_Port GPIOD
#define LIN_SLP_Pin GPIO_PIN_5
#define LIN_SLP_GPIO_Port GPIOB
#define LCD_BKLT_Pin GPIO_PIN_6
#define LCD_BKLT_GPIO_Port GPIOB
#define FLASH_CS_Pin GPIO_PIN_0
#define FLASH_CS_GPIO_Port GPIOE
#define TOUCH_CS_Pin GPIO_PIN_1
#define TOUCH_CS_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

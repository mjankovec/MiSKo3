//! @file    lcd.h
//! @brief   Grafični gonilnik za platformo MiŠKo3
//! @author  nbert, februar-marec 2022
#ifndef LCD_H_
#define LCD_H_

#include "lcd_ili9341.h"

/* RESET Pin mapping */
#define LCD_RESET_GPIO_PORT  GPIOD
#define LCD_RESET_GPIO_PIN   GPIO_PIN_3

/* LCd backlight Pin mapping */
#define LCD_BCKL_GPIO_PORT  GPIOB
#define LCD_BCKL_GPIO_PIN   GPIO_PIN_6

/* Enable TE function */
//#define LCD_TE_ENABLE

#ifdef LCD_TE_ENABLE
/* TE Pin mapping */
#define LCD_TE_GPIO_PORT     GPIOC
#define LCD_TE_GPIO_PIN      GPIO_PIN_14
#define LCD_TE_GPIO_LINE     EXTI_LINE_14
#define LCD_TE_GPIO_IRQn     EXTI15_10_IRQn
extern EXTI_HandleTypeDef    hexti_lcd_te;
#define H_EXTI_14            hexti_lcd_te
#endif

/* Chip Reset macro definition */
#define LCD_RST_LOW()        WRITE_REG(LCD_RESET_GPIO_PORT->BRR, LCD_RESET_GPIO_PIN)
#define LCD_RST_HIGH()       WRITE_REG(LCD_RESET_GPIO_PORT->BSRR, LCD_RESET_GPIO_PIN)

/* LCD backlight macro definitions */
#define LCD_BCKL_ON()        WRITE_REG(LCD_BCKL_GPIO_PORT->BSRR, LCD_BCKL_GPIO_PIN)
#define LCD_BCKL_OFF()       WRITE_REG(LCD_BCKL_GPIO_PORT->BRR, LCD_BCKL_GPIO_PIN)

void LCD_FillRect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint16_t c);
void LCD_Init();
void LCD_SetBacklight(uint8_t state);
void LCD_ClearScreen();
void LCD_SendData(LCD_IO_Data_t *data, uint32_t length);

#endif /* LCD_H_ */

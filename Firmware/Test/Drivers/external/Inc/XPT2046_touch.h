/*
 * XPT2046_touch.h
 *
 *  Created on: 20 sep. 2019 ð.
 *      Author: Andriy Honcharenko
 */

#ifndef XPT2046_TOUCH_H_
#define XPT2046_TOUCH_H_

#include "stm32g4xx_hal.h"
#include <stdbool.h>


/*** Redefine if necessary ***/

// Warning! Use SPI bus with < 2.5 Mbit speed, better ~650 Kbit to be save.
#define XPT2046_SPI_PORT hspi1
extern SPI_HandleTypeDef XPT2046_SPI_PORT;

#define XPT2046_IRQ_GPIO_Port GPIOD
#define XPT2046_IRQ_Pin       GPIO_PIN_6
#define XPT2046_CS_GPIO_Port  GPIOE
#define XPT2046_CS_Pin        GPIO_PIN_1

#define XPT2046_average	64

// change depending on screen orientation
/* LCD Orientation */
//#define XPT2046_ORIENTATION_PORTRAIT
//#define XPT2046_ORIENTATION_LANDSCAPE
//#define XPT2046_ORIENTATION_PORTRAIT_ROT180
#define XPT2046_ORIENTATION_LANDSCAPE_ROT180

#define XPT2046_SCALE_X 320
#define XPT2046_SCALE_Y 240

// to calibrate uncomment UART_Printf line in ili9341_touch.c
#define XPT2046_MIN_RAW_X 1756
#define XPT2046_MAX_RAW_X 28899
#define XPT2046_MIN_RAW_Y 3327
#define XPT2046_MAX_RAW_Y 30198

// call before initializing any SPI devices
bool XPT2046_TouchPressed();
bool XPT2046_TouchGetCoordinates(uint16_t* x, uint16_t* y, uint8_t raw);

#endif /* XPT2046_TOUCH_H_ */

/*
 * lcd_ugui.h
 *
 *  Created on: Dec 29, 2022
 *      Author: marko
 */

#ifndef EXTERNAL_INC_LCD_UGUI_H_
#define EXTERNAL_INC_LCD_UGUI_H_

#include "lcd.h"
#include "lcd_ili9341.h"
#include "ugui.h"

void UserPixelSetFunction(UG_S16 x, UG_S16 y, UG_COLOR c);
UG_RESULT _HW_FillFrame_(UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2, UG_COLOR c);
UG_S16 LCD_UG_init(void);
#endif /* EXTERNAL_INC_LCD_UGUI_H_ */

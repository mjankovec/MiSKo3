/*
 * lcd_ugui.c
 *
 *  Created on: Dec 29, 2022
 *      Author: marko
 */


#include "lcd_ugui.h"

void UserPixelSetFunction(UG_S16 x, UG_S16 y, UG_COLOR c)
{
	ILI9341_SetDisplayWindow(x, y, 1, 1);
	ILI9341_SendData((LCD_IO_Data_t *)&c, 1);
}

UG_RESULT _HW_FillFrame_(UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2, UG_COLOR c)
{
	LCD_FillRect(x1, y1, x2-x1, y2-y1, c);
	return UG_RESULT_OK;
}


UG_GUI gui;

UG_S16 LCD_UG_init(void)
{
	UG_Init(&gui, UserPixelSetFunction, ILI9341_GetParam(LCD_WIDTH), ILI9341_GetParam(LCD_HEIGHT));
	UG_DriverRegister(DRIVER_FILL_FRAME, (void *)_HW_FillFrame_);
	UG_DriverEnable(DRIVER_FILL_FRAME);

	UG_FontSelect(&FONT_8X12);
	UG_SetForecolor(C_WHITE);
	UG_SetBackcolor(C_BLACK);
	return 0;
}

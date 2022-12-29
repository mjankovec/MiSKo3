#include "lcd_demo.h"
#include <stdlib.h>

float DrawColors(uint32_t x, uint32_t y, float intensity)
{
	uint16_t Data;
	uint32_t time1, time2;
	float bitrate;
	HSV_t HSV;
	RGB_t RGB;
	uint16_t *array;

	array = (uint16_t *) malloc(180*100);

	HSV.V=intensity;

	for (int j=0; j<100;j++) //vrstice
	{
		HSV.S=j;
		for (int i=0; i<180;i++) //stolpci
		{
			HSV.H=360-2*i;
			HSVtoRGB(&HSV, &RGB);
			array[i+j*180]=RGB888_to_RGB565(&RGB);
	  }
	}


	time1 = HAL_GetTick();
	for (int i=0; i<100; i++)
	{
		LCD_FillRect(x, y+i, 180, 2, 0);
		ILI9341_SetDisplayWindow(x, y, 180, 100);
		LCD_SendData(array, 100*180);
	}
	time2=HAL_GetTick()-time1;

	bitrate = 100.0*1000*102*180*2/time2;
	free(array);
	return bitrate;
}

/*!
 * @brief Prikaži in animiraj logotip `MIŠKO 3'
 *
 * Funkcija izriše logotip, vklopi LED diode, počaka 3 sekunde in izstopi.
 * @note Potrebujeta se datoteki `lcd_grafika.{c,h}'
 */
void LCD_Intro_LogoSlide(uint32_t x,uint32_t y)
{
    ILI9341_SetOrientation(ILI9341_MISKO_ROTATE_270); // Zaradi smeri izrisovanja
    ILI9341_InvertDisplay(1);
    ILI9341_SetDisplayWindow(ILI9341_WIDTH-y, x, LOGO_X, LOGO_Y);

    for (uint32_t i = 0; i < LOGO_SIZE; i += 2) {
        ILI9341_SendData((LCD_IO_Data_t *)&img_logotip[i], 1);

        if (i % (LOGO_Y * 2) == 0)
            HAL_Delay(20);
    }
    ILI9341_InvertDisplay(0);
    ILI9341_SetOrientation(ILI9341_MISKO_ROTATE_0);
}

/*!
 * @brief Izris grafike z napisom `Ni programa...'
 *
 * Funkcija, ki nadomesti pomanjkanje programa (vsaj glavna ideja je taka). Deluje v neskončni
 * zanki in nikoli ne izstopi.
 * @note Potrebujeta se datoteki `lcd_grafika.{c,h}'
 * @note Grafika zasede dobršen del pomnilnika!
 */
void LCD_Intro_NoProgramHalt()
{
    uint16_t stevec = 0;

    UG_FillFrame(0, 0, 320, 240, C_WHITE);
    UG_FontSelect(&FONT_12X16);
    UG_SetBackcolor(C_WHITE);

    ILI9341_SetDisplayWindow(2, 20, AMIGA_X, AMIGA_Y);
    LCD_SendData((LCD_IO_Data_t *)&img_ni_programa, AMIGA_SIZE);

    for (uint8_t casovnik = 0; casovnik < 15; casovnik++) {
        UG_SetForecolor(C_DIM_GRAY);
        UG_PutString(120, 180, "Ni programa...");
        HAL_Delay(1000);
        UG_SetForecolor(C_MAROON);
        UG_PutString(120, 180, "Ni programa...");
        HAL_Delay(1000);
    }

    for (;;) {
        UG_SetForecolor(C_DIM_GRAY);
        UG_PutString(120, 180, "Ni programa...");
        HAL_Delay(100); ILI9341_ScrollScreen(stevec++, SCROLL_LEFT);
        HAL_Delay(100); ILI9341_ScrollScreen(stevec++, SCROLL_LEFT);
        HAL_Delay(100); ILI9341_ScrollScreen(stevec++, SCROLL_LEFT);
        HAL_Delay(100); ILI9341_ScrollScreen(stevec++, SCROLL_LEFT);
        HAL_Delay(100); ILI9341_ScrollScreen(stevec++, SCROLL_LEFT);
        HAL_Delay(100); ILI9341_ScrollScreen(stevec++, SCROLL_LEFT);
        HAL_Delay(100); ILI9341_ScrollScreen(stevec++, SCROLL_LEFT);
        HAL_Delay(100); ILI9341_ScrollScreen(stevec++, SCROLL_LEFT);
        HAL_Delay(100); ILI9341_ScrollScreen(stevec++, SCROLL_LEFT);
        HAL_Delay(100); ILI9341_ScrollScreen(stevec++, SCROLL_LEFT);
        UG_SetForecolor(C_MAROON);
        UG_PutString(120, 180, "Ni programa...");
        HAL_Delay(100); ILI9341_ScrollScreen(stevec++, SCROLL_LEFT);
        HAL_Delay(100); ILI9341_ScrollScreen(stevec++, SCROLL_LEFT);
        HAL_Delay(100); ILI9341_ScrollScreen(stevec++, SCROLL_LEFT);
        HAL_Delay(100); ILI9341_ScrollScreen(stevec++, SCROLL_LEFT);
        HAL_Delay(100); ILI9341_ScrollScreen(stevec++, SCROLL_LEFT);
        HAL_Delay(100); ILI9341_ScrollScreen(stevec++, SCROLL_LEFT);
        HAL_Delay(100); ILI9341_ScrollScreen(stevec++, SCROLL_LEFT);
        HAL_Delay(100); ILI9341_ScrollScreen(stevec++, SCROLL_LEFT);
        HAL_Delay(100); ILI9341_ScrollScreen(stevec++, SCROLL_LEFT);
        HAL_Delay(100); ILI9341_ScrollScreen(stevec++, SCROLL_LEFT);
        if(stevec == 320)
            stevec = 0;
    }
}

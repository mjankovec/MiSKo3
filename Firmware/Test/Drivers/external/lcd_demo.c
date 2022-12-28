#include "lcd_demo.h"

/*!
 * @brief Prikaži in animiraj logotip `MIŠKO 3'
 *
 * Funkcija izriše logotip, vklopi LED diode, počaka 3 sekunde in izstopi.
 * @note Potrebujeta se datoteki `lcd_grafika.{c,h}'
 */
void LCD_Intro_LogoSlide()
{
    ILI9341_SetOrientation(ILI9341_MISKO_ROTATE_270); // Zaradi smeri izrisovanja
    ILI9341_InvertDisplay(1);
    ILI9341_SetDisplayWindow(80, 80, LOGO_X, LOGO_Y);

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

    ILI9341_SendData((LCD_IO_Data_t *)&img_ni_programa, AMIGA_SIZE);

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

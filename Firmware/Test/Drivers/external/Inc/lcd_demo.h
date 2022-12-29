#ifndef LCD_DEMO_H_
#define LCD_DEMO_H_

#include "lcd.h"
#include "lcd_grafika.h"
#include "ugui.h"
#include "ColorSpaces.h"

float DrawColors(uint32_t x, uint32_t y, float intensity);
void LCD_Intro_LogoSlide(uint32_t x,uint32_t y);
void LCD_Intro_NoProgramHalt();

#endif /* LCD_DEMO_H */

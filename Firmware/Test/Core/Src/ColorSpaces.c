#include "ColorSpaces.h"
#include <math.h>


void HSVtoRGB(HSV_t *HSV, RGB_t *RGB)
{

	float r, g, b;

	float h = HSV->H / 360;
	float s = HSV->S / 100;
	float v = HSV->V / 100;

	int i = floor(h * 6);
	float f = h * 6 - i;
	float p = v * (1 - s);
	float q = v * (1 - f * s);
	float t = v * (1 - (1 - f) * s);

	switch (i % 6) {
		case 0: r = v, g = t, b = p; break;
		case 1: r = q, g = v, b = p; break;
		case 2: r = p, g = v, b = t; break;
		case 3: r = p, g = q, b = v; break;
		case 4: r = t, g = p, b = v; break;
		case 5: r = v, g = p, b = q; break;
	}


	RGB->R = r * 255;
	RGB->G = g * 255;
	RGB->B = b * 255;
}

uint16_t RGB888_to_RGB565(RGB_t *RGB)
{
	uint16_t r,g,b,out;
	r = RGB->R&0x00F8;
	g = RGB->G&0x00FC;
	b = RGB->B&0x00F8;
	out = (r<<8) | (g<<3) | (b>>3);
	return out;
}


/*
 * ColorSpaces.h
 *
 *  Created on: 23. feb. 2022
 *      Author: marko
 */

#ifndef INC_COLORSPACES_H_
#define INC_COLORSPACES_H_

#include <sys/_stdint.h>

/*
H(Hue): 0-360 degrees
S(Saturation): 0-100 percent
V(Value): 0-100 percent

R(Red): 0-255
G(Green): 0-255
B(Blue): 0-255
 */

typedef struct
{
	uint16_t R;
	uint16_t G;
	uint16_t B;
} RGB_t;

typedef struct
{
	float H;
	float S;
	float V;
} HSV_t;

void HSVtoRGB(HSV_t *HSV, RGB_t *RGB);
uint16_t RGB888_to_RGB565(RGB_t *RGB);

#endif /* INC_COLORSPACES_H_ */

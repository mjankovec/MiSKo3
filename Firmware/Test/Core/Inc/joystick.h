/*
 * joystick.h
 *
 *  Created on: 23. feb. 2022
 *      Author: marko
 */

#ifndef INC_JOYSTICK_H_
#define INC_JOYSTICK_H_

#include <sys/_stdint.h>

typedef struct
{
	int x;
	int y;
} coord_t;

typedef struct
{
	coord_t raw_min;
	coord_t raw_max;
	coord_t out_max;
	float x_k,y_k;
	coord_t n;

} joystick_t;

void joystick_init(joystick_t *joystick);
void joystick_get(coord_t *raw, coord_t *out, joystick_t *joystick);

#endif /* INC_JOYSTICK_H_ */

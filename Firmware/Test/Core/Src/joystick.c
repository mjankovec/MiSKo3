/*
 * joystick.c
 *
 *  Created on: 23. feb. 2022
 *      Author: marko
 */
#include "joystick.h"

void joystick_init(joystick_t *joystick)
{
	joystick->raw_min.x = 780;
	joystick->raw_max.x = 3330;
	joystick->raw_min.y = 780;
	joystick->raw_max.y = 3330;
	joystick->out_max.x = 90;
	joystick->out_max.y = 90;


	joystick->x_k = (float) joystick->out_max.x / (joystick->raw_max.x - joystick->raw_min.x);
	joystick->y_k = (float) joystick->out_max.y / (joystick->raw_max.y - joystick->raw_min.y);
	joystick->n.x = (joystick->raw_max.x+joystick->raw_min.x)/2;
	joystick->n.y = (joystick->raw_max.y+joystick->raw_min.y)/2;

}

void joystick_get(coord_t *raw, coord_t *out, joystick_t *joystick)
{
	out->x = joystick->x_k*(raw->x-joystick->n.x);
	out->y = -joystick->y_k*(raw->y-joystick->n.y);
}



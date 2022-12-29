//! @file    lcd_grafika.h
//! @brief   Logotip `MIŠKO 3' in grafika za zaslon `Ni programa...'
//! @author  nbert, marec 2022
#ifndef IMG_NALOZI_H
#define IMG_NALOZI_H

#include <stdint.h>

/* Demo sličice */
#define LOGO_X    73
#define LOGO_Y    158
#define LOGO_SIZE (2 * LOGO_X * LOGO_Y)

#define AMIGA_X    200
#define AMIGA_Y    200
#define AMIGA_SIZE (AMIGA_X * AMIGA_Y)

extern uint8_t img_logotip[];
extern uint8_t img_ni_programa[];

#endif /* IMG_NALOZI_H */

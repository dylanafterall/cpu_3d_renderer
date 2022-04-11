/*
*   Dylan Campbell
*   dyl@mailbox.org
*   3D Graphics Renderer in C
*    
*   This program contains source code from Gustavo Pezzi's "3D Computer
*   Graphics Programming" course, found here: https://pikuma.com/courses
*/

//  ---------------------------------------------------------------------------
//  light.h
//  Header file for positioning light source
//  ---------------------------------------------------------------------------
#ifndef LIGHT_H
#define LIGHT_H

#include "vector.h"
#include <stdint.h>

typedef struct {
    vec3_t direction;
} light_t;

extern light_t light;
uint32_t light_apply_intensity(uint32_t original_color, float percentage_factor);

#endif
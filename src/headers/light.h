/*
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

// Exported types -------------------------------------------------------------
// ----------------------------------------------------------------------------
typedef struct {
  vec3_t direction;
} light_t;

// Constructors-Destructors ---------------------------------------------------
// ----------------------------------------------------------------------------
void init_light(vec3_t direction);

// Access functions -----------------------------------------------------------
// ----------------------------------------------------------------------------
vec3_t get_light_direction(void);

// Other operations -----------------------------------------------------------
// ----------------------------------------------------------------------------
uint32_t light_apply_intensity(uint32_t original_color,
                               float percentage_factor);

#endif
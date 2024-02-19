/*
*   This program contains source code from Gustavo Pezzi's "3D Computer
*   Graphics Programming" course, found here: https://pikuma.com/courses
*/

//  ---------------------------------------------------------------------------
//  light.c
//  Implementation file for positioning light source
//  ---------------------------------------------------------------------------
#include <stdint.h>
#include "light.h"

// Structs, Arrays, Variables -------------------------------------------------
// ----------------------------------------------------------------------------
static light_t light;

// Constructors-Destructors ---------------------------------------------------
// ----------------------------------------------------------------------------
void init_light(vec3_t direction) {
    light.direction = direction;
}

// Access functions -----------------------------------------------------------
// ----------------------------------------------------------------------------
vec3_t get_light_direction(void) {
    return light.direction;
}

// Other operations -----------------------------------------------------------
// ----------------------------------------------------------------------------
uint32_t light_apply_intensity(uint32_t original_color, float percentage_factor) {
    if (percentage_factor < 0) {
        percentage_factor = 0;
    }
    if (percentage_factor > 1) {
        percentage_factor = 1;
    }

    uint32_t a = (original_color & 0xFF000000);
    uint32_t r = (original_color & 0x00FF0000) * percentage_factor;
    uint32_t g = (original_color & 0x0000FF00) * percentage_factor;
    uint32_t b = (original_color & 0x000000FF) * percentage_factor;

    uint32_t new_color = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);

    return new_color;
}
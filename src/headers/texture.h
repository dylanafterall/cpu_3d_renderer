/*
*   Dylan Campbell
*   campbell.dyl@gmail.com
*   3D Graphics Renderer in C
*    
*   This program contains source code from Gustavo Pezzi's "3D Computer
*   Graphics Programming" course, found here: https://pikuma.com/courses
*/

//  ---------------------------------------------------------------------------
//  texture.h
//  Header file for texture objects
//  ---------------------------------------------------------------------------
#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdint.h>
#include "upng.h"

typedef struct {
    float u;
    float v;
} tex2_t;

extern int texture_width;
extern int texture_height;

extern upng_t* png_texture;
extern uint32_t* mesh_texture;

void load_png_texture_data(char* filename);

#endif
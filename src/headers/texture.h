/*
*   This program contains source code from Gustavo Pezzi's "3D Computer
*   Graphics Programming" course, found here: https://pikuma.com/courses
*/

//  ---------------------------------------------------------------------------
//  texture.h
//  Header file for texture objects
//  ---------------------------------------------------------------------------
#ifndef TEXTURE_H
#define TEXTURE_H

// Exported types -------------------------------------------------------------
// ----------------------------------------------------------------------------
typedef struct {
    float u;
    float v;
} tex2_t;

// Other operations -----------------------------------------------------------
// ----------------------------------------------------------------------------
tex2_t tex2_clone(tex2_t* t);

#endif
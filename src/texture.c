/*
*   Dylan Campbell
*   campbell.dyl@gmail.com
*   3D Graphics Renderer in C
*    
*   This program contains source code from Gustavo Pezzi's "3D Computer
*   Graphics Programming" course, found here: https://pikuma.com/courses
*/

//  ---------------------------------------------------------------------------
//  texture.c
//  Implementation file for texture objects
//  ---------------------------------------------------------------------------
#include "texture.h"

///////////////////////////////////////////////////////////////////////////////
// Other operations -----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
tex2_t tex2_clone(tex2_t* t) {
    tex2_t result = {t->u, t->v};
    return result;
}
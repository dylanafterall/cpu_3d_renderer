/*
*   Dylan Campbell
*   campbell.dyl@gmail.com
*   3D Graphics Renderer in C
*    
*   This program contains source code from Gustavo Pezzi's "3D Computer
*   Graphics Programming" course, found here: https://pikuma.com/courses
*/

//  ---------------------------------------------------------------------------
//  matrix.h
//  Header file for matrix transformation functionality
//  ---------------------------------------------------------------------------
#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>
#include "vector.h"

///////////////////////////////////////////////////////////////////////////////
// Exported types -------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
typedef struct {
    float m[4][4];
} mat4_t;

///////////////////////////////////////////////////////////////////////////////
// Constructors-Destructors ---------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
mat4_t mat4_identity(void);
mat4_t mat4_make_scale(float sx, float xy, float sz);
mat4_t mat4_make_translation(float tx, float ty, float tz);
mat4_t mat4_make_rotation_z(float angle);
mat4_t mat4_make_rotation_y(float angle);
mat4_t mat4_make_rotation_x(float angle);
mat4_t mat4_make_perspective(float fov, float aspect, float znear, float zfar);
mat4_t mat4_look_at(vec3_t eye, vec3_t target, vec3_t up);

///////////////////////////////////////////////////////////////////////////////
// Manipulation procedures ----------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
vec4_t mat4_mul_vec4_project(mat4_t mat_proj, vec4_t v);

///////////////////////////////////////////////////////////////////////////////
// Other operations -----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
vec4_t mat4_mul_vec4(mat4_t m, vec4_t v);
mat4_t mat4_mul_mat4(mat4_t a, mat4_t b);

#endif
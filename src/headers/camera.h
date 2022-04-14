/*
*   Dylan Campbell
*   campbell.dyl@gmail.com
*   3D Graphics Renderer in C
*    
*   This program contains source code from Gustavo Pezzi's "3D Computer
*   Graphics Programming" course, found here: https://pikuma.com/courses
*/

//  ---------------------------------------------------------------------------
//  camera.h
//  Header file for camera object, matrix transformations.
//  ---------------------------------------------------------------------------
#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"

typedef struct {
    vec3_t position;
    vec3_t direction;
    vec3_t forward_velocity;
    float yaw;
} camera_t;

extern camera_t camera;

#endif
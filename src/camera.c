/*
*   Dylan Campbell
*   campbell.dyl@gmail.com
*   3D Graphics Renderer in C
*    
*   This program contains source code from Gustavo Pezzi's "3D Computer
*   Graphics Programming" course, found here: https://pikuma.com/courses
*/

//  ---------------------------------------------------------------------------
//  camera.c
//  Implementation file for camera object, matrix transformations.
//  ---------------------------------------------------------------------------
#include "camera.h"

camera_t camera = {
    .position = {0, 0, 0},
    .direction = {0, 0, 1}
};
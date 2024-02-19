/*
*   This program contains source code from Gustavo Pezzi's "3D Computer
*   Graphics Programming" course, found here: https://pikuma.com/courses
*/

//  ---------------------------------------------------------------------------
//  camera.h
//  Header file for camera object, matrix transformations.
//  ---------------------------------------------------------------------------
#ifndef CAMERA_H
#define CAMERA_H

#include "matrix.h"
#include "vector.h"

// Exported types -------------------------------------------------------------
// ----------------------------------------------------------------------------
typedef struct {
    vec3_t position;
    vec3_t direction;
    vec3_t forward_velocity;
    float yaw;
    float pitch;
} camera_t;

// Constructors-Destructors ---------------------------------------------------
// ----------------------------------------------------------------------------
void init_camera(vec3_t position, vec3_t direction);

// Access functions -----------------------------------------------------------
// ----------------------------------------------------------------------------
vec3_t get_camera_position(void);
vec3_t get_camera_direction(void);
vec3_t get_camera_forward_velocity(void);
float get_camera_yaw(void);
float get_camera_pitch(void);

// Manipulation procedures ----------------------------------------------------
// ----------------------------------------------------------------------------
void update_camera_position(vec3_t position);
void update_camera_direction(vec3_t direction);
void update_camera_forward_velocity(vec3_t forward_velocity);
void rotate_camera_yaw(float angle);
void rotate_camera_pitch(float angle);

// Other operations -----------------------------------------------------------
// ----------------------------------------------------------------------------
vec3_t get_camera_lookat_target(void);

#endif
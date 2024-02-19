/*
 *   This program contains source code from Gustavo Pezzi's "3D Computer
 *   Graphics Programming" course, found here: https://pikuma.com/courses
 */

//  ---------------------------------------------------------------------------
//  clipping.h
//  Header file for camera clipping operations.
//  ---------------------------------------------------------------------------
#ifndef CLIPPING_H
#define CLIPPING_H

#include "triangle.h"
#include "vector.h"
#include <math.h>
#define MAX_NUM_POLY_VERTICES 10
#define MAX_NUM_POLY_TRIANGLES 8

// Exported types -------------------------------------------------------------
// ----------------------------------------------------------------------------
enum {
  LEFT_FRUSTUM_PLANE,
  RIGHT_FRUSTUM_PLANE,
  TOP_FRUSTUM_PLANE,
  BOTTOM_FRUSTUM_PLANE,
  NEAR_FRUSTUM_PLANE,
  FAR_FRUSTUM_PLANE
};

typedef struct {
  vec3_t point;
  vec3_t normal;
} plane_t;

typedef struct {
  vec3_t vertices[MAX_NUM_POLY_VERTICES];
  tex2_t texcoords[MAX_NUM_POLY_VERTICES];
  int num_vertices;
} polygon_t;

// Constructors-Destructors ---------------------------------------------------
// ----------------------------------------------------------------------------
void init_frustum_planes(float fovx, float fovy, float z_near, float z_far);

// Other operations -----------------------------------------------------------
// ----------------------------------------------------------------------------
polygon_t create_polygon_from_triangle(vec3_t v0, vec3_t v1, vec3_t v2,
                                       tex2_t t0, tex2_t t1, tex2_t t2);
void clip_polygon(polygon_t *polygon);
void triangles_from_polygon(polygon_t *polygon, triangle_t triangles[],
                            int *num_triangles);

#endif
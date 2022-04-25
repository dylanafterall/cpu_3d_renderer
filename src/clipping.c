/*
*   Dylan Campbell
*   campbell.dyl@gmail.com
*   3D Graphics Renderer in C
*    
*   This program contains source code from Gustavo Pezzi's "3D Computer
*   Graphics Programming" course, found here: https://pikuma.com/courses
*/

//  ---------------------------------------------------------------------------
//  clipping.c
//  Implementation file for camera clipping operations.
//  ---------------------------------------------------------------------------
#include <math.h>
#include "clipping.h"

#define NUM_PLANES 6
plane_t frustum_planes[NUM_PLANES];

///////////////////////////////////////////////////////////////////////////////
// Frustum planes are defined by a point and a normal vector
///////////////////////////////////////////////////////////////////////////////
// Near plane   :  P=(0, 0, znear), N=(0, 0,  1)
// Far plane    :  P=(0, 0, zfar),  N=(0, 0, -1)
// Top plane    :  P=(0, 0, 0),     N=(0, -cos(fov/2), sin(fov/2))
// Bottom plane :  P=(0, 0, 0),     N=(0, cos(fov/2), sin(fov/2))
// Left plane   :  P=(0, 0, 0),     N=(cos(fov/2), 0, sin(fov/2))
// Right plane  :  P=(0, 0, 0),     N=(-cos(fov/2), 0, sin(fov/2))
///////////////////////////////////////////////////////////////////////////////
//
//           /|\
//         /  | | 
//       /\   | |
//     /      | |
//  P*|-->  <-|*|   ----> +z-axis
//     \      | |
//       \/   | |
//         \  | | 
//           \|/
//
///////////////////////////////////////////////////////////////////////////////
void init_frustum_planes(float fov, float z_near, float z_far)
{
    float cos_half_fov = cos(fov / 2);
	float sin_half_fov = sin(fov / 2);

	frustum_planes[LEFT_FRUSTUM_PLANE].point = vec3_new(0, 0, 0);
	frustum_planes[LEFT_FRUSTUM_PLANE].normal.x = cos_half_fov;
	frustum_planes[LEFT_FRUSTUM_PLANE].normal.y = 0;
	frustum_planes[LEFT_FRUSTUM_PLANE].normal.z = sin_half_fov;

	frustum_planes[RIGHT_FRUSTUM_PLANE].point = vec3_new(0, 0, 0);
	frustum_planes[RIGHT_FRUSTUM_PLANE].normal.x = -cos_half_fov;
	frustum_planes[RIGHT_FRUSTUM_PLANE].normal.y = 0;
	frustum_planes[RIGHT_FRUSTUM_PLANE].normal.z = sin_half_fov;

	frustum_planes[TOP_FRUSTUM_PLANE].point = vec3_new(0, 0, 0);
	frustum_planes[TOP_FRUSTUM_PLANE].normal.x = 0;
	frustum_planes[TOP_FRUSTUM_PLANE].normal.y = -cos_half_fov;
	frustum_planes[TOP_FRUSTUM_PLANE].normal.z = sin_half_fov;

	frustum_planes[BOTTOM_FRUSTUM_PLANE].point = vec3_new(0, 0, 0);
	frustum_planes[BOTTOM_FRUSTUM_PLANE].normal.x = 0;
	frustum_planes[BOTTOM_FRUSTUM_PLANE].normal.y = cos_half_fov;
	frustum_planes[BOTTOM_FRUSTUM_PLANE].normal.z = sin_half_fov;

	frustum_planes[NEAR_FRUSTUM_PLANE].point = vec3_new(0, 0, z_near);
	frustum_planes[NEAR_FRUSTUM_PLANE].normal.x = 0;
	frustum_planes[NEAR_FRUSTUM_PLANE].normal.y = 0;
	frustum_planes[NEAR_FRUSTUM_PLANE].normal.z = 1;

	frustum_planes[FAR_FRUSTUM_PLANE].point = vec3_new(0, 0, z_far);
	frustum_planes[FAR_FRUSTUM_PLANE].normal.x = 0;
	frustum_planes[FAR_FRUSTUM_PLANE].normal.y = 0;
	frustum_planes[FAR_FRUSTUM_PLANE].normal.z = -1;
}

polygon_t create_polygon_from_triangle(vec3_t v0, vec3_t v1, vec3_t v2) {
	polygon_t polygon = {
		.vertices = {v0, v1, v2},
		.num_vertices = 3
	};
	return polygon;
}

void clip_polygon_against_plane(polygon_t* polygon, int plane) {
	vec3_t plane_point = frustum_planes[plane].point;
	vec3_t plane_normal = frustum_planes[plane].normal;

	// declare a static array of inside vertices that will be part of final polygon
	vec3_t inside_vertices[MAX_NUM_POLY_VERTICES];
	int num_inside_vertices = 0;

	// start the current vertex with first polygon vertex, and previous with last one
	vec3_t* current_vertex = &polygon->vertices[0];
	vec3_t* previous_vertex = &polygon->vertices[polygon->num_vertices - 1];

	// calculate dot product of current and previous vertex
	float current_dot = 0;
	float previous_dot = vec3_dot(vec3_sub(*previous_vertex, plane_point), plane_normal);

	// loop all polygon vertices while current is different than last one
	while (current_vertex != &polygon->vertices[polygon->num_vertices]) {
		current_dot = vec3_dot(vec3_sub(*current_vertex, plane_point), plane_normal);

		// if we changed from inside to outisde or vice-versa
		if (current_dot * previous_dot < 0) {
			// find the interpolation factor t
			float t = previous_dot / (previous_dot - current_dot);
			// calculate the intersection point I = Q1 + t(Q2 - Q1)	
			vec3_t intersection_point = vec3_clone(current_vertex); 				// I = Qc
			intersection_point = vec3_sub(intersection_point, *previous_vertex);	// I = Qc - Qp
			intersection_point = vec3_mul(intersection_point, t);					// I = t(Qc - Qp)
			intersection_point = vec3_add(intersection_point, *previous_vertex);	// I = Qp + t(Qc - Qp)

			// insert the intersection point to the list of "inside vertices"
			inside_vertices[num_inside_vertices] = vec3_clone(&intersection_point);
			num_inside_vertices++;
		}

		// current vertex is inside the plane
		if (current_dot > 0) {
			// insert current vertex to list of "inside vertices"
			inside_vertices[num_inside_vertices] = vec3_clone(current_vertex);
			num_inside_vertices++;
		}

		// move to the next vertex
		previous_dot = current_dot;
		previous_vertex = current_vertex;
		current_vertex++;
	}

	// copy the list of inside vertices into the destination polygon (out parameter)
	for (int i = 0; i < num_inside_vertices; i++) {
		polygon->vertices[i] = vec3_clone(&inside_vertices[i]);
	}
	polygon->num_vertices = num_inside_vertices;
}

void clip_polygon(polygon_t* polygon) {
	clip_polygon_against_plane(polygon, LEFT_FRUSTUM_PLANE);
	clip_polygon_against_plane(polygon, RIGHT_FRUSTUM_PLANE);
	clip_polygon_against_plane(polygon, TOP_FRUSTUM_PLANE);
	clip_polygon_against_plane(polygon, BOTTOM_FRUSTUM_PLANE);
	clip_polygon_against_plane(polygon, NEAR_FRUSTUM_PLANE);
	clip_polygon_against_plane(polygon, FAR_FRUSTUM_PLANE);
}
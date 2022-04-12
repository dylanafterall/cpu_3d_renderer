/*
*   Dylan Campbell
*   campbell.dyl@gmail.com
*   3D Graphics Renderer in C
*    
*   This program contains source code from Gustavo Pezzi's "3D Computer
*   Graphics Programming" course, found here: https://pikuma.com/courses
*/

//  ---------------------------------------------------------------------------
//  mesh.h
//  Header file for mesh object functionality
//  ---------------------------------------------------------------------------
#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include "triangle.h"
#define N_CUBE_VERTICES 8
#define N_CUBE_FACES (6 * 2)

extern vec3_t cube_vertices[N_CUBE_VERTICES];
extern face_t cube_faces[N_CUBE_FACES];

void load_cube_mesh_data(void);
void load_obj_file_data(char* filename);

///////////////////////////////////////////////////////////////////////////////
//  Define a struct for dynamic size meshes, with array of vertices and faces
///////////////////////////////////////////////////////////////////////////////
typedef struct {
    vec3_t* vertices;   // dynamic array of vertices
    face_t* faces;      // dynamic array of faces
    vec3_t rotation;    // rotation with x, y, and z values
    vec3_t scale;       // scale with x, y, and z values
    vec3_t translation; // translation with x, y, and z values
} mesh_t;

extern mesh_t mesh;

#endif
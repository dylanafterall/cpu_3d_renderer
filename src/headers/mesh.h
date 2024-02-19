/*
*   This program contains source code from Gustavo Pezzi's "3D Computer
*   Graphics Programming" course, found here: https://pikuma.com/courses
*/

//  ---------------------------------------------------------------------------
//  mesh.h
//  Header file for mesh object functionality
//  ---------------------------------------------------------------------------
#ifndef MESH_H
#define MESH_H

#include <stdio.h>
#include <string.h>
#include "array.h"
#include "triangle.h"
#include "upng.h"
#include "vector.h"

// Exported types -------------------------------------------------------------
// ----------------------------------------------------------------------------
typedef struct {
    vec3_t* vertices;   // dynamic array of vertices
    face_t* faces;      // dynamic array of faces
    upng_t* texture;    // PNG texture pointer
    vec3_t rotation;    // rotation with x, y, and z values
    vec3_t scale;       // scale with x, y, and z values
    vec3_t translation; // translation with x, y, and z values
} mesh_t;

// Constructors-Destructors ---------------------------------------------------
// ----------------------------------------------------------------------------
void free_meshes(void);

// Access functions -----------------------------------------------------------
// ----------------------------------------------------------------------------
int get_num_meshes(void);
mesh_t* get_mesh(int index);

// Manipulation procedures ----------------------------------------------------
// ----------------------------------------------------------------------------
void load_mesh(char* obj_filename, char* png_filename, vec3_t scale, vec3_t translation, vec3_t rotation);

// Other operations -----------------------------------------------------------
// ----------------------------------------------------------------------------
void load_mesh_obj_data(mesh_t* mesh, char* obj_filename);
void load_mesh_png_data(mesh_t* mesh, char* png_filename);

#endif
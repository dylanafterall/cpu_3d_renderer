/*
*   Dylan Campbell
*   campbell.dyl@gmail.com
*   3D Graphics Renderer in C
*    
*   This program contains source code from Gustavo Pezzi's "3D Computer
*   Graphics Programming" course, found here: https://pikuma.com/courses
*/

//  ---------------------------------------------------------------------------
//  display.h
//  Header file for SDL window and pixel drawing functions
//  ---------------------------------------------------------------------------
#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

#define FPS 60
#define FRAME_TARGET_TIME (1000/FPS)

///////////////////////////////////////////////////////////////////////////////
// Exported types -------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
enum cull_method {
    CULL_NONE,
    CULL_BACKFACE
};

enum render_method {
    RENDER_WIRE,
    RENDER_WIRE_VERTEX,
    RENDER_FILL_TRIANGLE,
    RENDER_FILL_TRIANGLE_WIRE,
    RENDER_TEXTURED,
    RENDER_TEXTURED_WIRE
};

///////////////////////////////////////////////////////////////////////////////
// Constructors-Destructors ---------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
bool initialize_window(void);
void destroy_window(void);

///////////////////////////////////////////////////////////////////////////////
// Access functions -----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
int get_window_width(void);
int get_window_height(void);
float get_zbuffer_at(int x, int y);
bool is_cull_backface(void);
bool should_render_filled_triangles(void);
bool should_render_textured_triangles(void);
bool should_render_wireframe(void);
bool should_render_vertices(void);

///////////////////////////////////////////////////////////////////////////////
// Manipulation procedures ----------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
void set_render_method(int method);
void set_cull_method(int method);
void update_zbuffer_at(int x, int y, float value);

///////////////////////////////////////////////////////////////////////////////
// Other operations -----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
void draw_grid_lines(void);
void draw_grid_dots(void);
void draw_pixel(int x, int y, uint32_t color);
void draw_line(int x0, int y0, int x1, int y1, uint32_t color);
void draw_rect(int x, int y, int width, int height, uint32_t color);
void render_color_buffer(void);
void clear_color_buffer(uint32_t color);
void clear_z_buffer();

#endif

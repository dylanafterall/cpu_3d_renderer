#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "display.h"
#include "vector.h"

// Declare an array of vectors/points to represent 3D cube
const int N_POINTS = 9 * 9 * 9;
vec3_t cube_points[N_POINTS];  // 9x9x9 cube
vec2_t projected_points[N_POINTS];

float fov_factor = 120;

bool is_running = false;

void setup(void)
{
    // color_buffer will be array of pixel values, 32 bits, 8 for each: opacity, R, G, B
    color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);
    // if the return of malloc is a NULL pointer (allocation unsuccessful)
    if(!color_buffer)
    {
        fprintf(stderr, "Error initializing color buffer.\n");
    }

    // create a SDL texture used to display the color buffer
    color_buffer_texture = SDL_CreateTexture(
        renderer,                       // renderer object responsible for texture
        SDL_PIXELFORMAT_ARGB8888,       // pixel format (SDL_PixelFormatEnum)
        SDL_TEXTUREACCESS_STREAMING,    // continuously stream texture, frame by frame
        window_width,                   // texture width             
        window_height                   // texture height
    );

    // code for 3D cube (demonstration of using vec3_t struct)
    int point_count = 0;
    // load an array of vectors from -1 to 1 (9x9x9 cube)
    for(float x = -1; x <= 1; x += 0.25)
    {
        for(float y = -1; y <= 1; y += 0.25)
        {
            for(float z = -1; z <= 1; z += 0.25)
            {
                vec3_t new_point = {.x = x, .y = y, .z = z};
                cube_points[point_count++] = new_point;
            }
        }
    }
}

void process_input(void)
{
    // create a new event
    SDL_Event event;
    // poll the new event
    SDL_PollEvent(&event);

    switch(event.type)
    {
        // sdl_quit is clicking x button on window, not esc key
        case SDL_QUIT:
            is_running = false;
            break;
        // case for esc key, using alias SDLK_ESCAPE
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE)
                is_running = false;
                break;
    }
}

// orthographic projection ignores z axis
vec2_t orthographicProject(vec3_t point)
{
    vec2_t projected_point = {
        .x = (fov_factor * point.x),
        .y = (fov_factor * point.y)
    };
    return projected_point;
}

void update(void)
{
    for(int i = 0; i < N_POINTS; i++)
    {
        vec3_t point = cube_points[i];

        // project the current point
        vec2_t projected_point = orthographicProject(point);

        // save the projected 2D vector in the array of projected points
        // an array of vec2_t
        projected_points[i] = projected_point;
    }
}

void render(void)
{   
    draw_grid_dots();

    // loop all projected points and render them
    for(int i = 0; i < N_POINTS; i++)
    {
        vec2_t projected_point = projected_points[i];
        draw_rect(
            projected_point.x + (window_width / 2),
            projected_point.y + (window_height / 2),
            4,
            4,
            0xFF00FF00
            );
    }

    render_color_buffer();
    clear_color_buffer(0xFF000000);

    SDL_RenderPresent(renderer);
}


int main(void)
{
    // bool variable, initialized as true, change to false to break game loop
    is_running = initialize_window();

    setup();

    // game loop
    while(is_running)
    {
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}
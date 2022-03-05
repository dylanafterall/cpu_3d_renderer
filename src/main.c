#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "display.h"

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

void update(void)
{

}

void render(void)
{   
    SDL_SetRenderDrawColor(
        renderer,       // pass renderer object
        255,            // red value
        0,              // green value
        0,              // blue value
        255             // opacity value
    );
    SDL_RenderClear(renderer);

    //draw_grid_lines();
    draw_grid_dots();
    draw_rect(300, 200, 300, 150, 0xFFFF00FF);

    render_color_buffer();
    clear_color_buffer(0xFFFF8000);

    SDL_RenderPresent(renderer);
}


int main(void)
{
    is_running = initialize_window();

    setup();

    while(is_running)
    {
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}
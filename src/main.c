#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

bool is_running = false;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool initialize_window(void)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        // fprintf = format print function. outputs to a stream, not stdout
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }
    // create a SDL Window
    window = SDL_CreateWindow(
        NULL,                       // window title
        SDL_WINDOWPOS_CENTERED,     // x coordinate window position
        SDL_WINDOWPOS_CENTERED,     // y coordinate window position
        800,                        // window width                       
        600,                        // window height
        SDL_WINDOW_BORDERLESS       // flags
    );
    // if window pointer is NULL (checking if pointer has content)
    if(!window)
    {
        fprintf(stderr, "Error creating SDL window.\n");
        return false;
    }

    // create a SDL renderer
    renderer = SDL_CreateRenderer(
        window,     // pointer to window that renderer belongs to
        -1,         // default display device (-1 gets default)
        0           // flags
    );
    if(!renderer)
    {
        fprintf(stderr, "Error creating SDL renderer.\n");
        return false;
    }

    return true;
}

void setup(void)
{

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

    return 0;
}
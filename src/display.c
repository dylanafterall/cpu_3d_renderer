#include "display.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;
int window_width = 800;
int window_height = 600;

bool initialize_window(void)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        // fprintf = format print function. outputs to a stream, not stdout
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }

    // use SDL to query what is the fullscreen max width and height
    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);
    window_width = display_mode.w;
    window_height = display_mode.h;

    // create a SDL Window
    window = SDL_CreateWindow(
        NULL,                       // window title
        SDL_WINDOWPOS_CENTERED,     // x coordinate window position
        SDL_WINDOWPOS_CENTERED,     // y coordinate window position
        window_width,               // window width                       
        window_height,              // window height
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

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    return true;
}

void draw_grid_lines(void)
{
    for(int y = 0; y < window_height; y++)
    {
        for(int x = 0; x < window_width; x++)
        {
            if(x % 10 == 0 || y % 10 == 0)
            {
                color_buffer[(window_width * y) + x] = 0xFF7F00FF;
            }
        }
    }
}

void draw_grid_dots(void)
{
    for(int y = 0; y < window_height; y += 10)
    {
        for(int x = 0; x < window_width; x += 10)
        {
            color_buffer[(window_width * y) + x] = 0xFFFFFFFF;
        }
    }
}

void draw_pixel(int x, int y, uint32_t color)
{
    if(x >= 0 && x < window_width && y >= 0 && y < window_height)
    {
        color_buffer[(window_width * y) + x] = color;    
    }
}

void draw_rect(int x, int y, int width, int height, uint32_t color)
{
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            int current_x = x + i;
            int current_y = y + j;
            draw_pixel(current_x, current_y, color);
        }
    }
} 

void clear_color_buffer(uint32_t color)
{
    for(int y = 0; y < window_height; y++)
    {  
        for(int x = 0; x < window_width; x++)
        {
            color_buffer[(window_width * y) + x] = color;
        }
    }
}

void render_color_buffer(void)
{
    // renders color buffer. finds buffer in memory, copys values to texture

    SDL_UpdateTexture(
        color_buffer_texture,       // texture I want to update   
        NULL,                       // subdivisions in rectangles (NULL = entire texture)
        color_buffer,               // source (what I want to copy to texture)
        (int)(window_width * sizeof(uint32_t))  // texture pitch (size of each row)
    );

    SDL_RenderCopy(
        renderer,                   // rendering context
        color_buffer_texture,       // source texture
        NULL,                       // source SDL_Rect structure, NULL = entire texture
        NULL                        // destination SDL_Rect structure, NULL = entire text
    );
}

void destroy_window(void)
{
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
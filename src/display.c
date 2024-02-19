/*
*   This program contains source code from Gustavo Pezzi's "3D Computer
*   Graphics Programming" course, found here: https://pikuma.com/courses
*/

//  ---------------------------------------------------------------------------
//  display.c
//  Implementation file for SDL window and pixel drawing functions
//  ---------------------------------------------------------------------------
#include "display.h"

// Structs, Arrays, Variables -------------------------------------------------
// ----------------------------------------------------------------------------
static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

static uint32_t* color_buffer = NULL;
static float* z_buffer = NULL;

static SDL_Texture* color_buffer_texture = NULL;
static int window_width = 800;
static int window_height = 600;

static int render_method = 0;
static int cull_method = 0;

// Constructors-Destructors ---------------------------------------------------
// ----------------------------------------------------------------------------
bool initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
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
    if (!window) {
        fprintf(stderr, "Error creating SDL window.\n");
        return false;
    }

    // create a SDL renderer
    renderer = SDL_CreateRenderer(
        window,     // pointer to window that renderer belongs to
        -1,         // default display device (-1 gets default)
        0           // flags
    );
    if (!renderer) {
        fprintf(stderr, "Error creating SDL renderer.\n");
        return false;
    }

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    // color_buffer will be array of pixel values, 32 bits, 8 for each: opacity, R, G, B
    color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);
    z_buffer = (float*)malloc(sizeof(float) * window_width * window_height); 

    // create a SDL texture used to display the color buffer
    color_buffer_texture = SDL_CreateTexture(
        renderer,                       // renderer object responsible for texture
        SDL_PIXELFORMAT_RGBA32,       // pixel format (SDL_PixelFormatEnum)
        SDL_TEXTUREACCESS_STREAMING,    // continuously stream texture, frame by frame
        window_width,                   // texture width             
        window_height                   // texture height
    );

    return true;
}

void destroy_window(void) {
    free(color_buffer);
    free(z_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// Access functions -----------------------------------------------------------
// ----------------------------------------------------------------------------
int get_window_width(void) {
    return window_width;
}

int get_window_height(void) {
    return window_height;
}

float get_zbuffer_at(int x, int y) {
    if (x < 0 || x >= window_width || y < 0 || y >= window_height) {
        return 1.0;
    }
    return z_buffer[(window_width * y) + x];
}

bool is_cull_backface(void) {
    return cull_method == CULL_BACKFACE;
}

bool should_render_filled_triangles(void) {
    return (
        render_method == RENDER_FILL_TRIANGLE || 
        render_method == RENDER_FILL_TRIANGLE_WIRE
    );
}

bool should_render_textured_triangles(void) {
    return (
        render_method == RENDER_TEXTURED || 
        render_method == RENDER_TEXTURED_WIRE
    );
}

bool should_render_wireframe(void) {
    return (
        render_method == RENDER_WIRE || 
        render_method == RENDER_WIRE_VERTEX || 
        render_method == RENDER_FILL_TRIANGLE_WIRE || 
        render_method == RENDER_TEXTURED_WIRE
    );
}

bool should_render_vertices(void) {
    return (
        render_method == RENDER_WIRE_VERTEX
    );
}

// Manipulation procedures ----------------------------------------------------
// ----------------------------------------------------------------------------
void set_render_method(int method) {
    render_method = method;
}

void set_cull_method(int method) {
    cull_method = method;
}

void update_zbuffer_at(int x, int y, float value) {
    if (x < 0 || x >= window_width || y < 0 || y >= window_height) {
        return;
    }
    z_buffer[(window_width * y) + x] = value;
}

// Other operations -----------------------------------------------------------
// ----------------------------------------------------------------------------
void draw_grid_lines(void) {
    for (int y = 0; y < window_height; y++) {
        for (int x = 0; x < window_width; x++) {
            if (x % 10 == 0 || y % 10 == 0) {
                color_buffer[(window_width * y) + x] = 0xFF7F00FF;
            }
        }
    }
}

void draw_grid_dots(void) {
    for (int y = 0; y < window_height; y += 10) {
        for (int x = 0; x < window_width; x += 10) {
            color_buffer[(window_width * y) + x] = 0x00000000;
        }
    }
}

void draw_pixel(int x, int y, uint32_t color) {
    if (x < 0 || x >= window_width || y < 0 || y >= window_height) {
        return;
    }
    color_buffer[(window_width * y) + x] = color;
}

void draw_rect(int x, int y, int width, int height, uint32_t color) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int current_x = x + i;
            int current_y = y + j;
            draw_pixel(current_x, current_y, color);
        }
    }
}

void draw_line(int x0, int y0, int x1, int y1, uint32_t color) {
    // DDA - Digital Differential Analyzer (line drawing algorithm)
    int delta_x = (x1 - x0);
    int delta_y = (y1 - y0);

    int longest_side_length = (abs(delta_x) >= abs(delta_y)) ? abs(delta_x) : abs(delta_y);

    float x_inc = delta_x / (float)longest_side_length;
    float y_inc = delta_y / (float)longest_side_length;

    float current_x = x0;
    float current_y = y0;

    for (int i = 0; i <= longest_side_length; i++) {
        draw_pixel(round(current_x), round(current_y), color);
        current_x += x_inc;
        current_y += y_inc;
    }
}

void render_color_buffer(void) {
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

    SDL_RenderPresent(renderer);
}

void clear_color_buffer(uint32_t color) {
    for (int i = 0; i < window_width * window_height; i++) {  
        color_buffer[i] = color;
    }
}

void clear_z_buffer() {
    for (int i = 0; i < window_width * window_height; i++) {
       z_buffer[i] = 1.0;
    }
}
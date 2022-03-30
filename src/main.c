#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "array.h"
#include "display.h"
#include "vector.h"
#include "mesh.h"
#include "matrix.h"
#include "light.h"

///////////////////////////////////////////////////////////////////////////////
//  Array of triangles to render frame by frame
///////////////////////////////////////////////////////////////////////////////
triangle_t* triangles_to_render = NULL;

///////////////////////////////////////////////////////////////////////////////
//  Global variables for execution status and game loop
///////////////////////////////////////////////////////////////////////////////
bool is_running = false;
int previous_frame_time = 0;

vec3_t camera_position = {.x = 0, .y = 0, .z = 0};
mat4_t proj_matrix;

///////////////////////////////////////////////////////////////////////////////
//  Setup function to initialize variables and game objects
///////////////////////////////////////////////////////////////////////////////
void setup(void)
{
    // initialize render mode and triangle culling methods
    render_method = RENDER_WIRE;
    cull_method = CULL_BACKFACE;

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

    // initialize the perspective projection matrix
    float fov = M_PI / 3.0;         // 60 degrees
    float aspect = (float)window_height / (float)window_width;
    float znear = 0.1;
    float zfar = 100.0;
    proj_matrix = mat4_make_perspective(fov, aspect, znear, zfar);

    //load_cube_mesh_data();
    load_obj_file_data("./assets/f22.obj");
}

///////////////////////////////////////////////////////////////////////////////
//  Poll system events and handle keyboard input
///////////////////////////////////////////////////////////////////////////////
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
            if (event.key.keysym.sym == SDLK_1)
                render_method = RENDER_WIRE_VERTEX;
            if (event.key.keysym.sym == SDLK_2)
                render_method = RENDER_WIRE;
            if (event.key.keysym.sym == SDLK_3)
                render_method = RENDER_FILL_TRIANGLE;
            if (event.key.keysym.sym == SDLK_4)
                render_method = RENDER_FILL_TRIANGLE_WIRE;
            if (event.key.keysym.sym == SDLK_c)
                cull_method = CULL_BACKFACE;
            if (event.key.keysym.sym == SDLK_d)
                cull_method = CULL_NONE;
            break;
    }
}

/*
////////////////////////////////////////////////////////////////////////////////
//  Function that receives a 3D vector and returns a projected 2D point
////////////////////////////////////////////////////////////////////////////////
vec2_t orthographicProject(vec3_t point)
{
    vec2_t projected_point = {
        .x = (fov_factor * point.x),
        .y = (fov_factor * point.y)
    };
    return projected_point;
}

////////////////////////////////////////////////////////////////////////////////
//  Function that receives a 3D vector and returns a projected 2D point
////////////////////////////////////////////////////////////////////////////////
vec2_t perspectiveProject(vec3_t point)
{
    vec2_t projected_point = {
        .x = (fov_factor * point.x) / point.z,
        .y = (fov_factor * point.y) / point.z
    };
    return projected_point;
}
*/

///////////////////////////////////////////////////////////////////////////////
//  Update function frame by frame with a fixed time step
///////////////////////////////////////////////////////////////////////////////
void update(void)
{
    // to achieve a constant delta-time
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);
    if(time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
    {
        SDL_Delay(time_to_wait);
    }
    previous_frame_time = SDL_GetTicks();

    triangles_to_render = NULL;

    // change the mesh scale/rotation values per animation frame
    mesh.rotation.x += 0.01;
    //mesh.rotation.y += 0.01;
    //mesh.rotation.z += 0.01;
    //mesh.scale.x += 0.002;
    //mesh.scale.y += 0.001;
    //mesh.translation.x += 0.01;
    mesh.translation.z = 5.0;

    // create a scale matrix that will be used to multiply mesh vertices
    mat4_t scale_matrix = mat4_make_scale(mesh.scale.x, mesh.scale.y, mesh.scale.z);
    mat4_t rotation_matrix_x = mat4_make_rotation_x(mesh.rotation.x);
    mat4_t rotation_matrix_y = mat4_make_rotation_y(mesh.rotation.y);
    mat4_t rotation_matrix_z = mat4_make_rotation_z(mesh.rotation.z);
    mat4_t translation_matrix = mat4_make_translation(mesh.translation.x, mesh.translation.y, mesh.translation.z);

    // loop all triangle faces of our cube mesh
    int num_faces = array_length(mesh.faces);
    for(int i = 0; i < num_faces; i++)
    {
        face_t mesh_face = mesh.faces[i];

        vec3_t face_vertices[3];
        face_vertices[0] = mesh.vertices[mesh_face.a - 1];
        face_vertices[1] = mesh.vertices[mesh_face.b - 1];
        face_vertices[2] = mesh.vertices[mesh_face.c - 1];

        vec4_t transformed_vertices[4];

        // loop all 3 vertices of this current face and apply TRANSFORMATIONS
        for(int j = 0; j < 3; j++)
        {
            vec4_t transformed_vertex = vec4_from_vec3(face_vertices[j]);

            // create a world matrix combining scale, rotation, and translation vertices
            mat4_t world_matrix = mat4_identity();
            world_matrix = mat4_mul_mat4(scale_matrix, world_matrix);
            world_matrix = mat4_mul_mat4(rotation_matrix_x, world_matrix);
            world_matrix = mat4_mul_mat4(rotation_matrix_y, world_matrix);
            world_matrix = mat4_mul_mat4(rotation_matrix_z, world_matrix);
            world_matrix = mat4_mul_mat4(translation_matrix, world_matrix);
            
            transformed_vertex = mat4_mul_vec4(world_matrix, transformed_vertex);

            // save transformed vertex in the array of transformed vertices
            transformed_vertices[j] = transformed_vertex;
        }

        // perform BACKFACE CULLING
        vec3_t vector_a = vec3_from_vec4(transformed_vertices[0]); /*     A     */
        vec3_t vector_b = vec3_from_vec4(transformed_vertices[1]); /*    / \    */
        vec3_t vector_c = vec3_from_vec4(transformed_vertices[2]); /*   C---B   */
        
        vec3_t vector_ab = vec3_sub(vector_b, vector_a);
        vec3_t vector_ac = vec3_sub(vector_c, vector_a);
        vec3_normalize(&vector_ab);
        vec3_normalize(&vector_ac);

        // compute the face normal using the cross product to find perpendicular
        vec3_t normal = vec3_cross(vector_ab, vector_ac);
        // normalize the face normal vector
        vec3_normalize(&normal);

        // find the camera vector, between a point in the triangle and camera origin
        vec3_t camera_ray = vec3_sub(camera_position, vector_a);

        // calculate how aligned the camera ray is with face normal (use dot product)
        float dot_normal_camera = vec3_dot(normal, camera_ray);

        if(cull_method == CULL_BACKFACE)
        {
            // bypass the triangles that are facing away from camera (do not project)
            if(dot_normal_camera < 0)
            {
                continue;
            }
        }

        vec4_t projected_points[3];
        // loop all 3 vertices to perform PROJECTION
        for(int j = 0; j < 3; j++)
        {
            // project the current vertex
            projected_points[j] = mat4_mul_vec4_project(proj_matrix, transformed_vertices[j]); 

            // scale into the view
            projected_points[j].x *= (window_width / 2.0);
            projected_points[j].y *= (window_height / 2.0);
            
            // invert y values to account for flipped screen y coordinates
            projected_points[j].y *= -1;

            // translate the projected points to the middle of screen
            projected_points[j].x += (window_width / 2.0);
            projected_points[j].y += (window_height / 2.0);
        }

        // calculate the average depth for each face based on vertices after transformation
        float avg_depth = (transformed_vertices[0].z + transformed_vertices[1].z + transformed_vertices[2].z) / 3.0;

        // calculate the shade intensity based on how aligned is face normal and light direction
        float light_intensity_factor = -vec3_dot(normal, light.direction);

        // calculate the triangle color based on the light angle
        uint32_t triangle_color = light_apply_intensity(mesh_face.color, light_intensity_factor);

        triangle_t projected_triangle = {
            .points = {
                {projected_points[0].x, projected_points[0].y},
                {projected_points[1].x, projected_points[1].y},
                {projected_points[2].x, projected_points[2].y}
            },
            .color = triangle_color,
            .avg_depth = avg_depth 
        };

        // save the projected triangle in the array of triangles to render
        array_push(triangles_to_render, projected_triangle);
    }

    // sort triangles to render by their average depth- using Bubble Sort
    int num_triangles = array_length(triangles_to_render);
    for (int i = 0; i < num_triangles; i++) {
        for (int j = i; j < num_triangles; j++) {
            if (triangles_to_render[i].avg_depth < triangles_to_render[j].avg_depth) {
                // Swap the triangles positions in the array
                triangle_t temp = triangles_to_render[i];
                triangles_to_render[i] = triangles_to_render[j];
                triangles_to_render[j] = temp;
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
//  Render function to draw objects on the display
///////////////////////////////////////////////////////////////////////////////
void render(void)
{   
    SDL_RenderClear(renderer);

    draw_grid_dots();
 
    int num_triangles = array_length(triangles_to_render);
    for(int i = 0; i < num_triangles; i++)
    {
        triangle_t triangle = triangles_to_render[i];

        // Draw filled triangle
        if (render_method == RENDER_FILL_TRIANGLE || render_method == RENDER_FILL_TRIANGLE_WIRE) 
        {
            draw_filled_triangle(
                triangle.points[0].x, triangle.points[0].y, // vertex A
                triangle.points[1].x, triangle.points[1].y, // vertex B
                triangle.points[2].x, triangle.points[2].y, // vertex C
                triangle.color
            );
        }

        // Draw triangle wireframe
        if (render_method == RENDER_WIRE || render_method == RENDER_WIRE_VERTEX || render_method == RENDER_FILL_TRIANGLE_WIRE) 
        {
            draw_triangle(
                triangle.points[0].x, triangle.points[0].y, // vertex A
                triangle.points[1].x, triangle.points[1].y, // vertex B
                triangle.points[2].x, triangle.points[2].y, // vertex C
                0xFFFF0000
            );
        }

        // Draw triangle vertex points
        if (render_method == RENDER_WIRE_VERTEX) 
        {
            draw_rect(triangle.points[0].x - 3, triangle.points[0].y - 3, 6, 6, 0xFF00FF00); // vertex A
            draw_rect(triangle.points[1].x - 3, triangle.points[1].y - 3, 6, 6, 0xFF00FF00); // vertex B
            draw_rect(triangle.points[2].x - 3, triangle.points[2].y - 3, 6, 6, 0xFF00FF00); // vertex C
        }
    }

    // clear the array of triangles to render every frame loop
    array_free(triangles_to_render);

    render_color_buffer();

    clear_color_buffer(0xFF000000);

    SDL_RenderPresent(renderer);
}

///////////////////////////////////////////////////////////////////////////////
//  Free the memory that was dynamically allocated by the program
///////////////////////////////////////////////////////////////////////////////
void free_resources(void) 
{
    free(color_buffer);
    array_free(mesh.faces);
    array_free(mesh.vertices);
}


///////////////////////////////////////////////////////////////////////////////
//  Main function
///////////////////////////////////////////////////////////////////////////////
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
    free_resources();

    return 0;
}
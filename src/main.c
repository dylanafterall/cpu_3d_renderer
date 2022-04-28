/*
*   Dylan Campbell
*   campbell.dyl@gmail.com
*   3D Graphics Renderer in C
*    
*   This program contains source code from Gustavo Pezzi's "3D Computer
*   Graphics Programming" course, found here: https://pikuma.com/courses
*/

//  ---------------------------------------------------------------------------
//  main.c
//  Main program, controls game loop
//  ---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "array.h"
#include "camera.h"
#include "clipping.h"
#include "display.h"
#include "light.h"
#include "matrix.h"
#include "mesh.h"
#include "texture.h"
#include "triangle.h"
#include "upng.h"
#include "vector.h"

///////////////////////////////////////////////////////////////////////////////
//  Array of triangles to render frame by frame
///////////////////////////////////////////////////////////////////////////////
#define MAX_TRIANGLES_PER_MESH 10000
triangle_t triangles_to_render[MAX_TRIANGLES_PER_MESH];
int num_triangles_to_render = 0;

///////////////////////////////////////////////////////////////////////////////
//  Global variables for execution status and game loop
///////////////////////////////////////////////////////////////////////////////
bool is_running = false;
int previous_frame_time = 0;
float delta_time = 0;

mat4_t world_matrix;
mat4_t proj_matrix;
mat4_t view_matrix;

///////////////////////////////////////////////////////////////////////////////
//  Setup function to initialize variables and game objects
///////////////////////////////////////////////////////////////////////////////
void setup(void)
{
    // initialize render mode and triangle culling methods
    set_render_method(RENDER_WIRE);
    set_cull_method(CULL_BACKFACE);

    // initialize the scene light direction
    init_light(vec3_new(0, 0, 1));

    // initialize the perspective projection matrix
    float aspecty = (float)get_window_height() / (float)get_window_width();
    float aspectx = (float)get_window_width() / (float)get_window_height();
    float fovy = 3.141592 / 3.0;        // pi/3 = 60 degrees
    float fovx = atan(tan(fovy / 2) * aspectx) * 2.0;
    float znear = 0.1;
    float zfar = 100.0;
    proj_matrix = mat4_make_perspective(fovy, aspecty, znear, zfar);

    // initialize frustum planes with a point and a normal
    init_frustum_planes(fovx, fovy, znear, zfar);

    // add desired meshes to mesh array
    load_mesh("./assets/f22.obj", "./assets/f22.png", vec3_new(1, 1, 1), vec3_new(-3, 0, +8), vec3_new(0, 0, 0));
    load_mesh("./assets/cube.obj", "./assets/cube.png", vec3_new(1, 1, 1), vec3_new(+3, 0, +8), vec3_new(0, 0, 0));
}

///////////////////////////////////////////////////////////////////////////////
//  Poll system events and handle keyboard input
///////////////////////////////////////////////////////////////////////////////
void process_input(void)
{
    // create a new event
    SDL_Event event;
    // poll the new event
    while(SDL_PollEvent(&event)) {
        switch(event.type)
        {
            // sdl_quit is clicking x button on window, not esc key
            case SDL_QUIT:
                is_running = false;
                break;
            // case for esc key, using alias SDLK_ESCAPE
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE) {
                    is_running = false;
                    break;
                }
                if (event.key.keysym.sym == SDLK_1) {
                    set_render_method(RENDER_WIRE_VERTEX);
                    break;
                }
                if (event.key.keysym.sym == SDLK_2) {
                    set_render_method(RENDER_WIRE);
                    break;
                }
                if (event.key.keysym.sym == SDLK_3) {
                    set_render_method(RENDER_FILL_TRIANGLE);
                    break;
                }
                if (event.key.keysym.sym == SDLK_4) {
                    set_render_method(RENDER_FILL_TRIANGLE_WIRE);
                    break;
                }
                if (event.key.keysym.sym == SDLK_5) {
                    set_render_method(RENDER_TEXTURED);
                    break;
                }
                if (event.key.keysym.sym == SDLK_6) {
                    set_render_method(RENDER_TEXTURED_WIRE);
                    break;
                }

                if (event.key.keysym.sym == SDLK_c) {
                    set_cull_method(CULL_BACKFACE);
                    break;
                }
                if (event.key.keysym.sym == SDLK_x) {
                    set_cull_method(CULL_NONE);
                    break;
                }
            
                if (event.key.keysym.sym == SDLK_w) {
                    rotate_camera_pitch(+3.0 * delta_time);
                    break;
                }
                if (event.key.keysym.sym == SDLK_s) {
                    rotate_camera_pitch(-3.0 * delta_time);
                    break;
                }
                if (event.key.keysym.sym == SDLK_a) {
                    rotate_camera_yaw(+1.0 * delta_time);
                    break;
                }
                if (event.key.keysym.sym == SDLK_d) {
                    rotate_camera_yaw(-1.0 * delta_time);
                    break;
                }
                if (event.key.keysym.sym == SDLK_UP) {
                    update_camera_forward_velocity(vec3_mul(get_camera_direction(), 5.0 * delta_time));
                    update_camera_position(vec3_add(get_camera_position(), get_camera_forward_velocity()));
                    break;
                }
                if (event.key.keysym.sym == SDLK_DOWN) {
                    update_camera_forward_velocity(vec3_mul(get_camera_direction(), 5.0 * delta_time));
                    update_camera_position(vec3_sub(get_camera_position(), get_camera_forward_velocity()));
                    break;
                }
                break;
        }
    }
}

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

    // get a delta time factor converted to seconds to update game objects
    delta_time = (SDL_GetTicks() - previous_frame_time) / 1000.0;

    previous_frame_time = SDL_GetTicks();

    // initialize the counter of triangles to render for current frame
    num_triangles_to_render = 0;

    // loop all the meshes of our scene
    for (int mesh_index = 0; mesh_index < get_num_meshes(); mesh_index++) {
        mesh_t* mesh = get_mesh(mesh_index);

        // change the mesh scale/rotation/translation values per animation frame
        //mesh.rotation.x += 0.3 * delta_time;
        //mesh.rotation.y += 0.3 * delta_time;
        //mesh.rotation.z += 0.3 * delta_time;
        //mesh.translation.z = 4.0;

        // create scale, rotation, and translation matrices, to multiply mesh vertices
        mat4_t scale_matrix = mat4_make_scale(mesh->scale.x, mesh->scale.y, mesh->scale.z);
        mat4_t rotation_matrix_x = mat4_make_rotation_x(mesh->rotation.x);
        mat4_t rotation_matrix_y = mat4_make_rotation_y(mesh->rotation.y);
        mat4_t rotation_matrix_z = mat4_make_rotation_z(mesh->rotation.z);
        mat4_t translation_matrix = mat4_make_translation(mesh->translation.x, mesh->translation.y, mesh->translation.z);

        // update camera look at target to create view matrix
        vec3_t target = get_camera_lookat_target();
        vec3_t up_direction = vec3_new(0, 1, 0);
        view_matrix = mat4_look_at(get_camera_position(), target, up_direction);

        // loop all triangle faces of our cube mesh
        int num_faces = array_length(mesh->faces);
        for(int i = 0; i < num_faces; i++)
        {
            face_t mesh_face = mesh->faces[i];

            vec3_t face_vertices[3];
            face_vertices[0] = mesh->vertices[mesh_face.a];
            face_vertices[1] = mesh->vertices[mesh_face.b];
            face_vertices[2] = mesh->vertices[mesh_face.c];

            vec4_t transformed_vertices[4];

            // loop all 3 vertices of this current face and apply TRANSFORMATIONS
            for(int j = 0; j < 3; j++)
            {
                vec4_t transformed_vertex = vec4_from_vec3(face_vertices[j]);

                // create a world matrix combining scale, rotation, and translation vertices
                world_matrix = mat4_identity();

                // order matters: scale, then rotate, then translate
                world_matrix = mat4_mul_mat4(scale_matrix, world_matrix);
                world_matrix = mat4_mul_mat4(rotation_matrix_x, world_matrix);
                world_matrix = mat4_mul_mat4(rotation_matrix_y, world_matrix);
                world_matrix = mat4_mul_mat4(rotation_matrix_z, world_matrix);
                world_matrix = mat4_mul_mat4(translation_matrix, world_matrix);
            
                // multiply the world matrix by the original vector
                transformed_vertex = mat4_mul_vec4(world_matrix, transformed_vertex);

                // multiply the view matrix by the vector to transform scene to camera space
                transformed_vertex = mat4_mul_vec4(view_matrix, transformed_vertex);

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
            vec3_t origin = {0, 0, 0};
            vec3_t camera_ray = vec3_sub(origin, vector_a);

            // calculate how aligned the camera ray is with face normal (use dot product)
            float dot_normal_camera = vec3_dot(normal, camera_ray);

            // backface culling test to see if current face should be projected
            if(is_cull_backface())
            {
                // bypass the triangles that are facing away from camera (do not project)
                if(dot_normal_camera < 0)
                {
                    continue;
                }
            }

            // create a polygon from the original transformed triangle, to be clipped
            polygon_t polygon = create_polygon_from_triangle(
                vec3_from_vec4(transformed_vertices[0]),
                vec3_from_vec4(transformed_vertices[1]),
                vec3_from_vec4(transformed_vertices[2]),
                mesh_face.a_uv,
                mesh_face.b_uv,
                mesh_face.c_uv
            );

            // clip polygon and return new polygon with potential new vertices
            clip_polygon(&polygon);

            // after clipping, break the clipped polygon back into individual triangles
            triangle_t triangles_after_clipping[MAX_NUM_POLY_TRIANGLES];
            int num_triangles_after_clipping = 0;

            triangles_from_polygon(&polygon, triangles_after_clipping, &num_triangles_after_clipping);

            // loops all assembled triangles after clipping
            for (int t = 0; t < num_triangles_after_clipping; t++) {
                triangle_t triangle_after_clipping = triangles_after_clipping[t];

                vec4_t projected_points[3];
                // loop all 3 vertices to perform PROJECTION
                for(int j = 0; j < 3; j++)
                {
                    // project the current vertex
                    projected_points[j] = mat4_mul_vec4_project(proj_matrix, triangle_after_clipping.points[j]); 

                    // scale into the view
                    projected_points[j].x *= (get_window_width() / 2.0);
                    projected_points[j].y *= (get_window_height() / 2.0);
            
                    // invert y values to account for flipped screen y coordinates
                    projected_points[j].y *= -1;

                    // translate the projected points to the middle of screen
                    projected_points[j].x += (get_window_width() / 2.0);
                    projected_points[j].y += (get_window_height() / 2.0);
                }

                // calculate the shade intensity based on how aligned is face normal and light direction
                float light_intensity_factor = -vec3_dot(normal, get_light_direction());

                // calculate the triangle color based on the light angle
                uint32_t triangle_color = light_apply_intensity(mesh_face.color, light_intensity_factor);

                triangle_t triangle_to_render = {
                    .points = {
                        {projected_points[0].x, projected_points[0].y, projected_points[0].z, projected_points[0].w},
                        {projected_points[1].x, projected_points[1].y, projected_points[1].z, projected_points[1].w},
                        {projected_points[2].x, projected_points[2].y, projected_points[2].z, projected_points[2].w}
                    },
                    .texcoords = {
                        {triangle_after_clipping.texcoords[0].u, triangle_after_clipping.texcoords[0].v},
                        {triangle_after_clipping.texcoords[1].u, triangle_after_clipping.texcoords[1].v},
                        {triangle_after_clipping.texcoords[2].u, triangle_after_clipping.texcoords[2].v},
                    },
                    .color = triangle_color,
                    .texture = mesh->texture
                };

                // save the projected triangle in the array of triangles to render
                if(num_triangles_to_render < MAX_TRIANGLES_PER_MESH)
                {
                    triangles_to_render[num_triangles_to_render] = triangle_to_render;
                    num_triangles_to_render++;
                }
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
//  Render function to draw objects on the display
///////////////////////////////////////////////////////////////////////////////
void render(void)
{   
    // clear all the arrays to get ready for the next frame
    clear_color_buffer(0xFF000000);
    clear_z_buffer();

    draw_grid_dots();

    // loop all projected triangles and render them
    for(int i = 0; i < num_triangles_to_render; i++)
    {
        triangle_t triangle = triangles_to_render[i];

        // draw filled triangle
        if (should_render_filled_triangles()) 
        {
            draw_filled_triangle(
                triangle.points[0].x, triangle.points[0].y, triangle.points[0].z, triangle.points[0].w, // vertex A
                triangle.points[1].x, triangle.points[1].y, triangle.points[1].z, triangle.points[1].w, // vertex B
                triangle.points[2].x, triangle.points[2].y, triangle.points[2].z, triangle.points[2].w, // vertex C
                triangle.color
            );
        }

        // draw textured triangle
        if (should_render_textured_triangles())
        {
            draw_textured_triangle(
                triangle.points[0].x, triangle.points[0].y, triangle.points[0].z, triangle.points[0].w, triangle.texcoords[0].u, triangle.texcoords[0].v, // vertex A
                triangle.points[1].x, triangle.points[1].y, triangle.points[1].z, triangle.points[1].w, triangle.texcoords[1].u, triangle.texcoords[1].v, // vertex B
                triangle.points[2].x, triangle.points[2].y, triangle.points[2].z, triangle.points[2].w, triangle.texcoords[2].u, triangle.texcoords[2].v, // vertex C
                triangle.texture
            );
        }

        // Draw triangle wireframe
        if (should_render_wireframe()) 
        {
            draw_triangle(
                triangle.points[0].x, triangle.points[0].y, // vertex A
                triangle.points[1].x, triangle.points[1].y, // vertex B
                triangle.points[2].x, triangle.points[2].y, // vertex C
                0xFFFF0000
            );
        }

        // Draw triangle vertex points
        if (should_render_vertices()) 
        {
            draw_rect(triangle.points[0].x - 3, triangle.points[0].y - 3, 6, 6, 0xFF00FF00); // vertex A
            draw_rect(triangle.points[1].x - 3, triangle.points[1].y - 3, 6, 6, 0xFF00FF00); // vertex B
            draw_rect(triangle.points[2].x - 3, triangle.points[2].y - 3, 6, 6, 0xFF00FF00); // vertex C
        }
    }

    render_color_buffer();
}

///////////////////////////////////////////////////////////////////////////////
//  Free the memory that was dynamically allocated by the program
///////////////////////////////////////////////////////////////////////////////
void free_resources(void) 
{
    free_meshes();
    destroy_window();
}


///////////////////////////////////////////////////////////////////////////////
//  Main function
///////////////////////////////////////////////////////////////////////////////
int main(int argv, char** args)
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
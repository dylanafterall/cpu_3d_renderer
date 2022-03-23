#include "triangle.h"
#include "display.h"

void int_swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

///////////////////////////////////////////////////////////////////////////////
// Draw a filled a triangle with a flat bottom
///////////////////////////////////////////////////////////////////////////////
/*
//        (x0,y0)
//          / \
//         /   \
//        /     \
//       /       \
//      /         \
//  (x1,y1)------(x2,y2)
*/
///////////////////////////////////////////////////////////////////////////////
void fill_flat_bottom_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
    // find two slopes (two triangle legs)
    // slope is inverse, since I'm descending down the slope
    float inv_slope_1 = (float)(x1 - x0) / (y1 - y0);
    float inv_slope_2 = (float)(x2 - x0) / (y2 - y0);

    // start x_start and x_end from top vertex(x0,y0)
    float x_start = x0;
    float x_end = x0;

    // loop all scanlines from top to bottom
    for(int y = y0; y <= y2; y++)
    {
        draw_line(x_start, y, x_end, y, color);
        x_start += inv_slope_1;
        x_end += inv_slope_2;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Draw a filled a triangle with a flat top
///////////////////////////////////////////////////////////////////////////////
//
//  (x0,y0)------(x1,y1)
//      \         /
//       \       /
//        \     /
//         \   /
//          \ /
//        (x2,y2)
//
///////////////////////////////////////////////////////////////////////////////
void fill_flat_top_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
    // find two slopes (two triangle legs)
    float inv_slope_1 = (float)(x2 - x0) / (y2 - y0);
    float inv_slope_2 = (float)(x2 - x1) / (y2 - y1);

    // start x_start and x_end from the bottom vertex (x2, y2)
    float x_start = x2;
    float x_end = x2;

    for(int y = y2; y >= y0; y--)
    {
        draw_line(x_start, y, x_end, y, color);
        x_start -= inv_slope_1;
        x_end -= inv_slope_2;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Draw a filled triangle with the flat-top/flat-bottom method
// We split the original triangle in two, half flat-bottom and half flat-top
///////////////////////////////////////////////////////////////////////////////
/*
//          (x0,y0)
//            / \
//           /   \
//          /     \
//         /       \
//        /         \
//   (x1,y1)------(Mx,My)
//       \_           \
//          \_         \
//             \_       \
//                \_     \
//                   \    \
//                     \_  \
//                        \_\
//                           \
//                         (x2,y2)
*/
///////////////////////////////////////////////////////////////////////////////
void draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
    // sort y0 < y1 < y2
    if(y0 > y1)
    {
        int_swap(&y0, &y1);
        int_swap(&x0, &x1);
    }
    if(y1 > y2)
    {
        int_swap(&y1, &y2);
        int_swap(&x1, &x2);
    }
    if(y0 > y1)
    {
        int_swap(&y0, &y1);
        int_swap(&x0, &x1);
    }

    // this if/elseif is to eliminate possibility of dividing by zero
    if(y1 == y2)
    {
        // only flat-bottom triangle needed
        fill_flat_bottom_triangle(x0, y0, x1, y1, x2, y2, color);
    }
    else if(y0 == y1)
    {
        // only flat-top triangle needed
        fill_flat_top_triangle(x0, y0, x1, y1, x2, y2, color);
    }
    else
    {
        // calculate new vertex (Mx, My) - using triangle similarity
        int My = y1;
        int Mx = (((x2 - x0) * (y1 - y0)) / (y2 - y0)) + x0;

        fill_flat_bottom_triangle(x0, y0, x1, y1, Mx, My, color);
        fill_flat_top_triangle(x1, y1, Mx, My, x2, y2, color);
    }
}

///////////////////////////////////////////////////////////////////////////////
// Draw a triangle using three raw line calls
///////////////////////////////////////////////////////////////////////////////
void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
    draw_line(x0, y0, x1, y1, color);
    draw_line(x1, y1, x2, y2, color);
    draw_line(x2, y2, x0, y0, color);

}
/*
*   This program contains source code from Gustavo Pezzi's "3D Computer
*   Graphics Programming" course, found here: https://pikuma.com/courses
*/

//  ---------------------------------------------------------------------------
//  swap.c
//  Implementation file for integer and float swapping functionality
//  ---------------------------------------------------------------------------
#include "swap.h"

// Other operations -----------------------------------------------------------
// ----------------------------------------------------------------------------
void int_swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void float_swap(float* a, float* b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}
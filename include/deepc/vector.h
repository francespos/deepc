#ifndef DEEPC_VECTOR_H
#define DEEPC_VECTOR_H

#include "deepc/vector.h"

#ifdef __cplusplus
extern "C" {
#endif

void deepc_sum_vector_in_place(float* lhs, const float* rhs, unsigned int n);
void deepc_subtract_vector_in_place(float* lhs, const float* rhs, unsigned 
    int n);
void deepc_scale_vector_in_place(float* v, unsigned int n, float scalar);

float* deepc_sum_vectors(const float* lhs, const float* rhs, unsigned int n);
float* deepc_subtract_vectors(const float* lhs, const float* rhs, 
    unsigned int n);
float* deepc_scale_vector(const float* v, unsigned int n, float scalar);

float deepc_vector_dot(const float* lhs, const float* rhs, unsigned int n);

void deepc_are_vectors_equal(const float* lhs, const float* rhs, 
    unsigned int n);

#ifdef __cplusplus
}
#endif

#endif

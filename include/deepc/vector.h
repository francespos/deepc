#ifndef DEEPC_VECTOR_H
#define DEEPC_VECTOR_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void deepc_sum_vector_in_place(float* lhs, const float* rhs, size_t n);
void deepc_subtract_vector_in_place(float* lhs, const float* rhs, size_t n);
void deepc_scale_vector_in_place(float* v, size_t n, float scalar);

void deepc_sum_vectors(float* rslt, const float* lhs, const float* rhs, 
    size_t n);
void deepc_subtract_vectors(float* rslt, const float* lhs, const float* rhs, 
    size_t n);
void deepc_scale_vector(float* rslt, const float* v, size_t n, float scalar);

void deepc_dot_multiply_vectors(float* rslt, const float* lhs, const float* rhs, 
    size_t n);

#ifdef __cplusplus
}
#endif

#endif

#ifndef DEEPC_MATRIX_H
#define DEEPC_MATRIX_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void deepc_sum_matrix_in_place(float* lhs, const float* rhs, size_t n);
void deepc_subtract_matrix_in_place(float* lhs, const float* rhs, size_t n);
void deepc_scale_matrix_in_place(float* rslt, const float* m, size_t n, 
    float scalar);

void deepc_sum_matrices(float* rslt, const float* lhs, const float* rhs, 
    size_t n);

void deepc_subtract_matrices(float* rslt, const float* lhs, const float* rhs, 
    size_t n);

void deepc_scale_matrix(float* rslt, const float* m, size_t n, float scalar);

void deepc_hadamard_multiply_matrices(float* rslt, const float* lhs, 
    const float* rhs, size_t n);

void deepc_multiply_matrices(float* rslt, const float* lhs, const float* rhs, 
    size_t m, size_t n, size_t p);

void deepc_transpose_matrix(float* rslt, const float* m, size_t nr, size_t nc);

#ifdef __cplusplus
}
#endif

#endif // DEEPC_MATRIX_H

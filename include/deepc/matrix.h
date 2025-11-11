#ifndef DEEPC_MATRIX_H
#define DEEPC_MATRIX_H

#include "deepc/vector.h"

#ifdef __cplusplus
extern "C" {
#endif

void deepc_matrix_sum(float* rslt, const float* m1, const float* m2, size_t n);
void deepc_matrix_subtract(float* rslt, const float* m1, const float* m2, 
    size_t n);
void deepc_matrix_scale(float* rslt, const float* m, size_t n, float scalar);
void deepc_matrix_hadamard_product(float* rslt, const float* m1, 
    const float* m2, size_t n);
void deepc_matrix_vector_multiplication(float* rslt, const float* m1, 
    const float* m2, size_t nr, size_t n);
void deepc_matrix_multiplication(float* rslt, const float* m1, const float* m2, 
    size_t nr, size_t n, size_t nc);
void deepc_matrix_transpose(float* rslt, const float* m, size_t nr, size_t nc);

#ifdef __cplusplus
}
#endif

#endif // DEEPC_MATRIX_H

#include "deepc/matrix.h"

void deepc_sum_matrices_in_place(float* lhs, const float* rhs, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        lhs[i] += rhs[i];
    }
}   

void deepc_subtract_matrices_in_place(float* lhs, const float* rhs, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        lhs[i] -= rhs[i];
    }
}

void deepc_scale_matrix_in_place(float* lhs, size_t n, float scalar) {
    for (size_t i = 0; i < n; ++i) {
        lhs[i] *= scalar;
    }
}

void deepc_sum_matrices(float* rslt, const float* lhs, const float* rhs, 
    size_t n) 
{
    for (size_t i = 0; i < n; ++i) {
        rslt[i] = lhs[i] + rhs[i];
    }
}

void deepc_subtract_matrices(float* rslt, const float* lhs, const float* rhs, 
    size_t n)
{
    for (size_t i = 0; i < n; ++i) {
        rslt[i] = lhs[i] - rhs[i];
    }
}

void deepc_scale_matrix(float* rslt, const float* m, size_t n, float scalar) {
    for (size_t i = 0; i < n; ++i) {
        rslt[i] = m[i] * scalar;
    }
}

void deepc_hadamard_multiply_matrices(float* rslt, const float* lhs, 
    const float* rhs, size_t n)
{
    for (size_t i = 0; i < n; ++i) {
        rslt[i] = lhs[i] * rhs[i];
    }
}

void deepc_multiply_matrices(float* rslt, const float* lhs, const float* rhs, 
    size_t m, size_t n, size_t p)
{
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < p; ++j) {
            rslt[i * p + j] = 0.0f;
            for (size_t k = 0; k < n; ++k) {
                rslt[i * p + j] += lhs[i * n + k] * rhs[k * p + j]; 
            }
        }
    }
}

void deepc_transpose_matrix(float* rslt, const float* m, size_t nr, size_t nc) {
    for (size_t i = 0; i < nr; ++i) {
        for (size_t j = 0; j < nc; ++j) {
            rslt[j * nr + i] = m[i * nc + j];
        }
    }
}

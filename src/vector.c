#include "deepc/vector.h"

void deepc_sum_vector_in_place(float* lhs, const float* rhs, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        lhs[i] += rhs[i];
    }
}

void deepc_subtract_vector_in_place(float* lhs, const float* rhs, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        lhs[i] -= rhs[i];
    }
}

void deepc_scale_vector_in_place(float* v, unsigned int n, float scalar) {
    for (size_t i = 0; i < n; ++i) {
        v[i] *= scalar;
    }
}

void deepc_sum_vectors(float* rslt, const float* lhs, const float* rhs, 
    size_t n) 
{
    for (size_t i = 0; i < n; ++i) {
        rslt[i] = lhs[i] + rhs[i];
    }
}

void deepc_subtract_vectors(float* rslt, const float* lhs, const float* rhs, 
    size_t n) 
{
    for (size_t i = 0; i < n; ++i) {
        rslt[i] = lhs[i] - rhs[i];
    }
}

void deepc_scale_vector(float* rslt, const float* v, size_t n, float scalar) {
    for (size_t i = 0; i < n; ++i) {
        rslt[i] = v[i] * scalar;
    }
}

float deepc_dot_multiply_vectors(float* rslt, const float* lhs, 
    const float* rhs, size_t n) 
{
    float rslt = 0.0f;
    for (size_t i = 0; i < n; ++i) {
        rslt += lhs[i] * rhs[i];
    }   

    return rslt;
}

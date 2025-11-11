#include "deepc/matrix.h"

void deepc_matrix_sum(float* rslt, const float* m1, const float* m2, size_t n) 
{
    for (size_t i = 0; i < n; ++i) 
    {
        rslt[i] = m1[i] + m2[i];
    }
}

void deepc_matrix_subtract(float* rslt, const float* m1, const float* m2, 
    size_t n) 
{
    for (size_t i = 0; i < n; ++i) 
    {
        rslt[i] = m1[i] - m2[i];
    }
}

void deepc_matrix_scale(float* rslt, const float* m, size_t n, float scalar) 
{
    for (size_t i = 0; i < n; ++i) 
    {
        rslt[i] = m[i] * scalar;
    }
}

void deepc_matrix_hadamard_product(float* rslt, const float* m1, 
    const float* m2, size_t n)
{
    for (size_t i = 0; i < n; ++i) 
    {
        rslt[i] = m1[i] * m2[i];
    }
}

void deepc_matrix_multiply(float* rslt, const float* m1, const float* m2, 
    size_t nr, size_t n, size_t nc)
{
    for (size_t i = 0; i < nr; ++i) 
    {
        for (size_t j = 0; j < nc; ++j) 
        {
            rslt[i * nc + j] = 0.0f;

            for (size_t k = 0; k < n; ++k) 
            {
                rslt[i * nc + j] += m1[i * n + k] * m2[k * nc + j]; 
            }
        }
    }
}

void deepc_matrix_vector_multiply(float* rslt, const float* m, const float* v, 
    size_t nr, size_t n)
{
    for (size_t i = 0; i < nr; ++i)
    {
        rslt[i] = 0.0f;

        for (size_t j = 0; j < n; ++j) 
        {
            rslt[i] += m[i * n + j] * v[j];
        }
    }
}

void deepc_matrix_transpose(float* rslt, const float* m, size_t nr, size_t nc) 
{
    for (size_t i = 0; i < nr; ++i) 
    {
        for (size_t j = 0; j < nc; ++j) 
        {
            rslt[j * nr + i] = m[i * nc + j];
        }
    }
}

#include "deepc/vector.h"
#include <math.h>

float deepc_vector_length(const float* v, size_t n)
{
    float squared_length = 0.0f;

    for (size_t i = 0; i < n; ++i)
    {
        squared_length += v[i] * v[i];
    }

    return sqrt(squared_length);
}

void deepc_vector_normalize(float* rslt, const float* v, size_t n)
{
    float length = deepc_vector_length(v, n);

    for (size_t i = 0; i < n; ++i)
    {
        rslt[i] = v[i] / length;
    }
}

void deepc_vector_sum(float* rslt, const float* v1, const float* v2, size_t n) 
{
    for (size_t i = 0; i < n; ++i) 
    {
        rslt[i] = v1[i] + v2[i];
    }
}

void deepc_vector_subtract(float* rslt, const float* v1, const float* v2, 
    size_t n) 
{
    for (size_t i = 0; i < n; ++i) 
    {
        rslt[i] = v1[i] - v2[i];
    }
}

void deepc_vector_scale(float* rslt, const float* v, size_t n, float scalar) 
{
    for (size_t i = 0; i < n; ++i) 
    {
        rslt[i] = v[i] * scalar;
    }
}

float deepc_vector_dot_product(const float* v1, const float* v2, size_t n) 
{
    float rslt = 0.0f;

    for (size_t i = 0; i < n; ++i) 
    {
        rslt += v1[i] * v2[i];
    }   

    return rslt;
}

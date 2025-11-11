#ifndef DEEPC_VECTOR_H
#define DEEPC_VECTOR_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

float deepc_vector_length(const float* v1, size_t n);
void deepc_vector_normalize(float* rslt, const float* v, size_t n);

void deepc_vector_sum(float* rslt, const float* v1, const float* v2, size_t n);
void deepc_vector_subtract(float* rslt, const float* v1, const float* v2, 
    size_t n);
void deepc_vector_scale(float* rslt, const float* v, size_t n, float scalar);
float deepc_vector_dot_product(const float* v1, const float* v2, size_t n);

#ifdef __cplusplus
}
#endif

#endif

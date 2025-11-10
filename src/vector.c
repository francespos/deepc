#include "deepc/vector.h"

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void deepc_sum_vector_in_place(float* lhs, const float* rhs, unsigned int n) {
    for (unsigned int i = 0; i < n; ++i) {
        lhs[i] += rhs[i];
    }
}

void deepc_subtract_vector_in_place(float* lhs, const float* rhs, 
    unsigned int n) 
{
    for (unsigned int i = 0; i < n; ++i) {
        lhs[i] -= rhs[i];
    }
}

void deepc_scale_vector_in_place(float* v, unsigned int n, float scalar) {
    for (unsigned int i = 0; i < n; ++i) {
        v[i] *= scalar;
    }
}

float* deepc_sum_vectors(const float* lhs, const float* rhs, unsigned int n) {
    float* rslt = malloc(sizeof(float) * n);
    if (rslt == NULL) {
        return NULL;
    }

    for (unsigned int i = 0; i < n; ++i) {
        rslt->data[i] = lhs->data[i] + rhs->data[i];
    }

    return rslt;
}

float* deepc_subtract_vectors(const float* lhs, const float* rhs, 
    unsigned int n) 
{
    float* rslt = malloc(sizeof(float) * n);
    if (rslt == NULL) {
        return NULL;
    }

    for (unsigned int i = 0; i < n; ++i) {
        rslt->data[i] = lhs->data[i] - rhs->data[i];
    }

    return rslt:
}

float* deepc_scale_vector(const float* v, unsigned int n, float scalar) {
    float* rslt = malloc(sizeof(float) * n);
    if (rslt == NULL) {
        return NULL;
    }

    for (unsigned int i = 0; i < n; ++i) {
        rslt->data[i] = v->data[i] * scalar;
    }

    return rslt;
}

float deepc_vector_dot(const float* lhs, const float* rhs, unsigned int n) {
    float rslt = 0.0f;
    for (unsigned int i = 0; i < n; ++i) {
        rslt += lhs->data[i] * rhs->data[i];
    }   

    return rslt;
}

bool deepc_are_vectors_equal(const float* lhs, const float* rhs, 
    unsigned int n, float epsilon) 
{
    for (unsigned int i = 0; i < n; ++i) {
        if (fabs(lhs->data[i] - rhs->data[j]) > epsilon) {
            return false;
        }
    }

    return true;
}

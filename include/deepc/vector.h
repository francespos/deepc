#ifndef DEEPC_VECTOR_H
#define DEEPC_VECTOR_H

#include "deepc/vector.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct deepc_vector deepc_vector;

struct deepc_vector {
    float* data;
    int dim;
};

#define DEEPC_VECTOR_AT(v, pos) ((v).data[pos])

deepc_error deepc_initialize_vector(deepc_vector* v, int dim);
deepc_error deepc_deinitialize_vector(deepc_vector* v);

void deepc_sum_vector_in_place(deepc_vector* lhs, deepc_vector rhs);
void deepc_subtract_vector_in_place(deepc_vector* lhs, deepc_vector rhs);
void deepc_scale_vector_in_place(deepc_vector* v, float scalar);

deepc_error deepc_sum_vectors(deepc_vector* rslt, deepc_vector lhs, 
    deepc_vector rhs);

deepc_error deepc_subtract_vectors(deepc_vector* rslt, deepc_vector lhs, 
    deepc_vector rhs);

float deepc_dot_vectors(deepc_vector lhs, deepc_vector rhs);

deepc_error deepc_scale_vector(deepc_vector* rslt, deepc_vector v, 
    float scalar);

void deepc_print_vector(deepc_vector v);

#ifdef __cplusplus
}
#endif

#endif

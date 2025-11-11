#ifndef DEEPC_FLOAT_H
#define DEEPC_FLOAT_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cpluscplus
extern "C" {
#endif

bool deepc_are_floats_equal(float x, float y, float epsilon);
bool deepc_are_float_arrays_equal(const float* v1, const float* v2, size_t n, 
    float epsilon);

#ifdef __cpluscplus
}
#endif

#endif // DEEPC_FLOAT_H

#include "deepc/float.h"
#include <math.h>

bool deepc_are_floats_equal(float x, float y, float epsilon)
{
    return fabs(x - y) <= epsilon;
}

bool deepc_are_float_arrays_equal(const float* v1, const float* v2, size_t n,
    float epsilon)
{
    for (size_t i = 0; i < n; ++i) 
    {
        if (fabs(v1[i] - v2[i]) > epsilon)
        {
            return false;
        }
    }

    return true;
}

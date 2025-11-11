#include "deepc/vector.h"
#include "deepc/float.h"
#include <assert.h>
#include <stdio.h>

const float epsilon = 1e-6f;

void test_vector_length()
{
    float x[2] = {3.0f, 4.0f};
    float length = deepc_vector_length(x, sizeof(x) / sizeof(x[0]));
    assert(deepc_are_floats_equal(length, 5.0f, epsilon));
}

int main()
{
    test_vector_length();
}

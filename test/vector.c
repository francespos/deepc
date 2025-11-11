#include "deepc/vector.h"
#include "deepc/float.h"
#include <assert.h>

const float epsilon = 1e-6;

void test_vector_length()
{
    float x[2] = {3.0f, 4.0f};
    float length = deepc_vector_length(x, sizeof(3));
    assert(deepc_are_floats_equal(length, 5.0f, epsilon));
}

int main()
{
    test_vector_length();
}

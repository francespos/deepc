#include "deepc/matrix.h"
#include "deepc/float.h"
#include <assert.h>

const float epsilon = 1e-6f;

void test_matrix_sum()
{
    float m1[] = {1.0f, 2.0f, 3.0f, 4.0f};
    float m2[] = {2.0f, 3.0f, 4.0f, 5.0f};

    size_t nr = 2;
    size_t nc = 2;

    size_t n = nr * nc;

    float expected_value[n];
    deepc_matrix_sum(expected_value, m1, m2, n);

    float true_value[] = {3.0f, 5.0f, 7.0f, 9.0f};
    assert(deepc_are_float_arrays_equal(expected_value, true_value, n, 
        epsilon));
}

int main()
{
    test_matrix_sum();
}

#include "deepc/vector.h"
#include "deepc/float.h"
#include <assert.h>

const float epsilon = 1e-6f;

void test_vector_length()
{
    float v[] = {3.0f, 4.0f};
    size_t n = sizeof(v) / sizeof(v[0]);

    float expected_length = deepc_vector_length(v, sizeof(v) / n);
    float true_length = 5.0f;

    assert(deepc_are_floats_equal(expected_length, true_length, epsilon));
}

void test_vector_normalize()
{
    float v[] = {3.0f, 4.0f};
    size_t n = sizeof(v) / sizeof(v[0]);

    float expected_normalized_v[n];
    deepc_vector_normalize(expected_normalized_v, v, n);

    float true_normalized_v[] = {3.0f / 5.0f, 4.0f / 5.0f};

    assert(deepc_are_float_arrays_equal(expected_normalized_v, 
        true_normalized_v, n, epsilon));

}

void test_vector_sum()
{
    float v1[] = {1.0f, 2.0f};
    float v2[] = {3.0f, 4.0f};
    size_t n = 2;

    float expected_sum[n];
    deepc_vector_sum(expected_sum, v1, v2, n);

    float true_sum[] = {4.0f, 6.0f};

    assert(deepc_are_float_arrays_equal(expected_sum, true_sum, n, epsilon));
}

void test_vector_subtract()
{
    float v1[] = {1.0f, 2.0f};
    float v2[] = {3.0f, 4.0f};
    size_t n = 2;

    float expected_diff[n];
    deepc_vector_subtract(expected_diff, v1, v2, n);

    float true_diff[] = {-2.0f, -2.0f};

    assert(deepc_are_float_arrays_equal(true_diff, expected_diff, n, epsilon));
}

void test_vector_scale()
{
    float v[] = {2.0f, 3.0f};
    size_t n = sizeof(v) / sizeof(v[0]);
    float scalar = 2.0f;

    float expected_scaled_v[n];
    deepc_vector_scale(expected_scaled_v, v, n, scalar);

    float true_scaled_v[] = {4.0f, 6.0f};

    assert(deepc_are_float_arrays_equal(expected_scaled_v, true_scaled_v, n, 
        epsilon));
}

void test_vector_dot_product()
{
    float v1[] = {2.0f, 3.0f};
    float v2[] = {3.0f, 4.0f}; 
    size_t n = 2;

    float expected_dot_prod = deepc_vector_dot_product(v1, v2, n); 
    float true_dot_prod = 18.0f;

    assert(deepc_are_floats_equal(expected_dot_prod, true_dot_prod, n));
}

int main()
{
    test_vector_length();
    test_vector_normalize();
    test_vector_sum();
    test_vector_subtract();
    test_vector_scale();
    test_vector_dot_product();
}

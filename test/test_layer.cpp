#include <deepc/layer.h>
#include <deepc/float.h>
#include <deepc/activations.h>
#include <cassert>

const float epsilon = 1e-6f;

deepc_layer layer;

float weights[] = 
{
    1.0f, -2.0f, 2.0f, 
    -3.0f, 3.0f, -4.0f
};

float biases[] = {2.0f, -3.0f};

const size_t input_size = 3;
const size_t output_size = 2;

const float input[] = {1.0f, -2.0f, 3.0f};
float z[2];
float output[2];

void mat_vec_mul(float* rslt, const float* m, const float* v, size_t nr, 
    size_t n)
{
    for (size_t i = 0; i < nr; ++i)
    {
        rslt[i] = 0.0f; 

        for (size_t j = 0; j < n; ++j)
        {
            rslt[i] += m[i * n + j] * v[j];
        }
    }
}

void vec_sum(float* rslt, const float* v1, const float* v2, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        rslt[i] = v1[i] + v2[i]; 
    }
}

void vec_copy(float* dest, const float* src, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        dest[i] = src[i];
    }
}

void vec_apply_func(float* rslt, float (*func)(float), const float* v, 
    size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        rslt[i] = func(v[i]);
    }
}

void test_dense_layer_forward()
{
    layer.forward(output, z, &layer, input); 

    float true_z[2]; 
    mat_vec_mul(true_z, weights, input, output_size, input_size);
    vec_sum(true_z, true_z, biases, 2);

    assert(deepc_float_arrays_equal(z, true_z, 2, epsilon));
    
    float true_output[2];
    vec_apply_func(true_output, deepc_sigmoid, true_z, 2);  

    assert(deepc_float_arrays_equal(output, true_output, 2, epsilon));
}

int main()
{
    deepc_dense_layer_initialize(&layer, weights, biases, input_size, 
        output_size, deepc_sigmoid, deepc_sigmoid_derivative);

    test_dense_layer_forward();
}

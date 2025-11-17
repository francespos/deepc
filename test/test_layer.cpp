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


void test_dense_layer_backward()
{
    layer.forward(output, z, &layer, input);
    
    float delta[input_size];
    float forward_delta[] = {0.5f, -0.5f};
    
    layer.backward(delta, &layer, forward_delta, z);
    
    float expected_delta[input_size] = {0.0f, 0.0f, 0.0f};
    
    for (size_t i = 0; i < output_size; ++i)
    {
        float activation_grad = deepc_sigmoid_derivative(z[i]);
        float delta_i = forward_delta[i] * activation_grad;
        
        for (size_t j = 0; j < input_size; ++j)
        {
            expected_delta[j] += weights[i * input_size + j] * delta_i;
        }
    }
    
    assert(deepc_float_arrays_equal(delta, expected_delta, input_size, 
        epsilon));
}

void test_dense_layer_update()
{
    float original_weights[6];
    vec_copy(original_weights, weights, 6);

    float original_biases[2];
    vec_copy(original_biases, biases, 2);

    float learning_rate = 0.1f;
    float delta[] = {0.2f, -0.3f};
    
    layer.update(&layer, learning_rate, input, delta);

    float expected_weights[6];
    vec_copy(expected_weights, original_weights, 6);

    float expected_biases[2];
    vec_copy(expected_biases, original_biases, 2);
    
    for (size_t i = 0; i < output_size; ++i)
    {
        for (size_t j = 0; j < input_size; ++j)
        {
            expected_weights[i * input_size + j] -= learning_rate * input[j] * 
                delta[i];
        }

        expected_biases[i] -= learning_rate * delta[i];
    }

    assert(deepc_float_arrays_equal(weights, expected_weights, 6, epsilon));  
    assert(deepc_float_arrays_equal(biases, expected_biases, 2, epsilon));
}

int main()
{
    deepc_dense_layer_initialize(&layer, weights, biases, input_size, 
        output_size, deepc_sigmoid, deepc_sigmoid_derivative);

    test_dense_layer_forward();
    test_dense_layer_backward();
    test_dense_layer_update();
}

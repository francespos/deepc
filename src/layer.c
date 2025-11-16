#include <deepc/layer.h>

void deepc_dense_layer_initialize(deepc_layer* layer, float* weights, 
    float* biases, size_t input_size, size_t output_size, 
    float (*activation)(float), float (*activation_derivative)(float))
{
    layer->weights = weights;
    layer->biases = biases;
    layer->input_size = input_size;
    layer->output_size = output_size;
    layer->activation = activation;
    layer->activation_derivative = activation_derivative;
    layer->forward = deepc_dense_layer_forward;
    layer->backward = deepc_dense_layer_backward;
    layer->update = deepc_dense_layer_update;
}

void deepc_dense_layer_forward(float* output, float* z, 
    const deepc_layer* layer, const float* input)
{
    size_t nr = layer->output_size;
    size_t nc = layer->input_size;

    for (size_t i = 0; i < nr; ++i)
    {
        z[i] = layer->biases[i];
        
        for (size_t j = 0; j < nc; ++j)
        {
            z[i] += layer->weights[i * nc + j] * input[j]; 
        }

        output[i] = layer->activation(z[i]);
    }
}

void deepc_dense_layer_backward(float* delta, const deepc_layer* layer, 
    const float* forward_delta, const float* z)
{
    size_t nr = layer->output_size;
    size_t nc = layer->input_size;

    for (size_t j = 0; j < nc; ++j) {
        delta[j] = 0.0f;
    }

    for (size_t i = 0; i < nr; ++i)
    {
        float activation_grad = layer->activation_derivative(z[i]);
        float delta_i = forward_delta[i] * activation_grad;
        
        for (size_t j = 0; j < nc; ++j)
        {
            delta[j] += layer->weights[i * nc + j] * delta_i;
        }
    }
}

void deepc_dense_layer_update(deepc_layer* layer, float learning_rate, 
    const float* input, const float* delta)
{
    size_t nr = layer->output_size;
    size_t nc = layer->input_size;

    for (size_t i = 0; i < nr; ++i)
    {
        for (size_t j = 0; j < nc; ++j)
        {
            layer->weights[i * nc + j] -= learning_rate * input[j] * delta[i];
        }

        layer->biases[i] -= learning_rate * delta[i];
    }
}

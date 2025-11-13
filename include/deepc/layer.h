#ifndef DEEPC_LAYERS_H
#define DEEPC_LAYERS_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct deepc_layer deepc_layer;

struct deepc_layer 
{
    float* weights;
    float* biases;

    size_t input_size;
    size_t output_size;

    float (*activation)(float);
    float (*activation_derivative)(float);

    void (*forward)(float*, float*, const deepc_layer*, const float*);
    void (*backward)(float*, const deepc_layer*, const float*, const float*);
    void (*update)(deepc_layer*, float, const float*, const float*);
};

void deepc_dense_layer_initialize(deep_layer* layer, float* weights, 
    float* biases, size_t input_size, size_t output_size, 
    float (*activation)(float), float (*activation_derivative)(float));

void deepc_dense_layer_forward(float* output, float* z, 
    const deepc_layer* layer, const float* input);

void deepc_dense_layer_backward(float* delta, const deepc_layer* layer, 
    const float* forward_delta, const float* z);

void deepc_dense_layer_update(deepc_layer* layer, float learning_rate, 
    const float* input, const float* delta);

#ifdef __cplusplus
}
#endif

#endif // DEEPC_LAYERS_H

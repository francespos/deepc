#ifndef DEEPC_LAYERS_H
#define DEEPC_LAYERS_H

#include "deepc/matrix.h"

#ifdef __cpluscplus
extern "C" {
#endif

typedef struct deepc_layer deepc_layer;

struct deepc_layer {
    char* name;

    float (*activation)(float);
    float (*activation_derivative)(float);

    // int input_size, output_size;

    deepc_layer* next;
    
    deepc_matrix weights, biases;
    deepc_matrix dweights, dbiases;

    deepc_vector input, output, z;
};

void deepc_initialize_dense_layer(deepc_layer* layer, int num_units, 
    float (*activation)(float), int input_size);

void deepc_deinitialize_layer(deepc_layer* layer);

deepc_error deepc_forward_pass(deepc_vector* dest, const deepc_layer* layer, 
    deepc_vector input);

deepc_error deepc_backward_pass(deepc_vector* dest, deepc_layer* layer, 
    deepc_matrix gradient);

deepc_matrix deepc_apply_activation(deepc_matrix input, 
    deepc_activation activation);

deepc_matrix deepc_apply_activation_derivative(deepc_matrix input, 
    float (*activation)(float));

void deepc_initialize_weights_xavier(deepc_matrix* weights, int input_size);

void deepc_save_layer(deepc_layer* dest, const char* path);
void deepc_load_layer(deepc_layer* dest, const char* path);

#ifdef __cpluscplus
}
#endif

#endif // DEEPC_LAYERS_H

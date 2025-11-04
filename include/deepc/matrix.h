#ifndef DEEPC_MATRIX_H
#define DEEPC_MATRIX_H

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <time.h>
// #include <math.h>
// #include <execinfo.h>
// #include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct deepc_matrix deepc_matrix;

struct deepc_matrix {
    float* data;
    int num_rows;
    int num_cols;
};

#define DEEPC_MATRIX_AT(matrix, i, j) ((matrix).num_cols * (i) + (j))

int deepc_initialize_matrix(deepc_matrix* matrix, int num_rows, int num_cols);
void deepc_deinitialize_matrix(deepc_matrix* matrix);

deepc_matrix deepc_copy_matrix(deepc_matrix matrix);

deepc_matrix deepc_zeros_matrix(int num_rows, int num_cols);
deepc_matrix deepc_ones_matrix(int num_rows, int num_cols);

deepc_matrix deepc_rand_matrix(int num_rows, int num_cols);
void deepc_print_matrix(deepc_matrix matrix);

deepc_matrix deepc_matrix_row(deepc_matrix matrix, int row_pos);
deepc_matrix deepc_matrix_col(deepc_matrix matrix, int col_pos);

void deepc_set_row(deepc_matrix matrix, int row_pos, float* row);
void deepc_set_col(deepc_matrix matrix, int col_pos, float* col);

deepc_matrix deepc_sum_matrices(deepc_matrix lhs, deepc_matrix rhs);
deepc_matrix deepc_subtract_matrices(deepc_matrix lhs, deepc_matrix rhs);
deepc_matrix deepc_multiply_matrices(deepc_matrix lhs, deepc_matrix rhs);
deepc_matrix deepc_hadamard_multiply_matrices(deepc_matrix lhs, 
    deepc_matrix rhs);

deepc_matrix deepc_scale_matrix(deepc_matrix matrix, float scalar);

deepc_matrix deepc_transpose_matrix(deepc_matrix matrix);
deepc_matrix deepc_apply_function_to_matrix(deepc_matrix matrix, 
    float (*func)(float));

void deepc_add_matrix_inplace(deepc_matrix* lhs, deepc_matrix rhs);
void deepc_subtract_matrix_inplace(deepc_matrix* lhs, deepc_matrix rhs);
void deepc_scale_matrix_inplace(deepc_matrix* matrix, float scalar);

float deepc_sigmoid(float x);
float deepc_relu(float x);
float deepc_tanh(float x);

void deepc_print_stack_trace();
int deepc_matrix_has_nan(deepc_matrix mat);

deepc_matrix deepc_features(deepc_matrix data_with_labels, int label_column);
deepc_matrix deepc_labels(deepc_matrix data_with_labels, int label_column);
void deepc_print_class_distribution(deepc_matrix labels);

#ifdef __cplusplus
}
#endif

#endif // DEEPC_MATRIX

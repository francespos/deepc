#ifndef DEEPC_CSV_LOADER_H
#define DEEPC_CSV_LOADER_H

#include "deepc/matrix.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>
// #include <math.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int deepc_count_columns(const char* line);
void deepc_trim_whitespace(char* str);

int deepc_load_csv(deepc_matrix* dest, const char* filename, bool has_header);
int deepc_count_missing_values(deepc_matrix matrix);

void deepc_fill_missing_with_mean(deepc_matrix* matrix);
void deepc_fill_missing_with_zeros(deepc_matrix* matrix);

void deepc_print_matrix_stats(deepc_matrix matrix);

int deepc_train_test_split(deepc_matrix x, deepc_matrix y, float test_size, 
    deepc_matrix* x_train, deepc_matrix* x_test, 
    deepc_matrix* y_train, deepc_matrix* y_test);

int deepc_split_features_labels(deepc_matrix* dest, deepc_matrix data, 
    int label_column);

int deepc_one_hot_encode_labels(deepc_matrix* dest, deepc_matrix labels, 
    int num_classes);

int deepc_one_hot_decode_labels(deepc_matrix* dest, deepc_matric one_hot);

deepc_matrix deepc_normalized_matrix(deepc_matrix matrix);
deepc_matrix deepc_standardized_matrix(deepc_matrix matrix);

void deepc_shuffle_dataset(deepc_matrix* lhs, deepc_matrix* rhs);

#ifdef __cplusplus
}
#endif

#endif // DEEPC_CSV_LOADER_H

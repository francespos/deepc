#include "deepc/matrix.h"

// Stack trace function
void deepc_print_stack_trace() {
#ifdef EXECINFO_AVAILABLE
    void* buffer[100];
    char** strings;
    int nptrs;
    
    printf("\n=== STACK TRACE ===\n");
    nptrs = backtrace(buffer, 100);
    strings = backtrace_symbols(buffer, nptrs);
    
    if (strings == NULL) {
        perror("backtrace_symbols");
        return;
    }
    
    for (int i = 1; i < nptrs; i++) {
        printf("#%d %s\n", i-1, strings[i]);
    }
    
    free(strings);
    printf("===================\n\n");
#endif
}

// Initialize the matrix
deepc_error deepc_initialize_matrix(deepc_matrix* matrix, int num_rows, 
    int num_cols) 
{
    matrix->data = malloc(sizeof(float) * num_rows * num_cols);
    if (matrix->data == NULL) {
        return DEEPC_ALLOCATION_FAILED;
    }

    matrix->num_rows = num_rows;
    matrix->num_cols = num_cols;
    
    return DEEPC_SUCCESS;
}

// Deinitialize the matrix
void deepc_deinitialize_matrix(deepc_matrix* matrix) {
    free(matrix->data);
    matrix->data = NULL;
    matrix->num_rows = matrix->num_cols = 0;
}

// Create a deep copy of a matrix
deepc_error deepc_copy_matrix(deepc_matrix* dest, deepc_matrix src) {
    deepc_error err = deepc_initialize_matrix(dest, src.num_rows, src.num_cols);
    if (err) {
        return err;
    }

    for (int i = 0; i < num_rows * num_cols; ++i) {
        dest->data[i] = src.data[i];
    }
    
    return DEEPC_SUCCESS;
}

// Fill matrix with zeros
deepc_error deep_zeros_matrix(deepc_matrix* dest, int num_rows, int num_cols) {
    deepc_error err = deepc_initialize_matrix(dest, num_rows, num_cols);
    if (err) {
        return err;
    }

    for (int i = 0; i < num_rows * num_cols; ++i) {
        dest->data[i] = 0.0f;
    }

    return DEEPC_SUCCESS;
}

// Fill matrix with ones
deepc_error deepc_ones_matrix(deepc_matrix* dest, int num_rows, int num_cols) {
    deepc_error err = deepc_initialize_matrix(dest, num_rows, num_cols);
    if (err) {
        return err;
    }

    for (int i = 0; i < num_rows * num_cols; ++i) {
        dest->data[i] = 1.0f;
    }

    return DEEPC_SUCCESS;
}

// Fills matrix with random values between 0.0f and 1.0f
deepc_error deepc_rand_matrix(deepc_matrix* dest, int num_rows, int num_cols, 
    int seed) 
{
    deepc_error err = deepc_initialize_matrix(dest, num_rows, num_cols);
    if (err) {
        return err;
    }

    srand(seed);
    for (int i = 0; i < num_rows * num_cols; ++i) {
        dest->data[i] = (float)rand() / RAND_MAX;
    }
    
    return DEEPC_SUCCESS;
}

// Print matrix
void deepc_print_matrix(deepc_matrix matrix) {
    printf("Matrix (%d x %d):\n", matrix.num_rows, matrix.num_cols);

    for (int i = 0; i < matrix.num_rows; ++i) {
        for (int j = 0; j < matrix.num_cols; ++j) {
            if (isnan(DEEPC_MATRIX_AT(matrix, i, j))) {
                printf("     NaN ");
            } else {
                printf("%8.4f ", DEEPC_MATRIX_AT(matrix, i, j));
            }
        }

        printf("\n");
    }

    printf("\n");
}

// Get a specific row as a new 1xcols matrix
deepc_error deepc_matrix_row(deepc_matrix* dest, deepc_matrix src, int row_pos) 
{
    deepc_error_code err = deepc_initialize_matrix(dest, 1, src.num_cols);
    if (err) {
        return err;
    }
    
    for (int j = 0; j < src.num_cols; ++j) {
        DEEPC_MATRIX_AT(*dest, 0, j) = DEEPC_MATRIX_AT(src, row_pos, j);
    }
    
    return DEEPC_SUCCESS;
}

// Get a specific column as a new rowsx1 matrix
deepc_error_code deepc_matrix_col(deepc_matrix* dest, deepc_matrix src, 
    int col_pos) 
{
    deepc_error_code err = deepc_initialize_matrix(dest, src.num_rows, 1);
    if (err) {
        return err;
    }
    
    for (int i = 0; i < src.num_rows; ++i) {
        DEEPC_MATRIX_AT(*dest, i, 0) = DEEPC_MATRIX_AT(src, i, col_pos);
    }
    
    return DEEPC_SUCCESS;
}

// Set a specific row from a vector
void deepc_set_matrix_row(deepc_matrix* dest, int row_pos, deepc_matrix row) {
    for (int j = 0; j < dest->num_cols; ++j) {
        DEEPC_MATRIX_AT(*dest, row_pos, j) = DEEPC_MATRIX_AT(row, 0, j);
    }
}

// Set a specific column from a rows x 1 matrix
void deepc_set_matrix_col(deepc_matrix* dest, int col_pos, deepc_matrix col) {
    for (int i = 0; i < dest->num_rows; ++i) {
        DEEPC_MATRIX_AT(*dest, i, col_pos) = DEEPC_MATRIX_AT(col, i, 0);
    }
}

// Element-wise addition
deepc_error deepc_sum_matrices(deepc_matrix* rslt, deepc_matrix lhs, 
    deepc_matrix rhs) 
{
    DEEPC_ASSERT(lhs.num_rows == rhs.num_rows && lhs.num_cols == rhs.num_cols, 
        "Matrices must have the same number of rows and columns");

    deepc_error err = deepc_initialize_matrix(rslt, lhs.num_rows, lhs.num_cols);
    if (err) {
        return err;
    }

    for (int i = 0; i < lhs.num_rows * lhs.num_cols; ++i) {
        rslt->data[i] = lhs.data[i] + rhs.data[i];
    }

    return DEEPC_SUCCESS;
}

// Element-wise subtraction
deepc_error deepc_subtract_matrices(deepc_matrix* rslt , deepc_matrix lhs, 
    deepc_matrix rhs) 
{
    DEEPC_ASSERT(lhs.num_rows == rhs.num_rows && lhs.num_cols == rhs.num_cols, 
        "Matrices must have the same number of rows and columns");

    deepc_error err = deepc_initialize_matrix(rslt, lhs.num_rows, lhs.num_cols);
    if (err) {
        return err;
    }

    for (int i = 0; i < lhs.num_rows * lhs.num_cols; ++i) {
        rslt->data[i] = lhs.data[i] - rhs.data[i];
    }

    return DEEPC_SUCCESS; 
}

// Element-wise multiplication (Hadamard product)
deepc_error deepc_hadamard_multiply_matrices(deepc_matrix* rslt, 
    deepc_matrix lhs, deepc_matrix rhs) 
{
    DEEPC_ASSERT(lhs.num_rows == rhs.num_rows && lhs.num_cols == rhs.num_cols, 
        "Matrices must have the same number of rows and columns");

    deepc_error_code err = deepc_initialize_matrix(rslt, lhs.num_rows, 
        lhs.num_cols);

    if (err) {
        return err;
    }

    for (int i = 0; i < lhs.num_rows * lhs.num_cols; ++i) {
        rslt->data[i] = lhs.data[i] * rhs.data[i];
    }

    return DEEPC_SUCCESS;    
}

deepc_error deepc_multiply_matrices(deepc_matrix* rslt, deepc_matrix lhs, 
    deepc_matrix rhs) 
{
    deepc_error err = deepc_initialize_matrix(rslt, lhs.num_rows, rhs.num_cols);
    if (err) {
        return err;
    }

    for (int i = 0; i < lhs.num_rows; ++i) {
        for (int j = 0; j < rhs.num_cols; ++j) {
            DEEPC_MATRIX_AT(*rslt, i, j) = 0.0f;
            for (int k = 0; k < rhs.num_cols; ++k) {
                DEEPC_MATRIX_AT(*rslt, i, j) += DEEPC_MATRIX_AT(lhs, i, k) * 
                    DEEPC_MATRIX_AT(rhs, k, j);
            }
        }
    }

    return DEEPC_SUCCESS;
}   

// Scalar multiplication
deepc_error deepc_scale_matrix(deepc_matrix* rslt, deepc_matrix matrix, 
    float scalar) 
{
    deepc_error err = deepc_initialize_matrix(rslt, matrix.num_rows, 
        matrix.num_cols);

    if (err) {
        return err;
    }

    for (int i = 0; i < matrix.num_rows * matrix.num_cols; ++i) {
        rslt->data[i] = matrix.data[i] * scalar;
    }

    return DEEPC_SUCCESS;
}

// Matrix transpose
deepc_error deepc_transpose_matrix(deepc_matrix* rslt, deepc_matrix matrix) {
    deepc_error err = deepc_initialize_matrix(rslt, matrix.num_rows, 
        matrix.num_cols);

    if (err) {
        return err;
    }

    for (int i = 0; i < matrix.num_rows; ++i) {
        for (int j = 0; j < matrix.num_cols; ++j) {
            DEEPC_MATRIX_AT(*rslt, i, j) = DEEPC_MATRIX_AT(matrix, j, i);
        }
    }

    return DEEPC_SUCCESS;
}

// Apply function to each element
deepc_error deepc_apply_function_to_matrix(deepc_matrix* rslt, 
    deepc_matrix matrix, float (*func)(float)) 
{
    deepc_error err = deepc_initialize_matrix(rslt, matrix.num_rows, 
        matrix.num_cols);

    if (err) {
        return err;
    }

    for (int i = 0; i < matrix.num_rows * matrix.num_cols; ++i) {
        rslt->data[i] = func(matrix.data[i]);
    }

    return DEEPC_SUCCESS;
}

// In-place operations (more efficient)
void deepc_sum_matrix_in_place(deepc_matrix* lhs, deepc_matrix rhs) {
    for (int i = 0; i < rhs.num_rows * rhs.num_cols; ++i) {
        lhs->data[i] += rhs.data[i];
    }
}

void subtract_inplace(Matrix *a, const Matrix *b) {
    MATRIX_CHECK(a != NULL && b != NULL, "Matrices cannot be NULL");
    MATRIX_CHECK(a->rows == b->rows && a->cols == b->cols, 
                "Matrix dimensions don't match for in-place subtraction");
    
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            a->data[i][j] -= b->data[i][j];
        }
    }
}

void scale_inplace(Matrix *a, double scalar) {
    MATRIX_CHECK(a != NULL, "Matrix cannot be NULL");
    
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            a->data[i][j] *= scalar;
        }
    }
}

// Activation functions
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double relu(double x) {
    return x > 0 ? x : 0;
}

double tanh_func(double x) {
    return tanh(x);
}

// Helper function to check matrix for NaN values
int matrix_has_nan(const Matrix* m) {
    if (!m) return 0;
    
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            if (isnan(m->data[i][j])) {
                return 1;
            }
        }
    }
    return 0;
}


// Extract features from dataset (exclude label column)
Matrix* get_features(const Matrix* data_with_labels, int label_column) {
    MATRIX_CHECK(data_with_labels != NULL, "Data matrix cannot be NULL");
    MATRIX_CHECK(label_column >= 0 && label_column < data_with_labels->cols, 
                "Label column out of bounds");
    
    int num_samples = data_with_labels->rows;
    int num_features = data_with_labels->cols - 1;
    
    Matrix* features = create_matrix(num_samples, num_features);
    
    for (int i = 0; i < num_samples; i++) {
        int feature_idx = 0;
        for (int j = 0; j < data_with_labels->cols; j++) {
            if (j != label_column) {
                features->data[i][feature_idx] = data_with_labels->data[i][j];
                feature_idx++;
            }
        }
    }
    
    return features;
}

// Extract labels from dataset
Matrix* get_labels(const Matrix* data_with_labels, int label_column) {
    MATRIX_CHECK(data_with_labels != NULL, "Data matrix cannot be NULL");
    MATRIX_CHECK(label_column >= 0 && label_column < data_with_labels->cols, 
                "Label column out of bounds");
    
    int num_samples = data_with_labels->rows;
    Matrix* labels = create_matrix(num_samples, 1);
    
    for (int i = 0; i < num_samples; i++) {
        labels->data[i][0] = data_with_labels->data[i][label_column];
    }
    
    return labels;
}

// Print class distribution
void print_class_distribution(const Matrix* labels) {
    MATRIX_CHECK(labels != NULL, "Labels matrix cannot be NULL");
    MATRIX_CHECK(labels->cols == 1, "Labels must be a single column");
    
    int num_samples = labels->rows;
    
    // Count classes (assuming classes are 0,1,2,...)
    int max_class = 0;
    for (int i = 0; i < num_samples; i++) {
        int current_class = (int)labels->data[i][0];
        if (current_class > max_class) {
            max_class = current_class;
        }
    }
    
    int num_classes = max_class + 1;
    int* class_counts = (int*)calloc(num_classes, sizeof(int));
    
    // Count each class
    for (int i = 0; i < num_samples; i++) {
        int class_label = (int)labels->data[i][0];
        if (class_label >= 0 && class_label < num_classes) {
            class_counts[class_label]++;
        }
    }
    
    printf("Class Distribution:\n");
    printf("Class\tCount\tPercentage\n");
    printf("----------------------------\n");
    
    for (int i = 0; i < num_classes; i++) {
        double percentage = (double)class_counts[i] / num_samples * 100.0;
        printf("%d\t%d\t%.1f%%\n", i, class_counts[i], percentage);
    }
    
    free(class_counts);
}

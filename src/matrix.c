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
int deepc_initialize_matrix(deepc_matrix* matrix, int num_rows, int num_cols) {
    matrix->data = malloc(sizeof(float) * num_rows * num_cols);
    if (matrix->data == NULL) {
        return -1;
    }

    matrix->num_rows = num_rows;
    matrix->num_cols = num_cols;
    
    return 0;
}

// Deinitialize the matrix
void deepc_deinitialize_matrix(deepc_matrix* matrix) {
    free(matrix->data);
    matrix->data = NULL;
    matrix->num_rows = matrix->num_cols = 0;
}

// Create a deep copy of a matrix
int deepc_copy_matrix(deepc_matrix* dest, deepc_matrix src) {
    int err = deepc_initialize_matrix(dest, src.num_rows, src.num_cols);
    if (err) {
        return err;
    }

    for (int i = 0; i < num_rows * num_cols; ++i) {
        dest->data[i] = src.data[i];
    }
    
    return 0;
}

// Fill matrix with zeros
int deep_zeros_matrix(deepc_matrix* dest, int num_rows, int num_cols) {
    int err = deepc_initialize_matrix(dest, num_rows, num_cols);
    if (err) {
        return err;
    }

    for (int i = 0; i < num_rows * num_cols; ++i) {
        dest->data[i] = 0.0f;
    }

    return 0;
}

// Fill matrix with ones
int deepc_ones_matrix(deepc_matrix* dest, int num_rows, int num_cols) {
    int err = deepc_initialize_matrix(dest, num_rows, num_cols);
    if (err) {
        return err;
    }

    for (int i = 0; i < num_rows * num_cols; ++i) {
        dest->data[i] = 1.0f;
    }

    return 0;
}

// Fills matrix with random values between 0.0f and 1.0f
int deepc_rand_matrix(deepc_matrix* dest, int seed, int num_rows, int num_cols)
{
    int err = deepc_initialize_matrix(dest, num_rows, num_cols);
    if (err) {
        return err;
    }

    srand(seed);
    for (int i = 0; i < num_rows * num_cols; ++i) {
        dest->data[i] = (float)rand() / RAND_MAX;
    }
    
    return 0;
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
int deepc_matrix_row(deepc_matrix* dest, deepc_matrix matrix, 
    int row_pos) 
{
    int err = deepc_initialize_matrix(dest, 1, matrix.num_cols);
    if (err) {
        return err;
    }
    
    for (int j = 0; j < matrix.num_cols; ++j) {
        DEEPC_MATRIX_AT(*dest, 0, j) = DEEPC_MATRIX_AT(*dest, row_pos, j);
    }
    
    return 0;
}

// Get a specific column as a new rows x 1 matrix
Matrix* get_col(const Matrix *m, int col_index) {
    MATRIX_CHECK(m != NULL, "Matrix is NULL");
    MATRIX_CHECK(col_index >= 0 && col_index < m->cols, "Column index out of bounds");
    
    Matrix *col = create_matrix(m->rows, 1);
    
    for (int i = 0; i < m->rows; i++) {
        col->data[i][0] = m->data[i][col_index];
    }
    
    return col;
}

// Set a specific row from a 1 x cols matrix
void set_row(Matrix *m, int row_index, const Matrix *row_data) {
    MATRIX_CHECK(m != NULL, "Matrix is NULL");
    MATRIX_CHECK(row_data != NULL, "Row data is NULL");
    MATRIX_CHECK(row_index >= 0 && row_index < m->rows, "Row index out of bounds");
    MATRIX_CHECK(row_data->rows == 1 && row_data->cols == m->cols, 
                "Row data dimensions don't match");
    
    for (int j = 0; j < m->cols; j++) {
        m->data[row_index][j] = row_data->data[0][j];
    }
}

// Set a specific column from a rows x 1 matrix
void set_col(Matrix *m, int col_index, const Matrix *col_data) {
    MATRIX_CHECK(m != NULL, "Matrix is NULL");
    MATRIX_CHECK(col_data != NULL, "Column data is NULL");
    MATRIX_CHECK(col_index >= 0 && col_index < m->cols, "Column index out of bounds");
    MATRIX_CHECK(col_data->cols == 1 && col_data->rows == m->rows, 
                "Column data dimensions don't match");
    
    for (int i = 0; i < m->rows; i++) {
        m->data[i][col_index] = col_data->data[i][0];
    }
}

// Element-wise addition
Matrix* add(const Matrix *a, const Matrix *b) {
    MATRIX_CHECK(a != NULL && b != NULL, "Matrices cannot be NULL");
    MATRIX_CHECK(a->rows == b->rows && a->cols == b->cols, 
                "Matrix dimensions don't match for addition");
    
    Matrix *result = create_matrix(a->rows, a->cols);
    
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            result->data[i][j] = a->data[i][j] + b->data[i][j];
        }
    }
    
    return result;
}

// Element-wise subtraction
Matrix* subtract(const Matrix *a, const Matrix *b) {
    MATRIX_CHECK(a != NULL && b != NULL, "Matrices cannot be NULL");
    MATRIX_CHECK(a->rows == b->rows && a->cols == b->cols, 
                "Matrix dimensions don't match for subtraction");
    
    Matrix *result = create_matrix(a->rows, a->cols);
    
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            result->data[i][j] = a->data[i][j] - b->data[i][j];
        }
    }
    
    return result;
}

// Element-wise multiplication (Hadamard product)
Matrix* multiply(const Matrix *a, const Matrix *b) {
    MATRIX_CHECK(a != NULL && b != NULL, "Matrices cannot be NULL");
    MATRIX_CHECK(a->rows == b->rows && a->cols == b->cols, 
                "Matrix dimensions don't match for element-wise multiplication");
    
    Matrix *result = create_matrix(a->rows, a->cols);
    
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            result->data[i][j] = a->data[i][j] * b->data[i][j];
        }
    }
    
    return result;
}

Matrix* dot(const Matrix *a, const Matrix *b) {
    if (!a || !b) {
        printf("ERROR: One or both matrices are NULL in dot product\n");
        return NULL;
    }
    
    if (a->cols != b->rows) {
        printf("ERROR: Matrix dimension mismatch in dot product: ");
        printf("A(%d,%d) * B(%d,%d) - A cols (%d) != B rows (%d)\n", 
               a->rows, a->cols, b->rows, b->cols, a->cols, b->rows);
        return NULL;
    }
    
    Matrix *result = create_matrix(a->rows, b->cols);
    if (!result) {
        printf("ERROR: Failed to create result matrix in dot product\n");
        return NULL;
    }
    
    // Initialize to zero
    for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->cols; j++) {
            result->data[i][j] = 0.0;
        }
    }
    
    // Perform matrix multiplication
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            double sum = 0.0;
            for (int k = 0; k < a->cols; k++) {
                sum += a->data[i][k] * b->data[k][j];
            }
            result->data[i][j] = sum;
        }
    }
    
    return result;
}

// Scalar multiplication
Matrix* scale(const Matrix *a, double scalar) {
    MATRIX_CHECK(a != NULL, "Matrix cannot be NULL");
    
    Matrix *result = create_matrix(a->rows, a->cols);
    
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            result->data[i][j] = a->data[i][j] * scalar;
        }
    }
    
    return result;
}

// Matrix transpose
Matrix* transpose(const Matrix *a) {
    MATRIX_CHECK(a != NULL, "Matrix cannot be NULL");
    
    Matrix *result = create_matrix(a->cols, a->rows);
    
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            result->data[j][i] = a->data[i][j];
        }
    }
    
    return result;
}

// Apply function to each element
Matrix* apply_function(const Matrix *a, double (*func)(double)) {
    MATRIX_CHECK(a != NULL, "Matrix cannot be NULL");
    MATRIX_CHECK(func != NULL, "Function pointer cannot be NULL");
    
    Matrix *result = create_matrix(a->rows, a->cols);
    
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            result->data[i][j] = func(a->data[i][j]);
        }
    }
    
    return result;
}

// In-place operations (more efficient)
void add_inplace(Matrix *a, const Matrix *b) {
    MATRIX_CHECK(a != NULL && b != NULL, "Matrices cannot be NULL");
    MATRIX_CHECK(a->rows == b->rows && a->cols == b->cols, 
                "Matrix dimensions don't match for in-place addition");
    
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            a->data[i][j] += b->data[i][j];
        }
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

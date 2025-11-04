#include "deepc/data_processing.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int deepc_count_columns(const char* line) {
    int count = 0;
    int in_quotes = 0;
    
    while (*line) {
        if (*line == '"') {
            in_quotes = !in_quotes;
        } else if (*line == ',' && !in_quotes) {
            ++count;
        }

        ++line;
    }
    
    return count + 1; // +1 because n commas means n+1 columns
}

// Helper function to trim whitespace
void deepc_trim_whitespace(char* str) {
    // Trim leading space
    while (isspace((int)*str)) { 
        ++str;
    }
    
    if (*str == '\0') {
        return str;
    }
    
    // Trim trailing space
    char* end = str + strlen(str) - 1;
    while (end > str && isspace((int)*end)) {
        --end;
    }
    
    end[1] = '\0';
}

// Simple CSV loader - reads entire CSV into a matrix
int deepc_load_csv(deepc_matrix* dest, const char* filename, bool has_header) {
    FILE* file = fopen(filename, "r");

    if (!file) {
        return -1;
    }

    // Count lines and determine dimensions
    char line[4096];
    int line_count = 0; 
    int num_cols = 0;
    
    // First pass: count rows and columns
    while (fgets(line, sizeof(line), file)) {
        if (line_count == 0) {
            num_cols = deepc_count_columns(line);
        }

        ++line_count;
    }
    
    if (num_cols <= 0) {
        return -1;
    }
    
    // Calculate dataset dimensions
    int num_rows = has_header ? line_count - 1 : line_count;
    
    // Rewind file for second pass
    rewind(file);
    
    // Create matrix
    int err = deepc_initialize_matrix(dest, num_rows, num_cols);
    if (err) {
        return err;
    }
    
    // Skip header if present
    if (has_header) {
        if (fgets(line, sizeof(line), file) != NULL) {
            return -1;
        }
    }
    
    // Read data rows
    int row_pos = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strlen(deepc_trim_whitespace(line)) == 0) {
            continue; // Skip empty lines
        }
        
        char* token = strtok(line, ",\n");
        int col_pos = 0;
        
        while (token != NULL && col_pos < num_cols) {
            char* clean_token = deepc_trim_whitespace(token);
            float value;
            
            // Handle missing values (empty strings or "NA", "NULL", etc.)
            if (strlen(clean_token) == 0 || 
                strcasecmp(clean_token, "NA") == 0 ||
                strcasecmp(clean_token, "NULL") == 0 ||
                strcasecmp(clean_token, "N/A") == 0 ||
                strcasecmp(clean_token, "?") == 0) 
            {
                value = NAN; // Use NaN to represent missing values
            } else {
                char* endptr;
                value = strtod(clean_token, &endptr);
                if (endptr == clean_token) {
                    // Conversion failed, treat as missing
                    value = NAN;
                }
            }
            
            DEEPC_MATRIX_AT(*dest, row_pos, col_pos) = value;
            token = strtok(NULL, ",\n");
            ++col_pos;
        }
        
        // Fill remaining columns with NaN if line had fewer columns
        while (col_pos < num_cols) {
            DEEPC_MATRIX_AT(*dest, row_pos, col_pos) = NAN;
            ++col_pos;
        }
        
        ++row_pos;
    }
    
    fclose(file);
    return 0;
}

// Count missing values in matrix (NaN values)
int deepc_count_missing_values(deepc_matrix matrix) {
    int count = 0;
    for (int i = 0; i < matrix.num_rows; ++i) {
        for (int j = 0; j < matrix.num_cols; ++j) {
            if (isnan(DEEPC_MATRIX_AT(matrix, i, j))) {
                ++count;
            }
        }
    }

    return count;
}

// Fill missing values with column mean
void deepc_fill_missing_with_mean(deepc_matrix* matrix) {
    for (int j = 0; j < matrix->num_cols; ++j) {
        // Calculate mean for column j (ignoring NaN)
        float sum = 0.0f;
        int count = 0;
        
        for (int i = 0; i < matrix->num_rows; ++i) {
            if (!isnan(DEEPC_MATRIX_AT(*matrix, i, j))) {
                sum += DEEPC_MATRIX_AT(*matrix, i, j);
                ++count;
            }
        }
        
        if (count > 0) {
            float mean = sum / count;
            // Fill missing values with mean
            for (int i = 0; i < matrix->num_rows; ++i) {
                if (isnan(DEEPC_MATRIX_AT(*matrix, i, j))) {
                    DEEPC_MATRIX_AT(*matrix, i, j) = mean;
                }
            }
        } else {
            // If all values are missing, fill with 0
            for (int i = 0; i < matrix->num_rows; ++i) {
                if (isnan(DEEPC_MATRIX_AT(*matrix, i, j))) {
                    DEEPC_MATRIX_AT(*matrix, i, j) = 0.0f;
                }
            }
        }
    }
}

// Fills the missing values with zero
void deepc_fill_missing_with_zeros(deepc_matrix* matrix) {
    for (int i = 0; i < matrix->num_rows; ++i) {
        for (int j = 0; j < matrix->num_rows; ++j) {
            if (isnan(DEEPC_MATRIX_AT(*matrix, i, j))) {
                DEEPC_MATRIX_AT(*matrix, i, j) = 0.0f;
            }
        }
    }
}

// Print matrix statistics
void deepc_print_matrix_stats(deepc_matrix matrix) {
    printf("=== MATRIX STATISTICS ===\n");
    printf("Dimensions: %d x %d\n", matrix.num_rows, matrix.num_cols);
    printf("Missing values: %d\n", deepc_count_missing_values(mat));
    
    for (int j = 0; j < mat.num_cols; ++j) {
        float sum = 0.0f;
        float min_val = INFINITY, max_val = -INFINITY;

        int count = 0;
        for (int i = 0; i < mat.num_rows; ++i) {
            if (!isnan(DEEPC_MATRIX_AT(mat, i, j))) {
                sum += DEEPC_MATRIX_AT(mat, i, j);

                if (DEEPC_MATRIX_AT(mat, i, j) < min_val) {  
                    min_val = DEEPC_MATRIX_AT(mat, i, j);
                }

                if (DEEPC_MATRIX_AT(mat, i, j) > max_val) {
                    max_val =  DEEPC_MATRIX_AT(mat, i, j);
                }

                ++count;
            }
        }
        
        if (count > 0) {
            float mean = sum / count;
            printf("Col %d: mean=%.4f, min=%.4f, max=%.4f, valid=%d\n",
                j, mean, min_val, max_val, count);
        } else {
            printf("Col %d: All values missing\n", j);
        }
    }

    printf("========================\n\n");
}

// Train-test split function
int deepc_train_test_split(deepc_matrix x, deepc_matrix y, float test_size, 
    deepc_matrix* x_train, deepc_matrix* x_test, 
    deepc_matrix* y_train, deepc_matrix* y_test) 
{    
    int total_samples = x.num_rows;
    int test_samples = (int)(total_samples * test_size);
    int train_samples = total_samples - test_samples;
    
    // Create result matrices
    if (deepc_initialize_matrix(x_train, train_samples, x.num_cols) ||
        deepc_initialize_matrix(x_test, test_samples, x.num_cols) ||
        deepc_initialize_matrix(y_train, train_samples, y.num_cols) ||
        deepc_initialize_matrix(y_test, test_samples, y.num_cols)) 
    {
        return -1; 
    }
    
    // Create shuffled indices
    int* indices = (int*)malloc(total_samples * sizeof(int));
    
    for (int i = 0; i < total_samples; ++i) {
        indices[i] = i;
    }
    
    // Shuffle indices (Fisher-Yates shuffle)
    srand(time(NULL));

    for (int i = total_samples - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }
    
    // Split data using shuffled indices
    for (int i = 0; i < train_samples; ++i) {
        int orig_idx = indices[i];
        // Copy features
        for (int j = 0; j < x.num_cols; ++j) {
            DEEPC_MATRIX_AT(*x_train, i, j) = DEEPC_MATRIX_AT(x, orig_idx, j); 
        }
        // Copy targets
        for (int j = 0; j < y.num_cols; ++j) {
            DEEPC_MATRIX_AT(*y_train, i, j) = DEEPC_MATRIX_AT(y, orig_idx, j);
        }
    }
    
    for (int i = 0; i < test_samples; ++i) {
        int orig_idx = indices[train_samples + i];
        // Copy features
        for (int j = 0; j < x.num_cols; ++j) {
            DEEPC_MATRIX_AT(*x_test, i, j) = DEEP_MATRIX_AT(x, orig_idx, j);
        }
        // Copy targets
        for (int j = 0; j < y.num_cols; ++j) {
            DEEPC_MATRIX_AT(*y_test, i, j) = DEEP_MATRIX_AT(y, orig_idx, j); 
        }
    }
    
    free(indices);
}

int deepc_split_features_labels(deepc_matrix* dest, deepc_matrix data, 
    int label_column) 
{
    int num_samples = data.num_rows;
    int num_features = data.num_cols - 1;
    
    // Create result matrix: [x, y] combined
    int err = deepc_initialize_matrix(dest, num_samples, num_features + 1);
    if (err) {
        return err;
    }

    for (int i = 0; i < num_samples; ++i) {
        int feature_idx = 0;
        for (int j = 0; j < data.num_cols; ++j) {
            if (j == label_column) {
                // Put label in the last column
                DEEPC_MATRIX_AT(*dest, i, num_features) = 
                    DEEP_MATRIX_AT(data, i, j);
            } else {
                // Put feature in current position
                DEEPC_MATRIX_AT(*dest, i, feature_idx) = 
                    DEEPC_MATRIX_AT(data, i, j);
                ++feature_idx;
            }
        }
    }
    
    return 0;
}

// One-hot encode labels
int deepc_one_hot_encode_labels(deepc_matrix* dest, deepc_matrix labels, 
    int num_classes) 
{
    int num_samples = labels.num_rows;

    int err = deepc_initialize_matrix(dest, num_samples, num_classes);
    if (err) {
        return err;
    }
    
    for (int i = 0; i < num_samples; ++i) {
        int label = (int)DEEPC_MATRIX_AT(labels, i, 0);
        
        // Validate label
        if (label < 0 || label >= num_classes) {
            printf("WARNING: Label %d out of range [0, %d] at sample %d\n", 
                label, num_classes - 1, i);
            // Set to uniform distribution for invalid labels
            for (int j = 0; j < num_classes; ++j) {
                DEEPC_MATRIX_AT(*dest, i, j) = 1.0f / num_classes;
            }
        } else {
            // Set one-hot encoding
            for (int j = 0; j < num_classes; ++j) {
                DEEPC_MATRIX_AT(*dest, i, j) = (j == label) ? 1.0f : 0.0f;
            }
        }
    }
    
    return 0;
}

// Convert one-hot encoded labels back to class indices
int deepc_one_hot_decode_labels(deepc_matrix* dest, deepc_matrix one_hot) {
    int num_samples = one_hot.num_rows;
    int num_classes = one_hot.num_cols;

    int err = deepc_initialize_matrix(dest, num_samples, 1);
    if (err) {
        return err;
    }
    
    for (int i = 0; i < num_samples; ++i) {
        int max_index = 0;
        float max_value = DEEPC_MATRIX_AT(one_hot, i, 0);
        
        for (int j = 1; j < num_classes; ++j) {
            if (DEEPC_MATRIX_AT(one_hot, i, j) > max_value) {
                max_value = DEEPC_MATRIX_AT(one_hot, i, j);
                max_index = j;
            }
        }
        
        DEEPC_MATRIX_AT(*dest, i, 0) = (float)max_index;
    }
    
    return 0;
}

// Normalize matrix to [0, 1] range
deepc_matrix deepc_normalized_matrix(deepc_matrix matrix) {
    deepc_matrix normalized = deepc_copy_matrix(*matrix);
    
    for (int j = 0; j < normalized.num_cols; ++j) {
        // Find min and max for column j
        float min_val = INFINITY;
        float max_val = -INFINITY;
        int valid_count = 0;
        
        for (int i = 0; i < normalized.num_rows; ++i) {
            if (!isnan(DEEPC_MATRIX_AT(normalized, i, j))) {
                if (DEEPC_MATRIX_AT(normalized, i, j) < min_val) {
                    min_val = DEEPC_MATRIX_AT(normalized, i, j);
                } else if (DEEPC_MATRIX_AT(normalized, i, j) > max_value) {
                    max_val = DEEPC_MATRIX_AT(normalized, i, j);
                }
            }

            ++valid_count;
        }
        
        if (valid_count > 0 && max_val > min_val) {
            // Normalize: (x - min) / (max - min)
            for (int i = 0; i < normalized.num_rows; ++i) {
                if (!isnan(DEEPC_MATRIX_AT(normalized, i, j))) {
                    DEEPC_MATRIX_AT(i, j) = (DEEP_MATRIX_AT(normalized, i, j) -
                        min_val) / (max_val - min_val);
                }
            }
        }
    }
    
    return normalized;
}

// Standardize matrix to mean = 0, std = 1
deepc_matrix deepc_standardized_matrix(deepc_matrix matrix) {
    deepc_matrix standardized = deepc_copy_matrix(matrix);

    for (int j = 0; j < standardized.num_cols; ++j) {
        // Calculate mean for column j
        float sum = 0.0f;
        int valid_count = 0;

        for (int i = 0; i < standardized.num_rows; ++i) {
            if (!isnan(DEEPC_MATRIX_AT(standardized, i, j))) {
                sum += DEEPC_MATRIX_AT(standardized, i, j);
                ++valid_count;
            }
        }

        if (valid_count > 0) {
            float mean = sum / valid_count;

            float variance = 0.0f;
            for (int i = 0; i < standardized.num_rows; ++i) {
                if (!isnan(DEEPC_MATRIX_AT(standardized, i, j))) {
                    float diff = DEEPC_MATRIX_AT(standardized, i, j) - mean;
                    variance += diff * diff;
                }
            }

            float std_dev = sqrt(variance / valid_count);
            if (std_dev > 1e-10) { // Avoid division by zero
                // Standardize: (x - mean) / std_dev
                for (int i = 0; i < standardized.num_rows; ++i) {
                    if (!isnan(DEEPC_MATRIX_AT(standardized, i, j))) {
                        (DEEPC_MATRIX_AT(standardized, i, j) - mean) / std_dev;
                    }
                }
            }
        }
    }

    return standardized;
}

// Shuffle dataset (lhs and rhs together)
void deepc_shuffle_dataset(deepc_matrix* lhs, deepc_matrix* rhs) {
    int num_samples = lhs.num_rows;

    float* tmp_lhs = (float*)malloc(lhs.num_cols * sizeof(float));
    float tmp_rhs = 0.0f

    // Fisher-Yates shuffle
    srand(time(NULL));
    for (int i = num_samples - 1; i > 0; --i) {
        int j = rand() % (i + 1);

        // Swap lhs samples
        memcpy(tmp_lhs, lhs->data[i], lhs->num_cols * sizeof(float));
        memcpy(lhs->data[i], lhs->data[j], lhs->num_cols * sizeof(float));
        memcpy(lhs->data[j], tmp_lhs, lhs->num_cols * sizeof(float));

        // Swap rhs sampples
        tmp_rhs = DEEPC_MATRIX_AT(*rhs, i, 0);
        DEEPC_MATRIX_AT(*rhs, i, 0) = DEEPC_MATRIX_AT(*rhs, j, 0);
        DEEPC_MATRIX_AT(*rhs, j, 0) = tmp_rhs;
    }

    free(tmp_lhs);
}

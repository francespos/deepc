#ifndef DEEPC_TENSOR_MATRIX_HPP
#define DEEPC_TENSOR_MATRIX_HPP

#include <cstddef>

namespace deepc {

class Matrix {
public:
    explicit Matrix(std::size_t rows, std::size_t cols);

    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);

    Matrix(Matrix&& other) noexcept;
    Matrix& operator=(Matrix&& other) noexcept;

    ~Matrix() noexcept;

    float* operator[](std::size_t row);
    const float* operator[](std::size_t row) const;

    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;

    std::size_t size() const noexcept { return rows_ * cols_; }
    std::size_t rows() const noexcept { return rows_; }
    std::size_t cols() const noexcept { return cols_; }

    float* data() { return data_; }
    const float* data() const { return data_; }
private:
    std::size_t rows_;
    std::size_t cols_;
    float* data_;
};

} // namespace deepc

#endif // DEEPC_TENSOR_MATRIX_HPP
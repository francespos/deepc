#include <deepc/tensor/matrix.hpp>
#include <deepc/scalar/precision.hpp>
#include <algorithm>

namespace deepc {

Matrix::Matrix(std::size_t rows, std::size_t cols) 
    : rows_(rows), cols_(cols), data_(new float[rows * cols]) {}

Matrix::Matrix(const Matrix& other) 
    : rows_(other.rows_), cols_(other.cols_)
    , data_(new float[other.rows_ * other.cols_]) {
    std::copy(other.data_, other.data_ + rows_ * cols_, data_);
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) {
        return *this;
    }

    if (rows_ != other.rows_ || cols_ != other.cols_) {
        delete[] data_;
        rows_ = other.rows_;
        cols_ = other.cols_;
        data_ = new float[rows_ * cols_];
    }

    std::copy(other.data_, other.data_ + rows_ * cols_, data_);
    return *this;
}

Matrix::Matrix(Matrix&& other) noexcept 
    : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {
    other.rows_ = 0;
    other.cols_ = 0;
    other.data_ = nullptr;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        
        rows_ = other.rows_;
        other.rows_ = 0;

        cols_ = other.cols_;
        other.cols_ = 0;

        data_ = other.data_;
        other.data_ = nullptr;
    }

    return *this;
}

Matrix::~Matrix() noexcept { delete[] data_; }

bool Matrix::operator==(const Matrix& other) const {
    return (rows_ != other.rows_ || cols_ != other.cols_) ? false : 
        std::equal(data_, data_ + rows_ * cols_, other.data_, 
            deepc::detail::equal);
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}

} // namespace deepc
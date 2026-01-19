#include <deepc/Matrix.hpp>
#include <deepc/float.hpp>
#include <algorithm>
#include <cassert>
#include <cmath>

namespace deepc {

Matrix::Matrix(std::size_t nrows, std::size_t ncols) 
    : nrows_(nrows), ncols_(ncols), data_(new float[nrows * ncols]) {}

Matrix::Matrix(const Matrix& other) 
    : nrows_(other.nrows_), ncols_(other.ncols_)
    , data_(new float[nrows_ * ncols_]) {
    std::copy(other.data_, other.data_ + nrows_ * ncols_, data_);
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        delete[] data_;

        nrows_ = other.nrows_;
        ncols_ = other.ncols_;

        data_ = new float[nrows_, ncols_];
        std::copy(other.data_, other.data_ + nrows_ * ncols_, data_);
    }

    return *this;
}

Matrix::Matrix(Matrix&& other) noexcept 
    : nrows_(other.nrows_), ncols_(other.ncols_)
    , data_(other.data_) {
    other.nrows_ = other.ncols_ = 0;
    other.data_ = nullptr;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        
        nrows_ = other.nrows_;
        other.nrows_ = 0;

        ncols_ = other.ncols_;
        other.ncols_ = 0;

        data_ = other.data_;
        other.data_ = nullptr;
    }

    return *this;
}

Matrix::~Matrix() { delete[] data_; }

float* Matrix::operator[](std::size_t row_pos) {
    assert(row_pos < nrows_);
    return data_ + row_pos * ncols_;
}

const float* Matrix::operator[](std::size_t row_pos) const {
    assert(row_pos < nrows_);
    return data_ + row_pos * ncols_;
}

bool Matrix::operator==(const Matrix& other) const noexcept {
    if (nrows_ != other.nrows_ || ncols_ != other.ncols_) {
        return false;
    }

    for (std::size_t i = 0; i < nrows_ * ncols_; ++i) {
        if (std::abs(data_[i] - other.data_[i]) > EPSILON) {
            return false;
        }
    }

    return true;
}

bool Matrix::operator!=(const Matrix& other) const noexcept {
    if (nrows_ != other.nrows_ || ncols_ != other.ncols_) {
        return true;
    }

    for (size_t i = 0; i < nrows_ * ncols_; ++i) {
        if (abs(data_[i] - other.data_[i]) > EPSILON) {
            return true;
        }
    }

    return false;
}

} // namespace deepc
#include <deepc/Matrix.hpp>
#include <deepc/float.hpp>
#include <cassert>
#include <cmath>

namespace deepc {

Matrix::Matrix(std::initializer_list<float> il, size_t nr, size_t nc)
    : data_(new float[nr * nc]), nr_(nr), nc_(nc) {
    assert(il.size() == nr * nc);

    float* p = data_;
    for (auto elem : il) {
        *(p++) = elem;
    }
}

Matrix::Matrix(const Matrix& other) 
    : data_(new float[other.nr_ * other.nc_]), nr_(other.nr_), nc_(other.nc_) {
    for (size_t i = 0; i < nr_ * nc_; ++i) {
        data_[i] = other.data_[i];
    }
}

Matrix::Matrix(Matrix&& other) 
    : data_(other.data_), nr_(other.nr_), nc_(other.nc_) {
    other.data_ = nullptr;
    other.nr_ = other.nc_ = 0;
}

Matrix::~Matrix() { delete[] data_; }

bool Matrix::operator==(const Matrix& other) const {
    assert(nr_ == other.nr_ && nc_ == other.nc_);

    for (size_t i = 0; i < nr_ * nc_; ++i) {
        if (abs(data_[i] - other.data_[i]) > EPSILON) {
            return false;
        }
    }

    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    assert(nr_ == other.nr_ && nc_ == other.nc_);

    for (size_t i = 0; i < nr_ * nc_; ++i) {
        if (abs(data_[i] - other.data_[i]) > EPSILON) {
            return true;
        }
    }

    return false;
}

} // namespace deepc
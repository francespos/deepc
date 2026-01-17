#ifndef DEEPC_MATRIX_HPP
#define DEEPC_MATRIX_HPP

#include <deepc/Vector.hpp>
#include <cstddef>
#include <initializer_list>

namespace deepc {

class Matrix {
public:
    Matrix(std::initializer_list<float> il, size_t nr, size_t nc);

    Matrix(const Matrix& other);
    Matrix(Matrix&& other);

    ~Matrix();

    float& operator()(size_t r, size_t c) { return data_[r * nc_ + c]; }
    float operator()(size_t r, size_t c) const { return data_[r * nc_ + c]; }

    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;

    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(float scalar);
    Matrix& operator/=(float scalar);

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(float other) const;
    Matrix operator/(float other) const;

    Matrix operator*(const Matrix& other) const;
    Vector operator*(const Vector& other) const;

    float* data() { return data_; }
    const float* data() const { return data_; }
    size_t num_rows() const { return nr_; }
    size_t num_cols() const { return nc_; }
private:
    float* data_;
    size_t nr_;
    size_t nc_;
};

} // namespace deepc

#endif // DEEPC_MATRIX_HPP
#ifndef DEEPC_MATRIX_HPP
#define DEEPC_MATRIX_HPP

#include <cstddef>

namespace deepc {

class Matrix {
public:
    Matrix(std::size_t nrows, std::size_t ncols);

    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);

    Matrix(Matrix&& other) noexcept;
    Matrix& operator=(Matrix&& other) noexcept;

    ~Matrix() noexcept;

    float* operator[](std::size_t row_pos);
    const float* operator[](std::size_t row_pos) const;

    bool operator==(const Matrix& other) const noexcept;
    bool operator!=(const Matrix& other) const noexcept;

    std::size_t nrows() const noexcept { return nrows_; }
    std::size_t ncols() const noexcept { return ncols_; }

    float* data() { return data_; }
    const float* data() const { return data_; }
private:
    std::size_t nrows_;
    std::size_t ncols_;
    float* data_;
};

} // namespace deepc

#endif // DEEPC_MATRIX_HPP
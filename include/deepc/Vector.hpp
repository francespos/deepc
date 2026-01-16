#ifndef DEEPC_VECTOR_HPP
#define DEEPC_VECTOR_HPP

#include <cstddef>
#include <initializer_list>

namespace deepc {

class Vector {
public:
    Vector(std::initializer_list<float> il);

    Vector(const Vector& other);
    Vector(Vector&& other);

    ~Vector();

    float& operator[](size_t pos) { return data_[pos]; }
    float operator[](size_t pos) const { return data_[pos]; }

    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const;

    Vector& operator+=(const Vector& other);
    Vector& operator-=(const Vector& other);
    Vector& operator*=(float scalar);
    Vector& operator/=(float scalar);

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(float scalar) const;
    Vector operator/(float scalar) const;

    float operator*(const Vector& other) const;

    float* data() { return data_; }
    const float* data() const { return data_; }
    size_t size() const { return size_; }
private:
    float* data_;
    size_t size_;
};

Vector operator*(float scalar, const Vector& v) { return v * scalar; }

} // namespace deepc

#endif // DEEPC_VECTOR_HPP
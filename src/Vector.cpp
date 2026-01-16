#include <deepc/Vector.hpp>
#include <cassert>

namespace deepc {

Vector::Vector(std::initializer_list<float> il)
    : data_(new float[il.size()]), size_(il.size()) {
    float* data_ptr = data_;   

    for (float entry : il) {
        *data_ptr = entry;
        ++data_ptr; 
    }
}

Vector::Vector(const Vector& other)
    : data_(new float[other.size_]), size_(other.size_) {
    for (size_t i = 0; i < other.size_; ++i) {
        data_[i] = other.data_[i];
    }
}

Vector::Vector(Vector&& other) 
    : data_(other.data_), size_(other.size_) {
    other.data_ = nullptr;
    other.size_ = 0;
}

Vector::~Vector() {
    delete[] data_;
}

bool Vector::operator==(const Vector& other) const {
    assert(size_ == other.size_);
    
    for (size_t i = 0; i < size_; ++i) {
        if (data_[i] != other.data_[i]) {
            return false;
        }
    }

    return true;
}

bool Vector::operator!=(const Vector& other) const {
    assert(size_ == other.size_);

    for (size_t i = 0; i < size_; ++i) {
        if (data_[i] != other.data_[i]) {
            return true;
        }
    }

    return false;
}

Vector& Vector::operator+=(const Vector& other) {
    assert(size_ == other.size_);

    for (size_t i = 0; i < size_; ++i) {
        data_[i] += other.data_[i];
    }

    return *this;
}

Vector& Vector::operator-=(const Vector& other) {
    assert(size_ == other.size_);

    for (size_t i = 0; i < size_; ++i) {
        data_[i] -= other.data_[i];
    }

    return *this;
}

Vector& Vector::operator*=(float scalar) {
    for (size_t i = 0; i < size_; ++i) {
        data_[i] *= scalar;
    }

    return *this;
}

Vector& Vector::operator/=(float scalar) {
    for (size_t i = 0; i < size_; ++i) {
        data_[i] /= scalar;
    }

    return *this;
}

Vector Vector::operator+(const Vector& other) const {
    Vector rslt(*this);
    rslt += other;
    return rslt;
}

Vector Vector::operator-(const Vector& other) const {
    Vector rslt(*this);
    rslt -= other;
    return rslt;
}

Vector Vector::operator*(float scalar) const {
    Vector rslt(*this);
    rslt *= scalar;
    return rslt;
}

Vector Vector::operator/(float scalar) const {
    Vector rslt(*this);
    rslt /= scalar;
    return rslt;
}

float Vector::operator*(const Vector& other) const {
    assert(size_ == other.size_);

    float rslt = 0.0f;
    for (size_t i = 0; i < size_; ++i) {
        rslt += data_[i] * other.data_[i];
    }

    return rslt;
}

} // namespace deepc
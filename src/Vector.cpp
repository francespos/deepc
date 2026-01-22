#include <deepc/Vector.hpp>
#include <deepc/float.hpp>
#include <algorithm>
#include <cassert>

namespace deepc {

Vector::Vector(std::size_t size) 
    : size_(size), data_(new float[size]) {}

Vector::Vector(const Vector& other)
    : size_(other.size_), data_(new float[other.size_]) 
{
    std::copy(other.data_, other.data_ + size_, data_);
}

Vector& Vector::operator=(const Vector& other) {
    if (this == &other) {
        return *this;
    }
    
    if (size_ != other.size_) {
        delete[] data_;
        size_ = other.size_;
        data_ = new float[size_];
    }

    std::copy(other.data_, other.data_ + size_, data_);
    return *this;
}

Vector::Vector(Vector&& other) noexcept 
    : size_(other.size_), data_(other.data_) 
{
    other.size_ = 0;
    other.data_ = nullptr;
}

Vector& Vector::operator=(Vector&& other) noexcept {
    if (this != &other) {
        delete[] data_;

        size_ = other.size_;
        other.size_ = 0;

        data_ = other.data_;
        other.data_ = nullptr;
    }

    return *this;
}

Vector::~Vector() noexcept { delete[] data_; }

float& Vector::operator[](std::size_t pos) {
    assert(pos < size_);
    return data_[pos];
}

float Vector::operator[](std::size_t pos) const {
    assert(pos < size_);
    return data_[pos];
}

bool Vector::operator==(const Vector& other) const {
    return (size_ != other.size_) ? false : 
        std::equal(data_, data_ + size_, other.data_, deepc::equal);
}

bool Vector::operator!=(const Vector& other) const {
    return !(*this == other);
}

} // namespace deepc
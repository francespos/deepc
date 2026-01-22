#ifndef DEEPC_VECTOR_HPP
#define DEEPC_VECTOR_HPP

#include <cstddef>

namespace deepc {

class Vector {
public:
    explicit Vector(std::size_t size);

    Vector(const Vector& other);
    Vector& operator=(const Vector& other);

    Vector(Vector&& other) noexcept;
    Vector& operator=(Vector&& other) noexcept;

    ~Vector() noexcept;

    float& operator[](std::size_t pos);
    float operator[](std::size_t pos) const;

    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const;

    std::size_t size() const noexcept { return size_; }

    float* data() { return data_; }
    const float* data() const { return data_; }
private:
    std::size_t size_;
    float* data_;
};

} // namespace deepc

#endif // DEEPC_VECTOR_HPP
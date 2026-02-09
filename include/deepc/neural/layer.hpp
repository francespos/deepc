#ifndef DEEPC_NEURAL_LAYER_HPP
#define DEEPC_NEURAL_LAYER_HPP

#include <deepc/tensor/vector.hpp>

namespace deepc {

struct Layer {
    virtual ~Layer() noexcept = default;

    virtual Layer* clone() const = 0;

    virtual std::size_t output_size() const = 0;
    virtual std::size_t input_size() const = 0;

    virtual Vector forward(const Vector& input) = 0;
    virtual Vector backward(const Vector& delta) const = 0;

    virtual void update(const Vector& input, const Vector& delta, 
        float learning_rate) = 0;
};

} // namespace deepc

#endif // DEEPC_NEURAL_LAYER_HPP
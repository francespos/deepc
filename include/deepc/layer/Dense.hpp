#ifndef DEEPC_LAYER_DENSE_HPP
#define DEEPC_LAYER_DENSE_HPP

#include <deepc/tensor/Vector.hpp>
#include <deepc/tensor/Matrix.hpp>
#include <deepc/activation/Activation.hpp>
#include <deepc/scalar/Generator.hpp>

namespace deepc {
namespace layer {

class Dense {
public:
    explicit Dense(std::size_t size, std::size_t input, 
        const Activation& activation, scalar::Generator& weight_generator, 
        scalar::Generator& bias_generator);

    Vector forward(const Vector& input);
    Vector backward(const Vector& delta) const;
    void update(const Vector& input, const Vector& delta, float learning_rate);
private:
    Matrix weights_;
    Vector biases_;
    Vector z_;
    Activation activation_;
};

} // namespace layer
} // namespace deepc

#endif // DEEPC_LAYER_DENSE_HPP
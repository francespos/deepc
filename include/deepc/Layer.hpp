#ifndef DEEPC_LAYER_HPP
#define DEEPC_LAYER_HPP

#include <deepc/Vector.hpp>
#include <deepc/Matrix.hpp>
#include <deepc/Activation.hpp>

namespace deepc {

class Layer {
public:
    Layer(std::size_t output_size, std::size_t input_size, 
        const Activation& activation);

    Matrix weights() const { return weights_; }
    Vector biases() const { return biases_; }

    Vector z() const { return z_; }
    Activation activation() const { return activation_; }

    Vector forward(const Vector& input);
    Vector backward(const Vector& forward_delta) const;
    void update(const Vector& input, const Vector& delta, float learning_rate);
private:
    Matrix weights_;
    Vector biases_;

    Vector z_;
    Activation activation_;
};

} // namespace deepc

#endif // DEEPC_LAYER_HPP
#ifndef DEEPC_LAYER_HPP
#define DEEPC_LAYER_HPP

#include <deepc/Vector.hpp>
#include <deepc/Matrix.hpp>
#include <deepc/Activation.hpp>

namespace deepc {

class Layer {
public:
    explicit Layer(std::size_t size, std::size_t input, 
        const Activation& activation);

    const Matrix& weights() const { return weights_; }
    const Vector& biases() const { return biases_; }

    const Vector& z() const { return z_; }
    const Activation& activation() const { return activation_; }

    Vector forward(const Vector& input);
    Vector backward(const Vector& delta) const;
    void update(const Vector& input, const Vector& delta, float learning_rate);
private:
    Matrix weights_;
    Vector biases_;

    Vector z_;
    Activation activation_;
};

} // namespace deepc

#endif // DEEPC_LAYER_HPP
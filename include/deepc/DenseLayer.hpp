#ifndef DEEPC_DENSE_LAYER_HPP
#define DEEPC_DENSE_LAYER_HPP

#include <deepc/Vector.hpp>
#include <deepc/Matrix.hpp>
#include <deepc/Activation.hpp>
#include <deepc/FloatInitializer.hpp>

namespace deepc {

class DenseLayer {
public:
    explicit DenseLayer(std::size_t size, std::size_t input, 
        const Activation& activation, 
        FloatInitializer& weight_initializer, 
        FloatInitializer& bias_initializer);

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

#endif // DEEPC_DENSE_LAYER_HPP
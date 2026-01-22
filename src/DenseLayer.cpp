#include <deepc/DenseLayer.hpp>
#include <algorithm>

namespace deepc {

DenseLayer::DenseLayer(std::size_t size, std::size_t input, 
    const Activation& activation, 
    FloatInitializer& weight_initializer, 
    FloatInitializer& bias_initializer) 
    : weights_(size, input) , biases_(size), z_(size)
    , activation_(activation) 
{
    for (std::size_t i = 0; i < weights_.size(); ++i) {
        weights_.data()[i] = weight_initializer.generate();
    }

    for (std::size_t i = 0; i < biases_.size(); ++i) {
        biases_[i] = bias_initializer.generate();
    }
}

Vector DenseLayer::forward(const Vector& input) {
    Vector output(weights_.rows());

    for (std::size_t i = 0; i < weights_.rows(); ++i) {
        z_[i] = biases_[i];

        for (std::size_t j = 0; j < weights_.cols(); ++j) {
            z_[i] += weights_[i][j] * input[j];
        }

        output[i] = activation_.function(z_[i]);
    }

    return output;
}

Vector DenseLayer::backward(const Vector& delta) const {
    Vector rslt(weights_.cols());
    std::fill(rslt.data(), rslt.data() + rslt.size(), 0.0f);

    for (std::size_t i = 0; i < weights_.rows(); ++i) {
        for (std::size_t j = 0; j < weights_.cols(); ++j) {
            rslt[j] += weights_[i][j] * delta[i] * 
                activation_.derivative(z_[i]);
        }
    }

    return rslt;
}

void DenseLayer::update(const Vector& input, const Vector& delta, 
    float learning_rate) 
{
    for (std::size_t i = 0; i < weights_.rows(); ++i) {
        for (std::size_t j = 0; j < weights_.cols(); ++j) {
            weights_[i][j] -= learning_rate * input[j] * delta[i];
        }

        biases_[i] -= learning_rate * delta[i];
    }
}

} // namespace deepc
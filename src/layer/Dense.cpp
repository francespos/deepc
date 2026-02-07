#include <deepc/layer/Dense.hpp>
#include <algorithm>

namespace deepc {
namespace layer {

Dense::Dense(std::size_t size, std::size_t input, const Activation& activation, 
    scalar::Generator& weight_generator, scalar::Generator& bias_generator) 
    : weights_(size, input), biases_(size), z_(size), activation_(activation) {
    for (std::size_t i = 0; i < weights_.size(); ++i) {
        weights_.data()[i] = weight_generator.generate();
    }

    for (std::size_t i = 0; i < biases_.size(); ++i) {
        biases_[i] = bias_generator.generate();
    }
}

Vector Dense::forward(const Vector& input) {
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

Vector Dense::backward(const Vector& delta) const {
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

void Dense::update(const Vector& input, const Vector& delta, 
    float learning_rate) {
    for (std::size_t i = 0; i < weights_.rows(); ++i) {
        for (std::size_t j = 0; j < weights_.cols(); ++j) {
            weights_[i][j] -= learning_rate * input[j] * delta[i];
        }

        biases_[i] -= learning_rate * delta[i];
    }
}

} // namespace layer
} // namespace deepc
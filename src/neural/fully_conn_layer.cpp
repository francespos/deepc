#include <deepc/neural/fully_conn_layer.hpp>
#include <deepc/functional/activations.hpp>
#include <memory>
#include <algorithm>

namespace deepc {

FullyConnLayer::FullyConnLayer(std::size_t size, std::size_t input, 
    const std::string& activation, const NumberGenerator& weight_initializer) 
    : weights_(size, input), biases_(size), z_(size)
    , activation_function_(detail::activation_function.at(activation))
    , activation_derivative_(detail::activation_derivative.at(activation)) {
    std::unique_ptr<NumberGenerator> weight_generator(
        weight_initializer.clone());

    for (std::size_t i = 0; i < weights_.size(); ++i) {
        weights_.data()[i] = weight_generator->generate();
    }
}

Vector FullyConnLayer::forward(const Vector& input) {
    Vector output(weights_.rows());

    for (std::size_t i = 0; i < weights_.rows(); ++i) {
        z_[i] = biases_[i];

        for (std::size_t j = 0; j < weights_.cols(); ++j) {
            z_[i] += weights_[i][j] * input[j];
        }

        output[i] = activation_function_(z_[i]);
    }

    return output;
}

Vector FullyConnLayer::backward(const Vector& delta) const {
    Vector rslt(weights_.cols());
    std::fill(rslt.data(), rslt.data() + rslt.size(), 0.0f);

    for (std::size_t i = 0; i < weights_.rows(); ++i) {
        for (std::size_t j = 0; j < weights_.cols(); ++j) {
            rslt[j] += weights_[i][j] * delta[i] * 
                activation_derivative_(z_[i]);
        }
    }

    return rslt;
}

void FullyConnLayer::update(const Vector& input, const Vector& delta, 
    float learning_rate) {
    for (std::size_t i = 0; i < weights_.rows(); ++i) {
        for (std::size_t j = 0; j < weights_.cols(); ++j) {
            weights_[i][j] -= learning_rate * input[j] * delta[i];
        }

        biases_[i] -= learning_rate * delta[i];
    }
}

} // namespace deepc
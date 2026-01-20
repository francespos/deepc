#include <deepc/Layer.hpp>
#include <algorithm>

namespace deepc {

Layer::Layer(std::size_t output_size, std::size_t input_size, 
    const Activation& activation) 
    : weights_(output_size, input_size) , biases_(output_size), z_(output_size)
    , activation_(activation) {}

Vector Layer::forward(const Vector& input) {
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

Vector Layer::backward(const Vector& forward_delta) const {
    Vector delta(weights_.cols());
    std::fill(delta.data(), delta.data() + delta.size(), 0.0f);

    for (std::size_t i = 0; i < weights_.rows(); ++i) {
        for (std::size_t j = 0; j < weights_.cols(); ++j) {
            delta[j] += weights_[i][j] * forward_delta[i] * 
                activation_.derivative(z_[i]);
        }
    }

    return delta;
}

void Layer::update(const Vector& input, const Vector& delta, 
    float learning_rate) {
    for (std::size_t i = 0; i < weights_.rows(); ++i) {
        for (std::size_t j = 0; j < weights_.cols(); ++j) {
            weights_[i][j] -= learning_rate * input[j] * delta[i];
        }

        biases_[i] -= learning_rate * delta[i];
    }
}

} // namespace deepc
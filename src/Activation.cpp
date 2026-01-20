#include <deepc/Activation.hpp>
#include <cmath>

namespace deepc {

const Activation SIGMOID = { sigmoid, sigmoid_derivative };
const Activation RELU = { relu, relu_derivative };
const Activation TANH = { std::tanhf, tanh_derivative };

float sigmoid(float x) {
    return 1.0f / (1.0f + std::exp(x));
}

float sigmoid_derivative(float x) {
    return sigmoid(x) * (1.0f - sigmoid(x));
}

float relu(float x) {
    return std::fmax(0.0f, x);
}

float relu_derivative(float x) {
    return x > 0.0f ? 1.0f : 0.0f;
}

float tanh_derivative(float x) {
    return 1.0f - std::tanh(x) * std::tanh(x);
}

} // namespace deepc
#include <deepc/functional/activations.hpp>
#include <cmath>

namespace deepc {
namespace detail {

const std::unordered_map<std::string, std::function<float(float)>>
    activation_function = {
    { "relu", relu }, 
    { "sigmoid", sigmoid }, 
    { "tanh", tanh }
};

const std::unordered_map<std::string, std::function<float(float)>>
    activation_derivative = {
    { "relu", relu_derivative }, 
    { "sigmoid", sigmoid_derivative }, 
    { "tanh", tanh_derivative }
};   

float relu(float x) {
    return std::fmax(0.0f, x);
}

float relu_derivative(float x) {
    return x > 0.0f ? 1.0f : 0.0f;
}

float sigmoid(float x) {
    return 1.0f / (1.0f + std::exp(x));
}

float sigmoid_derivative(float x) {
    return sigmoid(x) * (1.0f - sigmoid(x));
}

float tanh(float x) {
    return std::tanh(x);
}

float tanh_derivative(float x) {
    return 1.0f - std::tanh(x) * std::tanh(x);
}

} // namespace detail
} // namespace deepc
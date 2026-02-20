#ifndef DEEPC_DIFFERENTIAL_ACTIVATIONS_HPP
#define DEEPC_DIFFERENTIAL_ACTIVATIONS_HPP

#include <unordered_map>
#include <functional>

namespace deepc {

enum class Activation {
    relu, sigmoid, tanh
};

namespace detail {

extern const std::unordered_map<Activation, std::function<float(float)>>
    activation_function;
extern const std::unordered_map<Activation, std::function<float(float)>>
    activation_derivative;    

float relu(float x);
float relu_derivative(float x);

float sigmoid(float x);
float sigmoid_derivative(float x);

float tanh(float x);
float tanh_derivative(float x);

} // namespace detail
} // namespace deepc

#endif // DEEPC_DIFFERENTIAL_ACTIVATIONS_HPP
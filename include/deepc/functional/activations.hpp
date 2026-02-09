#ifndef DEEPC_FUNCTIONAL_ACTIVATIONS_HPP
#define DEEPC_FUNCTIONAL_ACTIVATIONS_HPP

#include <unordered_map>
#include <string>
#include <functional>

namespace deepc {
namespace detail {

extern const std::unordered_map<std::string, std::function<float(float)>>
    activation_function;
extern const std::unordered_map<std::string, std::function<float(float)>>
    activation_derivative;    

float relu(float x);
float relu_derivative(float x);

float sigmoid(float x);
float sigmoid_derivative(float x);

float tanh(float x);
float tanh_derivative(float x);

} // namespace detail
} // namespace deepc

#endif // DEEPC_FUNCTIONAL_ACTIVATIONS_HPP
#ifndef DEEPC_ACTIVATION_RELU_HPP
#define DEEPC_ACTIVATION_RELU_HPP

#include <deepc/activation/Activation.hpp>

namespace deepc {

extern const Activation RELU;

namespace detail {

float relu(float x);
float relu_derivative(float x);

} // namespace detail

} // namespace deepc

#endif // DEEPC_ACTIVATION_RELU_HPP
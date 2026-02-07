#ifndef DEEPC_ACTIVATION_SIGMOID_HPP
#define DEEPC_ACTIVATION_SIGMOID_HPP

#include <deepc/activation/Activation.hpp>

namespace deepc {

extern const Activation SIGMOID;

namespace detail {

float sigmoid(float x);
float sigmoid_derivative(float x);

} // namespace detail

} // namespace deepc

#endif // DEEPC_ACTIVATION_SIGMOID_HPP
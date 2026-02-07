#ifndef DEEPC_ACTIVATION_TANH_HPP
#define DEEPC_ACTIVATION_TANH_HPP

#include <deepc/activation/Activation.hpp>

namespace deepc {

extern const Activation TANH;

namespace detail {

float tanh(float x);
float tanh_derivative(float x);

} // namespace detail

} // namespace deepc 

#endif // DEEPC_ACTIVATION_TANH_HPP


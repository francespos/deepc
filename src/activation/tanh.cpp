#include <deepc/activation/tanh.hpp>
#include <cmath>

namespace deepc {

const Activation TANH = { detail::tanh, detail::tanh_derivative };

namespace detail {

float tanh(float x) {
    return std::tanh(x);
}

float tanh_derivative(float x) {
    return 1.0f - std::tanh(x) * std::tanh(x);
}

} // namespace detail

} // namespace deepc
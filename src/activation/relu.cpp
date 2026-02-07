#include <deepc/activation/relu.hpp>
#include <cmath>

namespace deepc {

const Activation RELU = { detail::relu, detail::relu_derivative };

namespace detail {

float relu(float x) {
    return std::fmax(0.0f, x);
}

float relu_derivative(float x) {
    return x > 0.0f ? 1.0f : 0.0f;
}

} // namespace detail

} // namespace deepc
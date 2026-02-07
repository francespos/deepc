#include <deepc/activation/sigmoid.hpp>
#include <cmath>

namespace deepc {

const Activation SIGMOID = { detail::sigmoid, detail::sigmoid_derivative };

namespace detail {

float sigmoid(float x) {
    return 1.0f / (1.0f + std::exp(x));
}

float sigmoid_derivative(float x) {
    return sigmoid(x) * (1.0f - sigmoid(x));
}

} // namespace detail

} // namespace deepc
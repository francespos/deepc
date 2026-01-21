#ifndef DEEPC_ACTIVATION_HPP
#define DEEPC_ACTIVATION_HPP

#include <functional>

namespace deepc {

struct Activation {
    std::function<float(float)> function;
    std::function<float(float)> derivative;
};

extern const Activation SIGMOID;
extern const Activation RELU;
extern const Activation TANH;

float sigmoid(float x);
float sigmoid_derivative(float x);

float relu(float x);
float relu_derivative(float x);

float tanh(float x);
float tanh_derivative(float x);

} // namespace deepc

#endif // DEEPC_ACTIVATION_HPP
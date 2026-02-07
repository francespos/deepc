#include <deepc/network/Dense.hpp>
#include <stdexcept>

namespace deepc {
namespace network {

Dense::Dense(std::size_t input) 
    : inputs_{ Vector(input) }, deltas_{ Vector(input) } {}

void Dense::add_layer(std::size_t size, const Activation& activation, 
    scalar::Generator& weight_generator, scalar::Generator& bias_generator) {
    layers_.push_back(layer::Dense(size, inputs_.back().size(), activation,
        weight_generator, bias_generator));

    inputs_.push_back(Vector(size));;
    deltas_.push_back(Vector(size));
}

const Vector& Dense::forward(const Vector& input) {
    if (input.size() != inputs_.front().size()) {
        throw std::invalid_argument("deepc: wrong input size");
    }

    inputs_.front() = input;

    for (std::size_t i = 0; i < layers_.size(); ++i) {
        inputs_[i + 1] = layers_[i].forward(inputs_[i]);
    }

    return inputs_.back();
}

const Vector& Dense::backward(const Vector& delta) {
    if (delta.size() != deltas_.back().size()) {
        throw std::invalid_argument("deepc: wrong delta size");
    }

    deltas_.back() = delta;

    for (std::size_t i = layers_.size(); i > 0; --i) {
        deltas_[i - 1] = layers_[i - 1].backward(deltas_[i]);
    }

    return deltas_.front();
}

void Dense::update(float learning_rate) {
    for (std::size_t i = 0; i < layers_.size(); ++i) {
        layers_[i].update(inputs_[i], deltas_[i + 1], learning_rate);
    }
}

} // namespace network
} // namespace deepc
#include <deepc/DenseNetwork.hpp>
#include <stdexcept>

namespace deepc {

DenseNetwork::DenseNetwork(std::size_t input) 
    : inputs_{ Vector(input) }, deltas_{ Vector(input) } {}

void DenseNetwork::add_layer(std::size_t size, const Activation& activation, 
    FloatInitializer& weight_initializer, 
    FloatInitializer& bias_initializer) 
{
    layers_.push_back(DenseLayer(size, inputs_.back().size(), activation,
        weight_initializer, bias_initializer));

    inputs_.push_back(Vector(size));;
    deltas_.push_back(Vector(size));
}

const Vector& DenseNetwork::forward(const Vector& input) {
    if (input.size() != inputs_.front().size()) {
        throw std::invalid_argument("deepc: wrong input size");
    }

    inputs_.front() = input;

    for (std::size_t i = 0; i < layers_.size(); ++i) {
        inputs_[i + 1] = layers_[i].forward(inputs_[i]);
    }

    return inputs_.back();
}

const Vector& DenseNetwork::backward(const Vector& delta) {
    if (delta.size() != deltas_.back().size()) {
        throw std::invalid_argument("deepc: wrong delta size");
    }

    deltas_.back() = delta;

    for (std::size_t i = layers_.size(); i > 0; --i) {
        deltas_[i - 1] = layers_[i - 1].backward(deltas_[i]);
    }

    return deltas_.front();
}

void DenseNetwork::update(float learning_rate) {
    for (std::size_t i = 0; i < layers_.size(); ++i) {
        layers_[i].update(inputs_[i], deltas_[i + 1], learning_rate);
    }
}

} // namespace deepc
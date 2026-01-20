#include <deepc/Network.hpp>

namespace deepc {

Network::Network(std::size_t input) 
    : inputs_{ Vector(input) }, deltas_{ Vector(input) } {}

void Network::add_layer(std::size_t size, const Activation& activation) {
    Layer layer(size, inputs_.back().size(), activation);
    layers_.push_back(layer);
    inputs_.push_back(Vector(size));;
    deltas_.push_back(Vector(size));
}

const Vector& Network::forward(const Vector& input) {
    // todo: throw exception if input.size() != inputs_.front().size()
    inputs_.front() = input;

    for (std::size_t i = 0; i < layers_.size(); ++i) {
        inputs_[i + 1] = layers_[i].forward(inputs_[i]);
    }

    return inputs_.back();
}

const Vector& Network::backward(const Vector& delta) {
    // todo: throw exception if delta.size() != deltas_.back().size()
    deltas_.back() = delta;

    for (std::size_t i = layers_.size(); i > 0; --i) {
        deltas_[i - 1] = layers_[i - 1].backward(deltas_[i]);
    }

    return deltas_.front();
}

void Network::update(float learning_rate) {
    for (std::size_t i = 0; i < layers_.size(); ++i) {
        layers_[i].update(inputs_[i], deltas_[i + 1], learning_rate);
    }
}

} // namespace deepc
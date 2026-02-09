#include <deepc/neural/network.hpp>
#include <memory>
#include <stdexcept>

namespace deepc {

Network::Network(std::size_t input) 
    : inputs_{ Vector(input) }, deltas_{ Vector(input) } {}

void Network::add_layer(const Layer& layer) {
    layers_.push_back(std::unique_ptr<Layer>(layer.clone()));
    inputs_.push_back(Vector(layer.output_size()));;
    deltas_.push_back(Vector(layer.output_size()));
}

const Vector& Network::forward(const Vector& input) {
    if (input.size() != inputs_.front().size()) {
        throw std::invalid_argument("deepc: wrong input size");
    }

    inputs_.front() = input;

    for (std::size_t i = 0; i < layers_.size(); ++i) {
        inputs_[i + 1] = layers_[i]->forward(inputs_[i]);
    }

    return inputs_.back();
}

const Vector& Network::backward(const Vector& delta) {
    if (delta.size() != deltas_.back().size()) {
        throw std::invalid_argument("deepc: wrong delta size");
    }

    deltas_.back() = delta;

    for (std::size_t i = layers_.size(); i > 0; --i) {
        deltas_[i - 1] = layers_[i - 1]->backward(deltas_[i]);
    }

    return deltas_.front();
}

void Network::update(float learning_rate) {
    for (std::size_t i = 0; i < layers_.size(); ++i) {
        layers_[i]->update(inputs_[i], deltas_[i + 1], learning_rate);
    }
}

} // namespace deepc
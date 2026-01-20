#ifndef DEEPC_NETWORK_HPP
#define DEEPC_NETWORK_HPP

#include <deepc/Layer.hpp>
#include <vector>

namespace deepc {

class Network {
public:
    explicit Network(std::size_t input);

    const Layer& layer(std::size_t pos) const { return layers_.at(pos); }
    const Vector& input(std::size_t pos) const { return inputs_.at(pos); }
    const Vector& delta(std::size_t pos) const { return deltas_.at(pos); }

    void add_layer(std::size_t size, const Activation& activation);

    const Vector& forward(const Vector& input);
    const Vector& backward(const Vector& delta);
    void update(float learning_rate);
private:
    std::vector<Layer> layers_;
    std::vector<Vector> inputs_;
    std::vector<Vector> deltas_;
};

} // namespace deepc

#endif // DEEPC_NETWORK_HPP
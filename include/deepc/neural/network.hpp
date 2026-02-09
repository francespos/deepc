#ifndef DEEPC_NEURAL_NETWORK_HPP
#define DEEPC_NEURAL_NETWORK_HPP

#include <deepc/neural/layer.hpp>
#include <vector>
#include <memory>

namespace deepc {

class Network {
public:
    explicit Network(std::size_t input);
    void add_layer(const Layer& layer);

    const Vector& forward(const Vector& input);
    const Vector& backward(const Vector& delta);

    void update(float learning_rate);
private:
    std::vector<std::unique_ptr<Layer>> layers_;
    std::vector<Vector> inputs_;
    std::vector<Vector> deltas_;
};

} // namespace deepc

#endif // DEEPC_NEURAL_NETWORK_HPP
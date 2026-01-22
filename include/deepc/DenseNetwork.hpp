#ifndef DEEPC_DENSE_NETWORK_HPP
#define DEEPC_DENSE_NETWORK_HPP

#include <deepc/DenseLayer.hpp>
#include <vector>

namespace deepc {

class DenseNetwork {
public:
    explicit DenseNetwork(std::size_t input);

    void add_layer(std::size_t size, const Activation& activation, 
        FloatInitializer& weight_initializer, 
        FloatInitializer& bias_initializer);

    const Vector& forward(const Vector& input);
    const Vector& backward(const Vector& delta);
    void update(float learning_rate);
private:
    std::vector<DenseLayer> layers_;
    std::vector<Vector> inputs_;
    std::vector<Vector> deltas_;
};

} // namespace deepc

#endif // DEEPC_DENSE_NETWORK_HPP
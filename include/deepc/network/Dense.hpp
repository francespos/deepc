#ifndef DEEPC_NETWORK_DENSE_HPP
#define DEEPC_NETWORK_DENSE_HPP

#include <deepc/layer/Dense.hpp>
#include <vector>

namespace deepc {
namespace network {

class Dense {
public:
    explicit Dense(std::size_t input);

    void add_layer(std::size_t size, const Activation& activation, 
        scalar::Generator& weight_generator, scalar::Generator& bias_generator);

    const Vector& forward(const Vector& input);
    const Vector& backward(const Vector& delta);
    void update(float learning_rate);
private:
    std::vector<layer::Dense> layers_;
    std::vector<Vector> inputs_;
    std::vector<Vector> deltas_;
};

} // namespace network 
} // namespace deepc

#endif // DEEPC_NETWORK_DENSE_HPP
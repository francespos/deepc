#ifndef DEEPC_NEURAL_FULLY_CONN_LAYER_HPP
#define DEEPC_NEURAL_FULLY_CONN_LAYER_HPP

#include <deepc/neural/layer.hpp>
#include <deepc/tensor/matrix.hpp>
#include <deepc/random/number_generator.hpp>
#include <string>
#include <functional>

namespace deepc {

class FullyConnLayer : public Layer {
public:
    explicit FullyConnLayer(std::size_t size, std::size_t input, 
        const std::string& activation, 
        const NumberGenerator& weight_initializer);

    virtual Layer* clone() const override { return new FullyConnLayer(*this); }

    virtual std::size_t output_size() const override { return weights_.rows(); }
    virtual std::size_t input_size() const override { return weights_.cols(); }

    virtual Vector forward(const Vector& input) override;
    virtual Vector backward(const Vector& delta) const override;

    virtual void update(const Vector& input, const Vector& delta, 
        float learning_rate) override;
private:
    Matrix weights_;

    Vector biases_;
    Vector z_;

    std::function<float(float)> activation_function_;
    std::function<float(float)> activation_derivative_;
};

} // namespace deepc

#endif // DEEPC_NEURAL_FULLY_CONN_LAYER_HPP
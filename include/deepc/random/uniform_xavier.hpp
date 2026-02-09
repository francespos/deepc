#ifndef DEEPC_RNG_UNIFORM_XAVIER_HPP
#define DEEPC_RNG_UNIFORM_XAVIER_HPP

#include <deepc/random/number_generator.hpp>
#include <random>
#include <cstddef>

namespace deepc {

class UniformXavier : public NumberGenerator {
public:
    explicit UniformXavier(std::size_t fan_in, std::size_t fan_out, 
        unsigned int seed);

    virtual NumberGenerator* clone() const override {
        return new UniformXavier(*this);
    }

    virtual float generate() override;
private:
    std::size_t fan_in_;
    std::size_t fan_out_;
    std::mt19937 rng_;
};

} // namespace deepc

#endif // DEEPC_RNG_UNIFORM_XAVIER_HPP
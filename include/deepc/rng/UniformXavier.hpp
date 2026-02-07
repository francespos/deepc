#ifndef DEEPC_RNG_UNIFORM_XAVIER_HPP
#define DEEPC_RNG_UNIFORM_XAVIER_HPP

#include <deepc/scalar/Generator.hpp>
#include <random>
#include <cstddef>

namespace deepc {
namespace rng {

class UniformXavier : public scalar::Generator {
public:
    explicit UniformXavier(std::size_t fan_in, std::size_t fan_out, 
        const std::mt19937& rng);

    virtual float generate() override;
private:
    std::size_t fan_in_;
    std::size_t fan_out_;
    std::mt19937 rng_;
};

} // namespace rng
} // namespace deepc

#endif // DEEPC_RNG_UNIFORM_XAVIER_HPP
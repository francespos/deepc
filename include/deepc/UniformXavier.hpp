#ifndef DEEPC_UNIFORM_XAVIER_HPP
#define DEEPC_UNIFORM_XAVIER_HPP

#include <deepc/FloatInitializer.hpp>
#include <random>
#include <cstddef>

namespace deepc {

class UniformXavier : public FloatInitializer {
public:
    explicit UniformXavier(std::size_t fan_in, std::size_t fan_out, 
        const std::mt19937& rng);

    virtual float generate() override;
private:
    std::size_t fan_in_;
    std::size_t fan_out_;
    std::mt19937 rng_;
};

} // namespace deepc

#endif // DEEPC_UNIFORM_XAVIER_HPP
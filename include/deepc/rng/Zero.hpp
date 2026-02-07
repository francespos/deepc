#ifndef DEEPC_RNG_ZERO_HPP
#define DEEPC_RNG_ZERO_HPP

#include <deepc/scalar/Generator.hpp>

namespace deepc {
namespace rng {

struct Zero : public scalar::Generator {
    explicit Zero() = default;
    virtual float generate() override { return 0.0f; }
};

} // namespace rng
} // namespace deepc

#endif // DEEPC_RNG_ZERO_HPP
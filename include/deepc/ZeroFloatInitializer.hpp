#ifndef DEEPC_ZERO_FLOAT_INITIALIZER_HPP
#define DEEPC_ZERO_FLOAT_INITIALIZER_HPP

#include <deepc/FloatInitializer.hpp>

namespace deepc {

struct ZeroFloatInitializer : public FloatInitializer {
    explicit ZeroFloatInitializer() = default;
    virtual float generate() override { return 0.0f; }
};

} // namespace deepc

#endif // DEEPC_ZERO_FLOAT_INITIALIZER_HPP
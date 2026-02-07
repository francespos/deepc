#ifndef DEEPC_SCALAR_GENERATOR_HPP
#define DEEPC_SCALAR_GENERATOR_HPP

namespace deepc {
namespace scalar {

struct Generator {
    virtual float generate() = 0;
};

} // namespace scalar
} // namespace deepc

#endif // DEEPC_SCALAR_GENERATOR_HPP
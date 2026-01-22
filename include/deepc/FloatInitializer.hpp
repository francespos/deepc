#ifndef DEEPC_FLOAT_INITIALIZER_HPP
#define DEEPC_FLOAT_INITIALIZER_HPP

namespace deepc {

struct FloatInitializer {
    virtual float generate() = 0;
};

} // namespace deepc

#endif // DEEPC_FLOAT_INITIALIZER_HPP
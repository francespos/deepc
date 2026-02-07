#ifndef DEEPC_ACTIVATION_ACTIVATION_HPP
#define DEEPC_ACTIVATION_ACTIVATION_HPP

#include <functional>

namespace deepc {

struct Activation {
    std::function<float(float)> function;
    std::function<float(float)> derivative;
};

} // namespace deepc

#endif // DEEPC_ACTIVATION_ACTIVATION_HPP
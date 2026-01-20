#include <deepc/float.hpp>
#include <cstddef>
#include <cmath>

namespace deepc {

bool scalar_equal_f(float x, float y, float rtol, float atol) {
    auto diff = std::fabs(x - y);
    auto scale = std::fmax(std::fabs(x), std::fabs(y));
    return diff <= (atol + rtol * scale);
}
    
} // namespace deepc
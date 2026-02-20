#include <deepc/scalar/precision.hpp>
#include <cmath>

namespace deepc {
namespace detail {

bool equal(float x, float y) {
    auto diff = std::fabs(x - y);
    auto scale = std::fmax(std::fabs(x), std::fabs(y));
    return diff <= (atol + rtol * scale);
}
    
} // namespace detail
} // namespace deepc
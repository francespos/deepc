#include <deepc/scalar/precision.hpp>
#include <cmath>

namespace deepc {
namespace scalar {
namespace detail {

bool equal(float x, float y) {
    auto diff = std::fabs(x - y);
    auto scale = std::fmax(std::fabs(x), std::fabs(y));
    return diff <= (ATOL + RTOL * scale);
}
    
} // namespace detail
} // namespace scalar
} // namespace deepc
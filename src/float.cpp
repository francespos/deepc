#include <deepc/float.hpp>
#include <cmath>

namespace deepc {

bool equal(float x, float y) {
    auto diff = std::fabs(x - y);
    auto scale = std::fmax(std::fabs(x), std::fabs(y));

    return diff <= (ATOL + RTOL * scale);
}
    
} // namespace deepc
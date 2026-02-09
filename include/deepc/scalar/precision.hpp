#ifndef DEEPC_SCALAR_PRECISION_HPP
#define DEEPC_SCALAR_PRECISION_HPP

namespace deepc {
namespace detail {

constexpr float RTOL = 1e-5f;
constexpr float ATOL = 1e-8f;

bool equal(float x, float y);

} // namespace detail
} // namespace deepc

#endif // DEEPC_SCALAR_PRECISION_HPP
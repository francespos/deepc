#ifndef DEEPC_FLOAT_HPP
#define DEEPC_FLOAT_HPP

namespace deepc {

constexpr float RTOL = 1e-5f;
constexpr float ATOL = 1e-8f;

bool equal(float x, float y);

} // namespace deepc

#endif // DEEPC_FLOAT_HPP
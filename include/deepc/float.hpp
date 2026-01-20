#ifndef DEEPC_FLOAT_HPP
#define DEEPC_FLOAT_HPP

#include <cstddef>

namespace deepc {
namespace detail {

constexpr float RTOL = 1e-5f;
constexpr float ATOL = 1e-8f;

} // namespace detail
} // namespace deepc

namespace deepc {

bool scalar_equal_f(float x, float y, float rtol = detail::RTOL, 
    float atol = detail::ATOL);

template<typename T>
bool tensor_equal_f(const T& x, const T& y, float rtol = detail::RTOL, 
    float atol = detail::ATOL) {
    if (x.size() != y.size()) {
        return false;
    }

    for (std::size_t i = 0; i < x.size(); ++i) {
        if (!scalar_equal(x[i], y[i], rtol, atol)) {
            return false;
        }
    }

    return true;
}

} // namespace deepc

#endif // DEEPC_FLOAT_HPP
#include <deepc/rng/UniformXavier.hpp>
#include <cmath>

namespace deepc {
namespace rng {

UniformXavier::UniformXavier(std::size_t fan_in, std::size_t fan_out, 
    const std::mt19937& rng) 
    : fan_in_(fan_in), fan_out_(fan_out), rng_(rng) {}

float UniformXavier::generate() {
    auto denom = static_cast<float>(fan_in_ + fan_out_);
    auto limit = std::sqrt(6.0f / denom);
    std::uniform_real_distribution<float> dist(-limit, limit);
    return dist(rng_);
}

} // namespace rng
} // namespace deepc
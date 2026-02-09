#include <deepc/random/uniform_xavier.hpp>
#include <cmath>

namespace deepc {

UniformXavier::UniformXavier(std::size_t fan_in, std::size_t fan_out, 
    unsigned int seed) 
    : fan_in_(fan_in), fan_out_(fan_out), rng_(seed) {}

float UniformXavier::generate() {
    auto denom = static_cast<float>(fan_in_ + fan_out_);
    auto limit = std::sqrt(6.0f / denom);
    std::uniform_real_distribution<float> dist(-limit, limit);
    return dist(rng_);
}

} // namespace deepc
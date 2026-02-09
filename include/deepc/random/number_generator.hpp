#ifndef DEEPC_RANDOM_NUMBER_GENERATOR_HPP
#define DEEPC_RANDOM_NUMBER_GENERATOR_HPP

namespace deepc {

struct NumberGenerator {
    virtual ~NumberGenerator() noexcept = default;

    virtual NumberGenerator* clone() const = 0;
    virtual float generate() = 0;
};

} // namespace deepc

#endif // DEEPC_RANDOM_NUMBER_GENERATOR_HPP
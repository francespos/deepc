#include <deepc/scalar/precision.hpp>
#include <cassert>

void test_equal() {
    assert(deepc::detail::equal(1.0f, 1.0f));
    assert(!deepc::detail::equal(1.0f, 0.3f));
}

int main() {
    test_equal();
}
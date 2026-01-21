#include <deepc/deepc.hpp>
#include <cassert>

void test_equal() {
    assert(deepc::equal(1.0f, 1.0f));
    assert(!deepc::equal(1.0f, 0.3f));
}

int main() {
    test_equal();
}
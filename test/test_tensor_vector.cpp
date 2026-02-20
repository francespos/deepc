#include <deepc/tensor/vector.hpp>
#include <utility>
#include <cassert>

void test_constructor() {
    deepc::Vector v(2);
    assert(v.size() == 2);
}

void test_copy_constructor() {
    deepc::Vector v1(2);
    v1[0] = 1.0f;
    v1[1] = 2.0f;

    auto v2 = v1;
    assert(v2.size() == 2 && v2[0] == 1.0f && v2[1] == 2.0f);
}

void test_copy_assigment_operator() {
    deepc::Vector v1(2);
    v1[0] = 1.0f;
    v1[1] = 2.0f;
    v1 = v1;
    assert(v1.size() == 2 && v1[0] == 1.0f && v1[1] == 2.0f);
    // ...
}

void test_move_constructor() {
    deepc::Vector v1(2);
    v1[0] = 1.0f; 
    v1[1] = 2.0f;

    auto v2 = std::move(v1);
    assert(v1.size() == 0 && v1.data() == nullptr);
    assert(v2.size() == 2 && v2[0] == 1.0f && v2[1] == 2.0f);
}

void test_size() {
    deepc::Vector v(3);
    assert(v.size() == 3);
}

void test_data() {
    deepc::Vector v1(3);
    auto p1 = v1.data();
    const deepc::Vector v2 = std::move(v1);
    assert(p1 == v2.data());
}

void test_equal() {
    deepc::Vector v1(2);
    v1[0] = 1.0f;
    v1[1] = 2.0f;

    deepc::Vector v2(2);
    v2[0] = 1.0f;
    v2[1] = 2.0f;

    assert(v1 == v2);

    v2[1] = 1.5f;
    assert(v1 != v2);
}

int main() {
    test_constructor();
    test_copy_constructor();
    // ...
    test_move_constructor();
    // ...
    test_size();
    test_data();
    test_equal();
}
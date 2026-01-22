#include <deepc/deepc.hpp>
#include <cassert>

// I don't want you to do unit test for know, I just want to be sure DenseLayer
// class is written correctly

// Write class' unit test here:
// deepc::Vector test_dummy(deepc::DenseLayer& layer) {}
// ...

int main() {    
    std::mt19937 rng(41);
    deepc::UniformXavier weight_initializer(3, 4, rng);
    deepc::ZeroFloatInitializer bias_initializer;

    // Dummy values, initialize layer as you wish
    deepc::DenseLayer layer(4, 3, deepc::RELU, weight_initializer, 
        bias_initializer);

    // Run class' unit test here:
    //
    // auto v = test_dummy(layer);
    // assert(v == something);
    // ...
}
#include <deepc/neural/fully_conn_layer.hpp>
#include <deepc/random/uniform_xavier.hpp>
#include <cassert>

int main() {    
    deepc::FullyConnLayer layer(4, 3, "relu", deepc::UniformXavier(3, 4, 41)); 
}
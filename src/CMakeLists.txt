set(DEEPC_SRC activation/relu.cpp activation/sigmoid.cpp activation/tanh.cpp
    layer/Dense.cpp network/Dense.cpp scalar/precision.cpp tensor/Matrix.cpp 
    tensor/Vector.cpp rng/UniformXavier.cpp)

add_library(deepc STATIC ${DEEPC_SRC})
set_property(TARGET deepc PROPERTY CXX_STANDARD 11)

target_link_libraries(deepc PUBLIC m)
target_include_directories(deepc PUBLIC ../include)
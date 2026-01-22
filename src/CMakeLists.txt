set(DEEPC_SRC Activation.cpp DenseLayer.cpp DenseNetwork.cpp float.cpp 
    Matrix.cpp UniformXavier.cpp Vector.cpp)

add_library(deepc STATIC ${DEEPC_SRC})
set_property(TARGET deepc PROPERTY CXX_STANDARD 11)

target_link_libraries(deepc PUBLIC m)
target_include_directories(deepc PUBLIC ../include)
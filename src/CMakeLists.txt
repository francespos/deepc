set(DEEPC_SRC functional/activations.cpp neural/fully_conn_layer.cpp 
    neural/network.cpp random/uniform_xavier.cpp scalar/precision.cpp 
    tensor/matrix.cpp tensor/vector.cpp)

add_library(deepc STATIC ${DEEPC_SRC})
set_property(TARGET deepc PROPERTY CXX_STANDARD 11)

target_link_libraries(deepc PUBLIC m)
target_include_directories(deepc PUBLIC ../include)
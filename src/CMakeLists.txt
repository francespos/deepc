set(DEEPC_SRC Activation.cpp Layer.cpp Matrix.cpp Vector.cpp float.cpp)

add_library(deepc STATIC ${DEEPC_SRC})
set_property(TARGET deepc PROPERTY CXX_STANDARD 11)

target_link_libraries(deepc PUBLIC m)
target_include_directories(deepc PUBLIC ../include)
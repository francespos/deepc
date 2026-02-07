add_executable(TestScalarPrecision TestScalarPrecision.cpp)
set_property(TARGET TestScalarPrecision PROPERTY CXX_STANDARD 11)
target_link_libraries(TestScalarPrecision PRIVATE deepc)

add_executable(TestTensorVector TestTensorVector.cpp)
set_property(TARGET TestTensorVector PROPERTY CXX_STANDARD 11)
target_link_libraries(TestTensorVector PRIVATE deepc)

add_executable(TestLayerDense TestLayerDense.cpp)
set_property(TARGET TestLayerDense PROPERTY CXX_STANDARD 11)
target_link_libraries(TestLayerDense PRIVATE deepc)

enable_testing()
add_test(NAME TestScalarPrecision COMMAND TestScalarPrecision)
add_test(NAME TestTensorVector COMMAND TestTensorVector)
add_test(NAME TestLayerDense COMMAND TestLayerDense)
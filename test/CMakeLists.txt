add_executable(TestFloat TestFloat.cpp)
set_property(TARGET TestFloat PROPERTY CXX_STANDARD 11)
target_link_libraries(TestFloat PRIVATE deepc)

add_executable(TestVector TestVector.cpp)
set_property(TARGET TestVector PROPERTY CXX_STANDARD 11)
target_link_libraries(TestVector PRIVATE deepc)

add_executable(TestDenseLayer TestDenseLayer.cpp)
set_property(TARGET TestDenseLayer PROPERTY CXX_STANDARD 11)
target_link_libraries(TestDenseLayer PRIVATE deepc)

enable_testing()
add_test(NAME TestFloat COMMAND TestFloat)
add_test(NAME TestVector COMMAND TestVector)
add_test(NAME TestDenseLayer COMMAND TestDenseLayer)
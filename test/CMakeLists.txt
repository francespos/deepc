add_executable(float float.c)
target_link_libraries(float PRIVATE deepc)

add_executable(vector vector.c)
target_link_libraries(vector PRIVATE deepc)

add_executable(matrix matrix.c)
target_link_libraries(matrix PRIVATE deepc)

enable_testing()
add_test(NAME float_test COMMAND float)
add_test(NAME vector_test COMMAND vector)
add_test(NAME matrix_test COMMAND matrix)

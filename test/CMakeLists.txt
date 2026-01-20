add_executable(TestLayer TestLayer.cpp)
set_property(TARGET TestLayer PROPERTY CXX_STANDARD 11)
target_link_libraries(TestLayer PRIVATE deepc)

enable_testing()
add_test(NAME TestLayer COMMAND TestLayer)
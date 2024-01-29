add_executable(TestMap test.cpp)
add_compile_options(-fprofile-arcs -ftest-coverage)
link_libraries(gcov)
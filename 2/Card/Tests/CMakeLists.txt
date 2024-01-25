add_executable(TestCard test.cpp ../../catch.hpp)
add_compile_options(-fprofile-arcs -ftest-coverage)
link_libraries(gcov)
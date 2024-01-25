add_executable(TestDeckDynamic test.cpp ../../catch.hpp)
add_compile_options(-fprofile-arcs -ftest-coverage)
link_libraries(gcov)
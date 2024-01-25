cmake_minimum_required(VERSION 3.5)
project(Third_Lab)

set(CMAKE_CXX_STANDARD 20)


# установка флагов компилятора: CMAKE_CXX_FLAGS += -Wall -Wextra
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")



#Stations
add_subdirectory(Stations)
add_subdirectory(Line)
add_subdirectory(LineManager)
add_subdirectory(Stations/Tests)

# add_executable(mainClass main.cpp)
# add_executable(mainClass Stations/Tests/test.cpp)
#  add_executable(mainClass Line/Tests/test.cpp)
 add_executable(mainClass LineManager/Tests/test.cpp)

# add_executable(mainClass Stations/Tests/test.cpp
#                             Line/Tests/test.cpp
#                             LineManager/Tests/test.cpp)

target_link_libraries(mainClass LineManager)
target_link_libraries(mainClass Line)
target_link_libraries(mainClass Stations)
# target_link_libraries(mainClass TestStations)




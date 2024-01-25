cmake_minimum_required(VERSION 3.26)
project(second_lab)

set(CMAKE_CXX_STANDARD 20)

# установка флагов компилятора: CMAKE_CXX_FLAGS += -Wall -Wextra
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")


#TODO: Create a script that will test all files



# CARD CLASS
add_subdirectory(Card/Cards)

# add_executable(mainCard Card/main.cpp)
add_executable(mainCard Card/Tests/test.cpp)

target_link_libraries(mainCard Cards)



# DECK CLASS DYNAMIC
add_subdirectory(DeckDynamic/Deck)
add_subdirectory(DeckDynamic/Tests)

# add_executable(mainDeckDynamic DeckDynamic/main.cpp)
add_executable(mainDeckDynamic DeckDynamic/Tests/test.cpp)

target_link_libraries(mainDeckDynamic Cards)
target_link_libraries(mainDeckDynamic DeckDynamic)



# DECK CLASS STATIC
add_subdirectory(DeckStatic/Deck)
add_subdirectory(DeckStatic/Tests)

# add_executable(mainDeckStatic DeckStatic/main.cpp)
add_executable(mainDeckStatic DeckStatic/Tests/test.cpp)

target_link_libraries(mainDeckStatic Cards)
target_link_libraries(mainDeckStatic DeckStatic)


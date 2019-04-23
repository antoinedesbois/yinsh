cmake_minimum_required (VERSION 3.1)
project (Yinsh)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -fno-exceptions")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -fno-exceptions")

# Setup testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})
link_directories("/usr/local/lib")

add_executable(Yinsh main.cpp gameState.cpp board.cpp)
add_executable(boardTest  boardTest.cpp board.cpp )
add_executable(gameStateTest gameState.cpp gameStateTest.cpp board.cpp)
add_executable(benchmarks benchmarks.cpp board.cpp)

target_include_directories(boardTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(gameStateTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Yinsh PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(benchmarks PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(UNIX AND NOT APPLE)
  target_link_libraries(boardTest ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} pthread)
  target_link_libraries(gameStateTest ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} pthread)
  target_link_libraries(Yinsh pthread)
  target_link_libraries(benchmarks benchmark pthread)
else()
  target_link_libraries(boardTest ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} )
  target_link_libraries(gameStateTest ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})
  target_link_libraries(Yinsh )
  target_link_libraries(benchmarks benchmark pthread)
endif()



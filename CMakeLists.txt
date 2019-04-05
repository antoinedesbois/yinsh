cmake_minimum_required (VERSION 3.1)
project (Yinsh)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

# Setup testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

# Add test cpp file
add_executable(runUnitTests
    test.cpp
)

# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTests ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})
target_include_directories(runUnitTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_test(
    NAME runUnitTests
    COMMAND runUnitTests
)

add_executable(Yinsh main.cpp)

if(UNIX AND NOT APPLE)
  target_link_libraries(Yinsh benchmark pthread)
else()
  target_link_libraries(Yinsh benchmark)
  target_include_directories(Yinsh PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
endif()

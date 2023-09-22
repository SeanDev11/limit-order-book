cmake_minimum_required(VERSION 3.13)
project(limit-order-book)

set(CMAKE_CXX_STANDARD 17)

# ALL_SOURCES = list of all the source files for this project
#file(GLOB_RECURSE ALL_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
#add_executable(limit-order-book "${ALL_SOURCES}")

add_executable(limit-order-book src/Book.cpp src/Limit.cpp src/Order.cpp src/main.cpp)

target_include_directories(limit-order-book PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

# Tests
add_subdirectory(tests)

# For libraries
#add_subdirectory("lib/googletest")
#target_link_libraries(limit-order-book)
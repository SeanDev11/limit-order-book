cmake_minimum_required(VERSION 3.13)

project(server)
set(CMAKE_CXX_STANDARD 17)

# ALL_SOURCES = list of all the source files for this project
#file(GLOB_RECURSE ALL_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
#add_executable(limit-order-book "${ALL_SOURCES}")

add_executable(server src/Book.cpp src/Limit.cpp src/Order.cpp
        src/BookManager.cpp src/main.cpp
        src/Server.cpp)

# Client executable
add_executable(client src/Client.cpp)

target_include_directories(server PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

# Tests
add_subdirectory(tests)

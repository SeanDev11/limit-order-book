cmake_minimum_required(VERSION 3.13)

#add_executable(RunTests ${PROJECT_SOURCE_DIR}/include/Order.hpp ${PROJECT_SOURCE_DIR}/src/Order.cpp orderbooktests.cpp)
#file(GLOB_RECURSE ALL_SOURCES CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(RunTests orderbooktests.cpp ../src/Book.cpp ../src/Limit.cpp ../src/Order.cpp ../src/Heap.cpp)

#target_include_directories(RunTests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_include_directories(RunTests PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

add_subdirectory("lib/googletest")
target_link_libraries(RunTests PRIVATE gtest gtest_main)

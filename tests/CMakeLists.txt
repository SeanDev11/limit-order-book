cmake_minimum_required(VERSION 3.13)

add_executable(RunTests orderbooktests.cpp ../src/Book.cpp ../src/Limit.cpp
        ../src/Order.cpp ../src/Heap.cpp ../src/BookManager.cpp)

target_include_directories(RunTests PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

add_subdirectory("lib/googletest")
target_link_libraries(RunTests PRIVATE gtest gtest_main)

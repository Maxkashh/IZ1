cmake_minimum_required(VERSION 3.20)
project(DZ1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(LIB_SOURCE_FILES source.c)


add_library(tag STATIC ${LIB_SOURCE_FILES})

add_executable(main main.c)
target_link_libraries(main source)

enable_testing()

find_package(GTest REQUIRED)
find_package(Threads)

include_directories(${GTEST_INCLUDE_DIRS})
add_executable(tests tests.cpp)
target_link_libraries(tests ${GTEST_LIBRARIES} pthread source)
cmake_minimum_required(VERSION 3.15)
project(Matrix)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/CompileFlags.cmake)

find_package(GTest REQUIRED)

add_executable(matrix main.cpp)

target_include_directories(matrix PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

add_executable(tests tests/source/test_matrix.cpp tests/source/test_buffer.cpp tests/main.cpp)

target_include_directories(tests PRIVATE
	${CMAKE_SOURCE_DIR}/tests/utils/include
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/include/detail
)

target_link_libraries(tests
    GTest::gtest 
    GTest::gtest_main
)

enable_testing()
add_test(NAME UnitTests COMMAND tests)

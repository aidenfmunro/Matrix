cmake_minimum_required(VERSION 3.15)
project(Matrix)

option(ENABLE_LOGGING "Enable logging output to console" OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

find_package(GTest REQUIRED)

add_executable(matrix.x main.cpp)

target_compile_features(matrix.x PUBLIC cxx_std_20)

target_include_directories(matrix.x PRIVATE
    ${CMAKE_SOURCE_DIR}/include/detail
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/utils/include
)

if(ENABLE_LOGGING)
    target_compile_definitions(matrix.x PRIVATE ENABLE_LOGGING)
endif()

add_executable(tests tests/source/test_matrix.cpp tests/main.cpp)

target_compile_features(tests PUBLIC cxx_std_20)

target_include_directories(tests PRIVATE
	${CMAKE_SOURCE_DIR}/tests/utils/include
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/include/detail
    ${CMAKE_SOURCE_DIR}/utils/include
)

target_link_libraries(tests
    GTest::gtest 
    GTest::gtest_main
)

enable_testing()
add_test(NAME UnitTests COMMAND tests)

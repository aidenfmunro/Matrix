#include <gtest/gtest.h>
#include "matrix.hpp"
#include "utils.hpp"

TEST(MatrixTest, SimpleTest1)
{
    tests::utils::runTest("test1");
}

TEST(MatrixTest, SimpleTest2)
{
    tests::utils::runTest("test2");
}

TEST(MatrixTest, LargeTest)
{
    tests::utils::runTest("matrix_100x100");
}

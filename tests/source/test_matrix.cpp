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

TEST(MatrixTest, LargeTest1)
{
    tests::utils::runTest("matrix_100x100");
}

TEST(MatrixTest, LargeTest2)
{
    tests::utils::runTest("matrix_20x20");
}

TEST(MatrixTest, LargeTest3)
{
    tests::utils::runTest("matrix_50x50");
}

TEST(MatrixTest, LargeTest4)
{
    tests::utils::runTest("matrix_99x99");
}

TEST(MatrixTest, LargeTest5)
{
    tests::utils::runTest("matrix_10x10");
}





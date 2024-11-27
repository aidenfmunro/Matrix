#include <gtest/gtest.h>
#include "matrix.hpp"
#include "test_utils.hpp"

class MatrixTest : public ::testing::Test
{
protected:
    size_t rows_ = 3;
    size_t cols_ = 3;

    constexpr static int value_ = 1000 - 7;

    matrix::Matrix<int> matrix_{rows_, cols_, value_};
};

TEST_F(MatrixTest, ConstructorInitializesWithValue)
{
    for (size_t row = 0; row < rows_; ++row)
    {
        for (size_t col = 0; col < cols_; ++col)
        {
            EXPECT_EQ(matrix_[row][col], value_); 
        }
    }
}

TEST_F(MatrixTest, CopyConstructorCreatesDeepCopy)
{
    matrix::Matrix<int> mCopy{matrix_};

    for (size_t row = 0; row < rows_; ++row)
    {
        for (size_t col = 0; col < cols_; ++col)
        {
            EXPECT_EQ(mCopy[row][col], matrix_[row][col]); 
        }
    }
}

TEST_F(MatrixTest, CopyAssignmentCreatesDeepCopy)
{
    matrix::Matrix<int> mCopied = matrix_;

    for (size_t row = 0; row < rows_; ++row)
    {
        for (size_t col = 0; col < cols_; ++col)
        {
            EXPECT_EQ(mCopied[row][col], matrix_[row][col]); 
        }
    }
}

TEST_F(MatrixTest, MoveConstructorTransfersOwnership)
{
    matrix::Matrix<int> mMoved{std::move(matrix_)};

    for (size_t row = 0; row < rows_; ++row)
    {
        for (size_t col = 0; col < cols_; ++col)
        {
            EXPECT_EQ(mMoved[row][col], value_); 
        }
    }
}

TEST_F(MatrixTest, MoveAssignmentTransfersOwnership)
{
    matrix::Matrix<int> mMoved = std::move(matrix_);

    for (size_t row = 0; row < rows_; ++row)
    {
        for (size_t col = 0; col < cols_; ++col)
        {
            EXPECT_EQ(mMoved[row][col], value_); 
        }
    }
}


TEST_F(MatrixTest, isCorrectlyInitialized)
{
    for (size_t row = 0; row < rows_; ++row)
    {
        for (size_t col = 0; col < cols_; ++col)
        {
            EXPECT_EQ(matrix_[row][col], value_);
        }
    }
}

TEST_F(MatrixTest, ElementAccess)
{
    int newValue = 1000;
    size_t row = 2;
    size_t col = 2;

    matrix_[row][col] = newValue;

    EXPECT_EQ(matrix_[row][col], newValue);
}

TEST(MatrixDeterminantTest, SimpleTest1)
{
    tests::utils::runTest<int>("test1");
}

TEST(MatrixDeterminantTest, SimpleTest2)
{
    tests::utils::runTest<int>("test2");
}

TEST(MatrixDeterminantTest, SimpleTest3)
{
    tests::utils::runTest<int>("test3");
}

TEST(MatrixDeterminantTest, LargeTest1)
{
    tests::utils::runTest<double>("matrix_100x100");
}

TEST(MatrixDeterminantTest, LargeTest2)
{
    tests::utils::runTest<double>("matrix_99x99");
}

TEST(MatrixDeterminantTest, LargeTest3)
{
    tests::utils::runTest<int>("matrix_95x95");
}

TEST(MatrixDeterminantTest, LargeTest4)
{
    tests::utils::runTest<double>("matrix_50x50");
}

TEST(MatrixDeterminantTest, LargeTest5)
{
    tests::utils::runTest<int>("matrix_25x25");
}

TEST(MatrixDeterminantTest, LargeTest6)
{
    tests::utils::runTest<double>("matrix_20x20");
}

TEST(MatrixDeterminantTest, LargeTest7)
{
    tests::utils::runTest<double>("matrix_10x10");
}

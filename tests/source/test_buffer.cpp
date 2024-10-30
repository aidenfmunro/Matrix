#include <gtest/gtest.h>
#include "buffer.hpp"


class BufferTest : public ::testing::Test
{
protected:
    size_t rows_ = 3;
    size_t cols_ = 3;

    constexpr static int value_ = 1000 - 7;

    matrix::detail::Buffer<int> buffer_{rows_, cols_, value_};
};

TEST_F(BufferTest, ConstructorInitializesWithValue)
{
    for (size_t row = 0; row < rows_; ++row)
    {
        for (size_t col = 0; col < cols_; ++col)
        {
            EXPECT_EQ(buffer_[row][col], value_); 
        }
    }
}

TEST_F(BufferTest, CopyConstructorCreatesDeepCopy)
{
    matrix::detail::Buffer<int> BufferCopy{buffer_};

    for (size_t row = 0; row < rows_; ++row)
    {
        for (size_t col = 0; col < cols_; ++col)
        {
            EXPECT_EQ(buffer_[row][col], BufferCopy[row][col]); 
        }
    }
}

TEST_F(BufferTest, CopyAssignmentCreatesDeepCopy)
{
    matrix::detail::Buffer<int> BufferCopy = buffer_;

    for (size_t row = 0; row < rows_; ++row)
    {
        for (size_t col = 0; col < cols_; ++col)
        {
            EXPECT_EQ(buffer_[row][col], BufferCopy[row][col]); 
        }
    }
}

TEST_F(BufferTest, MoveConstructorTransfersOwnership)
{
    matrix::detail::Buffer<int> BufferMoved{std::move(buffer_)};

    for (size_t row = 0; row < rows_; ++row)
    {
        for (size_t col = 0; col < cols_; ++col)
        {
            EXPECT_EQ(BufferMoved[row][col], value_); 
        }
    }
}

TEST_F(BufferTest, MoveAssignmentTransfersOwnership)
{
    matrix::detail::Buffer<int> BufferMoved = std::move(buffer_);

    for (size_t row = 0; row < rows_; ++row)
    {
        for (size_t col = 0; col < cols_; ++col)
        {
            EXPECT_EQ(BufferMoved[row][col], value_); 
        }
    }
}

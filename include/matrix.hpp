#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cmath> // fabs
#include "buffer.hpp" // Buffer
#include "proxyrow.hpp" // ProxyRow
#include "utils.hpp" // isAlmostEqual
#include <iostream> // cerr
#include <stdexcept>

namespace matrix
{

namespace utils
{
} // namespace utils

template<class T> 
class Matrix : private detail::Buffer<T>
{
public:
    using detail::Buffer<T>::data_;
    using detail::Buffer<T>::size_;
    using detail::Buffer<T>::used_;

private:
    size_t dim_;

public:
    Matrix(size_t dim)
    :   detail::Buffer<T>(dim * dim),
        dim_(dim)
    {
        for (size_t id = 0; id < size_; ++id)
        {
            detail::construct(data_ + used_, T{});
            used_ += 1;
        }
    }

    Matrix(size_t dim, const T& value)
    :   detail::Buffer<T>(dim * dim),
        dim_(dim)
    {
        for (size_t id = 0; id < size_; ++id)
        {
            detail::construct(data_ + used_, value);
            used_ += 1;
        }
    }

    Matrix(Matrix&& rhs) = default;
    Matrix& operator=(Matrix&& rhs) = default;

    Matrix(const Matrix& rhs)
    :   detail::Buffer<T>(rhs.used_),
        dim_(rhs.dim_)
    {
        while (used_ < rhs.used_) 
        {
            detail::construct(data_ + used_, rhs.data_[used_]);
            used_ += 1;
        }
    }

    Matrix& operator=(const Matrix& rhs) 
    {
        Matrix tmp(rhs);
        std::swap(*this, tmp);
        return *this;
    }

    template<typename U>
    Matrix (const Matrix<U>& other)
    :   detail::Buffer<T>(other.getDim() * other.getDim()),
        dim_(other.getDim())
    {
        for (size_t i = 0; i < dim_; ++i)
        {
            for (size_t j = 0; j < dim_; ++j)
            {
                detail::construct(data_ + used_, static_cast<T>(other[i][j]));
                used_ += 1;
            }
        }
    }

    const detail::ProxyRow<T> operator[] (size_t index) const
    {
        if (index * dim_ >= size_)
        {
            throw std::out_of_range("Matrix index out of bounds");
        }

        return detail::ProxyRow<T>(data_ + index * dim_);
    }

    detail::ProxyRow<T> operator[] (size_t index)
    {
        if (index * dim_ >= size_)
        {
            throw std::out_of_range("Matrix index out of bounds");
        }

        return detail::ProxyRow<T>(data_ + index * dim_);
    }

private:
    T& at(size_t row, size_t col) 
    {
        return data_[row * dim_ + col];
    }

    const T& at(size_t row, size_t col) const 
    {
        return data_[row * dim_ + col];
    }

public:
    size_t getDim() const { return dim_; }

    double det() const
    {
#ifdef ENABLE_LOGGING 
        dump();
#endif
        size_t swapCount = 0;
        
        Matrix<double> matrixCopy = *this;
        
        if (!matrixCopy.gaussianElimination(swapCount))
        {
            return 0;
        }
#ifdef ENABLE_LOGGING
        matrixCopy.dump();
#endif
        double det = 1;

        for (size_t i = 0; i < dim_; ++i)
        {
            det *= matrixCopy[i][i];
        }

        return (swapCount % 2 == 0) ? det : -det;
    }
    
    bool gaussianElimination(size_t& swapCount)
    {
        for (size_t iRow = 0; iRow < dim_; ++iRow)
        {
            size_t pivotRow = findPivotRow(iRow);

            if (utils::isAlmostEqual(at(pivotRow, iRow), 0))
            {
                return false;
            }

            if (pivotRow != iRow)
            {
                swapRows(iRow, pivotRow);
                swapCount++;
            }

            eliminateColumn(iRow);
#ifdef ENABLE_LOGGING
            dump();
#endif
        }

        return true; 
    }

    void dump() const
    {
        for (size_t row = 0; row < dim_; ++row)
        {
            for (size_t col = 0; col < dim_; ++col)
            {
                 std::cerr << at(row, col) << " ";
            }
            
            std::cerr << "\n";
        }

        std::cerr << "\n";
    }

private:
    void swapRows(size_t row1, size_t row2)
    {
        if (row1 == row2)
            return;

        for (size_t col = 0; col < dim_; ++col)
        {
            std::swap(at(row1, col), at(row2, col));
        }
    }

    size_t findPivotRow(size_t col) const 
    {
        size_t maxRow = col;

        T maxElem = std::abs(at(col, col));

        for (size_t iCol = col + 1; iCol < dim_; iCol++)
        {
            T curElem = std::abs(at(iCol, col));

            if (curElem > maxElem)
            {
                maxElem = curElem; 
                maxRow = iCol;
            }
        }

        return maxRow;
    }

    void eliminateColumn(size_t pivotRow) 
    {
        for (size_t iRow = pivotRow + 1; iRow < dim_; ++iRow)
        {
            double factor = at(iRow, pivotRow) / at(pivotRow, pivotRow);

            for (int iCol = pivotRow; iCol < dim_; ++iCol) 
            {
                at(iRow, iCol) -= factor * at(pivotRow, iCol);
            }
        }
    }

};

} // namespace matrix

#endif // MATRIX_HPP


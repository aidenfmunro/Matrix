#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cmath> // nan
#include "detail/buffer.hpp" // Buffer
#include "detail/proxyrow.hpp" // ProxyRow

namespace matrix
{

template<class T> 
class Matrix
{
private:
    detail::Buffer<T> data_;
    size_t rows_;
    size_t cols_;

public:
    
    Matrix(size_t rows, size_t cols)
    :   rows_(rows),
        cols_(cols),
        data_(rows, cols, T{}) {}

    Matrix(size_t rows, size_t cols, const T& value)
    :   rows_(rows),
        cols_(cols),
        data_(rows, cols, value) {}

    Matrix(size_t dim)
    :   rows_(dim),
        cols_(dim),
        data_(dim, dim, T{}) {}

    Matrix(size_t dim, const T& value)
    :   rows_(dim),
        cols_(dim),
        data_(dim, dim, value) {}

    template<typename U>
    Matrix (const Matrix<U>& other)
    :   rows_(other.getRows()),
        cols_(other.getCols()),
        data_(other.getRows(), other.getCols())
    {
        for (size_t i = 0; i < rows_; ++i)
        {
            for (size_t j = 0; j < cols_; ++j)
            {
                data_[i][j] = static_cast<T>(other[i][j]);
            }
        }
    }

    detail::ProxyRow<T> operator[](size_t index)
    {
        return detail::ProxyRow<T>(data_[index]);
    }


    const detail::ProxyRow<T> operator[](size_t index) const
    {
        return detail::ProxyRow<T>(data_[index]);
    }

    size_t getRows() const { return rows_; }

    size_t getCols() const { return cols_; }

    double det() const
    {
        if (rows_ != cols_)
        {
            std::cerr << "can't count determinant!";

            return 0;
        }
#ifdef DEBUG 
        dump();
#endif
        size_t swapCount = 0;
        
        Matrix<double> matrixCopy = *this;
        
        if (!matrixCopy.gaussianElimination(swapCount))
        {
            return 0;
        }
#ifdef DEBUG
        matrixCopy.dump();
#endif
        double det = 1;

        for (size_t i = 0; i < cols_; ++i)
        {
            det *= matrixCopy[i][i];
        }

        return (swapCount % 2 == 0) ? det : -det;
    }
    
    bool gaussianElimination(size_t& swapCount)
    {
        for (size_t iRow = 0; iRow < rows_; ++iRow)
        {
            size_t pivotRow = findPivotRow(iRow);

            if (data_[pivotRow][iRow] == 0)
            {
                return false;
            }

            if (pivotRow != iRow)
            {
                swapRows(iRow, pivotRow);
                swapCount++;
            }

            eliminateColumn(iRow);
#ifdef DEBUG
            dump();
#endif
        }

        return true; 
    }

    void dump() const
    {
        for (size_t row = 0; row < rows_; ++row)
        {
            for (size_t col = 0; col < cols_; ++col)
            {
                 std::cerr << data_[row][col] << " ";
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

        for (size_t col = 0; col < cols_; ++col)
        {
            std::swap(data_[row1][col], data_[row2][col]);
        }
    }

    size_t findPivotRow(size_t col)
    {
        size_t maxRow = col;

        T maxElem = std::abs(data_[col][col]);

        for (size_t iCol = col + 1; iCol < cols_; iCol++)
        {
            T curElem = std::abs(data_[iCol][col]);

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
        for (size_t iRow = pivotRow + 1; iRow < rows_; ++iRow)
        {
            double factor = data_[iRow][pivotRow] / data_[pivotRow][pivotRow];

            for (int iCol = pivotRow; iCol < cols_; ++iCol) 
            {
                data_[iRow][iCol] -= factor * data_[pivotRow][iCol];
            }
        }
    }

};

} // namespace matrix

#endif // MATRIX_HPP

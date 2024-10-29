#ifndef MATRIX_HPP
#define MATRIX_HPP

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


    detail::ProxyRow<T> operator[](size_t index)
    {
        return detail::ProxyRow<T>(data_[index]);
    }

    T det() const
    {
        if (rows_ != cols_)
        {
            std::cerr << "can't count determinant!";

            return T{};
        }
#ifdef DEBUG 
        dump();
#endif
        size_t swapCount = 0;
        
        Matrix matrixCopy(*this);
        
        if (!matrixCopy.gaussianElimination(swapCount))
        {
            return 0;
        }
#ifdef DEBUG
        matrixCopy.dump();
#endif
        T det = 1;

        for (size_t i = 0; i < cols_; ++i)
        {
            det *= matrixCopy[i][i];
        }

        return (swapCount % 2 == 0) ? det : -det;
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

        T maxElem = std::abs((*this)[col][col]);

        for (size_t iCol = col + 1; iCol < cols_; iCol++)
        {
            T curElem = std::abs((*this)[iCol][col]);

            if (curElem > maxElem)
            {
                maxElem = curElem; 
                maxRow = iCol;
            }
        }

        return maxRow;
    }

    bool gaussianElimination(size_t& swapCount)
    {
        for (size_t iRow = 0; iRow < rows_; ++iRow)
        {
            size_t pivotRow = (*this).findPivotRow(iRow);

            if ((*this)[pivotRow][iRow] == 0)
            {
                return false;
            }

            if (pivotRow != iRow)
            {
                swapRows(iRow, pivotRow);
                swapCount++;
            }

            (*this).eliminateColumn(iRow);
#ifdef DEBUG
            (*this).dump();
#endif
        }

        return true; 
    }

    void eliminateColumn(size_t pivotRow) 
    {
        for (size_t iRow = pivotRow + 1; iRow < rows_; ++iRow)
        {
            T factor = (*this)[iRow][pivotRow] / (*this)[pivotRow][pivotRow];

            for (int iCol = pivotRow; iCol < cols_; ++iCol) 
            {
                (*this)[iRow][iCol] -= factor * (*this)[pivotRow][iCol];
            }
        }
    }

};

} // namespace matrix

#endif // MATRIX_HPP

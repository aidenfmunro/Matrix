#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "buffer.hpp" // Buffer
#include "proxyrow.hpp" // ProxyRow

template<class T> 
class Matrix
{
private:
    Buffer<T> buffer_;
    size_t rows_;
    size_t cols_;

public:


    ProxyRow<T> operator[](size_t row)
    {
        return ProxyRow<T>(buffer_[row * cols_]);
    }

    const ProxyRow<T> operator[](size_t row) const
    {
        return ProxyRow<T>(buffer_[row * cols_]);
    }

};

#endif // MATRIX_HPP

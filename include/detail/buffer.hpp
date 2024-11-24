#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <cstdlib> // size_t
#include <algorithm> // fill, copy
#include <utility> // move
#include "proxyrow.hpp" // ProxyRow

namespace matrix

{

namespace detail
{

template<class T>
class Buffer
{
private:
    T* data_;
    size_t size_;
    size_t cols_;

public:
    Buffer(size_t rows, size_t cols, const T& value) 
    :   data_(new T[rows * cols]),
        size_(rows * cols),
        cols_(cols)
    {
        std::fill(data_, data_ + size_, value);
    }
   
    Buffer(size_t dim, const T& value)
    :   data_(new T[dim * dim]),
        size_(dim * dim),
        cols_(dim)
    {
        std::fill(data_, data_ + size_, value);
    }

    Buffer(const Buffer& other)
    :   data_(nullptr), 
        size_(0), 
        cols_(0)
    {
        T* newData = nullptr;

        try 
        {
            newData = new T[other.size_];

            std::copy(other.data_, other.data_ + other.size_, newData);

            data_ = newData;
            size_ = other.size_;
            cols_ = other.cols_;
        } 
        catch (...) 
        {
            delete[] newData;

            throw;
        }
    }

    Buffer& operator=(const Buffer& other)
    {
        if (this == &other)
            return *this;

        Buffer tmp(other);

        swap(tmp);

        return *this;
    }

    void swap(Buffer& rhs) noexcept
    {
        std::swap(data_, rhs.data_);
        std::swap(size_, rhs.size_);
        std::swap(cols_, rhs.cols_);
    }

    Buffer(Buffer&& other) noexcept 
    :   data_(std::move(other.data_)),
        size_(other.size_),
        cols_(other.cols_)
    {
        other.data_ = nullptr;
    }

    Buffer& operator=(Buffer&& other) noexcept
    {
        if (this == &other)
            return *this;

        delete[] data_;

        data_ = std::move(other.data_); 
        size_ = other.size_;
        cols_ = other.cols_;

        other.data_ = nullptr;
    }

    ~Buffer()
    {
        delete[] data_;
    }
    
    const ProxyRow<T> operator[] (size_t index) const
    {
        return ProxyRow<T>(data_ + index * cols_);
    }

    ProxyRow<T> operator[] (size_t index)
    {
        return ProxyRow<T>(data_ + index * cols_);
    }
};

} // namespace detail

} // namespace matrix

#endif // BUFFER_HPP

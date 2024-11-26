#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <cstdlib> // size_t
#include <algorithm> // fill, copy
#include <sys/types.h>
#include <utility> // move
#include "proxyrow.hpp" // ProxyRow

namespace matrix
{

namespace detail
{

template <typename T> void construct(T *p, const T &rhs) { new (p) T(rhs); }

template<class T>
class Buffer
{
private:
    size_t size_, cols_, used_ = 0;
    T* data_ = nullptr;

public:
    Buffer() noexcept = default;

    Buffer(size_t rows, size_t cols, const T& value) 
    :   size_(rows * cols),
        cols_(cols),
        data_(static_cast<T*>(operator new(sizeof(T) * size_)))
    {
        for (size_t i = 0; i < size_; ++i)
        {
            construct(data_ + i, value);
            ++used_;
        }
    }
   
    Buffer(size_t dim, const T& value)
    :   size_(dim * dim),
        cols_(dim),
        data_(static_cast<T*>(operator new(sizeof(T) * size_)))
    {
        for (size_t i = 0; i < size_; ++i)
        {
            construct(data_ + i, value);
            ++used_;
        }
    }

    Buffer(const Buffer& other)
    :   size_(other.size_), 
        cols_(other.cols_),
        used_(other.used_),
        data_(static_cast<T*>(operator new(sizeof(T) * size_)))
    {
        for (size_t i = 0; i < size_; ++i)
        {
            construct(data_ + i, other.data_[i]);
            ++used_;
        }
    }

    Buffer& operator=(const Buffer& other)
    {
        Buffer tmp(other);

        swap(tmp);

        return *this;
    }

    void swap(Buffer& rhs) noexcept
    {
        std::swap(data_, rhs.data_);
        std::swap(size_, rhs.size_);
        std::swap(cols_, rhs.cols_);
        std::swap(used_, rhs.used_);
    }

    Buffer(Buffer&& other) noexcept 
    :   Buffer() 
    {
        swap(other);
    }

    Buffer& operator=(Buffer&& other) noexcept
    {
        Buffer moved(std::move(other));

        swap(moved);

        return *this;
    }

    ~Buffer()
    {
        if (data_)
        {
            for (size_t i = 0; i < used_; ++i)
            {
                data_[i].~T();
            }

            operator delete(data_);

            data_ = nullptr;
        }
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

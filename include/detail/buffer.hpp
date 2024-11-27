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
protected:
    T* data_ = nullptr;
    size_t size_, used_ = 0;

protected:
    Buffer(size_t size = 0)
    :   data_((size == 0) ? nullptr
                          : static_cast<T *>(::operator new(sizeof(T) * size))),
        size_(size) {}

    Buffer(const Buffer& ) = delete;
    
    Buffer& operator=(const Buffer& ) = delete;

    void swap(Buffer& rhs) noexcept
    {
        std::swap(data_, rhs.data_);
        std::swap(size_, rhs.size_);
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
};

} // namespace detail

} // namespace matrix

#endif // BUFFER_HPP

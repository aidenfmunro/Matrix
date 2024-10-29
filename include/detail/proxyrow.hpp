#ifndef PROXYROW_HPP
#define PROXYROW_HPP

#include <cstdlib> // size_t 

namespace matrix
{

namespace detail
{

template<class T>
class ProxyRow
{
private:
    T* row_;

public:
    ProxyRow(T* row) : row_(row) {}

    const T& operator[](size_t index) const { return row_[index]; }
    T& operator[](size_t index) {return row_[index]; }
};

} // namespace detail

} // namespace matrix

#endif // PROXYROW_HPP

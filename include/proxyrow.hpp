#ifndef PROXYROW_HPP
#define PROXYROW_HPP

#include <cstdlib> // size_t 

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

#endif // PROXYROW_HPP

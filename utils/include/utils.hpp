#ifndef UTILS_HPP
#define UTILS_HPP

#include <cmath>

namespace matrix
{

namespace utils
{

constexpr double EPSILON = 1e-8;

constexpr inline bool isAlmostEqual(double lhs, double rhs)
{
    return fabs(lhs - rhs) < EPSILON; 
}

} // namespace utils

} // namespace matrix

#endif // UTILS_HPP

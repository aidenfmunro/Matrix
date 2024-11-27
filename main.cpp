#include <iostream>
#include "matrix.hpp"

int main()
{
    int dim = 0;
    std::cin >> dim;

    if (dim <= 0)
    {
        std::cerr << "Incorrect input, size of matrix must be positive" << std::endl;

        return 1;
    }

    matrix::Matrix<double> matrix(static_cast<size_t>(dim));

    for (size_t row = 0; row < dim; ++row)
        for (size_t col = 0; col < dim; ++col)
            std::cin >> matrix[row][col];

    std::cout << matrix.det() << '\n';

    return 0;
}

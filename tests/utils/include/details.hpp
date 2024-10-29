#ifndef TESTS_UTILS_DETAILS_HPP
#define TESTS_UTILS_DETAILS_HPP

#include <fstream>
#include <filesystem>
#include "matrix.hpp"

namespace tests 
{

namespace utils 
{

namespace details 
{

std::string getFullPath(const std::string& relativePath) 
{
    std::filesystem::path path = std::filesystem::absolute(relativePath);
    return path.string(); 
}

double getResult(const std::string& datFilePath)
{
    std::ifstream inputFile(datFilePath);


    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file: " << datFilePath << std::endl;
        
        return 0.0;
    }

    size_t dim = 0;

    inputFile >> dim;

    Matrix<double> matrix(dim);

    for (size_t i = 0; i < dim; ++i)
    {
        for (size_t j = 0; j < dim; ++j)
        {
            inputFile >> matrix[i][j];
        }
    }

    return matrix.det();
}

double getAnswer(const std::string& ansFilePath)
{
    std::ifstream inputFile(ansFilePath);

    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file: " << ansFilePath << std::endl;
        
        return 0.0; 
    }
    double answer = 0;

    inputFile >> answer;
    
    return answer;
}

} // namespace detials

} // namespace utils

} // namespace tests

#endif // TESTS_UTILS_DETAILS_HPP

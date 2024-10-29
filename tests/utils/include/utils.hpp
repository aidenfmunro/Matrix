#ifndef TESTS_UTILS_UTILS_HPP
#define TESTS_UTILS_UTILS_HPP

#include <gtest/gtest.h>
#include "details.hpp"

namespace tests 
{

namespace utils 
{

void runTest(const std::string& testName)
{
    const std::string& testFilePath = "../tests/data/";

    double answer = details::getAnswer(details::getFullPath(testFilePath + testName + ".ans"));
    double result = details::getResult(details::getFullPath(testFilePath + testName + ".dat"));

    EXPECT_NEAR(result, answer, 10e-6);
}

} // namespace utils

} // namespace tests 

#endif // TESTS_UTILS_UTILS_HPP

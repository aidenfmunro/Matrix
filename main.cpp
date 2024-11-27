#include "matrix.hpp"

#include <exception>
#include <iostream>

struct MyInt {
    int x;
    MyInt(int x = 0) : x(x) {}

    MyInt (const MyInt &MI) {
        static int idx = 1;

        if (idx == 17)
            throw std::runtime_error("except");
        idx++;
    }    

    MyInt(MyInt &&) = delete;

    MyInt &operator=(const MyInt &) = delete;
    MyInt &operator=(MyInt &&) = delete; 

    ~MyInt() = default;
};

int main() {
    matrix::Matrix<MyInt> x(4, 4, 5);
    try {
        matrix::Matrix<MyInt> y(x);
    } catch(std::runtime_error &Err) {
        std::cerr << Err.what() << std::endl;
    }
}

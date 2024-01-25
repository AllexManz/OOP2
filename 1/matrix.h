#ifndef MATRIX_H
#define MATRIX_H
#include "vector.h"


namespace Matrix{

    struct Matrix{
        int n{}; //width
        int m{}; //length
        int c_size{};
        Vector::Vector row = {};
        Vector::Vector col = {};
        Vector::Vector val = {};
    };


    // Functions Prototypes
    void erase(Matrix& matrix);
    Matrix input();
    void output(Matrix& matrix);
    Vector::Vector calculate(Matrix& matrix);
    void print(Matrix& matrix);
}


#endif //MATRIX_H

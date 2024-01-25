#include "iostream"
#include "matrix.h"
#include "vector.h"
using std::cin, std::cout;


int main(){
    Matrix::Matrix matrix;
    Vector::Vector result;

    try{
        matrix = Matrix::input();
        result = Matrix::calculate(matrix);


        Vector::output(result);
        Matrix::print(matrix);

        Matrix::erase(matrix);
        Vector::erase(result);
    }
    catch(const std::bad_alloc &ba) { // в memory errors
        std::cerr << "Not enough memory" << std::endl;
        Matrix::erase(matrix);
        Vector::erase(result);
        return 1;
    }
    catch(const std::exception &e) { // other exceptions
        std::cerr << e.what() << std::endl;
        Matrix::erase(matrix);
        Vector::erase(result);
        return 1;
    }



    return 0;
}
#include "vector.h"
#include "matrix.h"
#include "interface.h"

namespace Matrix{

    void erase(Matrix& matrix){
        Vector::erase(matrix.row);
        Vector::erase(matrix.col);
        Vector::erase(matrix.val);
        // delete matrix;
    }

    Matrix input(){
        Matrix matrix;

        try{
            cout << "Enter m: ";
            matrix.m = InterFace::getNum<int>(0);

            cout << "Enter n: ";
            matrix.n = InterFace::getNum<int>(0);

            cout << "Enter the content of Matrix\n";
            int x;
            for (int i = 0; i < matrix.m; i++){
                for (int j = 0; j < matrix.n; j++){
                    x = InterFace::getNum<int>();
                    if (x != 0){
                        matrix.c_size ++;
                        Vector::push_back(matrix.row, i);
                        Vector::push_back(matrix.col, j);
                        Vector::push_back(matrix.val, x);
                    }
                }
            }
            output(matrix);
        }
        catch (...){
            erase(matrix);
            throw;
        }
        return matrix;
    }

    void output(Matrix& matrix){
        cout << "Matrix: \n\n";

        cout << "Row: \n";
        Vector::output(matrix.row);
        cout << "Col: \n";
        Vector::output(matrix.col);
        cout << "Val: \n";
        Vector::output(matrix.val);
    }

    Vector::Vector calculate(Matrix& matrix){
        Vector::Vector res;

        for (int i = 0; i < matrix.m; i++){
            Vector::push_back(res, 0);
        }

        int value{}, pos_row{};

        for (int i = 0; i < matrix.c_size; i++){
            if (i == 0){
                pos_row = matrix.row.arr[0];
                if (matrix.col.arr[0] == 0){
                    value = InterFace::calculate(matrix.val.arr[0]);
                }
            }

            if(pos_row != matrix.row.arr[i]){
                pos_row = matrix.row.arr[i];
                if (matrix.col.arr[i] == 0){
                    value = InterFace::calculate(matrix.val.arr[i]);
                }
            }

            if (pos_row == matrix.row.arr[i]){
                if (value == InterFace::calculate(matrix.val.arr[i])){
                    res.arr[matrix.row.arr[i]] += matrix.val.arr[i];
                }
            }
        }

        return res;
    }

    void print(Matrix& matrix){
        cout << "Matrix: \n\n";

        int cnt = 0;
        for (int i = 0; i < matrix.n; i++){
            for (int j = 0; j < matrix.m; j++){
                if (matrix.row.arr[cnt] == i){
                    if (matrix.col.arr[cnt] == j){
                        cout << matrix.val.arr[cnt] << " ";
                        cnt += 1;
                    }
                    else{
                        cout << 0 << " ";
                    }
                }
                else{
                    cout << 0 << " ";
                }
            }
            cout << '\n';
        }
        cout << "\n\n";
    }
}
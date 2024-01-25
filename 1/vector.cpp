#include <algorithm>
#include "iostream"
#include "vector.h"


namespace Vector{
    void erase(Vector& vector){
        delete [] vector.arr;
        //delete vector;
    }

    void push_back(Vector& vector, int x){
        try {
            resize(vector, vector.n + 1);
            vector.arr[vector.n - 1] = x;
        }
        catch (...) {
            throw;
        }
    }

    void resize(Vector& vector, int new_size) {
        int old_size = vector.n;
        vector.n = new_size;
        try {
            int* tmp = vector.arr;
            vector.arr = new int[new_size];
            if (new_size >= old_size)
                std::copy(tmp, tmp + old_size, vector.arr);
            else
                std::copy(tmp, tmp + new_size, vector.arr);
            delete[] tmp;
        }
        catch(...) {
            vector.n = old_size;
            throw;
        }
    }

    void output(Vector& vector){
        std::cout << "Vector \n";
        std::cout << "Vector size: " << vector.n << '\n';
        std::cout << "Vector contents: \n";
        for (int i = 0; i < vector.n; i++){
            std::cout << "i: " << i << " |Value: " << vector.arr[i] << '\n';
        }
        std::cout << '\n';
    }
}
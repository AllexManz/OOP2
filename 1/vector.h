#ifndef VECTOR_H
#define VECTOR_H

namespace Vector{
    struct Vector{
        int n{};
        int* arr = nullptr;
    };

    //Function Prototypes
    void erase(Vector& vector);
    void resize(Vector& vector, int new_size);
    void push_back(Vector& vector, int x);
    void output(Vector& vector);
}

#endif //VECTOR_H

#ifndef INTERFACE_H
#define INTERFACE_H
#include <limits>
#include <iostream>
#include <cstring>
using std::cin, std::cout;

namespace InterFace {
    template<class T>
    T getNum(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()) {
        T a;
        while (true) {
            cin >> a;
            if (cin.eof()) // End Of File
                throw std::runtime_error("Failed to read number: EOF");

            else if (cin.bad()) // Rips of the stream
                throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));

            else if (cin.fail()) { // For instance wrong data type
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "You are wrong; repeat please!" << std::endl;
            }

            else if (a >= min && a <= max)
                return a;
            else
                cout << "You are wrong; repeat please!" << '\n';
        }
    }

    int calculate(int x){
        int sum = 0;
        while (x != 0){
            sum += x % 10;
            x /= 10;
        }
        return sum;
    }
}

#endif //INTERFACE_H

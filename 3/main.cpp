#include <iostream>
#include <string>

#include "Stations/Station/Station.h"
#include "Stations/NonStopStation/NonStopStation.h"
#include "Stations/TransitionStation/TransitionStation.h"
#include "Stations/TransitionHub/TransitionHub.h"

#include "Line/Line.h"
#include "LineManager/LineManager.h"
#include <thread>

void output(){
    std::cout << "0 -- Exit the program\n";
    std::cout << "1 -- Find station by name\n";
    std::cout << "2 -- Create station\n";
    std::cout << "3 -- Create line\n";
    std::cout << "4 -- Get information about Station\n";
    std::cout << "5 -- Get information about Line\n";
    std::cout << "6 -- Get information about LineManager\n";
    std::cout << "7 -- Change station name\n";
    std::cout << "8 -- Change line name\n";
    std::cout << "9 -- Change station\n";
    std::cout << "10 -- Get Interchange\n";
}


int main(){
    int command = 1;

    LineManager manager;

    /*
    LineManager new_manager;

    auto threadNum = std::thread::hardware_concurrency();
    std::cout << "\n\nThreadNum " << threadNum << std::endl;


    Line* line1 = new Line{"line1"};
    Line* line2 = new Line{"line2"};
    Line* line3 = new Line{"line3"};
    Line* line4 = new Line{"line4"};


    line1->push_back(std::make_shared<TransitionStation>(TransitionStation{"line1", "st11"}));
    line1->push_back(std::make_shared<TransitionStation>(TransitionStation{"line1", "st12"}));
    line1->push_back(std::make_shared<TransitionStation>(TransitionStation{"line3", "st33"}));
    manager.add_line(line1);

    line2->push_back(std::make_shared<TransitionStation>(TransitionStation{"line2", "st21"}));
    line2->push_back(std::make_shared<NonStopStation>(NonStopStation{"line2", "st22"}));
    line2->push_back(std::make_shared<TransitionHub>(TransitionHub{"line3", "st32"}));
    manager.add_line(line2);

    line3->push_back(std::make_shared<TransitionStation>(TransitionStation{"line3", "st31"}));
    line3->push_back(std::make_shared<NonStopStation>(NonStopStation{"line2", "st23"}));
    line3->push_back(std::make_shared<TransitionHub>(TransitionHub{"line1", "st13"}));
    manager.add_line(line3);

    line4->push_back(std::make_shared<TransitionStation>(TransitionStation{"line4", "st41"}));
    line4->push_back(std::make_shared<NonStopStation>(NonStopStation{"line4", "st42"}));
    line4->push_back(std::make_shared<TransitionHub>(TransitionHub{"line4", "st43"}));
    manager.add_line(line4);

    manager.check_mt(new_manager.get_lines());

    manager.print(std::cout);
    */

    // /*
    while (command != 0){
        output();
        std::cin >> command;

        if (command == 0) {
            break;
        }
        else if (command == 1){
            std::cout << "Enter station name: \n";
            std::string s;
            std::cin >> s;
            try {
                manager.find_station(s)->print(std::cout);
            }
            catch(...){
                std::cout << "This station does not exist\n";
            }
        }
        else if (command == 2){
            std::cout << "Enter station name: \n";
            std::string s1;
            std::cin >> s1;

            std::cout << "Enter line name: \n";
            std::string s2;
            std::cin >> s2;

            std::cout << "1 -- For NonStopStation\n";
            std::cout << "2 -- For TransitionStation\n";
            std::cout << "3 -- For TransitionHub\n";
            int type;
            std::cin >> type;


            if (type == 1){
                NonStopStation station{s1, s2};
                try {
                    manager.find_line(s2)->push_back(std::make_shared<NonStopStation>(station));
                }
                catch(...){
                    std::cout << "This line does not exist\n";
                }
            }
            if (type == 2){
                TransitionStation station{s1, s2};
                try {
                    manager.find_line(s2)->push_back(std::make_shared<TransitionStation>(station));
                }
                catch(...){
                    std::cout << "This line does not exist\n";
                }
            }
            if (type == 3){
                TransitionHub station{s1, s2};
                try {
                    manager.find_line(s2)->push_back(std::make_shared<TransitionHub>(station));
                }
                catch(...){
                    std::cout << "This line does not exist\n";
                }
            }
        }
        else if (command == 3){
            std::cout << "Enter line name: \n";
            std::string s;
            std::cin >> s;

            Line* line = new Line{s};
            manager.add_line(line);
        }
        else if (command == 4){
            std::cout << "Enter station name: \n";
            std::string s;
            std::cin >> s;

            try{
                manager.find_station(s)->print(std::cout);
            }
            catch(...){
                std::cout << "This Station does not exist\n";
            }
        }
        else if (command == 5){
            std::cout << "Enter line name: \n";
            std::string s;
            std::cin >> s;

            try{
                manager.find_line(s)->print(std::cout);
            }
            catch(...){
                std::cout << "This Line does not exist\n";
            }
        }
        else if (command == 6){
            manager.print(std::cout);
        }
        else if (command == 7){
            std::cout << "Enter station name: \n";
            std::string s;
            std::cin >> s;


            std::cout << "Enter new station name: \n";
            std::string s1;
            std::cin >> s;

            try{
                manager.find_station(s)->set_station(s1);
            }
            catch(...){
                std::cout << "This Station does not exist\n";
            }
        }
        else if (command == 8){
            std::cout << "Enter line name: \n";
            std::string s;
            std::cin >> s;

            std::cout << "Enter new line name: \n";
            std::string s1;
            std::cin >> s;

            try{
                manager.find_line(s)->set_name(s1);
            }
            catch(...){
                std::cout << "This line does not exist\n";
            }
        }
        else if (command == 9){
            std::cout << "Enter station name: \n";
            std::string s;
            std::cin >> s;

            std::cout << "Enter new station type: \n";
            std::string s1;
            std::cin >> s;

            try{
                manager.find_line(s)->change_station(s, s1);
            }
            catch(...){
                std::cout << "This line does not exist\n";
            }
        }
        else if (command == 10){
            std::cout << "Enter station name: \n";
            std::string s;
            std::cin >> s;

            try{
                manager.find_station(s)->get_interchange();
            }
            catch(...){
                std::cout << "This Station does not exist\n";
            }
        }
    }
    // */

    return 0;
}
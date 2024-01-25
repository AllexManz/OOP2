#include <iostream>

#include "Stations/Station/Station.h"

#include "Stations/NonStopStation/NonStopStation.h"
#include "Stations/TransitionStation/TransitionStation.h"
#include "Stations/TransitionHub/TransitionHub.h"

#include "Line/Line.h"
#include "LineManager/LineManager.h"



int main() {
    std::vector<LinesPairs> temp;



    // NonStopStation
    NonStopStation nonstop{"Gold", "BMW"};
    for (const auto& pair: temp)
        std::cout << pair.line << ' ' << pair.station << '\n';
    temp = nonstop.get_interchange();
    nonstop.print(std::cout);



    // Transition Station
    TransitionStation transit{"Yellow", "HUI"};

    transit.add_line("Purple");
    transit.add_line("Green");
    transit.add_line("Brown");

    temp = transit.get_interchange();
    for (const auto& pair: temp)
        std::cout << pair.line << ' ' << pair.station << '\n';
    transit.print(std::cout);



    // TransitionHub
    TransitionHub hub{"Black", "ChanGan"};

    hub.add_data(LinesPairs("Purple", "Toyota"));
    hub.add_data(LinesPairs("Red", "Wolksvagen"));
    hub.add_data(LinesPairs("Pink", "Naruto"));

    hub.print(std::cout);



    // Line
    Line* line = new Line{"Green"};


    line->push_back(std::make_shared<NonStopStation>(nonstop));
    line->push_back(std::make_shared<TransitionStation>(transit));
    line->push_back(std::make_shared<TransitionHub>(hub));

    /*
    line.print(std::cout);
    line.find("HUI");

    line.change_station(*line.find("HUI"), "TransitionHub");
    line.find("HUI")->print(std::cout);

    line.remove("HUI");
    line.print(std::cout);
    */


    // LineManager
    LineManager manager;

    manager.add_line(line);
    std::cout<< "SIZE: " << manager.get_size() << "\n";

    std::string new_name = "White";
    manager.change_lines("Green", new_name);
    manager.print(std::cout);

    //manager.find_station("BMW")->print(std::cout);

    manager.remove_line("White");
    manager.print(std::cout);

    return 0;
}

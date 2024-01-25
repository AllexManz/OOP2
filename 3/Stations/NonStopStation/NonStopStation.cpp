#include "NonStopStation.h"




NonStopStation::NonStopStation(std::string line, std::string station){
    this->set_line(line);
    this->set_station(station);
}


std::ostream& NonStopStation::print(std::ostream &s){
    s << get_type() << '\n';

    s << "Line Name: " << get_line() << '\n';
    s << "Station Name: " << get_station() << '\n';
    s << "\n\n";

    return s;
}

std::vector<LinesPairs> NonStopStation::get_interchange(){
    std::vector<LinesPairs> ans;
    return ans;
}


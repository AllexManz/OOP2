#include "TransitionHub.h"


TransitionHub::TransitionHub(std::string line, std::string name){
    this->set_line(line);
    this->set_station(name);
}



void TransitionHub::add_data(const LinesPairs &new_data) {
    if (lines_and_stations.size() < 3)
        lines_and_stations.push_back(new_data);
    else
        throw std::length_error("Only 3 interchanges could exist at the one station");
}

std::ostream &TransitionHub::print(std::ostream &s) {
    s << get_type() << '\n';

    s << "Line Name: " << get_line() << '\n';
    s << "Station Name: " << get_station() << '\n';

    s << "Transitions:\n";
    for (const auto & line_and_station: lines_and_stations){
        s << "Line: " << line_and_station.line << " | Station: " << line_and_station.station << '\n';
    }
    s << "\n\n";

    return s;
}


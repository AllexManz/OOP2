#include "TransitionStation.h"


TransitionStation::TransitionStation(std::string line, std::string station) {
    this->set_line(line);
    this->set_station(station);
}


std::vector<LinesPairs> TransitionStation::get_interchange(){
    std::vector<LinesPairs> ans;
    for (const auto & line : lines) {
        ans.push_back(LinesPairs(line, get_station()));
        // std::cout << ans[i].line << ' ' << ans[i].station << '\n';
    }
    return ans;
}

std::ostream& TransitionStation::print(std::ostream &s){
    s << get_type() << '\n';

    s << "Line Name: " << get_line() << '\n';
    s << "Station Name: " << get_station() << '\n';

    s << "Transition Lines:\n";
    for (const auto & line : lines) {
        s << "Line: " << line << " | Station: " << get_station() << '\n';
    }
    s << "\n\n";

    return s;
}

void TransitionStation::add_line(const std::string &new_line) {
    if (lines.size() < 3)
        lines.push_back(new_line);
    else
        throw std::length_error("Only 3 interchanges could exist at the one station");
}

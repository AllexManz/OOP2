#include "Line.h"
#include "../Stations/NonStopStation/NonStopStation.h"
#include "../Stations/TransitionStation/TransitionStation.h"
#include "../Stations/TransitionHub/TransitionHub.h"

#include <utility>


Line::Line(std::string name){
    this->name = std::move(name);
}


void Line::push_back(const std::shared_ptr<Station>& new_station) {
    constexpr std::hash<std::string> hash;

    stations.insert({hash(new_station->get_station()), new_station});
}


std::shared_ptr<Station> Line::find(const std::string &exmp_name) {
    constexpr std::hash<std::string> hash;

    // std::cout << "SEARCH RESULTS:\n";
    auto result = stations.find(hash(exmp_name));

    if (result != stations.end())
        return result->second;

    throw std::invalid_argument("There is no station with this name");
}


void Line::print(std::ostream &s) {
    s << "Line: " << this->get_name() << '\n';

    s << "Stations:\n";
    for (auto & station : stations)
        s << station.second->get_station() << '\n';
    s << "\n\n";
}

void Line::change_station(const std::string& old_name, const std::string& new_type) {
    std::shared_ptr<Station> station;
    try{
        station = this->find(old_name);
    }
    catch(...){
        throw;
    }

    if (station->get_type() == new_type)
        throw std::invalid_argument("types could not be same");

    constexpr std::hash<std::string> hash;

    if(station->get_type() == "NonStopStation"){
        if (new_type == "TransitionStation") {
            TransitionStation new_station{station->get_line(), station->get_station()};

            this->remove(station->get_station());
            this->push_back(std::make_shared<TransitionStation>(new_station));

            return;
        }
        if (new_type == "TransitionHub") {
            TransitionHub new_station{station->get_line(), station->get_station()};

            this->remove(station->get_station());
            this->push_back(std::make_shared<TransitionHub>(new_station));

            return;
        }
    }

    if(station->get_type() == "TransitionStation"){
        if (new_type == "NonStopStation") {
            NonStopStation new_station{station->get_line(), station->get_station()};

            this->remove(station->get_station());
            this->push_back(std::make_shared<NonStopStation>(new_station));

            return;
        }
        if (new_type == "TransitionHub") {
            TransitionHub new_station{station->get_line(), station->get_station()};

            this->remove(station->get_station());

            for (auto & pair: new_station.get_interchange()){
                new_station.add_data(LinesPairs(pair.line, pair.station));
            }

            this->push_back(std::make_shared<TransitionHub>(new_station));

            return;
        }
    }

    if(station->get_type() == "TransitionHub"){
        if (new_type == "NonStopStation") {
            NonStopStation new_station{station->get_line(), station->get_station()};

            this->remove(station->get_station());
            this->push_back(std::make_shared<NonStopStation>(new_station));

            return;
        }
        if (new_type == "TransitionStation") {
            TransitionStation new_station{station->get_line(), station->get_station()};

            this->remove(station->get_station());
            this->push_back(std::make_shared<TransitionStation>(new_station));

            return;
        }
    }

}

void Line::remove(const std::string& exmp_name) {
    try{
        this->find(exmp_name);

        constexpr std::hash<std::string> hash;
        stations.erase(hash(exmp_name));
    }
    catch(...){
        throw;
    }
}



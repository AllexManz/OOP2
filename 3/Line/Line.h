#ifndef LINE_H
#define LINE_H

#include "../Stations/Station/Station.h"
#include "memory"
#include "map"

class Line{
    std::string name;
    std::map<size_t, std::shared_ptr<Station>> stations;
public:
    explicit Line(std::string name);

    [[nodiscard]] std::string get_name() const {return name;}
    [[nodiscard]] unsigned long get_size() const {return stations.size();}

    void set_name(std::string& new_name) {this->name = new_name;}

    void push_back(const std::shared_ptr<Station>& new_station);
    void remove(const std::string& exmp_name);

    std::shared_ptr<Station> find(const std::string& exmp_name);
    void print(std::ostream &s);
    void change_station(const std::string& name, const std::string& new_type);
};

#endif

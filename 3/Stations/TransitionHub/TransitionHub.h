#ifndef TRANSITIONHUB_H
#define TRANSITIONHUB_H

#include "../Station/Station.h"

class TransitionHub: public Station{
private:
    std::vector<LinesPairs> lines_and_stations;
public:
    TransitionHub(std::string line, std::string name);

    [[nodiscard]] std::string get_type() const override {return "TransitionHub";}
    std::ostream& print(std::ostream &s) override;
    void add_data(const LinesPairs& new_data);
    std::vector<LinesPairs> get_interchange() override;
};

#endif

#ifndef NONSTOPSTATION_H
#define NONSTOPSTATION_H

#include "../Station/Station.h"


class NonStopStation: public Station{
public:
    explicit NonStopStation(std::string line, std::string station);
    ~NonStopStation() override = default;

    std::ostream& print(std::ostream &s) override;
    std::vector<LinesPairs> get_interchange() override;
    [[nodiscard]] std::string get_type() const override {return "NonStopStation";}
};


#endif

#ifndef TRANSITIONSTATION_H
#define TRANSITIONSTATION_H

#include "../Station/Station.h"

class TransitionStation: public Station{
private:
    std::vector<std::string> lines;
public:
    explicit TransitionStation(std::string line, std::string station);
    ~TransitionStation() override = default;

    [[nodiscard]] std::string get_type() const override {return "TransitionStation";}
    std::vector<LinesPairs> get_interchange() override;
    std::ostream& print(std::ostream &s) override;
    void add_line(const std::string& new_line);
};

#endif

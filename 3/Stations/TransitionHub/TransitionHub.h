#ifndef TRANSITIONHUB_H
#define TRANSITIONHUB_H

#include "../Station/Station.h"

class TransitionHub: public Station{
private:
    std::vector<LinesPairs> lines_and_stations;
public:
    /*!
     * @brief Default constructor
     * @param line the name of the line
     * @param station the name of the station
     */
    TransitionHub(std::string line, std::string name);

    /*!
     * @brief Prints all information about the station
     * @param s A name of an output stream
     * @returns A stream with information about station
     */
    std::ostream& print(std::ostream &s) override;
    /*!
     * @brief Adds an interchange for a station
     * @param new_data A pair of a station and a line witch stand for interchange
     */
    void add_data(const LinesPairs& new_data);
    /*!
     * @brief Returns all interchanges for the station
     * @returns interchanges
     * @note Returns a vector of lines_and_stations
     */
    std::vector<LinesPairs> get_interchange() override {return lines_and_stations;};

    /*!
     * @brief Getter for a station type
     * @return station type for a specific station
     */
    [[nodiscard]] std::string get_type() const override {return "TransitionHub";}
};

#endif

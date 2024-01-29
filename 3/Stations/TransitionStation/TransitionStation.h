#ifndef TRANSITIONSTATION_H
#define TRANSITIONSTATION_H

#include "../Station/Station.h"

class TransitionStation: public Station{
private:
    std::vector<std::string> lines;
public:
    /*!
     * @brief Default constructor
     * @param line the name of the line
     * @param station the name of the station
     */
    explicit TransitionStation(std::string line, std::string station);
    /*!
     * @brief Default constructor
     */
    ~TransitionStation() override = default;

    /*!
     * @brief Returns all interchanges for the station
     * @returns interchanges
     * @note Returns a vector of LinePairs where for each value from lines stands the same station name
     */
    std::vector<LinesPairs> get_interchange() override;
    /*!
     * @brief Prints all information about the station
     * @param s A name of an output stream
     * @returns A stream with information about station
     */
    std::ostream& print(std::ostream &s) override;
    /*!
     * @brief Adds a line for a station with the ability to interchange
     * @param new_line A line witch stand for interchange
     */
    void add_line(const std::string& new_line);

    /*!
     * @brief Getter for a station type
     * @return station type for a specific station
     */
    [[nodiscard]] std::string get_type() const override {return "TransitionStation";}
};

#endif

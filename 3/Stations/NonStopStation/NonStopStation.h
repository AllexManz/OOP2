#ifndef NONSTOPSTATION_H
#define NONSTOPSTATION_H

#include "../Station/Station.h"


class NonStopStation: public Station{
public:
    /*!
     * @brief Default constructor
     * @param line the name of the line
     * @param station the name of the station
     */
    explicit NonStopStation(std::string line, std::string station);
    /*!
     * @brief Default constructor
     */
    ~NonStopStation() override = default;

    /*!
     * @brief Prints all information about the station
     * @param s A name of an output stream
     * @returns A stream with information about station
     */
    std::ostream& print(std::ostream &s) override;
    /*!
     * @brief Returns all interchanges for the station
     * @returns interchanges
     * @note Returns an empty vector
     */
    std::vector<LinesPairs> get_interchange() override;
    /*!
     * @brief Getter for a station type
     * @return station type for a specific station
     */
    [[nodiscard]] std::string get_type() const override {return "NonStopStation";}
};


#endif

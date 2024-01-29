#ifndef STATION_H
#define STATION_H

#include <iostream>
#include <vector>
#include <string>


struct LinesPairs{
    std::string line;
    std::string station;
};



// InterfaceClass
class Station{
private:
    std::string station_name;
    std::string line_name;
public:
    /*!
     * @brief Default destructor for virtual class
     */
    virtual ~Station() = default;

    /*!
     * @brief Getter for station name
     * @return station_name for a specific station
     */
    [[nodiscard]] virtual std::string get_station() const {return station_name;}
    /*!
     * @brief Getter for line name
     * @return line_name to witch this station belongs to
     */
    [[nodiscard]] virtual std::string get_line() const {return line_name;}

    /*!
     * @brief Setter for station name
     * @param new_name For a station
     */
    void set_station(std::string& new_name) {station_name = new_name;}
    /*!
     * @brief Setter for line name of a station
     * @param new_name For a line to witch this station belongs to
     */
    void set_line(std::string& new_name) {line_name = new_name;}

    /*!
     * @brief Prints all information about the station
     * @param s A name of an output stream
     * @returns A stream with information about station
     */
    virtual std::ostream& print(std::ostream &s) = 0;
    /*!
     * @brief Returns all interchanges for the station
     * @returns interchanges
     * @note Does not implemented for this type of station
     */
    virtual std::vector<LinesPairs> get_interchange() = 0;
    /*!
     * @brief Getter for a station type
     * @return station type for a specific station
     */
    [[nodiscard]] virtual std::string get_type() const {return "OrdinaryStation";}
};


#endif

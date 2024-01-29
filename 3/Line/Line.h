#ifndef LINE_H
#define LINE_H

#include "../Stations/Station/Station.h"
#include "memory"
#include "map"

class Line{
    std::string name;
    std::map<size_t, std::shared_ptr<Station>> stations;
public:
    /*!
     * @brief default constructor
     * @param the name of a line
     */
    explicit Line(std::string name);

    /*!
     * @brief Getter for a line name
     * @returns name of a line
     */
    [[nodiscard]] std::string get_name() const {return name;}
    /*!
     * @brief Getter for a line size
     * @returns a number of station in the line
     */
    [[nodiscard]] unsigned long get_size() const {return stations.size();}

    /*!
     * @brief Getter for stations
     * @returns stations in the line
     */
    std::map<size_t, std::shared_ptr<Station>> get_stations() {return stations;}
    /*!
     * @brief Setter for a line name
     * @param new_name of a line
     */
    void set_name(std::string& new_name) {this->name = new_name;}

    /*!
     * @brief Adds new station in a line
     * @param new_station A pointer to a station
     */
    void push_back(const std::shared_ptr<Station>& new_station);
    /*!
     * @brief Removes a station from the line by its name
     * @param exmp_name of a station
     */
    void remove(const std::string& exmp_name);

    /*!
     * @brief Finds a station in a line
     * @param exmp_name A name of a desired station
     * @returns A pointer to a station
     */
    std::shared_ptr<Station> find(const std::string& exmp_name);
    /*!
     * @brief Prints all information about the line
     * @param s A name of an output stream
     * @returns A stream with information about station
     */
    void print(std::ostream &s);
    /*!
     * @brief Changes station
     * @param name name of a station
     * @param new_type of a station
     */
    void change_station(const std::string& name, const std::string& new_type);
};

#endif

#ifndef LINEMANAGER_H
#define LINEMANAGER_H

#include "../Line/Line.h"

class LineManager{
private:
    std::vector<Line*> lines;
public:
    /*!
     * @brief Default destructor
     */
    ~LineManager();

    /*!
     * @brief Gets the number of lines in the manager
     * @returns The number of lines in the manager
     */
    size_t get_size() {return lines.size();}
    /*!
     * @brief Gets the lines from the manager
     * @returns Lines from the manager
     */
    std::vector<Line*> get_lines() {return lines;}
    /*!
     * @brief Changes a line name in a manager
     * @param old_name An old name of a line
     * @param new_name A new name of a line
     */
    void change_line(const std::string& old_name, std::string& new_name);
    /*!
     * @brief Adds a station to a manager
     * @param line A pointer to a new line
     */
    void add_line(Line *line) {lines.push_back( line);}
    /*!
     * @brief Removes a line from a manager
     * @param line_name A name of a line
     */
    void remove_line(const std::string& line_name);
    /*!
     * @brief Finds a line in a manager
     * @param line_name A name of a desired station
     * @returns A pointer to a line
     */
    Line* find_line(const std::string& line_name);
    /*!
     * @brief Finds a station in a manager
     * @param station A name of a desired station
     * @returns A pointer to a station
     */
    std::shared_ptr<Station> find_station(const std::string& station);
    /*!
     * @brief Prints all information about the line manager
     * @param s A name of an output stream
     * @returns A stream with information about station
     */
    void print(std::ostream& s);

    void check (auto begin, auto last, auto first_out, std::mutex* m1);

    void check_mt(std::vector<Line*> ans);
};


#endif

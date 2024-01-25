#ifndef LINEMANAGER_H
#define LINEMANAGER_H

#include "../Line/Line.h"

class LineManager{
private:
    std::vector<Line*> lines;
public:
    ~LineManager();

    size_t get_size() {return lines.size();}
    void change_line(const std::string& old_name, std::string& new_name);
    void add_line(Line *line) {lines.push_back( line);}
    void remove_line(const std::string& line_name);
    Line* find_line(const std::string& line_name);
    std::shared_ptr<Station> find_station(const std::string& station);
    void print(std::ostream& s);
    void check (const std::string line);
};


#endif

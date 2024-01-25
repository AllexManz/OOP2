#include "LineManager.h"

void LineManager::change_line(const std::string& old_name, std::string& new_name) {
    try{
        this->find_line(old_name)->set_name(new_name);
    }
    catch(...){
        throw;
    }
}

Line* LineManager::find_line(const std::string& line_name) {
    for (auto & line: lines){
        if (line->get_name() == line_name) {
            return line;
        }
    }

    throw std::invalid_argument("There is no station with this name");
}

std::shared_ptr<Station> LineManager::find_station(const std::string& station) {
    for (auto &line: lines) {
        try {
            return line->find(station);
        }
        catch (...){}
    }

    throw std::invalid_argument("There is no station with this name");
}

void LineManager::remove_line(const std::string &line_name) {
    int position = -1;

    for (size_t i = 0; i < lines.size(); i++){
        if (lines[i]->get_name() == line_name)
            position = i;
    }

    if (position == -1)
        throw std::invalid_argument("Station with this name doesn't exist");
    else
        lines.erase(lines.begin() + position);
}

void LineManager::print(std::ostream &s) {
    s << "Line Manager:\n";

    if(lines.empty()){
        s << "Empty\n";
        return;
    }

    for (auto& line: lines)
        line->print(s);
}

LineManager::~LineManager() {
    for (auto & line : lines)
        delete line;
}

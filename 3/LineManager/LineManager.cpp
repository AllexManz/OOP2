#include "LineManager.h"
#include <thread>
#include <algorithm>

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



void LineManager::check(auto begin, auto last, auto first_out, std::mutex* m1) {
    for (auto iter = begin; iter != last; iter++) {
        for (auto it = iter->get_stations().begin(); it != iter->get_stations().end(); it++) {
            if (it->second->get_line() != iter->get_name()) {
                it->second->set_line(iter->get_name());
            }

            m1->lock();
            std::vector<LinesPairs> interchanges = it->second->get_interchange();
            int i = 0;
            while (i < interchanges.size()){
                i = std::max(i, 0);
                try{
                    find_line(interchanges[i].line);
                }
                catch (...){
                    interchanges.erase(interchanges.begin() + i - 1);
                    i--;
                }
                try{
                    find_station(interchanges[i].station);
                }
                catch (...){
                    interchanges.erase(interchanges.begin() + i - 1);
                    i--;
                }
            }
            m1->unlock();
        }
    }
}



void LineManager::check_mt(std::vector<Line*> ans){
    auto threadNum = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(threadNum);
    auto lines = get_lines();
    auto elements = lines.size();

    std::mutex m1;
    for (size_t i = 0; i < threadNum; ++i) {
        size_t pos_start = i * elements / threadNum;
        size_t pos_end = (i + 1) * elements / threadNum;
        auto lines = get_lines();

        threads[i] = std::thread([pos_start, pos_end, lines, &m1, this](){

            for(int i = pos_start; i < pos_end; i++){
                auto stations = lines[i]->get_stations();
                for(auto it = stations.begin(); it != stations.end(); it++){
                    if (it->second->get_line() != lines[i]->get_name()) {
                        auto s = lines[i]->get_name();
                        it->second->set_line(s);
                    }

                    m1.lock();
                    std::vector<LinesPairs> interchanges = it->second->get_interchange();
                    int pos = 0;
                    while (pos < interchanges.size()){
                        pos = std::max(i, 0);
                        try{
                            find_line(interchanges[pos].line);
                        }
                        catch (...){
                            interchanges.erase(interchanges.begin() + pos - 1);
                            pos--;
                        }
                        try{
                            find_station(interchanges[pos].station);
                        }
                        catch (...){
                            interchanges.erase(interchanges.begin() + pos - 1);
                            pos--;
                        }
                    }
                    m1.unlock();
                }
            }
        });
    }

    for(auto& th : threads) {
        th.join();
    }
}


LineManager::~LineManager() {
    for (auto & line : lines)
        delete line;
}



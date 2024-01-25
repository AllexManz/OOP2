#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "../../Stations/Station/Station.h"
#include "../../Stations/NonStopStation/NonStopStation.h"
#include "../../Stations/TransitionStation/TransitionStation.h"
#include "../../Stations/TransitionHub/TransitionHub.h"
#include "../../Line/Line.h"
#include "../LineManager.h"


TEST_CASE("LINE_MANAGER"){
    SECTION("GET_SIZE"){
        Line* line = new Line{"A"};
        LineManager manager;

        manager.add_line(line);
        REQUIRE(manager.get_size() == 1);
    }
    SECTION("ADD_LINE"){
        Line* line = new Line{"A"};
        LineManager manager;

        manager.add_line(line);

        Line* new_line = manager.find_line("A");
        REQUIRE(new_line->get_name() == "A");
    }
    SECTION("FIND_LINE"){
        Line* line = new Line{"A"};
        LineManager manager;

        manager.add_line(line);

        Line* new_line = manager.find_line("A");
        REQUIRE(new_line->get_name() == "A");
        REQUIRE_THROWS(manager.find_line("Z"));
    }
    SECTION("FIND_STATION"){
        Line* line = new Line{"A"};
        NonStopStation station{"A", "B"};
        LineManager manager;

        line->push_back(std::make_shared<NonStopStation>(station));
        manager.add_line(line);

        std::shared_ptr new_station = manager.find_station("B");
        REQUIRE(new_station->get_station() == "B");
        REQUIRE_THROWS(manager.find_station("Z"));
    }
    SECTION("CHANGE_LINES"){
        Line* line = new Line{"A"};
        NonStopStation station{"A", "B"};
        LineManager manager;

        line->push_back(std::make_shared<NonStopStation>(station));
        manager.add_line(line);

        std::string new_name = "C";
        manager.change_line("A", new_name);
        REQUIRE(line->get_name() == "C");
        REQUIRE_THROWS(manager.change_line("Z", new_name));
    }
    SECTION("REMOVE_LINE"){
        Line* line = new Line{"A"};
        NonStopStation station{"A", "B"};
        LineManager manager;

        line->push_back(std::make_shared<NonStopStation>(station));
        manager.add_line(line);

        REQUIRE_THROWS(manager.remove_line("Z"));
        manager.remove_line("A");
        REQUIRE(manager.get_size() == 0);
    }
    SECTION("PRINT"){
        Line* line = new Line{"A"};
        NonStopStation station{"A", "B"};
        LineManager manager;

        std::stringstream out1;
        manager.print(out1);
        REQUIRE(out1.str() == "Line Manager:\nEmpty\n");

        line->push_back(std::make_shared<NonStopStation>(station));
        manager.add_line(line);

        std::stringstream out2;
        std::string ans = "Line Manager:\nLine: A\nStations:\nB\n\n\n";
        manager.print(out2);
        REQUIRE(out2.str() == ans);
    }
}
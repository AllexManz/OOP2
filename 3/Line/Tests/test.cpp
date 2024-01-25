#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "../../Stations/Station/Station.h"
#include "../../Stations/NonStopStation/NonStopStation.h"
#include "../../Stations/TransitionStation/TransitionStation.h"
#include "../../Stations/TransitionHub/TransitionHub.h"
#include "../Line.h"


TEST_CASE("Line"){
    SECTION("GET_NAME"){
        Line line{"A"};
        REQUIRE(line.get_name() == "A");
    }
    SECTION("GET_SIZE"){
        Line line{"A"};
        NonStopStation station{"A", "B"};
        line.push_back(std::make_shared<NonStopStation>(station));

        REQUIRE(line.get_size() == 1);
    }
    SECTION("SETTER"){
        Line line{"A"};
        std::string new_name = "B";
        line.set_name(new_name);

        REQUIRE(line.get_name() == new_name);
    }
    SECTION("PUSH_BACK"){
        Line line{"A"};
        NonStopStation station{"A", "B"};
        line.push_back(std::make_shared<NonStopStation>(station));

        std::stringstream out;
        std::string ans = "Line: A\nStations:\nB\n\n\n";

        line.print(out);
        REQUIRE(out.str() == ans);
    }
    SECTION("FIND"){
        Line line{"A"};
        NonStopStation station{"A", "B"};
        line.push_back(std::make_shared<NonStopStation>(station));

        std::shared_ptr<Station> new_station = line.find("B");

        REQUIRE(station.get_station() == new_station->get_station());
        REQUIRE_THROWS(line.find("Z"));
    }
    SECTION("CHANGE_STATION"){
        Line line{"A"};
        NonStopStation station{"A", "B"};

        line.push_back(std::make_shared<NonStopStation>(station));
        TransitionStation station1{"A", "C"};
        line.push_back(std::make_shared<TransitionStation>(station1));
        TransitionHub station2{"A", "D"};
        line.push_back(std::make_shared<TransitionHub>(station2));

        REQUIRE_THROWS(line.change_station("Z", "TransitionStation"));
        REQUIRE_THROWS(line.change_station("B", "NonStopStation"));

        line.change_station("B", "TransitionStation");
        REQUIRE(line.find("B")->get_type() == "TransitionStation");
        line.change_station("B", "TransitionHub");
        REQUIRE(line.find("B")->get_type() == "TransitionHub");

        line.change_station("C", "NonStopStation");
        REQUIRE(line.find("C")->get_type() == "NonStopStation");
        line.change_station("C", "TransitionHub");
        REQUIRE(line.find("C")->get_type() == "TransitionHub");

        line.change_station("D", "NonStopStation");
        REQUIRE(line.find("D")->get_type() == "NonStopStation");
        line.change_station("D", "TransitionStation");
        REQUIRE(line.find("D")->get_type() == "TransitionStation");
    }
    SECTION("REMOVE"){
        Line line{"A"};
        NonStopStation station{"A", "B"};
        line.push_back(std::make_shared<NonStopStation>(station));

        REQUIRE_THROWS(line.remove("Z"));
        line.remove("B");
        REQUIRE_THROWS(line.find("B"));
    }
    SECTION("PRINT"){
        Line line{"A"};
        NonStopStation station{"A", "B"};
        line.push_back(std::make_shared<NonStopStation>(station));

        std::stringstream out;
        std::string ans = "Line: A\nStations:\nB\n\n\n";

        line.print(out);
        REQUIRE(out.str() == ans);
    }
}
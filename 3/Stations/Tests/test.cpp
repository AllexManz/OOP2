#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "../NonStopStation/NonStopStation.h"
#include "../TransitionStation/TransitionStation.h"
#include "../TransitionHub/TransitionHub.h"



TEST_CASE("NONSTOP_STATION"){
    SECTION("GETTERS"){
        NonStopStation station{"A", "B"};
        REQUIRE(station.get_line() == "A");
        REQUIRE(station.get_station() == "B");
        REQUIRE(station.get_type() == "NonStopStation");
    }
    SECTION("GET_INTERCHANGE"){
        NonStopStation station{"A", "B"};
        REQUIRE(station.get_interchange().empty());
    }
    SECTION("PRINT"){
        NonStopStation station{"A", "B"};

        std::stringstream out;
        std::string ans = "NonStopStation\nLine Name: A\nStation Name: B\n\n\n";

        station.print(out);
        REQUIRE(out.str() == ans);
    }
}



TEST_CASE("TRANSITION_STATION"){
    SECTION("GETTERS"){
        TransitionStation station{"A", "B"};
        REQUIRE(station.get_line() == "A");
        REQUIRE(station.get_station() == "B");
        REQUIRE(station.get_type() == "TransitionStation");
    }
    SECTION("GET_INTERCHANGE"){
        std::vector<LinesPairs> res;
        TransitionStation station{"A", "B"};
        station.add_line("AA");
        station.add_line("AAA");
        station.add_line("AAAA");

        res = station.get_interchange();
        REQUIRE(res[0].station == "B");
        REQUIRE(res[0].line == "AA");
        REQUIRE(res[1].station == "B");
        REQUIRE(res[1].line == "AAA");
        REQUIRE(res[2].station == "B");
        REQUIRE(res[2].line == "AAAA");
    }
    SECTION("ADD_LINE"){
        std::vector<LinesPairs> res;
        TransitionStation station{"A", "B"};
        station.add_line("AA");
        station.add_line("AAA");
        station.add_line("AAAA");

        res = station.get_interchange();
        REQUIRE(res[0].station == "B");
        REQUIRE(res[0].line == "AA");
        REQUIRE(res[1].station == "B");
        REQUIRE(res[1].line == "AAA");
        REQUIRE(res[2].station == "B");
        REQUIRE(res[2].line == "AAAA");

        REQUIRE_THROWS(station.add_line("AAAAA"));
    }
    SECTION("PRINT"){
        TransitionStation station{"A", "B"};

        std::stringstream out;
        std::string ans = "TransitionStation\nLine Name: A\nStation Name: B\nTransition Lines:\n\n\n";

        station.print(out);
        REQUIRE(out.str() == ans);
    }
}


TEST_CASE("TransitionHub"){
    SECTION("GETTERS"){
        TransitionHub station{"A", "B"};
        REQUIRE(station.get_line() == "A");
        REQUIRE(station.get_station() == "B");
        REQUIRE(station.get_type() == "TransitionHub");
    }
    SECTION("GET_INTERCHANGE"){
        std::vector<LinesPairs> res;
        TransitionHub station{"A", "B"};

        station.add_data(LinesPairs("C", "D"));
        res = station.get_interchange();

        REQUIRE(res[0].line == "C");
        REQUIRE(res[0].station == "D");
    }
    SECTION("ADD_DATA"){
        TransitionHub station{"A", "B"};

        station.add_data(LinesPairs("C", "D"));
        station.add_data(LinesPairs("E", "F"));
        station.add_data(LinesPairs("G", "H"));

        REQUIRE_THROWS(station.add_data(LinesPairs("I", "J")));
    }
    SECTION("PRINT"){
        TransitionHub station{"A", "B"};

        station.add_data(LinesPairs("C", "D"));

        std::stringstream out;
        std::string ans = "TransitionHub\nLine Name: A\nStation Name: B\nTransitions:\nLine: C | Station: D\n\n\n";

        station.print(out);
        REQUIRE(out.str() == ans);
    }
}

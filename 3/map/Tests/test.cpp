#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "../map.h"



TEST_CASE("CONSTRUCTORS") {
    SECTION("DEFAULT_CONSTRUCTOR") {
        auto map = Map<int, int>();
        REQUIRE(map.empty());
        REQUIRE(!map.size());
        REQUIRE(map.max_size() == std::numeric_limits<int>::max());
    }
    SECTION("COPYING_CONSTRUCTOR") {
        auto map1 = Map<int, int>();
        auto map2(map1);
        REQUIRE(map1.empty() == map2.empty());
        REQUIRE(map1.size() == map2.size());
        REQUIRE(map1.max_size() == map2.max_size());
    }
    SECTION("MOVING_CONSTRUCTOR") {
        auto map1 = Map<int, int>();
        Map<int, int> map2 = Map<int, int>(map1);
        REQUIRE(map1.empty() == map2.empty());
        REQUIRE(map1.size() == map2.size());
        REQUIRE(map1.max_size() == map2.max_size());
    }
}



TEST_CASE("FUNCTIONS") {
    SECTION("INSERT") {
        auto map = Map<int, int>();
        auto el1 = Node{2, 3};
        auto el2 = Node{3, 4};
        auto el3 = Node{4, 5};

        map.insert(el1);
        REQUIRE(map.size() == 1);
        REQUIRE(!map.empty());
        map.insert(el2);
        REQUIRE(map.size() == 2);
        map.insert(el3);
        REQUIRE(map.size() == 3);
    }
    SECTION("INSERT*") {
        auto map = Map<int, int>();
        auto el1 = new Node{2, 3};
        auto el2 = new Node{3, 4};
        auto el3 = new Node{4, 5};

        map.insert(el1);
        REQUIRE(map.size() == 1);
        REQUIRE(!map.empty());
        map.insert(el2);
        REQUIRE(map.size() == 2);
        map.insert(el3);
        REQUIRE(map.size() == 3);

        delete el1;
        delete el2;
        delete el3;
    }
    SECTION("ERASE") {
        auto map = Map<int, int>();
        auto el1 = Node{2, 3};
        auto el2 = Node{3, 4};
        auto el3 = Node{4, 5};

        map.insert(el1);
        map.insert(el2);
        map.insert(el3);

        REQUIRE(map.size() == 3);

        map.erase_node(2);
        REQUIRE(map.size() == 2);

        map.erase_node(3);
        REQUIRE(map.size() == 1);

        map.erase_node(6);
        REQUIRE(map.size() == 1);

        map.erase_node(4);
        REQUIRE(map.empty());
    }
    SECTION("FIND") {
        auto map = Map<int, int>();
        auto el1 = Node{2, 3};
        auto el2 = Node{3, 4};
        auto el3 = Node{4, 5};

        map.insert(el1);
        map.insert(el2);
        map.insert(el3);

        REQUIRE(map.find(1) == map.end());
        auto f2 = map.find(2);
        REQUIRE(f2->value == 3);
    }
    SECTION("SWAP"){
        auto map1 = Map<int, int>();
        auto el1 = Node{2, 3};

        auto map2 = Map<int, int>();
        auto el2 = Node{3, 4};

        map1.insert(el1);
        map2.insert(el2);

        map1.swap(map2);

        REQUIRE(map1.find(2) == map1.end());
        REQUIRE(map1.find(3)->value == 4);

        REQUIRE(map2.find(3) == map2.end());
        REQUIRE(map2.find(2)->value == 3);
    }
}



#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "../Cards/card.cpp"

TEST_CASE("CARD_CONSTRUCTORS"){
    SECTION("ORDINARY_CONSTRUCTOR"){
        Card::Card card;
        REQUIRE(card.get_rang() == 0);
        REQUIRE(card.get_suits() == 0);
    }
    SECTION("SEED_CONSTRUCTOR"){
        Card::Card card{123};
        REQUIRE(card.get_rang() <= 12);
        REQUIRE(card.get_suits() <= 3);
    }
    SECTION("CUSTOM_CONSTRUCTOR"){
        Card::Card card{1, 1};
        REQUIRE(card.get_rang() == 1);
        REQUIRE(card.get_suits() == 1);
        REQUIRE_THROWS(Card::Card(123, 1));
        REQUIRE_THROWS(Card::Card(1, 123));
    }
}

TEST_CASE("CARD_SETTERS"){
    SECTION("RANG_SETTER"){
        Card::Card card;
        REQUIRE_THROWS(card.set_rang(-123));
        card.set_rang(11);
        REQUIRE(card.get_rang() == 11);
    }
    SECTION("SUIT_SETTER"){
        Card::Card card;
        REQUIRE_THROWS(card.set_suits(-123));
        card.set_suits(2);
        REQUIRE(card.get_suits() == 2);
    }
}

TEST_CASE("CARD_OPERATORS"){
    SECTION("<<"){
        Card::Card card;
        for (int rang = 0; rang < 13; rang++){
            for (int suit = 0; suit < 4; suit++){
                card.set_rang(rang);
                card.set_suits(suit);
                std::cout << card;
            }
        }
    }
    SECTION("<"){
        Card::Card card1{1, 1};
        Card::Card card2{2, 2};
        REQUIRE_THROWS(card1 < card2);
        card2.set_suits(1);
        REQUIRE((card1 < card2) == true);
        REQUIRE((card2 < card1) == false);
    }
    SECTION(">"){
        Card::Card card1{1, 1};
        Card::Card card2{2, 2};
        REQUIRE_THROWS(card1 > card2);
        card2.set_suits(1);
        REQUIRE((card1 > card2) == false);
        REQUIRE((card2 > card1) == true);
    }
    SECTION("<="){
        Card::Card card1{1, 1};
        Card::Card card2{2, 2};
        REQUIRE_THROWS(card1 <= card2);
        card2.set_suits(1);
        REQUIRE((card1 <= card2) == true);
        REQUIRE((card2 <= card1) == false);
    }
    SECTION(">="){
        Card::Card card1{1, 1};
        Card::Card card2{2, 2};
        REQUIRE_THROWS(card1 >= card2);
        card2.set_suits(1);
        REQUIRE((card1 >= card2) == false);
        REQUIRE((card2 >= card1) == true);
    }
    SECTION("=="){
        Card::Card card1{1, 1};
        Card::Card card2{2, 2};
        REQUIRE((card1 == card2) == false);
        card2.set_suits(1);
        card2.set_rang(1);
        REQUIRE((card1 == card2) == true);
    }
    SECTION("!="){
        Card::Card card1{1, 1};
        Card::Card card2{2, 2};
        REQUIRE((card1 != card2) == true);
        card2.set_suits(1);
        card2.set_rang(1);
        REQUIRE((card1 != card2) == false);
    }
}


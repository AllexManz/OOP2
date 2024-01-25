#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "../Deck/deck.cpp"
#include "../../Card/Cards/card.cpp"

TEST_CASE("DECK_DYNAMIC_CONSTRUCTORS"){
    SECTION("DefaultConstructor") {
        Deck::Deck deck;
        REQUIRE(deck.get_card_n() == 52);
        REQUIRE(deck.duplicate() == false);
    }
    SECTION("RandomConstructor") {
        Deck::Deck deck1(15, 1);
        REQUIRE(deck1.get_card_n() == 15);
        REQUIRE(deck1.duplicate() == false);
        REQUIRE_THROWS(Deck::Deck (60, 3));
    }
    SECTION("CopyConstructor, MoveConstructor") {
        Deck::Deck deck1(10, 1);
        Deck::Deck deck2(deck1);
        REQUIRE((deck1 == deck2) == true);
        Deck::Deck deck4(Deck::Deck (10, 1));
        REQUIRE(deck4.get_card_n() == 10);
        REQUIRE(deck4.duplicate() == false);
    }
}


TEST_CASE("GETTERS", "SETTERS"){
    SECTION("SETTERS"){
    }
}


TEST_CASE("DECK_DYNAMIC_OPERATORS"){
    SECTION("=="){
        Deck::Deck deck1;
        Deck::Deck deck2;
        Deck::Deck deck3{10, 12};
        REQUIRE(deck1 == deck2);
        REQUIRE_FALSE(deck1 == deck3);
        deck2[0].set_rang(1);
        REQUIRE((deck1 == deck2) == false);
    }
    SECTION("[]"){
        Deck::Deck deck;
        Card::Card card{0, 0};
        int index = 0;
        REQUIRE((deck[index] == card) == true);
        index = 55;
        REQUIRE_THROWS(deck[index]);
    }
    SECTION(">>"){
        Deck::Deck dec1{0, 123};
        Deck::Deck deck2{10, 123};
        Deck::Deck deck3{10, 154};
        Card::Card card = deck2[deck2.get_card_n() - 1];

        deck2 >> deck3;

        REQUIRE(deck3.get_card_n() - 2 == deck2.get_card_n());
        REQUIRE(deck3[deck3.get_card_n() - 1] == card);
        REQUIRE_THROWS(dec1 >> deck2);
    }
    SECTION("+"){
        Deck::Deck deck1{10, 123};
        Deck::Deck deck2{10, 154};
        Deck::Deck deck4;
        Deck::Deck deck3 = deck1 + deck2;
        REQUIRE(deck3.get_card_n() == (deck1.get_card_n() + deck2.get_card_n()));
        REQUIRE(deck3 == (deck1 + deck2));
        REQUIRE_THROWS(deck3 + deck4);
    }
    SECTION("COPY="){
        Deck::Deck deck1{10, 123};
        Deck::Deck deck2{10, 23};
        deck1 = deck2;
        REQUIRE((deck1 == deck2) == true);
    }
    SECTION("MOVE="){
        Deck::Deck deck1(Deck::Deck (10, 1));
        Deck::Deck deck2(Deck::Deck (20, 23));
        deck1 = (Deck::Deck (20, 23));
        REQUIRE((deck1 == deck2) == true);
    }
    SECTION("<<"){
        Deck::Deck deck;
        Deck::Deck deck1{0, 123};
        std::cout << deck1;
        std::cout << deck;
    }
    SECTION(">> input"){
        Deck::Deck deck{1, 1};
        std::cin >> deck;
    }
}

TEST_CASE("DECK_DYNAMIC_METHODS"){
    SECTION("SORT"){
        Deck::Deck deck{12, 12};
        deck.sort(1);
        for (int i = 1; i < deck.get_card_n(); i++){
            if (deck[i - 1].get_suits() == deck[i].get_suits()) {
                REQUIRE(deck[i - 1] <= deck[i]);
            }
        }
        deck.sort(-1);
        for (int i = 1; i < deck.get_card_n(); i++){
            if (deck[i - 1].get_suits() == deck[i].get_suits()) {
                REQUIRE(deck[i - 1] >= deck[i]);
            }
        }
        REQUIRE_THROWS(deck.sort(0));
    }
    SECTION("SHUFFLE"){
        Deck::Deck deck;
        deck.shuffle();
        bool flag = true;
        int cnt = 0;
        for (int suit = 0; suit < 4; suit ++){
            for (int rang = 0; rang < 13; rang++){
                if (deck[cnt].get_rang() != rang)
                    flag = false;
                if (deck[cnt].get_suits() != suit)
                    flag = false;
                cnt += 1;
            }
        }
        REQUIRE(flag == false);
    }
    SECTION("ADD"){
        Deck::Deck deck{10, 1};
        Deck::Deck deck1;
        int card_n = deck.get_card_n();
        deck.add(123);
        REQUIRE(card_n + 1 == deck.get_card_n());
        REQUIRE_THROWS(deck.add(-1));
    }
    SECTION("SEPARATE"){
        Deck::Deck deck;
        int suit = 1;
        bool flag = true;
        Deck::Deck new_deck = deck.separate(suit);
        for (int i = 0; i < new_deck.get_card_n(); i++){
            if (new_deck[i].get_suits() != suit)
                flag = false;
        }
        REQUIRE(flag == true);
        REQUIRE_THROWS(deck.separate(-1));
    }
    SECTION("DUPLICATE"){
        Deck::Deck deck;
        REQUIRE(deck.duplicate() == false);
        deck[1].set_rang(0);
        REQUIRE(deck.duplicate() == true);
    }
    SECTION("RESIZE"){
        Deck::Deck deck;
        REQUIRE_THROWS(deck.resize(-100));
    }
}





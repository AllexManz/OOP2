#include <iostream>
#include "../Card/Cards/card.h"
#include "Deck/deck.h"


int main(){
    Deck::Deck old_deck{23, 14};
    Deck::Deck new_deck{23, 15};

    old_deck.sort();
    new_deck.sort();

    std::cout << old_deck;
    std::cout << new_deck;


    old_deck >> new_deck;

    std::cout << old_deck;
    std::cout << new_deck;
    std::cout << (old_deck + new_deck);
    std::cout << new_deck.duplicate();

    std::cout << new_deck;

    std::cout << "Separated\n";
    new_deck = old_deck.separate(1);

    std::cout << new_deck;

    new_deck.shuffle();
    std::cout << new_deck;
    new_deck.add(123);
    std::cout << new_deck;

    return 0;
}
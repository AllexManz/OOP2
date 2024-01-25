#include <iostream>
#include "Cards/card.h"


int main(){
    Card::Card card;

    std::cout << card.get_rang() << ' ';
    std::cout << card.get_suits() << '\n';
    std::cout << card << '\n';

    Card::Card new_card{3, 2};

    std::cout << new_card.get_rang() << ' ';
    std::cout << new_card.get_suits() << '\n';
    std::cout << new_card;


    card.set_suits(Card::hearts);
    card.set_rang(3);

    if (card == new_card )
        std::cout << "Equal\n";
    else
        std::cout << "Different\n";

    if (card < new_card )
        std::cout << "True\n";
    else
        std::cout << "False\n";

    if (card > new_card )
        std::cout << "True\n";
    else
        std::cout << "False\n";

    if (card <= new_card )
        std::cout << "True\n";
    else
        std::cout << "False\n";

    if (card >= new_card )
        std::cout << "True\n";
    else
        std::cout << "False\n";
    return 0;
}
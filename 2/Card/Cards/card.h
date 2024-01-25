#ifndef CARD_H
#define CARD_H
#include <iostream>


namespace Card{
    enum Colours {clubs, diamonds, hearts, spades};

    class Card{
    private:
        int rang;
        int suits;
    public:
        // Constructors
        explicit Card ();
        explicit Card (int seed);
        explicit Card (int new_rang, int new_suits);
        // Cards(const Cards& card); // copy constructor
        // Cards(Cards&& card) noexcept; // move constructor

        // Setters
        Card &set_rang(int new_rang);
        Card &set_suits(int new_suits);

        // Getters
        [[nodiscard]] int get_rang() const { return rang; }
        [[nodiscard]] int get_suits() const { return suits; }

        //Overloading
        bool operator<(const Card &rhs) const;

        bool operator>(const Card &rhs) const;

        bool operator<=(const Card &rhs) const;

        bool operator>=(const Card &rhs) const;

        bool operator==(const Card &rhs) const;

        bool operator!=(const Card &rhs) const;

        //Cards& operator=(const Cards& card);

        friend std::ostream &operator<<(std::ostream &s, const Card &card);
        friend std::istream &operator>>(std::istream &in, Card &card);

    };
}

#endif //CARD_H
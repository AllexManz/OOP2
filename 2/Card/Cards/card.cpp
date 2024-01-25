#include "card.h"


namespace Card{
    Card::Card() {
        rang = 0;
        suits = 0;
    }

    Card::Card(int seed) {
        srand(seed);
        rang = rand() % 13;
        suits = rand() % 4;
    }

    Card::Card(int new_rang, int new_suits) {
        if (new_rang < 0 || new_rang > 12)
            throw std::invalid_argument("invalid rang");
        if (new_suits < 0 || new_suits > 3)
            throw std::invalid_argument("invalid suit");
        rang = new_rang;
        suits = new_suits;
    }

    Card &Card::set_rang(int new_rang) {
        if (new_rang < 0 || new_rang > 12)
            throw std::invalid_argument("invalid rang");
        rang = new_rang;
        return *this;
    }

    Card &Card::set_suits(int new_suits) {
        if (new_suits < 0 || new_suits > 3)
            throw std::invalid_argument("invalid suit");
        suits = new_suits;
        return *this;
    }

    std::ostream &operator<<(std::ostream &s, const Card &card) {
        s << "Cards: ";
        if (card.get_rang() <= 8) {
            s << card.get_rang() + 2;
        }
        else {
            if (card.get_rang() == 9)
                s << "J";
            if (card.get_rang() == 10)
                s << "Q";
            if (card.get_rang() == 11)
                s << "K";
            if (card.get_rang() == 12)
                s << "A";
        }

        if (card.get_suits() == clubs)
            s << "♣\n";
        if (card.get_suits() == diamonds)
            s << "♦\n";
        if (card.get_suits() == hearts)
            s << "♥\n";
        if (card.get_suits() == spades)
            s << "♠\n";

        return s;
    }

    /*
    Cards::Cards (const Cards &card)  {
        //if (this == &card)
            //return *this;

        this->suits = card.suits;
        this->rang = card.rang;

        //return *this;
    }

    Cards::Cards (Cards &&card) noexcept {
        //if (this == &card)
        //    return *this;

        this->suits = std::move(card.suits);
        this->rang = std::move(card.rang);

        //return *this;
    }
    */

    /*
    Cards &Cards::operator=(const Cards &card){
        if (this == &card)
            return *this;

        this->suits = card.suits;
        this->rang = card.rang;

        return *this;
    }
    */

    bool Card::operator<(const Card &rhs) const {
        if (suits != rhs.suits)
            throw std::invalid_argument("Suits should be the same");

        if (rang < rhs.rang)
            return true;
        else
            return false;
    }

    bool Card::operator>(const Card &rhs) const {
        if (suits != rhs.suits)
            throw std::invalid_argument("Suits should be the same");

        if (rang > rhs.rang)
            return true;
        else
            return false;
    }

    bool Card::operator<=(const Card &rhs) const {
        if (suits != rhs.suits)
            throw std::invalid_argument("Suits should be the same");

        if (rang <= rhs.rang)
            return true;
        else
            return false;
    }

    bool Card::operator>=(const Card &rhs) const {
        if (suits != rhs.suits)
            throw std::invalid_argument("Suits should be the same");

        if (rang >= rhs.rang)
            return true;
        else
            return false;
    }

    bool Card::operator==(const Card &rhs) const {
        if (rang == rhs.rang && suits == rhs.suits)
            return true;
        else
            return false;
    }

    bool Card::operator!=(const Card &rhs) const {
        if (rang != rhs.rang || suits != rhs.suits)
            return true;
        else
            return false;
    }

    std::istream &operator >>(std::istream &in, Card &card) {
        int suit, rang;
        in >> rang >> suit;

        if (in.good()){
            if (rang < 0 || rang > 12) {
                in.setstate(std::ios::failbit);
                if (suit < 0 || suit > 3) {
                    in.setstate(std::ios::failbit);
                    card.set_rang(rang);
                    card.set_suits(suit);
                }
            }
        }

        return in;
    }

}
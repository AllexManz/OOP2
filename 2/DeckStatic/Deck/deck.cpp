#include "deck.h"
#include <algorithm>


namespace Deck{
    Deck::Deck() {
        card_n = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 13; j++){
                cards[card_n].set_suits(i);
                cards[card_n].set_rang(j);
                card_n ++;
            }
        }
    }

    Deck::Deck(int n, int seed) {
        if (n < 0 || n > 52){
            throw std::invalid_argument("Number of cards should lesser than 53"
                                        "and be positive number");
        }

        srand(seed);

        card_n = 0;
        Card::Card temp_card;

        for (int i = 0; i < n; i++){

            while (true){
                int flag = 0;

                temp_card.set_suits(rand() % 4);
                temp_card.set_rang(rand() % 13);

                for (int j = 0; j < card_n; j++){
                    if (cards[j].get_rang() == temp_card.get_rang() &&
                        cards[j].get_suits() == temp_card.get_suits()) {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0)
                    break;
            }


            cards[card_n].set_suits(temp_card.get_suits());
            cards[card_n].set_rang(temp_card.get_rang());
            card_n ++;
        }
    }



    std::ostream &operator<<(std::ostream &s, const Deck &deck) {
        if (deck.card_n == 0){
            s << "Deck is Empty\n";
            return s;
        }

        s << "\n\nDECK:\n";
        for (int i = 0; i < deck.card_n; i++){
            s << deck.cards[i];
        }
        s << '\n';
        return s;
    }


    Card::Card Deck::pop(int n) {
        if (card_n == 0)
            throw std::out_of_range("The deck is empty");

        if (n == -1)
            n = card_n - 1;

        if (n < 0 || n >= card_n + 1)
            throw std::invalid_argument("The element does not exist");

        Card::Card card;
        card.set_rang(cards[n].get_rang());
        card.set_suits(cards[n].get_suits());
        card_n--;

        return card;
    }

    Card::Card &Deck::operator[](int index) {
        try{
            if (index < 0 || index > card_n)
                throw std::invalid_argument("index should be greater than zero and lesser that number of cards in the deck");
            return this->cards[index];
        }
        catch (...){
            throw;
        }
    }

    Deck operator+(const Deck &lhs, const Deck &rhs) {
        try {
            if (lhs.get_card_n() + rhs.get_card_n() >= Deck::get_card_max()){
                throw std::overflow_error("Number of cards in both decks should be lesser than card_max in one deck");
            }

            Deck deck{lhs.card_n + rhs.card_n, 1};

            int cnt = 0;
            for (int i = 0; i < lhs.get_card_n(); i++, cnt++) {
                deck.cards[cnt].set_rang(lhs.cards[i].get_rang());
                deck.cards[cnt].set_suits(lhs.cards[i].get_suits());
            }

            for (int i = 0; i < rhs.get_card_n(); i++, cnt++) {
                deck.cards[cnt].set_rang(rhs.cards[i].get_rang());
                deck.cards[cnt].set_suits(rhs.cards[i].get_suits());
            }

            return deck;
        }
        catch (...){
            throw;
        }
    }

    void Deck::operator>>(Deck &rhs) {
        try {
            if (this->card_n == 0)
                throw std::invalid_argument("Number of cards should be greater than zero");
            rhs.push_back(this->pop());
        }
        catch (...) {
            throw;
        }
    }

    Deck &Deck::push_back(Card::Card card) {
        try {
            if (this->card_n + 1 == Deck::Deck::card_max){
                throw std::length_error("Deck is already full");
            }
            this->cards[card_n] = card;
            this->card_n += 1;
        }
        catch (...) {
            throw;
        }
        return *this;
    }

    struct {
        bool operator()(Card::Card l, Card::Card r) {
            if (l.get_suits() < r.get_suits())
                return false;
            if (l.get_suits() > r.get_suits())
                return true;

            return l > r;
        }
    }comparator;

    void Deck::sort(int flag) {
        if (flag == -1){
            for (int i = 0; i < this->card_n; i++){
                for (int j = 0; j < this->card_n; j++){
                    if (comparator(cards[i], cards[j])){
                        Card::Card card = cards[i];
                        cards[i] = cards[j];
                        cards[j] = card;
                    }
                }
            }
            //std::sort(this->get_cards(), this->get_cards() + this->get_card_n(), comparator);
            return;
        }
        if (flag == 1){
            for (int i = 0; i < this->card_n; i++){
                for (int j = 0; j < this->card_n; j++){
                    if (!comparator(cards[i], cards[j])){
                        Card::Card card = cards[i];
                        cards[i] = cards[j];
                        cards[j] = card;
                    }
                }
            }
            //std::sort(this->get_cards(), this->get_cards() + this->get_card_n(), comparator);
            return;
        }
        throw std::invalid_argument("Wrong value of flag");
    }


    void Deck::shuffle() {
        for (int i = 0; i < card_n; i++){
            int j = rand() % card_n;
            Card::Card temp = cards[i];
            cards[i] = cards[j];
            cards[j] = temp;
        }
    }


    void Deck::add(int seed){
        try{
            if (seed < 0)
                throw std::invalid_argument("Seed should be positive");

            Card::Card card{seed};
            this->push_back(card);
        }
        catch (...){
            throw;
        }
    }


    bool Deck::duplicate() {
        try{
            for (int i = 0; i < this->card_n; i++){
                for (int j = i + 1; j < this->card_n; j++){
                    if (this->cards[i] == this->cards[j])
                        return true;
                }
            }
            return false;
        }
        catch (...){
            throw;
        }
    }

    bool Deck::operator==(const Deck &rhs) const {
        if (this->card_n != rhs.card_n)
            return false;
        for (int i = 0; i < this->card_n; i++){
            if (this->cards[i] != rhs.cards[i])
                return false;
        }
        return true;
    }

    Deck Deck::separate(int suit) {
        try {
            if (suit < 0 || suit > 3)
                throw std::invalid_argument("Suit value should be positive and less than 4");

            Deck deck{0, 1};

            for (int i = 0; i < this->card_n; i++) {
                if (this->cards[i].get_suits() == suit) {
                    deck.push_back(this->cards[i]);
                }
            }

            return deck;
        }
        catch (...){
            throw;
        }
    }

}
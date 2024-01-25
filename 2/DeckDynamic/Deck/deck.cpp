#include "deck.h"
#include <algorithm>


namespace Deck{
    Deck::Deck() {
        cards = new Card::Card[52];
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

        cards = new Card::Card[n];
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

    Deck::Deck(const Deck &deck): card_n(deck.card_n), cards(nullptr){
        if(card_n){
            cards = new Card::Card[card_n];
            std::copy(deck.cards, deck.cards + card_n, cards);
        }
    }

    Deck &Deck::operator=(const Deck &deck) {
        if (this != &deck){
            card_n = deck.card_n;
            auto new_cards = new Card::Card[card_n];
            delete [] cards;
            cards = new_cards;
            std::copy(deck.cards, deck.cards + deck.card_n, cards);
        }
        return *this;
    }

    Deck::Deck(Deck &&deck) noexcept: card_n(deck.card_n), cards(deck.cards) {
        deck.card_n = 0;
        deck.cards = nullptr;
    }

    Deck &Deck::operator=(Deck &&deck) noexcept{
        delete[] cards;
        card_n = deck.card_n;
        cards = deck.cards;
        deck.card_n = 0;
        deck.cards = nullptr;
        return *this;
    }


    Card::Card Deck::pop(int n) {
        if (get_card_n() == 0)
            throw std::out_of_range("The deck is empty");

        if (n == -1)
            n = this->get_card_n() - 1;

        if (n < 0 || n >= this->get_card_n())
            throw std::invalid_argument("The element does not exist");

        Card::Card card; //= new Card::Card;
        card.set_rang(this->cards[n].get_rang());
        card.set_suits(this->cards[n].get_suits());

        this->resize(this->card_n - 1);

        return card;
    }

    bool Deck::operator==(const Deck &rhs) const {
        if (this->card_n != rhs.card_n)
            return false;
        //std::equals
        for (int i = 0; i < this->card_n; i++){
            if (this->cards[i].get_suits() == rhs.cards[i].get_suits()) {
                if (this->cards[i] != rhs.cards[i]) {
                    return false;
                }
            }
        }
        return true;
    }

    void Deck::resize(int new_size) {
        int old_size = this->card_n;
        this->card_n = new_size;
        try {
            Card::Card* tmp = this->cards;
            this->cards = new Card::Card[new_size];
            std::copy(tmp, tmp + std::min(new_size, old_size), this->cards);
            delete[] tmp;
        }
        catch(...) {
            this->card_n = old_size;
            throw;
        }
    }

    Card::Card &Deck::operator[](int index) {
        if (index > card_n - 1 || index < 0)
            throw std::invalid_argument("index should be positive number lesser than number of cards\n");
        return this->cards[index];
    }

    Deck operator+(const Deck &l, const Deck &r) {
        Deck deck(l.card_n + r.card_n, 1); //= new Deck{l.card_n + r.card_n, 1};

        int cnt = 0;
        for (int i = 0; i < l.card_n; i++){
            deck.cards[cnt].set_rang(l.cards[i].get_rang());
            deck.cards[cnt].set_suits(l.cards[i].get_suits());
        }

        for (int i = 0; i < r.card_n; i++){
            deck.cards[cnt].set_rang(r.cards[i].get_rang());
            deck.cards[cnt].set_suits(r.cards[i].get_suits());
        }

        return deck;

    }

    void Deck::operator>>(Deck &rhs) {
        if (this->card_n == 0)
            throw std::invalid_argument("Number of cards should be greater than zero\n");
        rhs.push_back(this->pop());
    }

    Deck &Deck::push_back(Card::Card card) {
        this->resize(this->card_n + 1);
        this->cards[this->card_n - 1] = card;
        return *this;
    }

    struct comparator{
        bool operator()(Card::Card l, Card::Card r) {
            if (l.get_suits() < r.get_suits())
                return false;
            if (l.get_suits() > r.get_suits())
                return true;

            return l > r;
        }
    };

    void Deck::sort(int flag) {
        if (flag == -1){
            /*
            for (int i = 0; i < this->card_n; i++){
                for (int j = 0; j < this->card_n; j++){
                    if (comparator{}(cards[i], cards[j])){
                        Card::Card card = cards[i];
                        cards[i] = cards[j];
                        cards[j] = card;
                    }
                }
            }
            */
            std::sort(cards, cards + this->get_card_n(), comparator{});
            return;
        }
        if (flag == 1){
//            for (int i = 0; i < this->card_n; i++){
//                for (int j = 0; j < this->card_n; j++){
//                    if (!comparator(cards[i], cards[j])){
//                        Card::Card card = cards[i];
//                        cards[i] = cards[j];
//                        cards[j] = card;
//                    }
//                }
//            }
            std::sort(cards, cards + this->get_card_n(),
                      [](auto l, auto r){return !comparator{}(l, r);});
            return;
        }
        throw std::invalid_argument("Wrong value of flag");
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

    std::istream &operator >>(std::istream &in, Deck &deck) {
        for (int i = 0; i < deck.get_card_n(); i++){
            if (!in.good()){
                break;
            }
            in >> deck[i];
        }
        return in;
    }

    

    void Deck::shuffle() {
        //std::shuffle
        for (int i = 0; i < card_n; i++){
            int j = rand() % card_n;
            Card::Card temp = cards[i];
            cards[i] = cards[j];
            cards[j] = temp;
        }
    }

    void Deck::add(int seed){
        if (seed < 0)
            throw std::invalid_argument("Seed should be positive");

        Card::Card card{seed};
        this->push_back(card);
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

    Deck Deck::separate(int suit) {
        try{
            if (suit < 0 || suit > 3)
                throw std::invalid_argument("Suit value should be positive and less than 4");

            Deck deck{0, 1}; // = new Deck;

            for (int i = 0; i < this->card_n; i++){
                if (this->cards[i].get_suits() == suit){
                    deck.push_back(this->cards[i]);
                }
            }

            return deck;
        }
        catch (...){
            throw;
        }

    }

    Deck::~Deck() {
        delete[] cards;
    }
}
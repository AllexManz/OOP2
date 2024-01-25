#ifndef DECK_DYNAMIC_H
#define DECK_DYNAMIC_H
#include "../../Card/Cards/card.h"


namespace Deck{
    class Deck{
    private:
        int card_n;
        Card::Card* cards;

        /*!
         * @brief Methods that pops one Card from the top of the Deck
         * @param n = -1 Position of card to pop
         * @throw out_of_range The deck is empty
         * @throw invalid_argument The element does not exist
         */
        Card::Card pop(int n = -1);
        /*!
         * @brief Methods that pushes card Card to the top of the Deck
         * @param card Card that should be put on the top
         * @throw out_of_range The deck is empty
         * @throw invalid_argument The element does not exist
         */
        Deck& push_back(Card::Card card);
    public:
        // struct full_deck_t{};
        // static const full_deck_t full_deck;
        // explicit Deck(full_deck_t) {};
        // Deck(Deck::full_deck)
        // Constructors
        /*!
         * @brief Constructor that creates a full deck
         */
        explicit Deck ();

        /*!
         * @brief Random Constructor that creates a deck of size n filled with random cards
         * @param n number of cards
         * @param seed seed of randomness
         * @throw invalid_argument Number of cards should lesser than 53 and be positive number
         */
        explicit Deck (int n, int seed);

        /*!
         * @brief Copy Constructor
         * @param deck that should be copied
         */
        Deck(const Deck &deck);

        /*!
         * @brief Move Constructor
         * @param deck that should be moved
         */
        Deck(Deck &&deck) noexcept;

        // Getters
        /*!
         * @brief Getter that returns number of cards in the deck
         */
        [[nodiscard]] int get_card_n() const { return card_n; }
        /*!
         * @brief Getter that returns whole array of cards
         */
        [[nodiscard]] const Card::Card* get_cards() const { return cards; }

        // Overloading
        /*!
         * @brief overloaded == Operator compares two Decks
         * @param rhs Ride Hand Side example of Deck which is compared to the left one
         */
        bool operator==(const Deck &rhs) const;

        /*!
         * @brief Overloaded operator [] that returns Card from deck by index
         * @param index number of Card in the Deck that should be returned
         * @throw invalid_argument index should be greater than zero and lesser that number of cards in the deck
         */
        Card::Card& operator[](int index);

        /*!
         * @brief overloaded >> Operator that reads Deck from the stream that is given
         * @param s The stream it self
         * @param deck Deck that would be entered from the stream
         */
        friend std::istream &operator>>(std::istream &in, Deck &deck);

        /*!
         * @brief overloaded << Operator that brings Deck out in the stream that is given
         * @param s The stream it self
         * @param deck Deck that would be printed in the stream
         */
        friend std::ostream& operator<<(std::ostream &s, const Deck &deck);

        /*!
         * @brief overloaded >> Operator that shifts Card from the top of the one Deck on the top of an another
         * @param rhs Ride Hand Side example of Deck. Card should be put on that Deck
         * @throw invalid_argument Number of cards should be greater than zero
         * @throw length_error Deck is already full
         */
        void operator>>(Deck& rhs);

        /*!
         * @brief overloaded + Operator that merges two decks
         * @param l Left Hand Side Deck example
         * @param r Right Hand Side Deck example
         * @throw overflow_error Number of cards in both decks should be lesser than card_max in one deck
         */
        friend Deck operator+(const Deck& l, const Deck& r);
        /*!
         * @brief Overload = Operator to copy Deck
         * @param deck that should be copied
         */
        Deck& operator=(const Deck&);
        /*!
         * @brief Overload = Operator to move Deck
         * @param deck that should be moved
         */
        Deck& operator=(Deck&&) noexcept ;

        /*!
         * @brief Methods that resizes an array of Cards
         * @param new_size New size of an array
         */
        void resize(int new_size);

        /*!
         * @brief Methods that sorts Cards in the Deck by rang and suit
         * @param flag flag that is stands for the order
         */
        void sort(int flag = 1);

        /*!
         * @brief Methods that shuffles Cards in the random order
         * @param seed Random seed
         */
        void shuffle();

        /*!
         * @brief Methods that adds random Card to the Deck
         * @param seed Random seed for card
         * @throw invalid_argument Seed should be positive
         */
        void add(int seed);

        /*!
         * @brief Methods that searches for duplicates in the deck
         */
        bool duplicate();

        /*!
         * @brief Methods that separates Cards of certain suit from the Deck
         * @param suit Suit of the Card as an example for separation
         * @throw invalid_argument Suit value should be positive and less than 4
         */
        Deck separate(int suit);

        // Destructor
        /*!
         * @brief Destructor of Deck that cleans an array of Cards
         */
        ~Deck();
    };

}

#endif //DECK_DYNAMIC_H

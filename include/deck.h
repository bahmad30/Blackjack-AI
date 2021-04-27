#pragma once
#include "card.h"

namespace blackjack {
    
class Deck {
private:
    std::vector<Card> cards_in_deck_;
    std::vector<Card> cards_on_table_;
    
    size_t kNumRanks = 13;
    
public:
    /**
     * Constructor, creates 52 card deck
     */
    Deck();
    
    /**
     * Randomizes the order of cards_in_deck_.
     */
    void Shuffle();

    /**
     * Moves all elements in cards_on_table_ to cards_in_deck_, shuffles deck
     */
    void Reset();
    
    /**
     * Gets last card in cards_in_deck_, moves it from cards_in_deck_ to cards_on_table_
     * @return last card in cards_in_deck
     */
    Card DrawCard();
    
    // self-explanatory getters
    std::vector<Card> GetCardsInDeck() const;
    std::vector<Card> GetCardsOnTable() const;
};


} // namespace blackjack
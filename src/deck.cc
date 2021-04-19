#include "deck.h"
#include <random>

blackjack::Deck::Deck() {
    for (size_t rank = 1; rank <= kNumRanks; rank++) {
        cards_in_deck_.emplace_back(rank, 'D');
        cards_in_deck_.emplace_back(rank, 'H');
        cards_in_deck_.emplace_back(rank, 'C');
        cards_in_deck_.emplace_back(rank, 'S');
    }
    Shuffle();
}

void blackjack::Deck::Shuffle() {
    std::shuffle(cards_in_deck_.begin(), cards_in_deck_.end(), std::mt19937(std::random_device()()));
}

void blackjack::Deck::Reset() {
    for (Card& card : cards_on_table_) {
        cards_in_deck_.push_back(card);
    }
    cards_on_table_.clear();
    Shuffle();
}

blackjack::Card blackjack::Deck::DrawCard() {
    Card &card = cards_in_deck_[cards_in_deck_.size() - 1];
    cards_in_deck_.erase(cards_in_deck_.begin() + cards_in_deck_.size() - 1);
    cards_on_table_.push_back(card);
    return cards_on_table_[cards_on_table_.size() - 1];
}

std::vector<blackjack::Card> blackjack::Deck::GetCardsInDeck() const {
    return cards_in_deck_;
}

std::vector<blackjack::Card> blackjack::Deck::GetCardsOnTable() const {
    return cards_on_table_;
}


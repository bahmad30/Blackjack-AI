#pragma once

#include "deck.h"
#include "card.h"

namespace blackjack {
    
/*
 * The gameplay of blackjack
 */
class Game {
private:
    Deck deck_;
    std::vector<Card> dealer_hand_;
    std::vector<Card> player_hand_;
    int dealer_hand_value_;
    int player_hand_value_;
    
    
    float kCardWidth = 90;
    float kCardHeight = kCardWidth * 1.4f;
    float kHCardSpacing = 20;
    float kVCardSpacing = 20;
    
    float kLeftBoxWall = 50;
    float kDealerBoxTopWall = 100;
    float kBoxHeight = kCardHeight + (kVCardSpacing * 2);
    float kPlayerBoxTopWall = kDealerBoxTopWall + kBoxHeight + 150;
    
    float kHandValueMargin = 15;


public:
    /**
     * Constructor, initializes deck and calls NewRound()
     */
    Game();

    /**
     * Displays the table state.
     */
    void Display() const;
    
    /**
     * Resets deck, deals cards (1 face up 1 face down for dealer, 2 face up for player)
     */
    void NewRound();
    
    // self-explanatory getters
    std::vector<Card> GetDealerHand() const;
    std::vector<Card> GetPlayerHand() const;
    int GetDealerHandValue() const;
    int GetPlayerHandValue() const;
    
    
private:
    /**
     * Displays the box, cards, and value corresponding to a hand
     * @param is_dealer: true if displaying dealer's hand, false for player
     */
    void DisplayHand(bool is_dealer) const;
    
    /**
     * Updates the values of player's and dealer's hand.
     */
    void UpdateHandValues();

    /**
     * Calculates total value of cards in a hand.
     * @param hand of cards
     * @return sum of card values
     */
    static int CalculateHandValue(const std::vector<Card>& hand);
    
};

} // namespace blackjack
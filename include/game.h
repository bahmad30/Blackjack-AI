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
    
    void DisplayHand(bool is_dealer) const;
    
    /**
     * Resets deck, deals cards (1 face up 1 face down for dealer, 2 face up for player)
     */
    void NewRound();
    
    /**
     * Calculates total value of cards in a hand.
     * @param hand of cards
     * @return sum of card values
     */
    static int CalculateHandValue(const std::vector<Card>& hand);
    
};

} // namespace blackjack
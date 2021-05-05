#pragma once
#include "deck.h"
#include "card.h"

namespace blackjack {

class Predictor {
private:
    Deck deck_;
    std::vector<Card> player_hand_;
    int dealer_hand_value_;
    int player_hand_value_;
    
public:
    
    /**
     * Constructor.
     */
    Predictor(Deck deck, std::vector<Card> player_hand, int dealer_hand_value, int player_hand_value);
    
    /**
     * Updates the predictor's game state. 
     */
    void Update(Deck deck, std::vector<Card> player_hand, int dealer_hand_value, int player_hand_value);
    
    /**
     * Calculates the percentage of drawing a card that puts player total above 21 (bust).
     * @return percentage as float
     */
    float CalculateBustProbability() const;
    
    /**
     * Determines the best move for a player using optimal strategy.
     * @return 0 for stand, 1 for hit
     */
    int DetermineBestMove() const;
    
private:
    
};


} // namespace blackjack
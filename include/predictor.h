#pragma once
#include "deck.h"
#include "card.h"

namespace blackjack {

class Predictor {
private:
    Deck deck_;
    std::vector<Card> dealer_hand_;
    std::vector<Card> player_hand_;
    int dealer_hand_value_;
    int player_hand_value_;
    
public:
    
    /**
     * Constructor, takes in parameters as references to avoid updating.
     */
    Predictor(Deck deck, std::vector<Card> dealer_hand, std::vector<Card> player_hand, int dealer_hand_value, int player_hand_value);
    
    void Update(Deck deck, std::vector<Card> dealer_hand, std::vector<Card> player_hand, int dealer_hand_value, int player_hand_value);
    
    /**
     * Calculates the percentage of drawing a card that puts player total above 21 (bust).
     * @return percentage as float
     */
    float CalculateBustProbability() const;
    
    // determine recommended move
    
private:
    
    
};


} // namespace blackjack
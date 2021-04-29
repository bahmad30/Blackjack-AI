#pragma once
#include "game.h"

namespace blackjack {

class Predictor {
private:
    Deck& deck_;
    std::vector<Card>& dealer_hand_;
    std::vector<Card>& player_hand_;
    int& dealer_hand_value_;
    int& player_hand_value_;
    
    
public:
    /**
     * Constructor, takes in parameters as references to avoid updating.
     */
    Predictor(Deck& deck, std::vector<Card>& dealer_hand, std::vector<Card>& player_hand, int& dealer_hand_value, int& player_hand_value);
    
    /**
     * Calls CalculateBustPercentage and returns value.
     * @return percentage as float
     */
    float GetBustPercentage() const;
    
    // determine recommended move
    
    // temporary 
    void Temporary();
    
private:
    /**
     * Calculates the percentage of drawing a card that puts player total above 21 (bust).
     * @return percentage as float
     */
    float CalculateBustPercentage() const;
    
};


} // namespace blackjack
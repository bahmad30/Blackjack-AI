#include "predictor.h"


blackjack::Predictor::Predictor(Deck& deck, std::vector<Card> &dealer_hand, std::vector<Card> &player_hand, 
                                int &dealer_hand_value, int &player_hand_value) : 
                                deck_(deck), dealer_hand_(dealer_hand), player_hand_(player_hand),
                                dealer_hand_value_(dealer_hand_value), player_hand_value_(player_hand_value) {}

float blackjack::Predictor::CalculateBustPercentage() const {
    std::vector<Card> table_cards = deck_.GetCardsOnTable();
    int bust_cards = 0;
    
    for (Card &card : table_cards) {
        if (player_hand_value_ + card.GetValue() > 21) {
            bust_cards++;
        }
    }
    
    return (float)bust_cards/table_cards.size();
}

float blackjack::Predictor::GetBustPercentage() const {
    return CalculateBustPercentage();
}

void blackjack::Predictor::Temporary() {
    dealer_hand_value_ = 0;
    dealer_hand_ = {};
    player_hand_ = {};
}
                                

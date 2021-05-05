#include "predictor.h"

#include <utility>


blackjack::Predictor::Predictor(Deck deck, std::vector<Card> dealer_hand, std::vector<Card> player_hand, 
                                int dealer_hand_value, int player_hand_value) : 
                                deck_(std::move(deck)), dealer_hand_(std::move(dealer_hand)), player_hand_(std::move(player_hand)),
                                dealer_hand_value_(dealer_hand_value), player_hand_value_(player_hand_value) {}
                                
float blackjack::Predictor::CalculateBustProbability() const {
    std::vector<Card> deck_cards = deck_.GetCardsInDeck();
    int bust_cards = 0;
    
    for (Card &card : deck_cards) {
        if (player_hand_value_ + card.GetValue() > 21) {
            bust_cards++;
        }
    }
    
    return (float)bust_cards/deck_cards.size();
}

void blackjack::Predictor::Update(Deck deck, std::vector<Card> dealer_hand, std::vector<Card> player_hand, int dealer_hand_value, int player_hand_value) {
    deck_ = std::move(deck);
    dealer_hand_ = std::move(dealer_hand);
    player_hand_ = std::move(player_hand);
    dealer_hand_value_ = dealer_hand_value;
    player_hand_value_ = player_hand_value;
}


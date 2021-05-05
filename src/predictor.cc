#include "predictor.h"

#include <utility>


blackjack::Predictor::Predictor(Deck deck, std::vector<Card> player_hand, 
                                int dealer_hand_value, int player_hand_value) : 
                                deck_(std::move(deck)), player_hand_(std::move(player_hand)),
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

void blackjack::Predictor::Update(Deck deck, std::vector<Card> player_hand, int dealer_hand_value, int player_hand_value) {
    deck_ = std::move(deck);
    player_hand_ = std::move(player_hand);
    dealer_hand_value_ = dealer_hand_value;
    player_hand_value_ = player_hand_value;
}

int blackjack::Predictor::DetermineBestMove() const {
    int upcard = dealer_hand_value_;
    bool soft = std::any_of(player_hand_.begin(), player_hand_.end(), 
                            [](Card i){return i.GetValue() == 11;});
    if (!soft) {
        if (player_hand_value_ >= 17) {
            return 0;
        } else if (player_hand_value_ >= 13) {
            if (upcard <= 6) {
                return 0;
            } else {
                return 1;
            }
        } else if (player_hand_value_ == 12) {
            if (upcard == 4 || upcard == 5 || upcard == 6) {
                return 0;
            } else {
                return 1;
            }
        } else {
            return 1;
        }
    } else {
        if (player_hand_value_ >= 19) {
            return 0;
        } else if (player_hand_value_ == 18) {
            if (upcard <= 8) {
                return 0;
            } else {
                return 1;
            }
        } else {
            return 1;
        }
    }
}


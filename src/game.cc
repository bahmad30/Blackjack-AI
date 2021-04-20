#include "game.h"

using glm::vec2;

blackjack::Game::Game() {
    deck_ = Deck();
    NewRound();
}

void blackjack::Game::NewRound() {
    deck_.Reset();
    
    // deal dealer's cards
    dealer_hand_.push_back(deck_.DrawCard());
    dealer_hand_[0].Flip();
    dealer_hand_.push_back(deck_.DrawCard());
    // deal player's hand
    player_hand_.push_back(deck_.DrawCard());
    player_hand_[0].Flip();
    player_hand_.push_back(deck_.DrawCard());
    player_hand_[1].Flip();
    
    UpdateHandValues();
}

void blackjack::Game::Display() const {
    // display dealer and player hands
    DisplayHand(true);
    DisplayHand(false);
    
    // display buttons 
}

void blackjack::Game::DisplayHand(bool is_dealer) const {
    // assign variables based on dealer/player
    std::vector<Card> hand;
    int hand_value = 0;
    float top_wall = 0;
    std::string content;
    if (is_dealer) {
        hand = dealer_hand_;
        hand_value = dealer_hand_value_;
        top_wall = kDealerBoxTopWall;
        content = "Dealer hand value: ";
    } else {
        hand = player_hand_;
        hand_value = player_hand_value_;
        top_wall = kPlayerBoxTopWall;
        content = "Player hand value: ";
    }
    float box_width = kHCardSpacing + (hand.size() * (kHCardSpacing + kCardWidth));

    // display box
    ci::gl::color(ci::Color("white"));
    ci::gl::drawStrokedRoundedRect(ci::Rectf(vec2(kLeftBoxWall, top_wall),
                                      vec2(kLeftBoxWall + box_width, top_wall + kBoxHeight)), kHCardSpacing);

    // display cards
    for (size_t i = 0; i < hand.size(); i++) {
        auto i_f = float(i);
        hand[i].Display(vec2(kLeftBoxWall + (kHCardSpacing * (i_f + 1)) + (kCardWidth * i_f),
                             top_wall + kVCardSpacing));
    }

    // display hand value
    ci::gl::drawStringCentered(content + std::to_string(hand_value),
                               glm::vec2(kLeftBoxWall + box_width / 2, top_wall - kHandValueMargin),
                               ci::Color("white"));
}

void blackjack::Game::UpdateHandValues() {
    dealer_hand_value_ = CalculateHandValue(dealer_hand_);
    player_hand_value_ = CalculateHandValue(player_hand_);
}

int blackjack::Game::CalculateHandValue(const std::vector<Card>& hand) {
    int sum = 0;
    for (Card card : hand) {
        if (card.IsFaceUp()) {
            sum += card.GetValue();
        }
    }
    return sum;
}

std::vector<blackjack::Card> blackjack::Game::GetDealerHand() const {
    return dealer_hand_;
}

std::vector<blackjack::Card> blackjack::Game::GetPlayerHand() const {
    return player_hand_;
}

int blackjack::Game::GetDealerHandValue() const {
    return dealer_hand_value_;
}

int blackjack::Game::GetPlayerHandValue() const {
    return player_hand_value_;
}


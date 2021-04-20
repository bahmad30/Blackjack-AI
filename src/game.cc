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
}

void blackjack::Game::Display() const {
    // display dealer and player hands
    DisplayHand(true);
    DisplayHand(false);
    
    // display buttons 
}

void blackjack::Game::DisplayHand(bool is_dealer) const {
    std::vector<Card> hand;
    std::string content;
    float top_wall = 0;
    if (is_dealer) {
        hand = dealer_hand_;
        content = "Dealer hand value: ";
        top_wall = kDealerBoxTopWall;
    } else {
        hand = player_hand_;
        content = "Player hand value: ";
        top_wall = kPlayerBoxTopWall;
    }
    float hand_size = hand.size();
    float box_width = kHCardSpacing + (hand_size * (kHCardSpacing + kCardWidth));

    // draw box
    ci::gl::color(ci::Color("white"));
    ci::gl::drawStrokedRoundedRect(ci::Rectf(vec2(kLeftBoxWall, top_wall),
                                      vec2(kLeftBoxWall + box_width, top_wall + kBoxHeight)), kHCardSpacing);

    // display cards
    for (size_t i = 0; i < hand_size; i++) {
        auto i_f = float(i);
        hand[i].Display(vec2(kLeftBoxWall + (kHCardSpacing * (i_f + 1)) + (kCardWidth * i_f),
                             top_wall + kVCardSpacing));
    }

    // display hand value
    ci::gl::drawStringCentered(content + std::to_string(CalculateHandValue(hand)),
                               glm::vec2(kLeftBoxWall + box_width / 2, top_wall - kHandValueMargin),
                               ci::Color("white"));
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

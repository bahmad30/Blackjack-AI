#include "game.h"
#include <chrono>
#include <thread>

using glm::vec2;

blackjack::Game::Game() {
    deck_ = Deck();
    NewRound();
}

void blackjack::Game::NewRound() {
    // reset state
    deck_.Reset();
    player_bust_ = false;
    dealer_win_ = false;
    player_win_ = false;
    dealer_hand_.clear();
    player_hand_.clear();
    
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
    
    // display buttons and messages
    if (player_bust_ || dealer_win_) {
        DisplayMessage(0);
        DisplayButton(2);
    } else if (player_win_) {
        DisplayMessage(1);
        DisplayButton(2);
    } else {
        DisplayButton(0);
        DisplayButton(1);
    }
}

// handle click and helpers

void blackjack::Game::HandleClick(glm::vec2 coordinates) {
    float x = coordinates[0];
    float y = coordinates[1];
    
    if (x >= ((kWindowSize / 2) - (kButtonSpacing / 2) - kButtonWidth) && 
        x <= ((kWindowSize / 2) - (kButtonSpacing / 2)) &&
        y >= (kButtonTopWall) && y <= (kButtonTopWall + kButtonHeight)) {
        
        PlayerHit();
    } else if (x >= ((kWindowSize / 2) + (kButtonSpacing / 2)) &&
               x <= ((kWindowSize / 2) + (kButtonSpacing / 2) + kButtonWidth) &&
               y >= (kButtonTopWall) && y <= (kButtonTopWall + kButtonHeight)) {

        DealerPlay();
    } else if (x >= ((kWindowSize / 2) - (kButtonWidth / 2)) &&
                x < ((kWindowSize / 2) + (kButtonWidth / 2)) &&
                y >= (kButtonTopWall) && y <= (kButtonTopWall + kButtonHeight)) {
        
        if (player_bust_ || player_win_ || dealer_win_) {
            NewRound();
        }
    }
}

void blackjack::Game::DealerPlay() {
    dealer_hand_[1].Flip();
    UpdateHandValues();
    
    while (dealer_hand_value_ < kDealerThreshold) {
        dealer_hand_.push_back(deck_.DrawCard());
        dealer_hand_[dealer_hand_.size() - 1].Flip();
        UpdateHandValues();
    }
    
    if (dealer_hand_value_ > kTwentyOne) {
        player_win_ = true;
    } else if (dealer_hand_value_ > player_hand_value_ || dealer_hand_value_ == 21) {
        dealer_win_ = true;
    } else {
        player_win_ = true;
    }
}

void blackjack::Game::PlayerHit() {
    if (!player_bust_) {
        player_hand_.push_back(deck_.DrawCard());
        player_hand_[player_hand_.size() - 1].Flip();
        UpdateHandValues();
        
        if (player_hand_value_ == 21) {
            player_win_ = true;
        } else if (player_hand_value_ > 21) {
            player_bust_ = true;
        }
    }
}

// display helpers

void blackjack::Game::DisplayHand(bool is_dealer) const {
    // assign variables based on dealer/player
    std::vector<Card> hand;
    int hand_value;
    float top_wall;
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
    auto left_box_wall = float((0.5 * kWindowSize) - (0.5 * box_width));

    // display box
    if (top_wall == kDealerBoxTopWall) {
        ci::gl::color(ChooseOutlineColor(true));
    } else {
        ci::gl::color(ChooseOutlineColor(false));
    }
    ci::gl::drawStrokedRoundedRect(ci::Rectf(vec2(left_box_wall, top_wall),
                                      vec2(left_box_wall + box_width, top_wall + kBoxHeight)), kHCardSpacing);

    // display cards and hand value
    for (size_t i = 0; i < hand.size(); i++) {
        auto i_f = float(i);
        hand[i].Display(vec2(left_box_wall + (kHCardSpacing * (i_f + 1)) + (kCardWidth * i_f),
                             top_wall + kVCardSpacing));
    }
    ci::gl::drawStringCentered(content + std::to_string(hand_value),
                               glm::vec2((kWindowSize / 2), top_wall - kHandValueMargin),
                               ci::Color("white"));
}

void blackjack::Game::DisplayButton(int button) const {
    std::string content;
    float left_wall;
    if (button == 0) {
        content = "HIT";
        left_wall = (kWindowSize / 2) - (kButtonSpacing / 2) - kButtonWidth;
    } else if (button == 1) {
        content = "STAND";
        left_wall = (kWindowSize / 2) + (kButtonSpacing / 2);
    } else {
        content = "NEW ROUND";
        left_wall = (kWindowSize / 2) - (kButtonWidth / 2);
    }
    
    // display box
    ci::gl::color(ci::Color("lightgrey"));
    ci::gl::drawSolidRoundedRect(ci::Rectf(vec2(left_wall, kButtonTopWall), 
                                    vec2(left_wall + kButtonWidth, kButtonTopWall + kButtonHeight)), 
                                 kHCardSpacing / 2);
    ci::gl::color(ci::Color("black"));
    ci::gl::drawStrokedRoundedRect(ci::Rectf(vec2(left_wall, kButtonTopWall),
                                    vec2(left_wall + kButtonWidth, kButtonTopWall + kButtonHeight)), 
                                   kHCardSpacing / 2);
    // display text
    ci::gl::drawStringCentered(content,
                               glm::vec2(left_wall + (kButtonWidth / 2), kButtonTopWall + (kButtonHeight / 2)),
                               ci::Color("black"));
}

void blackjack::Game::DisplayMessage(int index) const {
    ci::gl::drawStringCentered(kMessages[index],
                               glm::vec2((kWindowSize / 2), kTextHeight),
                               ci::Color("white"));
}

ci::Color blackjack::Game::ChooseOutlineColor(bool is_dealer) const {
    cinder::Color color = ci::Color("white");
    if (is_dealer) {
        if (dealer_win_ || player_bust_) {
            color = ci::Color("blue");
        } else if (player_win_) {
            color = ci::Color("red");
        }
    } else {
        if (player_win_) {
            color = ci::Color("blue");
        } else if (dealer_win_ || player_bust_) {
            color = ci::Color("red");
        }
    }
    return color;
}

// update/calculate values

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

// getters

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

#include "game.h"

using glm::vec2;

blackjack::Game::Game() {
    deck_ = Deck();
    NewRound();
}

void blackjack::Game::NewRound() {
    // reset state
    deck_.Reset();
    player_bust_ = false;
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
    // display buttons
    if (player_bust_) {
        DisplayMessage(0);
        DisplayButton(2);
    } else {
        DisplayButton(0); // hit
        DisplayButton(1); // stand
    }
    
    
}

// handle clicks

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

        std::cout << "stand" << std::endl;
        
    } else if (player_bust_ && 
                x >= ((kWindowSize / 2) - (kButtonWidth / 2)) &&
                x < ((kWindowSize / 2) + (kButtonWidth / 2)) &&
                y >= (kButtonTopWall) && y <= (kButtonTopWall + kButtonHeight)) {
        
        NewRound();
    }
}

void blackjack::Game::PlayerHit() {
    if (!player_bust_) {
        player_hand_.push_back(deck_.DrawCard());
        player_hand_[player_hand_.size() - 1].Flip();
        UpdateHandValues();

        if (player_hand_value_ > 21) {
            player_bust_ = true;
            // player loses
        }
    }
}

// display helpers

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
    auto left_box_wall = float((0.5 * kWindowSize) - (0.5 * box_width));

    // display box
    ci::gl::color(ci::Color("white"));
    ci::gl::drawStrokedRoundedRect(ci::Rectf(vec2(left_box_wall, top_wall),
                                      vec2(left_box_wall + box_width, top_wall + kBoxHeight)), kHCardSpacing);

    // display cards
    for (size_t i = 0; i < hand.size(); i++) {
        auto i_f = float(i);
        hand[i].Display(vec2(left_box_wall + (kHCardSpacing * (i_f + 1)) + (kCardWidth * i_f),
                             top_wall + kVCardSpacing));
    }

    // display hand value
    ci::gl::drawStringCentered(content + std::to_string(hand_value),
                               glm::vec2((kWindowSize / 2), top_wall - kHandValueMargin),
                               ci::Color("white"));
}

void blackjack::Game::DisplayButton(int button) const {
    std::string content;
    float left_wall = 0;
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
    ci::gl::drawSolidRect(ci::Rectf(vec2(left_wall, kButtonTopWall), 
                                    vec2(left_wall + kButtonWidth, kButtonTopWall + kButtonHeight)));
    ci::gl::color(ci::Color("black"));
    ci::gl::drawStrokedRect(ci::Rectf(vec2(left_wall, kButtonTopWall),
                                    vec2(left_wall + kButtonWidth, kButtonTopWall + kButtonHeight)));
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




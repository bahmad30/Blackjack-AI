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
    dealer_win_ = false;
    player_win_ = false;
    dealer_hand_.clear();
    player_hand_.clear();
    dealer_has_ace_ = false;
    player_has_ace_ = false;
    bet_ = kInitialBet;
    
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
    // display hands and betting info
    DisplayHand(true);
    DisplayHand(false);
    DisplayBet();
    
    // display buttons and messages
    if (dealer_win_) {
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

        if (!(player_win_ || dealer_win_)) {
            PlayerHit();
        }
    } else if (x >= ((kWindowSize / 2) + (kButtonSpacing / 2)) &&
               x <= ((kWindowSize / 2) + (kButtonSpacing / 2) + kButtonWidth) &&
               y >= (kButtonTopWall) && y <= (kButtonTopWall + kButtonHeight)) {

        if (!(player_win_ || dealer_win_)) {
            DealerPlay();
        }
    } else if (x >= ((kWindowSize / 2) - (kButtonWidth / 2)) &&
                x < ((kWindowSize / 2) + (kButtonWidth / 2)) &&
                y >= (kButtonTopWall) && y <= (kButtonTopWall + kButtonHeight)) {
        
        if (player_win_ || dealer_win_) {
            NewRound();
        }
    }
}

void blackjack::Game::DealerPlay() {
    // flip face-down card
    dealer_hand_[1].Flip();
    UpdateHandValues();
    
    while (dealer_hand_value_ <= kDealerThreshold || dealer_hand_value_ <= player_hand_value_) {
        // draw card and flip
        dealer_hand_.push_back(deck_.DrawCard());
        dealer_hand_[dealer_hand_.size() - 1].Flip();
        UpdateHandValues();
        // check for ace flip low
        if (dealer_hand_value_ > kTwentyOne && dealer_has_ace_) {
            FlipAce(false, 1);
            UpdateHandValues();
        }
    }
    // check who won
    if ((dealer_hand_value_ > player_hand_value_ && dealer_hand_value_ <= kTwentyOne)) {
        dealer_win_ = true;
        balance_ -= bet_;
    } else {
        player_win_ = true;
        balance_ += payout_;
    }
}

void blackjack::Game::PlayerHit() {
    if (!dealer_win_) {
        player_hand_.push_back(deck_.DrawCard());
        player_hand_[player_hand_.size() - 1].Flip();
        UpdateHandValues();

        // check for 21
        if (player_hand_value_ == kTwentyOne) {
            player_win_ = true;
            balance_ += payout_;
        }
        // check for ace flip low
        if (player_hand_value_ > kTwentyOne && player_has_ace_) {
            FlipAce(false, 1);
            UpdateHandValues();
        }
        // check for bust
        if (player_hand_value_ > kTwentyOne) {
            dealer_win_ = true;
            balance_ -= bet_;
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
        content = "Dealer hand value: " + std::to_string(hand_value) + " ";
        top_wall = kDealerBoxTopWall;
    } else {
        hand = player_hand_;
        hand_value = player_hand_value_;
        content = "Player hand value: " + std::to_string(hand_value) + " ";
        top_wall = kPlayerBoxTopWall;
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

    // display cards
    for (size_t i = 0; i < hand.size(); i++) {
        auto i_f = float(i);
        hand[i].Display(vec2(left_box_wall + (kHCardSpacing * (i_f + 1)) + (kCardWidth * i_f),
                             top_wall + kVCardSpacing));
    }
    
    // display hand value
    if (!(dealer_win_ || player_win_)) {
        if (is_dealer && dealer_has_ace_) {
            content += "(soft)";
        } else if (!is_dealer && player_has_ace_) {
            content += "(soft)";
        }
    }
    
    ci::gl::drawStringCentered(content,
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

void blackjack::Game::DisplayBet() const {
    std::string balance = "Balance: " + 
            std::to_string(balance_).substr(0, std::to_string(balance_).find('.') + 3);
    std::string bet = "Bet: -" + 
            std::to_string(bet_).substr(0, std::to_string(bet_).find('.') + 3);
    std::string payout = "Payout: +" + 
            std::to_string(payout_).substr(0, std::to_string(payout_).find('.') + 3);

    ci::gl::drawString(balance,
                               glm::vec2(kBetTextSpacing, kBetTextSpacing),
                               ci::Color("white"));
    ci::gl::drawString(bet,
                               glm::vec2(kBetTextSpacing, kBetTextSpacing * 2),
                               ci::Color("red"));
    ci::gl::drawString(payout,
                               glm::vec2(kBetTextSpacing, kBetTextSpacing * 3),
                               ci::Color("lightgreen"));
}

ci::Color blackjack::Game::ChooseOutlineColor(bool is_dealer) const {
    cinder::Color color = ci::Color("grey");
    if (is_dealer) {
        if (dealer_win_) {
            color = kWinColor;
        } else if (player_win_) {
            color = kLoseColor;
        }
    } else {
        if (player_win_) {
            color = kWinColor;
        } else if (dealer_win_) {
            color = kLoseColor;
        }
    }
    return color;
}

// update/calculate values

void blackjack::Game::UpdateHandValues() {
    for (Card &card : dealer_hand_) {
        if (card.IsAce() && card.IsFaceUp()) {
            dealer_has_ace_ = true;
            FlipAce(true, kHighAce);
        }
    }
    for (Card &card : player_hand_) {
        if (card.IsAce()) {
            player_has_ace_ = true;
            FlipAce(false, kHighAce);
        }
    }
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

void blackjack::Game::FlipAce(bool is_dealer, int new_val) {
    if (is_dealer) {
        for (Card &card : dealer_hand_) {
            if (card.IsAce()) {
                card.SetAce(new_val);
            }
        }
    } else {
        for (Card &card : player_hand_) {
            if (card.IsAce()) {
                card.SetAce(new_val);
            }
        }
    }
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

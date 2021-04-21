#include "card.h"

blackjack::Card::Card(int rank, char suit, bool face_up) {
    if ((suit == 'D' || suit == 'H' || suit == 'C' || suit == 'S' ) && (rank > 0 && rank < 14)) {
        suit_ = suit;
        rank_ = rank;
        face_up_ = face_up;
        if (rank == 1) {
            value_ = 1;
            face_card_ = true;
            ace_ = true;
        } else if (rank > 10) {
            value_ = 10;
            face_card_ = true;
            ace_ = false;
        } else {
            value_ = rank;
            face_card_ = false;
            ace_ = false;
        }
    } else {
        throw std::invalid_argument("Card rank or suit is invalid: ");
    }
}

void blackjack::Card::Display(const glm::vec2 &left_top) const {
    ci::gl::color(ci::Color("white"));
    ci::gl::drawSolidRoundedRect(ci::Rectf(glm::vec2(left_top[0], left_top[1]),
                                           glm::vec2(left_top[0] + kCardWidth, left_top[1] + kHeight)), kCornerRadius);
    ci::gl::color(ci::Color("black"));
    ci::gl::drawStrokedRoundedRect(ci::Rectf(glm::vec2(left_top[0], left_top[1]),
                                             glm::vec2(left_top[0] + kCardWidth, left_top[1] + kHeight)), kCornerRadius);
    ci::gl::color(ci::Color("grey"));
    
    if (face_up_) {
        DisplayFaceUp(left_top);
    } else {
        ci::gl::drawSolidRect(ci::Rectf(glm::vec2(left_top[0] + kMargin,
                                                  left_top[1] + kMargin),
                                        glm::vec2(left_top[0] + kCardWidth - kMargin,
                                                  left_top[1] + kHeight - kMargin)));
    }
}

void blackjack::Card::DisplayFaceUp(const glm::vec2& left_top) const {
    ci::gl::drawStrokedRect(ci::Rectf(glm::vec2(left_top[0] + kMargin,
                                           left_top[1] + kMargin),
                                      glm::vec2(left_top[0] + kCardWidth - kMargin,
                                           left_top[1] + kHeight - kMargin)));
    // convert rank to A,J,Q,K if needed
    std::string rank;
    if (ace_) {
        rank = "A";
    } else if (face_card_) {
        if (rank_ == 11) {
            rank = "J";
        } else if (rank_ == 12) {
            rank = "Q";
        } else {
            rank = "K";
        }
    } else {
        rank = std::to_string(rank_);
    }
    std::string content = rank + " of " + suit_;
    
    // draw text on card, red if D/H, black otherwise
    if (suit_ == 'D' || suit_ == 'H') {
        ci::gl::drawStringCentered(content,
                                   glm::vec2(left_top[0] + kCardWidth / 2, left_top[1] + kHeight / 2),
                                   ci::Color("red"));
    } else {
        ci::gl::drawStringCentered(content,
                                   glm::vec2(left_top[0] + kCardWidth / 2, left_top[1] + kHeight / 2),
                                   ci::Color("black"));
    }
}

void blackjack::Card::SetAce(int value) {
    if (ace_) {
        if (value == 1 || value == 11) {
            value_ = value;
        } else {
            throw std::invalid_argument("Ace cannot be given value: " + std::to_string(value));
        }
    } else {
        throw std::invalid_argument("Card is not an ace");
    }
}

void blackjack::Card::Flip() {
    face_up_ = !face_up_;
}

// getters

int blackjack::Card::GetRank() const {
    return rank_;
}

char blackjack::Card::GetSuit() const {
    return suit_;
}

int blackjack::Card::GetValue() const {
    return value_;
}

bool blackjack::Card::IsFaceCard() const {
    return face_card_;
}

bool blackjack::Card::IsAce() const {
    return ace_;
}

bool blackjack::Card::IsFaceUp() const {
    return face_up_;
}

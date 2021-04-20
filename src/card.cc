#include "card.h"

blackjack::Card::Card(int rank, char suit) {
    if ((suit == 'D' || suit == 'H' || suit == 'C' || suit == 'S' ) && (rank > 0 && rank < 14)) {
        suit_ = suit;
        rank_ = rank;
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
        throw std::invalid_argument("Card [rank, suit] is invalid: "
                                    "[" + std::to_string(rank) + ", " + suit + "]");
    }
}

void blackjack::Card::Draw(const glm::vec2& left_top, bool face_up) const {
    ci::gl::color(ci::Color("white"));
    ci::gl::drawSolidRoundedRect(ci::Rectf(vec2(left_top[0], left_top[1]),
                                    vec2(left_top[0] + kWidth, left_top[1] + kHeight)), 10);
    ci::gl::color(ci::Color("black"));
    ci::gl::drawStrokedRoundedRect(ci::Rectf(vec2(left_top[0], left_top[1]),
                                           vec2(left_top[0] + kWidth, left_top[1] + kHeight)), 10);
    ci::gl::color(ci::Color("grey"));
    
    if (!face_up) {
        ci::gl::drawSolidRect(ci::Rectf(vec2(left_top[0] + kMargin,
                                             left_top[1] + kMargin),
                                        vec2(left_top[0] + kWidth - kMargin,
                                             left_top[1] + kHeight - kMargin)));
    } else {
        DrawFaceUp(left_top);
    }
}

void blackjack::Card::DrawFaceUp(const vec2& left_top) const {
    ci::gl::drawStrokedRect(ci::Rectf(vec2(left_top[0] + kMargin,
                                           left_top[1] + kMargin),
                                      vec2(left_top[0] + kWidth - kMargin,
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
                                   vec2(left_top[0] + kWidth/2, left_top[1] + kHeight/2),
                                   ci::Color("red"));
    } else {
        ci::gl::drawStringCentered(content,
                                   vec2(left_top[0] + kWidth/2, left_top[1] + kHeight/2),
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

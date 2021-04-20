#pragma once

#include "gameplay.h"

namespace blackjack {
    
using glm::vec2;
    
class Card {
private:
    // card identities
    int rank_; // number on card (A=1, J=11, Q=12, K=13)
    char suit_;
    int value_; // value in blackjack
    bool face_card_;
    bool ace_;
    
    // card dimensions for drawing
    float kWidth = 90;
    float kHeight = kWidth * 1.4f;
    float kMargin = kWidth/12;
    
public:
    /**
     * Constructor, populates all private variables. 
     * Throws invalid_argument if given bad params.
     * @param rank of card 1-13
     * @param suit of card D,H,C,S
     */
    Card(int rank, char suit);

    /**
     * Draws a card.
     * @param left_top coordinates of card vec2(left, top)
     * @param face_up status of card
     */
    void Draw(const vec2& left_top, bool face_up) const;
    
    /**
     * Allows value of ace to be changed to 1 or 11. 
     * Throws invalid_argument if given bad param or card is not ace.
     * @param value of new ace
     */
    void SetAce(int value);
    
    // self-explanatory getters
    int GetRank() const;
    char GetSuit() const;
    int GetValue() const;
    bool IsFaceCard() const;
    bool IsAce() const;
    
private:
    /**
     * Draws the face-up version of a card.
     * @param left_top coordinates of card vec2(left, top)
     */
    void DrawFaceUp(const vec2& left_top) const;
    
};


} // namespace blackjack
#pragma once
#include "cinder/gl/gl.h" // don't delete this

namespace blackjack {
    
class Card {
private:
    // card identities
    int rank_; // number on card (A=1, J=11, Q=12, K=13)
    char suit_;
    int value_; // value in blackjack
    bool face_up_;
    bool face_card_;
    bool ace_;
    
    // constants
    float kCardWidth = 90;
    float kHeight = kCardWidth * 1.4f;
    float kMargin = kCardWidth / 12;
    float kCornerRadius = 10;
    
    int kHighAce = 11;
    int kFaceCard = 10;
    
    
public:
    /**
     * Constructor, populates all private variables. 
     * Throws invalid_argument if given bad params.
     * @param rank of card 1-13
     * @param suit of card D,H,C,S
     */
    Card(int rank, char suit, bool face_up);

    /**
     * Draws a card.
     * @param left_top coordinates of card vec2(left, top)
     * @param face_up status of card
     */
    void Display(const glm::vec2 &left_top) const;
    
    /**
     * Allows value of ace to be changed to 1 or 11. 
     * Throws invalid_argument if given bad param or card is not ace.
     * @param value of new ace
     */
    void SetAce(int value);
    
    /**
     * Flips the face_up_ boolean.
     */
    void Flip();
    
    // self-explanatory getters
    int GetRank() const;
    char GetSuit() const;
    int GetValue() const;
    bool IsFaceUp() const;
    bool IsFaceCard() const;
    bool IsAce() const;
    
private:
    /**
     * Draws the face-up version of a card.
     * @param left_top coordinates of card vec2(left, top)
     */
    void DisplayFaceUp(const glm::vec2& left_top) const;
    
};


} // namespace blackjack
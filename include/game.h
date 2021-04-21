#pragma once

#include "deck.h"
#include "card.h"

namespace blackjack {
    
/*
 * The gameplay of blackjack
 */
class Game {
private:
    Deck deck_;
    std::vector<Card> dealer_hand_;
    std::vector<Card> player_hand_;
    int dealer_hand_value_;
    int player_hand_value_;
    
    bool player_bust_ = false;
    
    float kWindowSize = 700;
    
    float kCardWidth = 90;
    float kCardHeight = kCardWidth * 1.4f;
    float kHCardSpacing = 20;
    float kVCardSpacing = 20;
    
    float kDealerBoxTopWall = 100;
    float kBoxHeight = kCardHeight + (kVCardSpacing * 2);
    float kPlayerBoxTopWall = kDealerBoxTopWall + kBoxHeight + 100;
    float kHandValueMargin = 15;

    float kButtonTopWall = kPlayerBoxTopWall + kBoxHeight + 50;
    float kButtonWidth = 100;
    float kButtonHeight = 60;
    float kButtonSpacing = 100;
    
    float kTextHeight = kDealerBoxTopWall + kBoxHeight + 45;
    std::vector<std::string> kMessages = {"You lost! \nClick 'NEW ROUND' to try again.",
                                          "You won! \nClick 'NEW ROUND' to play again."};

public:
    /**
     * Constructor, initializes deck and calls NewRound()
     */
    Game();

    /**
     * Displays the table state.
     */
    void Display() const;
    
    /**
     * Resets deck, deals cards (1 face up 1 face down for dealer, 2 face up for player)
     */
    void NewRound();
    
    void HandleClick(glm::vec2 coordinates);
    
    // self-explanatory getters
    std::vector<Card> GetDealerHand() const;
    std::vector<Card> GetPlayerHand() const;
    int GetDealerHandValue() const;
    int GetPlayerHandValue() const;
    
    
private:
    /**
     * Displays the box, cards, and value corresponding to a hand.
     * @param is_dealer: true if displaying dealer's hand, false for player
     */
    void DisplayHand(bool is_dealer) const;
    
    /**
     * Displays the hit and stand buttons for player.
     * @param is_hit: is true if displaying the hit button, false for stand button
     */
    void DisplayButton(int button) const;
    
    /**
     * Displays a index based on outcome of round.
     * @param index that corresponds to message in kMessages
     */
    void DisplayMessage(int index) const;
    
    /**
     * Adds another face-up card to players hand, updates hand value, checks for bust.
     */
    void PlayerHit();
    
    /**
     * Updates the values of player's and dealer's hand.
     */
    void UpdateHandValues();

    /**
     * Calculates total value of cards in a hand.
     * @param hand of cards
     * @return sum of card values
     */
    static int CalculateHandValue(const std::vector<Card>& hand);
    
};

} // namespace blackjack
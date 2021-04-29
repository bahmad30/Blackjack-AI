#pragma once

#include "deck.h"
#include "card.h"

namespace blackjack {
    
class Game {
private:
    Deck deck_;
    std::vector<Card> dealer_hand_;
    std::vector<Card> player_hand_;
    int dealer_hand_value_{};
    int player_hand_value_{};
    bool dealer_win_{};
    bool player_win_{};
    bool dealer_has_ace_{};
    bool player_has_ace_{};

    float balance_ = 100;
    float kPayoutMultiplier = 2;
    float kInitialBet = 10;
    float bet_ = kInitialBet;
    float payout_ = kPayoutMultiplier * bet_;
    

public:
    /**
     * Constructor, initializes deck and calls NewRound.
     */
    Game();

    /**
     * Displays the table state.
     */
    void Display() const;
    
    /**
     * Resets deck, deals cards (1 face up 1 face down for dealer, 2 face up for player).
     */
    void NewRound();
    
    /**
     * Handles a click and dispatches accordingly if click is on a button.
     * @param coordinates of click
     */
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
     * Displays the balance, bet, and payout.
     */
    void DisplayBet() const;
    
    /**
     * Adds another face-up card to player's hand, updates hand value, checks for bust.
     */
    void PlayerHit();
    
    /**
     * Adds face-up card to dealer's hand until value >= 17.
     */
    void DealerPlay();
    
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
     
     /**
      * Changes the value of an ace card.
      * @param is_dealer true if dealer
      * @param new_val of ace
      */
     void FlipAce(bool is_dealer, int new_val);
    
     /**
      * Selects color for box outline based on game state.
      * @param is_dealer: true if dealer, false if player
      * @return color for outline
      */
     ci::Color ChooseOutlineColor(bool is_dealer) const;
    
private:
    // constants
    int kDealerThreshold = 17;
    int kTwentyOne = 21;
    int kHighAce = 11;
    
    float kWindowSize = 700;

    float kCardWidth = 90;
    float kCardHeight = kCardWidth * 1.4f;
    float kHCardSpacing = 20;
    float kVCardSpacing = 20;

    float kDealerBoxTopWall = 80;
    float kBoxHeight = kCardHeight + (kVCardSpacing * 2);
    float kPlayerBoxTopWall = kDealerBoxTopWall + kBoxHeight + 100;
    float kHandValueMargin = 15;

    float kButtonTopWall = kPlayerBoxTopWall + kBoxHeight + 70;
    float kButtonWidth = 100;
    float kButtonHeight = 60;
    float kButtonSpacing = 100;
    
    float kBetTextSpacing = 20;

    float kTextHeight = kDealerBoxTopWall + kBoxHeight + 45;
    std::vector<std::string> kMessages = {"You lost! \nClick 'NEW ROUND' to try again.",
                                          "You won! \nClick 'NEW ROUND' to play again."};
    ci::Color kWinColor = "lightgreen";
    ci::Color kLoseColor = "red";
};


} // namespace blackjack
#pragma once

#include "deck.h"
#include "card.h"
#include "predictor.h"

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
    bool dealer_soft_{};
    bool player_soft_{};

    Predictor predictor_ = Predictor({}, {}, 0, 0);
    float bust_probability_ = 0;
    int best_move_ = 0;

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

    /**
     * Adds another face-up card to player's hand, updates hand value, checks for bust.
     */
    void PlayerHit();

    /**
     * Adds face-up card to dealer's hand until value >= 17.
     */
    void DealerPlay();
    
    // self-explanatory getters
    Deck GetDeck() const;
    std::vector<Card> GetDealerHand() const;
    std::vector<Card> GetPlayerHand() const;
    int GetDealerHandValue() const;
    int GetPlayerHandValue() const;
    bool IsRoundOver() const;
    int GetWinner() const; // 0 = no winner, 1 = dealer win, 2 = player win
    float GetBalance() const;
    
private:
    /**
     * Displays the probability of the next card being a bust and the reccomended move.
     */
    void DisplayPredictor() const;
    
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
     * Updates the values of player's and dealer's hand.
     */
    void UpdateHands();
    
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
    void SetAce(bool is_dealer, int new_val);
    
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
    float kPlayerBoxTopWall = kDealerBoxTopWall + kBoxHeight + 70;
    float kHandValueMargin = 15;

    float kButtonTopWall = kPlayerBoxTopWall + kBoxHeight + 40;
    float kButtonWidth = 100;
    float kButtonHeight = 60;
    float kButtonSpacing = 100;
    
    float kPredictorTextHeight = kButtonTopWall + kButtonHeight + 30;
    
    float kBetTextSpacing = 20;

    float kTextHeight = ((kDealerBoxTopWall + kBoxHeight + kPlayerBoxTopWall) / 2) - 5;
    std::vector<std::string> kMessages = {"You lost! Click 'NEW ROUND' to try again.",
                                          "You won! Click 'NEW ROUND' to play again."};
    ci::Color kWinColor = "lightgreen";
    ci::Color kLoseColor = "red";
};


} // namespace blackjack
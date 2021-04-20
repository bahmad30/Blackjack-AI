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
    
public:
    Game();
    
    /**
     * Displays the container walls and the current positions of the particles.
     */
    void Display() const;
    
    /**
     * Updates the positions and velocities of all particles (based on the rules
     * described in the assignment documentation).
     */
    //void AdvanceOneFrame();
};

} // namespace blackjack
#pragma once

#include "cinder/gl/gl.h"

namespace blackjack {

class Gameplay {
public:
    /**
     * Displays the container walls and the current positions of the particles.
     */
    void Display() const;
    
    
    /**
     * Updates the positions and velocities of all particles (based on the rules
     * described in the assignment documentation).
     */
    void AdvanceOneFrame();
};

} // namespace blackjack
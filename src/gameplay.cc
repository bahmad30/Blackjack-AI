#include "gameplay.h"

using glm::vec2;
    
void blackjack::Gameplay::Display() const {
    
    ci::gl::color(ci::Color("white"));
    ci::gl::drawStrokedRect(ci::Rectf(vec2(100, 100), vec2(600, 400)));
}

void blackjack::Gameplay::AdvanceOneFrame() {
    
}

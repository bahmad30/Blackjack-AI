#include "card.h"
#include "game.h"

using glm::vec2;
    
void blackjack::Game::Display() const {
    //ci::gl::color(ci::Color("white"));
    //ci::gl::drawStrokedRect(ci::Rectf(vec2(100, 100), vec2(600, 400)));
    
    Card card(1, 'D');
    card.Draw(vec2(100, 100), true);

    Card card2(10, 'C');
    card2.Draw(vec2(300, 100), false);
}

void blackjack::Game::AdvanceOneFrame() {
    
}

#include "game.h"


blackjack::Game::Game() {
    deck_ = Deck();
}

void blackjack::Game::Display() const {
    //ci::gl::color(ci::Color("white"));
    //ci::gl::drawStrokedRect(ci::Rectf(vec2(100, 100), vec2(600, 400)));
    
    Card card(1, 'D', false);
    card.Draw(glm::vec2(100, 100));

    Card card2(10, 'C', false);
    card2.Draw(glm::vec2(300, 100));
}


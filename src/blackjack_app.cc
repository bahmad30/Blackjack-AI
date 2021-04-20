#include "blackjack_app.h"



blackjack::BlackjackApp::BlackjackApp() {
    ci::app::setWindowSize(kWindowSize, kWindowSize);
    game_ = Game();
}

void blackjack::BlackjackApp::draw() {
    ci::Color background_color(ci::Color("darkgreen"));
    ci::gl::clear(background_color);

    game_.Display();
}

/*
void BlackjackApp::update() {
    gameplay_.AdvanceOneFrame();
}
 */
    
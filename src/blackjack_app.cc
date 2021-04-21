#include "blackjack_app.h"


blackjack::BlackjackApp::BlackjackApp() {
    ci::app::setWindowSize(kWindowSize, kWindowSize);
    ci::app::getWindow()->setTitle(kTitle);
    game_ = Game();
}

void blackjack::BlackjackApp::draw() {
    ci::Color background_color(ci::Color("darkgreen"));
    ci::gl::clear(background_color);
    game_.Display();
}

void blackjack::BlackjackApp::mouseDown(cinder::app::MouseEvent event) {
    game_.HandleClick(event.getPos());
}

    
#include "blackjack_app.h"

namespace blackjack {

    BlackjackApp::BlackjackApp() {
        ci::app::setWindowSize(kWindowSize, kWindowSize);
    }

    void BlackjackApp::draw() {
        ci::Color background_color(ci::Color("green"));
        ci::gl::clear(background_color);

        gameplay_.Display();
    }

    void BlackjackApp::update() {
        gameplay_.AdvanceOneFrame();
    }
    
}  // namespace blackjack
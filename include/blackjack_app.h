#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "game.h"


namespace blackjack {

/**
 * An app for blackjack game.
 */
class BlackjackApp : public ci::app::App {
    public:
        BlackjackApp();

        // for displaying on screen
        void draw() override;
        
        // for clicking buttons
        void mouseDown(ci::app::MouseEvent event) override;
        
        const int kWindowSize = 700;
        const std::string kTitle = "Blackjack";

    private:
        Game game_;
};

}  // namespace blackjack
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

        void draw() override;
        void mouseDown(ci::app::MouseEvent event) override;
        
        
        const int kWindowSize = 700;

    private:
        Game game_;
};

}  // namespace blackjack
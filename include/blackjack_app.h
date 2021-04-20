#pragma once

#include "Cinder/app/App.h"
#include "Cinder/app/RendererGl.h"
#include "Cinder/gl/gl.h"
#include "game.h"


namespace blackjack {

/**
 * An app for blackjack game.
 */
class BlackjackApp : public ci::app::App {
    public:
        BlackjackApp();

        void draw() override;
        void update() override;

        // TODO: Delete this comment. Feel free to play around with these variables
        
        const int kWindowSize = 600;
        const int kMargin = 100;

    private:
        Gameplay gameplay_;
};

}  // namespace blackjack
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

        // TODO: Add input functions here
        
        const int kWindowSize = 600;

    private:
        Game gameplay_;
};

}  // namespace blackjack
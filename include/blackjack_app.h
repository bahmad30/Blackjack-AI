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
private:
    Game game_;

    bool home_screen_;
    bool play_screen_;
    bool simulation_screen_;
    
public:
    BlackjackApp();

    // for displaying on screen
    void draw() override;
    
    // for clicking buttons
    void mouseDown(ci::app::MouseEvent event) override;
    
    const float kWindowSize = 700;
    const std::string kTitle = "Blackjack AI";

private:
    void DisplayHomeScreen() const;
    void DisplayBackButton() const;
    void HandleClick(glm::vec2 coordinates);   
    
public:
    const float kButtonTopWall = kWindowSize / 2;
    const float kButtonWidth = 100;
    const float kButtonHeight = 60;
    const float kPlayButtonLeftWall = kWindowSize / 2 - 30 - kButtonWidth;
    const float kSimButtonLeftWall = kWindowSize / 2 + 30;

    const float kTextHeight = kButtonTopWall - 40;
    const float kRounding = 10;
    const float kBoxLeftWall = kPlayButtonLeftWall - 40;
    const float kBoxRightWall = kSimButtonLeftWall + kButtonWidth + 40;
    const float kBoxTopWall = kTextHeight - 40;
    const float kBoxBottomWall = kButtonTopWall + kButtonHeight + 40;

    const float kBackButtonTopWall = 15;
    const float kBackButtonWidth = 60;
    const float kBackButtonLeftWall = kWindowSize - kBackButtonWidth - 15;
    const float kBackButtonHeight = 40;
};

}  // namespace blackjack
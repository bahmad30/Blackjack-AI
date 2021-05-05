#include "blackjack_app.h"


blackjack::BlackjackApp::BlackjackApp() {
    ci::app::setWindowSize(kWindowSize, kWindowSize);
    ci::app::getWindow()->setTitle(kTitle);
    game_ = Game();
    home_screen_ = true;
    play_screen_ = false;
    simulation_screen_ = false;
}

void blackjack::BlackjackApp::draw() {
    
    
    if (home_screen_) {
        ci::Color background_color(ci::Color("navy"));
        ci::gl::clear(background_color);
        DisplayHomeScreen();
    } else if (play_screen_) {
        ci::Color background_color(ci::Color("navy"));
        ci::gl::clear(background_color);
        game_.Display();
        DisplayBackButton();
    } else if (simulation_screen_) {
        ci::Color background_color(ci::Color("navy"));
        ci::gl::clear(background_color);
        // display sim
        DisplayBackButton();
    }
}

void blackjack::BlackjackApp::mouseDown(cinder::app::MouseEvent event) {
    if (home_screen_) {
        HandleClick(event.getPos());
    } else if (play_screen_) {
        game_.HandleClick(event.getPos());
        HandleClick(event.getPos());
    } else if (simulation_screen_) {
        // sim handle click
        HandleClick(event.getPos());
    }
}

void blackjack::BlackjackApp::HandleClick(glm::vec2 coordinates) {
    float x = coordinates[0];
    float y = coordinates[1];

    if (x >= (kPlayButtonLeftWall) &&
        x <= (kPlayButtonLeftWall + kButtonWidth) &&
        y >= (kButtonTopWall) && y <= (kButtonTopWall + kButtonHeight) && home_screen_) {

        home_screen_ = false;
        simulation_screen_ = false;
        play_screen_ = true;
    } else if (x >= (kSimButtonLeftWall) &&
               x <= (kSimButtonLeftWall + kButtonWidth) &&
               y >= (kButtonTopWall) && y <= (kButtonTopWall + kButtonHeight) && home_screen_) {

        home_screen_ = false;
        play_screen_ = false;
        simulation_screen_ = true;
    } else if (x >= (kBackButtonLeftWall) &&
               x <= (kBackButtonLeftWall + kBackButtonWidth) &&
               y >= (kBackButtonTopWall) && y <= (kBackButtonTopWall + kBackButtonHeight) && !home_screen_) {
        
        play_screen_ = false;
        simulation_screen_ = false;
        home_screen_ = true;
    }
}

void blackjack::BlackjackApp::DisplayBackButton() const {
    ci::gl::color(ci::Color("lightgrey"));
    ci::gl::drawSolidRoundedRect(ci::Rectf(glm::vec2(kBackButtonLeftWall, kBackButtonTopWall),
                                           glm::vec2(kBackButtonLeftWall + kBackButtonWidth, kBackButtonTopWall + kBackButtonHeight)),
                                 10);
    ci::gl::color(ci::Color("black"));
    ci::gl::drawStrokedRoundedRect(ci::Rectf(glm::vec2(kBackButtonLeftWall, kBackButtonTopWall),
                                             glm::vec2(kBackButtonLeftWall + kBackButtonWidth, kBackButtonTopWall + kBackButtonHeight)),
                                   10);
    ci::gl::drawStringCentered("BACK",
                               glm::vec2(kBackButtonLeftWall + (kBackButtonWidth / 2), kBackButtonTopWall + (kBackButtonHeight / 2)),
                               ci::Color("black"));
}

void blackjack::BlackjackApp::DisplayHomeScreen() const {
    ci::gl::drawStringCentered("Welcome to Blackjack AI",
                               glm::vec2(kWindowSize / 2, kTextHeight),
                               ci::Color("white"));
    ci::gl::color(ci::Color("white"));
    ci::gl::drawStrokedRoundedRect(ci::Rectf(glm::vec2(kBoxLeftWall, kBoxTopWall),
                                             glm::vec2(kBoxRightWall, kBoxBottomWall)),
                                   kRounding);

    // display play button
    ci::gl::color(ci::Color("white"));
    ci::gl::drawSolidRoundedRect(ci::Rectf(glm::vec2(kPlayButtonLeftWall, kButtonTopWall),
                                           glm::vec2(kPlayButtonLeftWall + kButtonWidth, kButtonTopWall + kButtonHeight)),
                                 kRounding);
    ci::gl::color(ci::Color("black"));
    ci::gl::drawStrokedRoundedRect(ci::Rectf(glm::vec2(kPlayButtonLeftWall, kButtonTopWall),
                                             glm::vec2(kPlayButtonLeftWall + kButtonWidth, kButtonTopWall + kButtonHeight)),
                                   kRounding);
    ci::gl::drawStringCentered("PLAY",
                               glm::vec2(kPlayButtonLeftWall + (kButtonWidth / 2), kButtonTopWall + (kButtonHeight / 2)),
                               ci::Color("black"));

    // display simulate button
    ci::gl::color(ci::Color("white"));
    ci::gl::drawSolidRoundedRect(ci::Rectf(glm::vec2(kSimButtonLeftWall, kButtonTopWall),
                                           glm::vec2(kSimButtonLeftWall + kButtonWidth, kButtonTopWall + kButtonHeight)),
                                 10);
    ci::gl::color(ci::Color("black"));
    ci::gl::drawStrokedRoundedRect(ci::Rectf(glm::vec2(kSimButtonLeftWall, kButtonTopWall),
                                             glm::vec2(kSimButtonLeftWall + kButtonWidth, kButtonTopWall + kButtonHeight)),
                                   10);
    ci::gl::drawStringCentered("SIMULATE",
                               glm::vec2(kSimButtonLeftWall + (kButtonWidth / 2), kButtonTopWall + (kButtonHeight / 2)),
                               ci::Color("black"));
}

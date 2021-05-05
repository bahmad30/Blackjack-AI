#pragma once
#include "game.h"
#include "predictor.h"

namespace blackjack {

class Simulator {
private:
    Game game_;
    Predictor predictor_ = Predictor({}, {}, 0, 0);
    bool simulating_;
    
    int rounds_ = 0;
    float profit_ = 0;
    int wins_ = 0;
    int loses_ = 0;
    float win_percentage_ = 0;
    int win_streak_ = 0;
    
    float kWindowSize = 700;
    
public:
    Simulator();
    
    void RunSimulation(int sims);
    
    void Display() const;
    
    void HandleClick(glm::vec2 coordinates);
    
    void AnalyzeRecord(const std::vector<int>& record);
    
private:
    void UpdatePredictor();
    void DisplayButtons(int button) const;
    void DisplayAnalysis() const;
    void DisplayBets() const;

    std::vector<int> kSims{1000, 10000, 100000};
    float kButtonTopWall = 160;
    float kButtonWidth = 120;
    float kButtonHeight = 60;
    float kFirstLeftWall = (kWindowSize / 4) - ( kButtonWidth / 2);
    float kMiddleLeftWall = (2 * kWindowSize / 4) - ( kButtonWidth / 2);
    float kLastLeftWall = (3 * kWindowSize / 4) - ( kButtonWidth / 2);
    
    float kBoxWidth = 300;
    float kBoxLeftWall = (kWindowSize - kBoxWidth) / 2;
    float kBoxTopWall = kButtonTopWall + kButtonHeight + 100;
    float kBoxHeight = 280;
    
    float kRounding = 10;
    float kTextSpacing = 40;
    std::string kBalance = "Starting Balance: 100.00";
    std::string kBet = "Bet: -10.00";
    std::string kPayout = "Payout: +20.00";
};


} // namespace blackjack
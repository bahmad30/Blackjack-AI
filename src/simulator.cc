#include "simulator.h"


blackjack::Simulator::Simulator() {
    game_ = Game();
    UpdatePredictor();
    simulating_ = false;
}

void blackjack::Simulator::RunSimulation(int sims) {
    std::vector<int> record;
    
    for (size_t round = 0; round < sims; round++) {
        UpdatePredictor();
        
        while (!game_.IsRoundOver()) {
            if (predictor_.DetermineBestMove() == 0) {
                game_.DealerPlay();
            } else {
                game_.PlayerHit();
            }
            UpdatePredictor();
        }
        
        if (game_.GetWinner() == 1) {
            record.emplace_back(0);
        } else if (game_.GetWinner() == 2) {
            record.emplace_back(1);
        }
        
        game_.NewRound();
    }
    rounds_ = sims;
    profit_ = game_.GetBalance() - profit_;
    AnalyzeRecord(record);
}

void blackjack::Simulator::AnalyzeRecord(const std::vector<int>& record) {
    float wins = 0;
    float loses = 0;
    float total = 0;
    int max_win_streak = 0;
    int running_counter = 0;

    for (int round : record) {
        if (round == 1) {
            wins += 1;
            running_counter++;
            if (running_counter > max_win_streak) {
                max_win_streak = running_counter;
            }
        } else {
            loses += 1;
            running_counter = 0;
        }
        total += 1;
    }

    wins_ = (int)wins;
    loses_ = (int)loses;
    win_percentage_ = wins / total;
    win_streak_ = max_win_streak;
}

void blackjack::Simulator::Display() const {
    if (simulating_) {
        ci::gl::drawStringCentered("RUNNING SIMULATION...",
                                   glm::vec2(kWindowSize / 2, kWindowSize / 2),
                                   ci::Color("white"));
    } else {
        DisplayButtons(0);
        DisplayButtons(1);
        DisplayButtons(2);
        DisplayAnalysis();
        DisplayBets();
    }
}

void blackjack::Simulator::HandleClick(glm::vec2 coordinates) {
    float x = coordinates[0];
    float y = coordinates[1];

    if (x >= (kFirstLeftWall) &&
        x <= (kFirstLeftWall + kButtonWidth) &&
        y >= (kButtonTopWall) && y <= (kButtonTopWall + kButtonHeight)) {

        simulating_ = true;
        RunSimulation(kSims[0]);
        simulating_ = false;
    } else if (x >= (kMiddleLeftWall) &&
               x <= (kMiddleLeftWall + kButtonWidth) &&
               y >= (kButtonTopWall) && y <= (kButtonTopWall + kButtonHeight)) {

        simulating_ = true;
        RunSimulation(kSims[1]);
        simulating_ = false;
    } else if (x >= (kLastLeftWall) &&
               x <= (kLastLeftWall + kButtonWidth) &&
               y >= (kButtonTopWall) && y <= (kButtonTopWall + kButtonHeight)) {

        simulating_ = true;
        RunSimulation(kSims[2]);
        simulating_ = false;
    }
}

void blackjack::Simulator::DisplayAnalysis() const {
    ci::gl::color(ci::Color("white"));
    ci::gl::drawStrokedRoundedRect(ci::Rectf(glm::vec2(kBoxLeftWall, kBoxTopWall),
                                             glm::vec2(kBoxLeftWall + kBoxWidth, kBoxTopWall + kBoxHeight)),
                                   kRounding);
    ci::gl::drawStringCentered("Simulation Analysis",
                               glm::vec2(kWindowSize / 2, kBoxTopWall - (kTextSpacing / 2)),
                               ci::Color("white"));
    ci::gl::drawStringCentered("Rounds: " + std::to_string(rounds_),
                               glm::vec2(kWindowSize / 2, kBoxTopWall + kTextSpacing),
                               ci::Color("white"));
    ci::gl::drawStringCentered("AI Wins: " + std::to_string(wins_),
                               glm::vec2(kWindowSize / 2, kBoxTopWall + (kTextSpacing * 2)),
                               ci::Color("white"));
    ci::gl::drawStringCentered("AI Loses: " + std::to_string(loses_),
                               glm::vec2(kWindowSize / 2, kBoxTopWall + (kTextSpacing * 3)),
                               ci::Color("white"));
    ci::gl::drawStringCentered("Win Percentage: " + 
                                    std::to_string(win_percentage_ * 100).substr(0,
                                 std::to_string(win_percentage_ * 100).find('.') + 3) + "%",
                               glm::vec2(kWindowSize / 2, kBoxTopWall + (kTextSpacing * 4)),
                               ci::Color("white"));
    ci::gl::drawStringCentered("Longest Win Streak: " + std::to_string(win_streak_),
                               glm::vec2(kWindowSize / 2, kBoxTopWall + (kTextSpacing * 5)),
                               ci::Color("white"));
    ci::gl::drawStringCentered("Betting Profit: $" +
                                    std::to_string(profit_).substr(0,std::to_string(profit_).find('.') + 3),
                               glm::vec2(kWindowSize / 2, kBoxTopWall + (kTextSpacing * 6)),
                               ci::Color("white"));
}

void blackjack::Simulator::DisplayButtons(int button) const {
    std::string content;
    float left_wall;
    if (button == 0) {
        content = "1,000 ROUNDS";
        left_wall = kFirstLeftWall;
    } else if (button == 1) {
        content = "10,000 ROUNDS";
        left_wall = kMiddleLeftWall;
    } else {
        content = "100,000 ROUNDS";
        left_wall = kLastLeftWall;
    }

    ci::gl::color(ci::Color("lightgrey"));
    ci::gl::drawSolidRoundedRect(ci::Rectf(glm::vec2(left_wall, kButtonTopWall),
                                           glm::vec2(left_wall + kButtonWidth, kButtonTopWall + kButtonHeight)),
                                 kRounding);
    ci::gl::color(ci::Color("black"));
    ci::gl::drawStrokedRoundedRect(ci::Rectf(glm::vec2(left_wall, kButtonTopWall),
                                             glm::vec2(left_wall + kButtonWidth, kButtonTopWall + kButtonHeight)),
                                   kRounding);
    ci::gl::drawStringCentered(content,
                               glm::vec2(left_wall + (kButtonWidth / 2), kButtonTopWall + (kButtonHeight / 2)),
                               ci::Color("black"));
}

void blackjack::Simulator::DisplayBets() const {
    ci::gl::drawString(kBalance,
                               glm::vec2(kTextSpacing / 3, (kTextSpacing / 2)),
                               ci::Color("white"));
    ci::gl::drawString(kBet,
                               glm::vec2(kTextSpacing / 3, 2 * (kTextSpacing / 2)),
                               ci::Color("white"));
    ci::gl::drawString(kPayout,
                               glm::vec2(kTextSpacing / 3, 3 * (kTextSpacing / 2)),
                               ci::Color("white"));
}

void blackjack::Simulator::UpdatePredictor() {
    predictor_ = Predictor(game_.GetDeck(), game_.GetPlayerHand(),
                           game_.GetDealerHandValue(), game_.GetPlayerHandValue());
}
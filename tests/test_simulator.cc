#include <catch2/catch.hpp>
#include <simulator.h>


TEST_CASE("Run Simulation") {
    blackjack::Simulator simulator;
    simulator.RunSimulation(10);

    SECTION("Number of rounds") {
        REQUIRE(simulator.GetRecord().size() == 10);
    }
    SECTION("Record cleared") {
        simulator.RunSimulation(10);
        simulator.RunSimulation(10);
        REQUIRE(simulator.GetRecord().size() == 10);
    }
}

TEST_CASE("Analyze Record") {
    blackjack::Simulator simulator;
    simulator.AnalyzeRecord({1,1,1,1,0,0,1,0,0,0,1,1,1,0,1,0});

    SECTION("Wins") {
        REQUIRE(simulator.GetWins() == 9);
    }
    SECTION("Win streak") {
        REQUIRE(simulator.GetWinStreak() == 4);
    }
    SECTION("Win Percentage") {
        REQUIRE(simulator.GetWinPercentage() == 0.5625);
    }
    SECTION("Profit") {
        REQUIRE(simulator.GetProfit() == 100);
    }
}




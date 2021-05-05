#include <catch2/catch.hpp>
#include "game.h"

using blackjack::Game;

TEST_CASE("Constructor and new round") {
    Game game = Game();
    std::vector<blackjack::Card> dealer = game.GetDealerHand();
    std::vector<blackjack::Card> player = game.GetPlayerHand();
    
    SECTION("Dealer hand") {
        REQUIRE(dealer.size() == 2);
        REQUIRE((dealer[0].IsFaceUp() == true && dealer[1].IsFaceUp() == false));
    }
    SECTION("Player hand") {
        REQUIRE(player.size() == 2);
        REQUIRE((player[0].IsFaceUp() == true && player[1].IsFaceUp() == true));
    }
    SECTION("Hand values updated") {
        REQUIRE((game.GetDealerHandValue() != 0 && game.GetDealerHandValue() != 0));
    }
}

TEST_CASE("Calculate/Update hand values") {
    Game game = Game();

    SECTION("Sum is correct (player hand)") {
        std::vector<blackjack::Card> dealer = game.GetDealerHand();
        int expected = dealer[0].GetValue();
        REQUIRE(expected == game.GetDealerHandValue());
    }
    SECTION("Doesn't count face-down cards (dealer hand)") {
        std::vector<blackjack::Card> player = game.GetPlayerHand();
        int expected = player[0].GetValue() + player[1].GetValue();
        REQUIRE(expected == game.GetPlayerHandValue());
    }
}

TEST_CASE("Player hit") {
    Game game = Game();

    SECTION("Player gets another card") {
        game.PlayerHit();
        REQUIRE(game.GetPlayerHand().size() == 3);
    }
    SECTION("Player hand value updated") {
        int before = game.GetPlayerHandValue();
        game.PlayerHit();
        int after = game.GetPlayerHandValue();
        REQUIRE(before < after);
    }
}

TEST_CASE("Dealer play (player stand)") {
    Game game = Game();

    SECTION("Dealer gets another card") {
        game.DealerPlay();
        REQUIRE(game.GetPlayerHand().size() >= 2);
    }
    SECTION("Dealer hand value updated") {
        int before = game.GetDealerHandValue();
        game.DealerPlay();
        int after = game.GetDealerHandValue();
        REQUIRE(before < after);
    }
    SECTION("Play until win/lose") {
        game.DealerPlay();
        REQUIRE(game.IsRoundOver() == true);
    }
}
